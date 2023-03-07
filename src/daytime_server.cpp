//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp> # library for I/O operations

using boost::asio::ip::tcp; # create an alias for the tcp protocol 

std::string make_daytime_string() # This function creates a string that represent the live data and time.
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

int main()
{
  try
  {
    boost::asio::io_context io_context; # creating an io_context (I/O functionality)

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    while (true)
    {
      tcp::socket socket(io_context);
      acceptor.accept(socket); # accepting connections from clients and creating new tcp,socet objects, each time there is a connection

      std::string message = make_daytime_string(); # create message (containing data and time) and send it back to the client

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }
  # Here the program look for the problems that may occur during the exeution and prints out the message.
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
