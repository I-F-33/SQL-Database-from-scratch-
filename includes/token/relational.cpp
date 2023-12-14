#include "relational.h"

ResultSet* Relational::eval(Map<string,int> field_names, vector<MMap<string,long>> _table, Token* left, Token* right)
{
    //get the field number
        int queryfield = field_names[static_cast<TokenStr *>(left)->get_value()];

        //get the map of the field
        MMap<std::string, long> querymap = _table[queryfield];

        vectorlong recnos;


        if(_relation == "=")
        {
            //get the record numbers
            recnos = querymap.get(static_cast<TokenStr *>(right)->get_value());
            
        }
        else if(_relation == "<")
        {
            //bounds
            recnos = querymap.equal_range(querymap.begin(), querymap.lower_bound(static_cast<TokenStr *>(right)->get_value()));


        }
        else if(_relation == ">")
        {

             recnos = querymap.equal_range(querymap.upper_bound(static_cast<TokenStr *>(right)->get_value()), querymap.end());


          //  MMap<string,long>::Iterator it = querymap.find(static_cast<TokenStr *>(right)->get_value());
        }
        else if(_relation == "<=")
        {
            recnos = querymap.equal_range(querymap.begin(), querymap.upper_bound(static_cast<TokenStr *>(right)->get_value()));

            
        }
        else if(_relation == ">=")
        {
            //just add them and start from after them
            recnos = querymap.equal_range(querymap.lower_bound(static_cast<TokenStr *>(right)->get_value()), querymap.end());

        }


        return new ResultSet(recnos);
}