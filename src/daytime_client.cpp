//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>  // bos

using boost::asio::ip::tcp; // bost.asio a cross-platfor C++ library. 
                            // in this code asio is used to implement network communication over TCP 
int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)    // 
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;  // io_context is used to manage I/O operations in the program 
                                        // class is being created here 
    tcp::resolver resolver(io_context); // a class is created to resolve a hostname and service 
    tcp::resolver::results_type endpoints = // here we to resolve the hostname and service name to a list of endpoints
      resolver.resolve(argv[1], "daytime");

    tcp::socket socket(io_context);   // here, tcp socket connect to the endpoint,, and a class is created 
    boost::asio::connect(socket, endpoints);

    while(true)
    {
      boost::array<char, 128> buf;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf), error); // read_some() function provided by Boost.Asio 
                                                                      //is used to read data from the socket into a buffer that is created 
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.
        //system_error class provided by Boost.Asio is used to throw an exception when an error occurs.

      std::cout.write(buf.data(), len);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
