#ifndef SQL_H
#define SQL_H

#include "../parser/parser.h"
#include "../token/tokenizer/ftokenize.h"


class SQL
{
    public:

        //Batch Mode
        SQL(string txt_file);

        

        SQL(){};

        ~SQL(){};

        /// @brief returns a table based on the command
        /// @param command 
        /// @return 
        Table command(string command);

        /// @brief returns a vector of record numbers
        /// @return 
        vectorlong select_recnos() const {return recnos;}

    
    
    private:

        //file tokenize
        void file_tokenize(string txt_file);

        Table run_command(mmap_ss& parse_map);
    
        vectorlong recnos;

        string txt_file_name = "";
    
};



#endif // SQL_H