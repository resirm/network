//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <asio.hpp>
#include <functional>
#include <thread>

void print(const asio::error_code& /*e*/,
    asio::steady_timer* t, int* count)
{
  if (*count < 5)
  {
    std::cout << *count << std::endl;
    ++(*count);

    t->expires_at(t->expiry() + asio::chrono::seconds(1));
    t->async_wait(std::bind(print,
          std::placeholders::_1, t, count));
  }
}


void prints(const asio::error_code& /*e*/)
{
  std::cout << "Hello World!" << std::endl;
}

int main()
{
  asio::io_context io;

  int count = 0;
  asio::steady_timer t(io, asio::chrono::seconds(2));
//   t.async_wait(std::bind(print,
//         std::placeholders::_1, &t, &count));
  t.async_wait(prints);

//   std::thread th([&io](){ io.run(); });
std::cout << "Final count is " << count << std::endl;
  io.run();
  

  
//   th.join();

  return 0;
}