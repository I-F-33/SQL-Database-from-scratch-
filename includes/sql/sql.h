#ifndef SQL_H
#define SQL_H
#include "../table/table.h"
#include "../parser/parser.h"
//#include "../token/tokenizer/ftokenize.h"

using namespace std;
class SQL
{
    public:

        SQL(){
            cout << "intializing SQL" << endl;
        };

        ~SQL(){};

        /// @brief returns a table based on the command
        /// @param command 
        /// @return 
        Table command(const string& command);

        /// @brief returns a vector of record numbers
        /// @return 
        vectorlong select_recnos() const {return recnos;}

    
    
    private:

        Table run_command(const mmap_ss& parse_map); 
    
        vectorlong recnos = {};

};



#endif // SQL_H