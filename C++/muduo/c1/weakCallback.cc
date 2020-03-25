#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <mutex>
#include <functional>
#include <cassert>

using namespace std;

class Stock
{
public:
    Stock(const string &s): key_(s){}
    string key(){
        // cout << "Stock out: "+key_ << endl;
        return key_;
    }
private:
    string key_;
};

class StockFactory: public enable_shared_from_this<StockFactory>
{
public:
    shared_ptr<Stock> get(const string &key){
        shared_ptr<Stock> pStock;
        lock_guard<mutex> lock(mutex_);
        weak_ptr<Stock> &wkStock = stocks_[key];
        pStock = wkStock.lock();
        if(!pStock){
            pStock.reset(new Stock(key), bind(&StockFactory::weakDeleteCallback, weak_ptr<StockFactory>(shared_from_this()), placeholders::_1));
            wkStock = pStock;
        }
        return pStock;
    }

private:
    static void weakDeleteCallback(const weak_ptr<StockFactory> &wkFactory, Stock *stock){
        shared_ptr<StockFactory> factory(wkFactory.lock());
        if(factory){
            cout << "Factory calls remove:" << endl;
            factory->removeStock(stock);
        }else{
            cout << "Factory already gone." << endl;
        }
        delete stock; // ??? 
    }

    void removeStock(Stock *stock){
        if(stock){
            lock_guard<mutex> lock(mutex_);
            cout << "Delete "+stock->key() << endl;
            stocks_.erase(stock->key());
        }
    }
private:
    mutable mutex mutex_;
    map<string, weak_ptr<Stock>> stocks_;

};

void testLongLifeFactory(){
    shared_ptr<StockFactory> factory(new StockFactory);
    {
        shared_ptr<Stock> stock = factory->get("NYSE:IBM");
        cout << "testLong out: stock, "+stock->key() << endl;
        shared_ptr<Stock> stock2 = factory->get("NYSE:IBM");
        cout << "testLong out: stock2, "+stock2->key() << endl;
        assert(stock == stock2);
    }
}

void testShortLifeFactory(){
    shared_ptr<Stock> stock;
    {
        shared_ptr<StockFactory> factory(new StockFactory);
        stock = factory->get("NYSE:IBM");
        cout << "testShort out: stock, "+stock->key() << endl;
        shared_ptr<Stock> stock2 = factory->get("NYSE:IBM");
        cout << "testShort out: stock2, "+stock2->key() << endl;
        assert(stock == stock2);
    }
}

int main(){
    testLongLifeFactory();
    testShortLifeFactory();
}