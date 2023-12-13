#include "table.h"

int Table::serial = 0;

Table::Table(std::string tableName):_table_name(tableName){      


    FileRecord recordHolder;

    //open field file name
    string fields_filename = tableName + "fields.txt";
    fstream field_file(fields_filename,field_file.in);

    //open the table data

    //set the table field names to "tablename" field names
    long counter = 0;
    string buffer;

    if(field_file.good())
    {
        while(getline(field_file,buffer))
        {
            field_names.insert(buffer,counter);

            table += MMap<std::string, long>();

            counter++;
        }
    }

    

    field_file.close();

    int field_names_size = counter;
    
    fstream _file;

    open_fileRW(_file,tableName.c_str());


    //insert the records from "tablename" to this table

    //this is the record number
    counter = 0;
    vectorstr record_values;

    while( recordHolder.read(_file,counter) > 0)
    {
        record_values = recordHolder.get_record();

        for(int i = 0; i < field_names_size;i++)
        {
            table.at(i).insert(record_values[i],counter);
        }

        recnums.push_back(counter);
        counter++;
    }

    totalrecnums = counter;


    //close streams

    _file.close();
        

}

    /// @brief creates a new table with the name of fname and the fields of ftype
    /// @param fname 
    /// @param ftype 
Table::Table(std::string fname, vectorstr ftype): totalrecnums(0), _table_name(fname){

        fstream _file;

        open_fileW(_file, fname.c_str());  
        
        string fields_filename = fname+"fields.txt";
        
        fstream f(fields_filename,f.out);

        for(int i = 0; i < ftype.size(); i++)   
        {
            f << ftype[i] + "\n";

            field_names.insert(ftype[i], i);

            table += MMap<std::string, long>();

        }

        f.close();

        _file.close();
    }

    // big three


    /// @brief destructor
    Table::~Table(){

    }

    /// @brief copy constructor
    /// @param other table to be copied
    /// set the fields and ready to read
    Table::Table(const Table& other): totalrecnums(other.totalrecnums), _table_name(other._table_name), field_names(other.field_names){
        fstream _file;
        open_fileRW(_file, other._table_name.c_str());
        // _table_name = other._table_name;
        // field_names = other.field_names;
        // trecno = other.trecno;
        _file.close();
    }

    // member functions
    
    /// @brief returns a vector of record numbers
    /// @return vector<long> records
    vector<long> Table::select_recnos()            
    {
        return recnums;
    }  
    
    /// @brief create a queue of tokens to use in the select function
    /// @param strings 
    /// @return 
    Queue<Token*> Table::parse_strings(vectorstr strings)
    {
        Queue<Token*> tokens;

        for(int i = 0; i < strings.size(); i++)
        {
            if(strings[i] == "and")
            {
                tokens.push(new Logical("and"));
            }
            else if(strings[i] == "or")
            {
                tokens.push(new Logical("or"));
            }
            else if(strings[i] == "=")
            {
                tokens.push(new Relational("="));
            }
            else if(strings[i] == "<")
            {
                tokens.push(new Relational("<"));
            }
            else if(strings[i] == ">")
            {
                tokens.push(new Relational(">"));
            }
            else if(strings[i] == "<=")
            {
                tokens.push(new Relational("<="));
            }
            else if(strings[i] == ">=")
            {
                tokens.push(new Relational(">="));
            }
            else if(strings[i] == "(")
            {
                tokens.push(new LeftParen());
            }
            else if(strings[i] == ")")
            {
                tokens.push(new RightParen());
            }
            else
            {
                tokens.push(new TokenStr(strings.at(i)));
            }
        }

        return tokens;
    }

    /// @brief 
    /// @param values 
    /// @return 
    int Table::insert_into(vectorstr values){

        fstream _file;

        open_fileRW(_file, _table_name.c_str());

        //write the file record to the file - store its record number
        fileRecord = FileRecord(values);

        long recno = fileRecord.write(_file);

        //find the matching values and insert record number into the map

        for(int i = 0; i < values.size(); i++)
        {

            table[i].insert(values[i], recno);      
            

        }

        //increment record numbers
        totalrecnums++;


        _file.close();
                
        return recno;
    }

    Table Table::select_all()
    {
        //create new table with the columns

        vectorstr resultrecord;

        //get columns
        string fields_filename = _table_name+"fields.txt";

        fstream a(fields_filename, a.in);

        vectorstr field_names_vectr;

        string temp;

        if(a.is_open())
        {
            while(getline(a,temp))
            {
                field_names_vectr.push_back(temp);
            }
        }

        a.close();


        ///////////////////////////////

        Table result("table_select_" + to_string(serial++), field_names_vectr);

        fstream _file;

        open_fileRW(_file, _table_name.c_str());

        for(int i = 0; i < totalrecnums;i++)
        {
            result.recnums.push_back(i);
        }

        //iterate through the record numbers
        for(int i = 0; i < recnums.size(); i++)
        {   
            //read the record
            fileRecord.read(_file, recnums.at(i));

            //get the record values
            vectorstr record = fileRecord.get_record();

            //organize the record to the columns
            for(int j = 0; j < field_names_vectr.size(); j++)
            {
                resultrecord.push_back(record[field_names.get(field_names_vectr.at(j))]);
            }

            //insert the record into the result table
            result.insert_into(resultrecord);

            resultrecord.clear();
        }


        _file.close();

        return result;
    }

    Table Table::select(vectorstr columns, Queue<Token*> tokens)
    {
        //create new table with the columns
        Table result("table_select_" + to_string(serial++), columns);

        RPN rpn(tokens, field_names, table);

        vectorlong recnos = rpn();

        vectorstr resultrecord;

        fstream _file;

        open_fileRW(_file, _table_name.c_str());


        //iterate through the record numbers
        for(int i = 0; i < recnos.size(); i++)
        {   
            //read the record
            fileRecord.read(_file, recnos.at(i));

            //get the record values
            vectorstr record = fileRecord.get_record();

            //organize the record to the columns
            for(int j = 0; j < columns.size(); j++)
            {
                resultrecord.push_back(record[field_names.get(columns[j])]);
            }

            //insert the record into the result table
            result.insert_into(resultrecord);

            recnums.push_back(recnos.at(i));

    

            resultrecord.clear();
        }

        _file.close();

        return result;

    }

    Table Table::select(vectorstr columns, vectorstr strings)
    {
        //create new table with the columns
        Table result("table_select_" + to_string(serial++), columns);

        //build token queue
        Queue<Token*> tokens = parse_strings(strings);

        ShuntingYard sy(tokens);

        Queue<Token*> postfix = sy.postfix();

        RPN rpn(postfix, field_names, table);

        vectorlong recnos = rpn();

        vectorstr resultrecord;
        fstream _file;


        open_fileRW(_file, _table_name.c_str());

        //iterate through the record numbers
        for(int i = 0; i < recnos.size(); i++)
        {   
            //read the record
            fileRecord.read(_file, recnos.at(i));

            //get the record values
            vectorstr record = fileRecord.get_record();

            //organize the record to the columns
            for(int j = 0; j < columns.size(); j++)
            {
                resultrecord.push_back(record[field_names.get(columns.at(j))]);
            }

            //insert the record into the result table
            result.insert_into(resultrecord);

            result.recnums.push_back(recnos.at(i));

            resultrecord.clear();
        }


        _file.close();

        return result;
        

    }


    Table Table::select(vectorstr columns, std::string field, std::string operato, std::string query)
    {
        //create new table with the columns
        Table result("table_select_" + to_string(serial++), columns);

        //get the field number
        int queryfield = field_names.get(field);

        //get the map of the field
        MMap<std::string, long> querymap = table[queryfield];

        cout << querymap << endl;

        vectorlong recnos;


        if(operato == "=")
        {
            //get the record numbers
            recnos = querymap[query];
            
        }
        else if(operato == "<")
        {
            recnos = querymap.equal_range(querymap.begin(), querymap.lower_bound(query));

        }
        else if(operato == ">")
        {
            recnos = querymap.equal_range(querymap.lower_bound(query)++, querymap.end());
        }
        else if(operato == "<=")
        {
            vectorlong recnos2 = querymap.equal_range(querymap.begin(), querymap.upper_bound(query));

            for(int i = 0; i < recnos2.size(); i++)
            {
                recnos.push_back(recnos2.at(i));
            }
        }
        else if(operato == ">=")
        {
            recnos = querymap.equal_range(querymap.lower_bound(query), querymap.end());
        }

        recnums.clear();

        for(long rec : recnos)
        {
            recnums.push_back(rec);
        }

        sort(recnos.begin(), recnos.end());
        vectorstr resultrecord;

        fstream _file;


        open_fileRW(_file, _table_name.c_str());

        //iterate through the record numbers
        for(int i = 0; i < recnos.size(); i++)
        {   
            //read the record
            fileRecord.read(_file, recnos.at(i));

            //get the record values
            vectorstr record = fileRecord.get_record();

            //organize the record to the columns
            for(int j = 0; j < columns.size(); j++)
            {
                resultrecord.push_back(record[field_names.get(columns.at(j))]);
            }

            //insert the record into the result table
            result.insert_into(resultrecord);


            resultrecord.clear();
        }


        _file.close();

        return result;
    }

    Table Table::select_all_columns(vectorstr columns)
    {
        //create new table with the columns
        Table result("table_select_" + to_string(serial++), columns);

        vectorstr resultrecord;

        fstream _file;

        open_fileRW(_file, _table_name.c_str());

        for(int i = 0; i < totalrecnums;i++)
        {
            result.recnums.push_back(i);
        }


        //iterate through the record numbers
        for(int i = 0; i < recnums.size(); i++)
        {   
            //read the record
            fileRecord.read(_file, recnums.at(i));

            //get the record values
            vectorstr record = fileRecord.get_record();

            //organize the record to the columns
            for(int j = 0; j < columns.size(); j++)
            {
                resultrecord.push_back(record[field_names.get(columns[j])]);
            }

            //insert the record into the result table
            result.insert_into(resultrecord);

            resultrecord.clear();
        }


        _file.close();

        return result;
    }

    Table Table::select_all_condition(vectorstr condition)
    {
        //create new table with the columns

        vectorstr resultrecord;

        //get columns
        string fields_filename = _table_name+"fields.txt";

        fstream a(fields_filename, a.in);

        vectorstr field_names_vectr;

        string temp;

        if(a.good())
        {
            while(getline(a,temp))
            {
                field_names_vectr.push_back(temp);
            }
        }

        a.close();


        ///////////////////////////////

        Table result("table_select_" + to_string(serial++), field_names_vectr);

        //build token queue
        Queue<Token*> tokens = parse_strings(condition);

        ShuntingYard sy(tokens);

        Queue<Token*> postfix = sy.postfix();

        RPN rpn(postfix, field_names, table);

        vectorlong recnos = rpn();
        
        fstream _file;


        open_fileRW(_file, _table_name.c_str());

        //iterate through the record numbers
        for(int i = 0; i < recnos.size(); i++)
        {   
            //read the record
            fileRecord.read(_file, recnos[i]);

            //get the record values
            vectorstr record = fileRecord.get_record();

            //organize the record to the columns
            for(int j = 0; j < field_names_vectr.size(); j++)
            {
                resultrecord.push_back(record[field_names.get(field_names_vectr[j])]);
            }

            //insert the record into the result table
            result.insert_into(resultrecord);

            result.recnums.push_back(recnos[i]);

            resultrecord.clear();
        }


        _file.close();

        return result;
        

    }