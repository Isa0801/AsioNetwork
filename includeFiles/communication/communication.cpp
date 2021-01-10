#include <communication.h>
#include <tcp_connection.h>

// yes, my comments are like these for now.
// First example: oh yes, floor is made of floor.
// Second example: functions does what functions do.


    communication::communication(boost::shared_ptr<boost::asio::io_context> io_context, boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : io_context_(io_context), socket_(socket)
    {
      std::cout <<"made con" << std::endl;
    }

//=======Send============
    // start sending message
    void communication::send(){

      if (send_message_.empty()){
        ownerClass->handleSend();
      }

      socket_->async_write_some(boost::asio::buffer(send_message_),
      boost::bind(&communication::onSend, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
      );
    }

    // this function is called when message is sent (callback handler)
    // it does x
    void communication::onSend(const boost::system::error_code &ec, size_t bytes_transferred){
      if(ec) {
        std::cout << send_message_ << " OnSend Error: " << ec << std::endl;
        error = ec;
        closeConnection();
        return;
      }
      ownerClass->handleSend();
    }
//========EndSend============

//=======Recv============
    // start reveiving message
    void communication::recv(){
      //boost::asio::async_read(*socket_, boost::asio::buffer(buff), boost::bind(&communication::onRecv, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
      socket_->async_receive(boost::asio::buffer(buff), boost::bind(&communication::onRecv, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }


    // this function is called when message is sent (callback handler)
    // it does x
    void communication::onRecv(const boost::system::error_code &ec, size_t bytes_transferred){
      if(ec) {
        std::cout << send_message_ << " OnSend Error: " << ec << std::endl;
        error = ec;
        closeConnection();
        return;
      }

      ownerClass->handleRecv(std::string(buff.begin(), buff.begin() + bytes_transferred));

    }


//========EndRecv============

    // sets parrent class
    void communication::setOwner(boost::shared_ptr<tcp_connection> owner){
      ownerClass = owner;
    }

    // sets message to send
    void communication::set_SendMessage_(std::string message){
      send_message_ = message;
    }

    // close connection and remove parent class
    void communication::closeConnection(){

            try
      {
        std::cout << "closing connection: " << std::to_string(socket_->remote_endpoint().port()) << std::endl;
        socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket_->close();
        ownerClass.reset();
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }

      if(ownerClass){
        std::cout << "parent class is alive\n";
      }
      else
        std::cout << "parent class is null\n";


      
    }

    // get error code
    boost::system::error_code communication::getEc(){
      return error;
    }



