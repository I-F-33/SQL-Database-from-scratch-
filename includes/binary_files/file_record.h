#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>
#include "utilities.h"
#include <vector>

using namespace std;

class FileRecord{
public:
    
    /// @brief default constructor
    FileRecord(){
        _record[0][0] = '\0';
        recno = -1;
    }

    /// @brief constructor that takes a vector of strings
    /// @param v 
    FileRecord(vector<string> v){
        for(int i = 0; i < v.size(); i++){
            strncpy(_record[i], v.at(i).c_str(), MAX);
            _record[i][v.at(i).size()] = '\0';
        }
        recno = v.size();
        _record[recno][0] = '\0';
    }
    

    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file
    vector<string> get_record() const;


    friend ostream& operator<<(ostream& outs, const FileRecord& r);
    


    static const int MAX = 100;
    char _record[MAX + 1][MAX + 1]; //NULL char
    int recno = 0;
};

#endif