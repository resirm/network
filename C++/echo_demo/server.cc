#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <asio.hpp>

// echo demo

using asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

void daytime(){
  try
  {
    asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    for (;;)
    {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      std::cout << "Accept new connection from " << socket.remote_endpoint().address().to_string() << std::endl;
      std::string message = make_daytime_string();
      

      asio::error_code ignored_error;
      asio::write(socket, asio::buffer(message), ignored_error);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void port_8998(){
  try
  {
    asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8998));

    for (;;)
    {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      std::cout << "Accept new connection from " << socket.remote_endpoint().address().to_string() << std::endl;
      std::string message = "You said: ";

      std::vector<char> buf(128);
      asio::error_code error;

      size_t len = socket.read_some(asio::buffer(buf), error);

      if (error == asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw asio::system_error(error); // Some other error.

      std::cout.write(buf.data(), len);
      asio::error_code ignored_error;
      // std::istream is()
      std::cout << message << std::endl; 
      std::string r(buf.data());
      message += r;
      std::cout << message << std::endl; 
      asio::write(socket, asio::buffer(message), ignored_error);


      
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

int main()
{
  
  // daytime();
  port_8998();
  return 0;
}