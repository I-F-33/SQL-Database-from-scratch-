  #include "utilities.h"
   #include <iostream>
    #include <fstream>
    #include <vector>

    using namespace std;
   
   
    bool open_fileW(fstream& f, const char* filename)
    {
        f.open(filename, ios::out | ios::binary);
        return f.good();
    }
  
  //open_file_RW
  //open file for reading and writing
    bool open_fileRW(fstream& f, const char* filename)
    {
        f.open(filename, ios::in | ios::out | ios::binary);
        return f.good();
    }
  
  
  //write_info
  //write data from a vector into a text_file
    void write_info(const char* filename, vector<string> v)
    {
        fstream f;
        open_fileW(f, filename);
        for (int i = 0; i < v.size(); i++)
        {
            f << v[i] << endl;
        }
        f.close();
    } 
  
  //read_info
  //read data from a file into a vector of strings
    vector<string> read_info(const char* filename)
    {
        vector<string> v;
        fstream f;
        open_fileRW(f, filename);
        string s;
        while (getline(f, s))
        {
            v.push_back(s);
        }
        f.close();
        return v;
    }
  
    bool file_exists(const char* filename)
    {
        fstream f;
        f.open(filename, ios::in | ios::binary);
        if (f.good())
        {
            f.close();
            return true;
        }
        else
        {
            f.close();
            return false;
        }
    }