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
    Table(const std::string& tname);

    /// @brief creates a new table with the name of fname and the fields of ftype
    /// @param fname 
    /// @param ftype 
    Table(const std::string& fname, const vectorstr& ftype);

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
    long insert_into(const vectorstr& values);

    /// @brief returns a table with all the records
    /// @return 
    Table select_all();

    Table select(const vectorstr& columns, const std::string& field, const std::string& operato, const std::string& query);

    /// @brief returns a table with the records specified by the condition and the columns specified
    /// @param columns 
    /// @param tokens 
    /// @return 
    Table select(const vectorstr& columns, Queue<Token*> tokens);

    /// @brief returns a table with the records specified by the condition and the columns specified
    /// @param columns 
    /// @param strings 
    /// @return 
    Table select(const vectorstr& columns, const vectorstr& strings);

    /// @brief returns a table with all the records,per condition, and all columns 
    /// @param condition 
    /// @return 
    Table select_all_condition(const vectorstr& condition);

    /// @brief returns a table with all the records and the columns specified
    /// @param columns 
    /// @return 
    Table select_all_columns(const vectorstr& columns);

    /// @brief tokenizes the string and returns a queue of tokens
    /// @param strings 
    /// @return 
    Queue<Token*> parse_strings(const vectorstr& strings);



        
    /// @brief print out the table  
    /// @param outs 
    /// @param t 
    /// @return outs
    friend ostream& operator << (ostream& outs, const Table& t){
        
        fstream _file;

        FileRecord fileRecord;

        outs << "Table name: " << t._table_name << ", records: " << t.totalrecnums << endl;
        
        vectorstr fnames;

        string fields_filename = t._table_name + "fields.txt";
        fstream f;
        f.open(fields_filename, ios::in);
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

            cout << setw(30) << fnames[i];
        }

        cout << endl;

        string table_file_name = t._table_name + ".bin";

        open_fileRW(_file, table_file_name.c_str());
        
        int i = 0;
        long bytes = fileRecord.read(_file, i);

        while (bytes > 0){
            
            outs << "     " << i << setw(30) << fileRecord << endl;
            vectorstr vecs = fileRecord.get_record();
            i++;
            bytes = fileRecord.read(_file, i);
        }

        _file.close();

        f.close();

        return outs;
    } 
    
    private:

        static int serial;

        Map<std::string, int> field_names = {};

        vector<MMap<std::string, long> >table  = {};
        
        std::string _table_name = "";

        int totalrecnums = 0;

        vector<long> recnums = {};

};


    #endif

      /* */