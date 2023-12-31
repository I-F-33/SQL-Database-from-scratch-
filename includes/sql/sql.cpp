#include "sql.h"



Table SQL::command(const string& command)
{   
    Table t;

    //create parser object
    Parser p(command.c_str());
    
    //if the parse tree is valid, run the command
     mmap_ss parse_map = p.parse_tree();

    t = run_command(parse_map);

    return t;
    
  
}

Table SQL::run_command(const mmap_ss& parse_map)
{
    vectorstr command = parse_map["command"];

    //if the command is make
    if(command[0] == "make" || command[0] == "create")
    {
        vectorstr tablename = parse_map["table_name"];
        vectorstr column_names = parse_map["columns"];
        //create a table with the name specified
        Table result(tablename[0], column_names);

        cout << setw(80) << "Table " << tablename[0] << " successfully created" << endl;

        return result;
    }

    //then table exists
    vectorstr table_name = parse_map["table_name"];

    Table result(table_name[0]);

    Table t;

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
               t = result.select_all_condition(condition);
                   recnos = result.select_recnos();


            }
            //else select the columns specified
            else
            {
                t =  result.select(fields, condition);
                    recnos = result.select_recnos();


            }
        }
        //else if where is "false"
        else{
            //if fields is a "*" then select all columns
            if(fields[0] == "*")
            {
                t =  result.select_all();
                    recnos = result.select_recnos();


            }
            //else select the columns specified
            else
            {
                t = result.select_all_columns(fields);
                    recnos = result.select_recnos();

            }
        }
        
    }
    
    
    return t;
    
}