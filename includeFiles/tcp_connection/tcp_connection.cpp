#include <tcp_connection.h>
#include <boost/filesystem.hpp>
#include <IOFile.h>


ReqStatus_e findMethod(std::string msg){

  if(msg.find("0101get1010") != std::string::npos)
    return ReqStatus_e::GET;

  if(msg.find("0101set1010") != std::string::npos)
    return ReqStatus_e::SET;

  return ReqStatus_e::NONE;
  
}


 tcp_connection::pointer tcp_connection::create(boost::shared_ptr<boost::asio::io_context> io_context)
  {
    return tcp_connection::pointer(new tcp_connection(io_context));
  }

  boost::asio::ip::tcp::socket& tcp_connection::socket()
  {
    return *socket_;
  }

  void tcp_connection::start()
  {
    communication_.setOwner(shared_from_this());
    communication_.recv();
  }

  void tcp_connection::handleSend(){

    if(req == ReqStatus_e::GET){

      if(iof.getStatus()){
        // the reason why, we are using delay in async is because that, when we close connection and remove owner wont cause error
        // otherwise it will cause assertation error due to this class still is running in some sense.
        // we want to close connection after the handleSend methode ran, otherwise we would get error when restting owner for the communtion.
        // we could have used while loop in close connection that checks for boolean true (tcp_connection status some kind) to ran function .reset() method
        boost::asio::steady_timer delay(*io_context_, boost::asio::chrono::seconds(5));
        delay.async_wait(boost::bind(&communication::closeConnection, communication_));
        }
      else{
        communication_.set_SendMessage_(iof.get());
        
        communication_.send();
      }
    }

  }

  void tcp_connection::firstReq(std::string reqs){
    req = findMethod(reqs);

    int temp = reqs.find("filename:");
    
    if(temp != std::string::npos){
      std::string filename = reqs.substr(temp+9, reqs.size());
      iof = IOFile(filename, ".\\serverTemp\\");
      std::cout << "filename is: " << filename << std::endl;
    }

    if (req == ReqStatus_e::GET)
      handleSend();
    else if (req == ReqStatus_e::SET)
      communication_.recv();
    else {
      communication_.set_SendMessage_("0101NOREQ1010");
      communication_.send();
    }



  }

  void tcp_connection::handleRecv(std::string receivedMsg){

    if (req == ReqStatus_e::NONE){
      firstReq(receivedMsg);
      return;
    } else if(req == ReqStatus_e::SET){
      iof.insert(receivedMsg);
      communication_.recv();
    }
    // std::string t = temp.get();
    // std::cout << "file outputs: " << t << std::endl;
    // std::cout << "i got this msg: "  << receivedMsg << std::endl;
    // communication_.set_SendMessage_(t);
    // Sleep(5);
    // communication_.send();
    // communication_.recv();
    
  }

  tcp_connection::tcp_connection(boost::shared_ptr<boost::asio::io_context> io_context)
    : io_context_(io_context), socket_(new boost::asio::ip::tcp::socket(*io_context)), communication_(io_context_, socket_), iof("", ".\\serverTemp\\")
  {
    
    std::cout << "construction of the tcp connection" << std::endl;
  }

  tcp_connection::~tcp_connection(){
    iof.close();
    std::cout << "Deconstruction of the tcp connection" << std::endl;
  }