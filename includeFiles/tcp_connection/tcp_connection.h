#pragma once
#include <communication.h>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <IOFile.h>


#ifndef tcp_connection_h
#define tcp_connection_h


enum ReqStatus_e{
  NONE,
  SET,
  GET
};

class tcp_connection
  : public boost::enable_shared_from_this<tcp_connection>
{
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::shared_ptr<boost::asio::io_context> io_context);

  boost::asio::ip::tcp::socket& socket();

  void start();

  void firstReq(std::string receivedMsg);
  void handleSend();
  void handleRecv(std::string receivedMsg);


  tcp_connection(boost::shared_ptr<boost::asio::io_context> io_context);
  ~tcp_connection();

private:

  void handle_write(const boost::system::error_code& ec/*error*/,
      size_t /*bytes_transferred*/);

    boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
    boost::shared_ptr<boost::asio::io_context> io_context_;
    std::string message_;
    communication communication_;
    IOFile iof;
    ReqStatus_e req = ReqStatus_e::NONE;

};

#endif