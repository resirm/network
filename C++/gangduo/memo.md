# Notes

## Base部分

### 1. **FileUtil.cc文件**

#### template不带尖括号[(StackOverflow link)](https://stackoverflow.com/questions/28354752/template-vs-template-without-brackets-whats-the-difference).

template <> void foo<int>(int& t); declares a ***specialization*** of the template, with potentially different body.

template void foo<int>(int& t); causes an ***explicit instantiation*** of the template, but doesn't introduce a specialization. It just forces the instantiation of the template for a specific type.

### 2. **WeakCallback.h文件**

该代码使用了模板类，使用makeWeakCallback函数生成实例对象。代码如下：
```C++
template<typename CLASS, typename... ARGS>
class WeakCallback
{
 public:

  WeakCallback(const std::weak_ptr<CLASS>& object,
               const std::function<void (CLASS*, ARGS...)>& function)
    : object_(object), function_(function)
  {
  }

  // Default dtor, copy ctor and assignment are okay

  void operator()(ARGS&&... args) const
  {
    std::shared_ptr<CLASS> ptr(object_.lock());
    if (ptr)
    {
      function_(ptr.get(), std::forward<ARGS>(args)...);
    }
```

问题发现：在测试时，发现对实例化的WeakCallback对象只能只能传右值参数。通过修改源码，增加了一个函数get()返回类内部的function对象进行测试，发现直接调用function没有出现该问题，于是推测可能是operator()函数转发出现了问题。测试代码如下：
```C++
class A{
public:
    int& get(){
        cout << "get called: " << a_ << endl; 
        return a_;
    }
    void set(int a){
        a_ = a;
    }
    static void set2(A* obj, int a){
        obj->get() = a;
    }
    void remove(A* obj, int a){
        obj->get() = a;
        cout << "remove called: " << a << endl;
        // delete obj;
    }
    static void remove2(A* obj, int a){
        obj->get() = a;
        cout << "remove2 called: " << a << endl;
        // delete obj;
    }
private:
    int a_;
};

int main(){
    {
        shared_ptr<A> sp2(new A);
        auto wc = muduo::makeWeakCallback(sp2, &A::remove);
        auto wc2 = muduo::WeakCallback<A, A*, int>(sp2, &A::remove);
        auto pp = sp2.get();
        wc(pp, 666); // 传左值参数，error!
        wc(std::move(pp), 666); // 传右值参数，fine
        wc2(pp, 778);  // error!
        auto fff = wc2.get();
        fff(sp2.get(), pp, 789); // 绕过operator()转发测试，fine

        shared_ptr<A> sp(new A, [&wc](A* a){return wc(std::move(a), 777);});       //error!
        shared_ptr<A> sp3(new A, [&sp2](A* a){return muduo::makeWeakCallback(sp2, &A::remove)(a, 787);}); // error!

        sp->set(555);
    }
}
```

正常来说，对于模板函数，参数类型为&&，可以接受任意类型参数，左值右值均可，但是这里出现了错误。

推测是因为在示例化WeakCallback类之后，由于operator()函数的参数类型是由类模板类型决定，所以在类实例化时已经确定，无法再像普通模板函数一样接受任意左值或右值参数，而是根据实例化类时的参数类型，只接受特定类型的参数。具体到该代码，就是只能接受右值参数，所以通过左值pp调用时报错，但是通过std::move(pp)调用之后编译通过。

为了验证猜想，使用如下代码测试：

```C++

template<typename T1, typename T2>
class A{
public:
    void operator()(T1&& t1, T2&& t2) const{
        cout << t1 << ", " << t2 << endl;
    }
};

int main(){
    A<int, string> a1;
    a1(2, string("aaa"));
    int i = 3;
    string s("ohhh");
    // a1(i, s);   // error!
    A<int&, string&> a2;
    a2(i, s); // fine
}
```

与猜想一致。然后尝试修改WeakCallback源码进行测试。修改如下：
```C++
template<typename CLASS, typename... ARGS>
class WeakCallback
{
 public:

  WeakCallback(const std::weak_ptr<CLASS>& object,
               const std::function<void (CLASS*, ARGS...)>& function)
    : object_(object), function_(function)
  {
  }

  // Default dtor, copy ctor and assignment are okay
  template<typename... FARGS>    //我为了试验添加的。实验代码为 callback_test.cc
  void operator()(FARGS&&... args) const
  {
    std::shared_ptr<CLASS> ptr(object_.lock());
    if (ptr)
    {
      function_(ptr.get(), std::forward<FARGS>(args)...);
    }

  }
```

将operator()函数的模板参数独立，不依赖于类模板参数，再进行测试，发现只能接受右值参数的问题已经解决。