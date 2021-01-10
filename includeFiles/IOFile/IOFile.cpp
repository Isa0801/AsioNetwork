#include <IOFile.h>
#include <iostream>



IOFile::IOFile(std::string fileName, std::string pathFile)
{
  if (fileName == ""){
    std::cout << "File name is not givien, giving it temp.txt name";
    fileName = "temp.txt";
  }
  
  if (fileName[0] != '.' && fileName[1] != '.'){
    
    this->status = 0;
    

    std::cout << "current path " << boost::filesystem::current_path() << std::endl;

    boost::filesystem::path p(pathFile+fileName);

    if (boost::filesystem::exists(p))
    {
      std::cout << pathFile << fileName <<" exists" << std::endl;
      fopen_s(&file, (pathFile+fileName).c_str(), "rb+");
    } else
    {
      std::cout << pathFile << fileName <<" does not exists" << std::endl;
      fopen_s(&file, (pathFile+fileName).c_str(), "wb+");
    }

    fileN = fileName;

  }

};

void IOFile::close(){
  fclose(file);
};


void IOFile::insert(std::string input){
  
  fwrite(input.c_str(), 1, input.length(), file);

}

std::string IOFile::get(){
  
  if (this->status == 0)
  {
    char temp[1000];

    int read = fread(temp, 1, sizeof(temp), file);

    if (read == 0){
      this->status = 1;
      this->close();
      }
    return std::string(temp, read);
  }

  return fileN;
}


bool IOFile::getStatus(){
  return status;
}
