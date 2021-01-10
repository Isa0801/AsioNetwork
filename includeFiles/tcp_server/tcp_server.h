#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <tcp_connection.h>

#ifndef TCP_SERVER_H
#define TCP_SERVER_H

class tcp_server
{
public:
// save ref of context and iniate acceptor, and call function which accepts connections  
  tcp_server( boost::shared_ptr<boost::asio::io_context>, uint16_t);
private:
  void start_accept();

  void handle_accept(tcp_connection::pointer,
      const boost::system::error_code&);

  boost::shared_ptr<boost::asio::io_context> io_context_;
  boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
};

#endif