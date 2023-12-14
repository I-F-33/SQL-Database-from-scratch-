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
            MMap<string, long>::Iterator it = querymap.begin();
            MMap<string, long>::Iterator end = querymap.upper_bound(static_cast<TokenStr *>(right)->get_value());

            for(; it != end; it++)
            {
                MPair<string, long> p = *it;

                if(p.key == static_cast<TokenStr *>(right)->get_value())
                    break;

                for(long rec : p.value_list)
                {
                    recnos.push_back(rec);
                }
            }

        }
        else if(_relation == ">")
        {

            //bounds
            MMap<string, long>::Iterator it = querymap.upper_bound(static_cast<TokenStr *>(right)->get_value());
            MMap<string, long>::Iterator end = querymap.end();

            for(; it != end; it++)
            {
                MPair<string, long> p = *it;

                for(long rec : p.value_list)
                {
                    recnos.push_back(rec);
                }
            }

          //  MMap<string,long>::Iterator it = querymap.find(static_cast<TokenStr *>(right)->get_value());
        }
        else if(_relation == "<=")
        {
            //bounds
            MMap<string, long>::Iterator it = querymap.begin();
            MMap<string, long>::Iterator end = querymap.lower_bound(static_cast<TokenStr *>(right)->get_value());

            for(; it != end; it++)
            {
                MPair<string, long> p = *it;

                if(p.key == static_cast<TokenStr *>(right)->get_value())
                    break;

                for(long rec : p.value_list)
                {
                    recnos.push_back(rec);
                }
            }

            
        }
        else if(_relation == ">=")
        {
            //just add them and start from after them
            recnos = querymap.get(static_cast<TokenStr *>(right)->get_value());

            //bounds
            MMap<string, long>::Iterator it = querymap.upper_bound(static_cast<TokenStr *>(right)->get_value());
            MMap<string, long>::Iterator end = querymap.end();

            for(; it != end; it++)
            {
                MPair<string, long> p = *it;

                for(long rec : p.value_list)
                {
                    recnos.push_back(rec);
                }
            }
        }

        sort(recnos.begin(), recnos.end());

        return new ResultSet(recnos);
}