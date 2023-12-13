#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "../bplustree/multimap.h"
#include "../bplustree/map.h"
#include "../binary_files/file_record.h"
#include "../rpn/rpn.h"
#include "../shunting_yard/shunting_yard.h"

#include "typedefs.h"



using namespace std;


class Table{

    //constructors
    public: 
    Table(){};
    /// @brief opens a table with the name of tname
    /// @param tname 
    Table(std::string tname);

    /// @brief creates a new table with the name of fname and the fields of ftype
    /// @param fname 
    /// @param ftype 
    Table(std::string fname, vectorstr ftype);

    // big three

    /// @brief copy constructor
    /// @param other 
    /// @return this is the new table, this
  /*   Table operator = (const Table& other){
         fstream _file;

        open_fileRW(_file, other._table_name.c_str());
        _table_name = other._table_name;
        field_names = other.field_names;
        totalrecnums = other.totalrecnums;
        table = other.table;
        recnums = other.recnums;

        _file.close();
        return *this;
    } */

    /// @brief destructor
    ~Table();

    /// @brief copy constructor
    /// @param other table to be copied
    /// set the fields and ready to read
    Table(const Table& other);

    // member functions
    
    /// @brief returns a vector of record numbers
    /// @return vector<long> records
    vector<long> select_recnos();
    
    /// @brief inserts a record into the table
    /// @param values 
    /// @return 
    int insert_into(vectorstr values);

    /// @brief returns a table with all the records
    /// @return 
    Table select_all();

    Table select(vectorstr columns, std::string field, std::string operato, std::string query);

    /// @brief returns a table with the records specified by the condition and the columns specified
    /// @param columns 
    /// @param tokens 
    /// @return 
    Table select(vectorstr columns, Queue<Token*> tokens);

    /// @brief returns a table with the records specified by the condition and the columns specified
    /// @param columns 
    /// @param strings 
    /// @return 
    Table select(vectorstr columns, vectorstr strings);

    /// @brief returns a table with all the records,per condition, and all columns 
    /// @param condition 
    /// @return 
    Table select_all_condition(vectorstr condition);

    /// @brief returns a table with all the records and the columns specified
    /// @param columns 
    /// @return 
    Table select_all_columns(vectorstr columns);

    /// @brief tokenizes the string and returns a queue of tokens
    /// @param strings 
    /// @return 
    Queue<Token*> parse_strings(vectorstr strings);



        
    /// @brief print out the table  
    /// @param outs 
    /// @param t 
    /// @return outs
    friend ostream& operator << (ostream& outs, Table t){
        
        fstream _file;

        open_fileRW(_file, t._table_name.c_str());
        
        int i = 0;
        long bytes = t.fileRecord.read(_file, i);
        
        outs << "Table name: " << t._table_name << ", records: " << t.totalrecnums << endl;
        
        vectorstr fnames;

        string fields_filename = t._table_name + "fields.txt";
        fstream f;
        f.open(fields_filename, f.in);
        string temp;

        if(f.is_open())
        {
            while(getline(f,temp))
            {
                fnames.push_back(temp);
            }
        }

        for(int i = 0; i < fnames.size(); i++)
        {
            if(i == 0)
            {
                cout << "record";
            }

            cout << setw(20) << fnames[i];
        }

        cout << endl;

        while (bytes > 0){
            
            outs << "     " << i << setw(20) << t.fileRecord << endl;
            vectorstr vecs = t.fileRecord.get_record();
            i++;
            bytes = t.fileRecord.read(_file, i);
        }

        _file.close();

        f.close();

        return outs;
    } 
    
    private:

        static int serial;

        FileRecord fileRecord = FileRecord();

        Map<std::string, int> field_names = {};

        vector<MMap<std::string, long> >table  = {};
        
        std::string _table_name = "";

        int totalrecnums = 0;

        vector<long> recnums = {};

};


    #endif

      /* */