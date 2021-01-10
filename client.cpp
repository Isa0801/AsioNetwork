#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <IOFile.h>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 5)
    {
      std::cerr << "Usage: client <host> <port> <send/recv> <file>" << std::endl;
      return 1;
    }


    std::string filename = std::string(argv[4]);
    std::string ReqType = std::string(argv[3]);
    std::string ReqBuffer;

    IOFile iof(filename, ".\\clientTemp\\");

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);
    boost::system::error_code error;

    

    if (ReqType == "send"){
      ReqBuffer += "0101set1010"+ (std::string) "filename:" + filename;
    } else if (ReqType == "recv")
    {
      ReqBuffer +="0101get1010" + (std::string) "filename:" + filename;
    } else
      std::cerr << "<recv/send> request was not recognized" << std::endl;

    std::cout << "req: " << ReqBuffer;
    
    socket.write_some(boost::asio::buffer(ReqBuffer), error);

    // without sleep, we might send too fast, it might read read req message with the contents of file which we dont want
    // there is better way to do it but for now it will do
    Sleep(2);

    for (;;)
    {
      if (boost::asio::error::eof != error && !iof.getStatus()){

        boost::array<char, 1024> buf;
        
        if (ReqType == "send"){

          socket.write_some(boost::asio::buffer(iof.get()));

        } else if (ReqType == "recv"){

          size_t len = socket.read_some(boost::asio::buffer(buf), error);

          std::string message(buf.begin(), buf.begin() + len);
          iof.insert(message);

        }
        

      } else
      {
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket.close();
        break;
      }
      
      //size_t len = socket.read_some(boost::asio::buffer(buf), error);
      
      //std::cout.write(buf.data(), len) << std::endl;

      //std::string sendmsg = "client says: " + std::string(buf.begin(), buf.begin() + len);

      //socket.write_some(boost::asio::buffer(sendmsg), error);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}