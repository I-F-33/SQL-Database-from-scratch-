#include "resultset.h"

/// @brief This function takes the union of two resultsets
/// @param other : The other resultset to union with
/// @return  A new resultset that is the union of the two resultsets
/// @pre  The resultsets must be sorted
/// @post  A new resultset is created
ResultSet* ResultSet::or_with(ResultSet* other)
{
    vectorlong result = {};

    vectorlong recnos = get_recnos();
    vectorlong other_recnos = other->get_recnos();

    sort(recnos.begin(), recnos.end());
    sort(other_recnos.begin(), other_recnos.end());

    set_union(recnos.begin(), recnos.end(), other_recnos.begin(), other_recnos.end(), back_inserter(result));

    return new ResultSet(result);


}

/// @brief  This function takes the intersection of two resultsets
/// @param other : The other resultset to intersect with
/// @return  A new resultset that is the intersection of the two resultsets
ResultSet* ResultSet::and_with(ResultSet* other)
{
    vectorlong result = {};

    vectorlong recnos = get_recnos();
    vectorlong other_recnos = other->get_recnos();

    sort(recnos.begin(), recnos.end());
    sort(other_recnos.begin(), other_recnos.end());

    set_intersection(recnos.begin(), recnos.end(), other_recnos.begin(), other_recnos.end(), back_inserter(result));
    return new ResultSet(result);
}