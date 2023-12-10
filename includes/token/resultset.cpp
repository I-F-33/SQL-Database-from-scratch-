#include "resultset.h"

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

ResultSet* ResultSet::and_with(ResultSet* other)
{
    vectorlong result;

    set_intersection(recnos.begin(), recnos.end(), other->get_recnos().begin(), other->get_recnos().end(), back_inserter(result));

    return new ResultSet(result);
}