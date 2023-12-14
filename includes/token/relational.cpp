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
            MMap<string,long>::Iterator begin = querymap.begin();
            MMap<string,long>::Iterator end = querymap.end();

            for(; begin != end; begin++)
            {
                MPair<string,long> m = *begin;
                if(m.key < static_cast<TokenStr *>(right)->get_value())
                {
                    for(long element : m.value_list)
                    {
                        recnos.push_back(element);
                    }
                }
            }


        }
        else if(_relation == ">")
        {

            MMap<string,long>::Iterator begin = querymap.begin();
            MMap<string,long>::Iterator end = querymap.end();

            for(; begin != end; begin++)
            {
                MPair<string,long> m = *begin;
                if(m.key > static_cast<TokenStr *>(right)->get_value())
                {
                    for(long element : m.value_list)
                    {
                        recnos.push_back(element);
                    }
                }
            }


          //  MMap<string,long>::Iterator it = querymap.find(static_cast<TokenStr *>(right)->get_value());
        }
        else if(_relation == "<=")
        {
            recnos = querymap.get(static_cast<TokenStr *>(right)->get_value());

            MMap<string,long>::Iterator begin = querymap.begin();
            MMap<string,long>::Iterator end = querymap.end();

            for(; begin != end; begin++)
            {
                MPair<string,long> m = *begin;
                if(m.key < static_cast<TokenStr *>(right)->get_value())
                {
                    for(long element : m.value_list)
                    {
                        recnos.push_back(element);
                    }
                }
            }

            
        }
        else if(_relation == ">=")
        {
            recnos = querymap.get(static_cast<TokenStr *>(right)->get_value());

            MMap<string,long>::Iterator begin = querymap.begin();
            MMap<string,long>::Iterator end = querymap.end();

            for(; begin != end; begin++)
            {
                MPair<string,long> m = *begin;
                if(m.key > static_cast<TokenStr *>(right)->get_value())
                {
                    for(long element : m.value_list)
                    {
                        recnos.push_back(element);
                    }
                }
            }
        }


        return new ResultSet(recnos);
}