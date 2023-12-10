#ifndef utilities_h
#define utilities_h

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

  //Open_File_r
  //open file for reading
  //return true if file exists
  //return false if file does not exist

  
  //Open_File_w
  //create a new file
  //overwrite file if it exists
    bool open_fileW(fstream& f, const char* filename);
  
  //open_file_RW
  //open file for reading and writing
    bool open_fileRW(fstream& f, const char* filename);
  
  
  //write_info
  //write data from a vector into a text_file
    void write_info(const char* filename, vector<string> v);
  
  //read_info
  //read data from a file into a vector of strings
    vector<string> read_info(const char* filename);
  
    bool file_exists(const char* filename);




#endif // utilities_h