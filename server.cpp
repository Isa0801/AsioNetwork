#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <tcp_connection.h>
#include <tcp_server.h>

// MAIN =====================================
int main()
{
  try
  {
    boost::shared_ptr<boost::asio::io_context> io_context_(new boost::asio::io_context());
    tcp_server server(io_context_, 13);
    io_context_->run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

// MAIN END =====================================