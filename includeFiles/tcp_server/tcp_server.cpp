#include <tcp_server.h>


// save ref of context and iniate acceptor, and call function which accepts connections  
  tcp_server::tcp_server( boost::shared_ptr<boost::asio::io_context> io_context, uint16_t port)
    : io_context_(io_context),
      acceptor_(new boost::asio::ip::tcp::acceptor(*io_context,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)))
  {
    start_accept();
  }

  void tcp_server::start_accept()
  {
    // create pointer for new connections
    tcp_connection::pointer new_connection =
      tcp_connection::create(io_context_);

      // accept connection and save it to new connections sockets after completion call handle accepts
    acceptor_->async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
  }

  void tcp_server::handle_accept(tcp_connection::pointer new_connection,
      const boost::system::error_code& error)
  {
    // if no errors initate the new connection
    if (!error)
    {
      new_connection->start();
    }
    // continue accepting new connections
    start_accept();
  }
