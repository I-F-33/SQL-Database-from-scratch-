#ifndef SQL_H
#define SQL_H

#include "../parser/parser.h"


class SQL
{
    public:

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

        Table run_command(mmap_ss& parse_map);
    
        vectorlong recnos;
    
};



#endif // SQL_H