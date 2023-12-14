#include "resultset.h"

/// @brief This function takes the union of two resultsets
/// @param other : The other resultset to union with
/// @return  A new resultset that is the union of the two resultsets
/// @pre  The resultsets must be sorted
/// @post  A new resultset is created
ResultSet* ResultSet::or_with(ResultSet* other)
{
    vectorlong result;

    set<long> removedup;

    //set_union(recnos.begin(), recnos.end(), other->get_recnos().begin(), other->get_recnos().end(), back_inserter(result));

    for(long rec : recnos)
    {
        removedup.insert(rec);
    }

    for(long rec : other->get_recnos())
    {
        removedup.insert(rec);
    }

    for(long rec : removedup)
    {
        result.push_back(rec);
    }

    sort(result.begin(), result.end());



    return new ResultSet(result);


}

/// @brief  This function takes the intersection of two resultsets
/// @param other : The other resultset to intersect with
/// @return  A new resultset that is the intersection of the two resultsets
ResultSet* ResultSet::and_with(ResultSet* other)
{
    vectorlong result;


    for(int i = 0; i < recnos.size(); i++)
    {
        for(int j = 0; j < other->get_recnos().size(); j++)
        {
            if(recnos[i] == other->get_recnos()[j])
            {
                result.push_back(recnos[i]);
            }
        }
    }


    return new ResultSet(result);
}