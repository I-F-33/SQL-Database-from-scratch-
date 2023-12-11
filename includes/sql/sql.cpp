#include "sql.h"

////////////BATCH MODE////////////
SQL::SQL(string txt_file)
{
    txt_file_name = txt_file;
}

void SQL::file_tokenize(string txt_file)
{
    
}











Table SQL::command(string command)
{   
    //convert string to cstring
    char* command_cstr = new char[command.length()];
    strcpy(command_cstr, command.c_str());

    //create parser object
    Parser p(command_cstr);

    delete[] command_cstr;
    //if the parse tree is valid, run the command
   
        mmap_ss parse_map = p.parse_tree();
        return run_command(parse_map);
    
  
}

Table SQL::run_command(mmap_ss& parse_map)
{
    vectorstr command = parse_map["command"];

    //if the command is make
    if(command[0] == "make")
    {
        vectorstr tablename = parse_map["table_name"];
        vectorstr column_names = parse_map["columns"];
        //create a table with the name specified
        Table result(tablename[0], column_names);

        return result;
    }

    //then table exists
    vectorstr table_name = parse_map["table_name"];

    Table result(table_name[0]);

    //if the command is insert
    if(command[0] == "insert")
    {
        vectorstr values = parse_map["values"];

        //insert the values into the table
        result.insert_into(values);

    }
    //if the command is select
    else if(command[0] == "select")
    {
        vectorstr fields = parse_map["fields"];
        vectorstr where = parse_map["where"];
        vectorstr condition = parse_map["condition"];

        //create a table with the name specified

        //if there is a where clause
        if(where[0] == "yes")
        {
            //if fields is a "*" then select all columns
            if(fields[0] == "*")
            {
                Table t = result.select_all_condition(condition);

                recnos = t.select_recnos();

                return t;
                
            }
            //else select the columns specified
            else
            {
                Table t = result.select(fields, condition);

                recnos = t.select_recnos();

                 return t;
               
            }
        }
        //else if where is "false"
        else{
            //if fields is a "*" then select all columns
            if(fields[0] == "*")
            {
                Table t = result.select_all();

                recnos = t.select_recnos();

                return t;
               
            }
            //else select the columns specified
            else
            {
                Table t = result.select_all_columns(fields);

                recnos = t.select_recnos();

                return t;
            }
        }
        
    }

    return result;
    
}