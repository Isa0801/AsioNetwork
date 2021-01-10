#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>


#ifndef IOFILE_H

#define IOFILE_H

class IOFile
{
private:
    // status == 1 will act as done and 0 will acts in process  
    bool status;
    FILE *file;
    std::string fileN;
public:
    IOFile(std::string, std::string);
    

    void insert(std::string);
    std::string get();

    bool getStatus();
    void close();
};

#endif
