#pragma once
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/array.hpp>

#ifndef communication_h
#define communication_h

class tcp_connection;

class communication{
  public:
    void send();

    void recv();

    communication(boost::shared_ptr<boost::asio::io_context> io_context, boost::shared_ptr<boost::asio::ip::tcp::socket> socket);

    void setOwner(boost::shared_ptr<tcp_connection> owner);

    void set_SendMessage_(std::string message);

    void closeConnection();

    boost::system::error_code getEc();

  private:

    void onSend(const boost::system::error_code &ec, size_t bytes_transferred);
    void onRecv(const boost::system::error_code &ec, size_t bytes_transferred);

    boost::array<char, 1024> buff;
    boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
    boost::shared_ptr<boost::asio::io_context> io_context_;
    std::string send_message_;
    boost::system::error_code error;
    boost::shared_ptr<tcp_connection> ownerClass;
};

#endif