#ifndef BTREE_ARRAY_FUNCS_H
#define BTREE_ARRAY_FUNCS_H
#include <vector>
using namespace std;


template <class T>
T maximal(const T& a, const T& b)                     //return the larger of the two items
{
    return a > b ? a : b;
}

template <class T>
void swap(T& a, T& b)  //swap the two items
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
int index_of_maximal(T data[ ], int n)                 //return index of the largest item in data
{
    int index = 0;
    for(int i = 0; i < n; i++)
    {
        if(data[i] > data[index])
        {
            index = i;
        }
    }

    return index;
}

template <class T>
void insert_item(T data[ ], int i, int& n, T entry)    //insert entry at index i in data
{

    for(int j = n; j > i; j--)
    {
        data[j] = data[j - 1];
    }

    data[i] = entry;

    n++;
}

template <class T>
void ordered_insert(T data[ ], int& n, T entry)        //insert entry into the sorted array data with length n
{
    int i = 0;
    while(i < n && data[i] < entry)
    {
        i++;
    }

    insert_item(data, i, n, entry);
    
}

template <class T>
int first_ge(const T data[ ], int n, const T& entry)   //return the first element in data that is                                                      
{                                                      //not less than entry
    
    for(int i = 0; i < n; i++)
    {
        
        if(data[i] >= entry)
        {
            return i;

        }
    }

    return n;
}

template <class T>
void attach_item(T data[ ], int& n, const T& entry)    //append entry to the right of data
{
    data[n] = entry;
    n++;
}



template <class T>
void detach_item(T data[ ], int& n, T& entry)          //remove the last element in data and place it in entry
{
    entry = data[n - 1];

    data[n-1] = T();
    
    n--;
}

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry)   //delete item at index i and place it in entry
{
    entry = data[i];

    if(i < n)
    {
        for(int j = i; j+1 < n; j++)
        {
            data[j] = data[j + 1];
        }
    }
    n--;
}

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2)   //append data2 to the right of data1
{
    for(int i = 0; i < n2; i++)
    {
        data1[n1++] = data2[i];
    }

    n2 = 0;
}

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2)   //move n/2 elements from the right of data1 and move to data2
{
    int half = n1 / 2;

    for(int i = half; i < n1; i++)
    {
        data2[n2++] = data1[i];

        data1[i] = T();
    }

    n1 = half;

}

template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size)              //copy src[] into dest[]
{
    for(int i = 0; i < src_size; i++)
    {
        dest[dest_size++] = src[i];
    }

}

template <class T>
void print_array(const T data[], int n, int pos = -1)  //print array data
{
    for(int i = 0; i < n; i++)
    {
        if(i == pos)
        {
            cout << "[" << data[i] << "] ";
        }
        else
        {
            cout << data[i] << " ";
        }
    }
    cout << endl; 
}

template <class T>
bool is_gt(const T data[], int n, const T& item)       //item > all data[i]
{
    for(int i = 0; i < n; i++)
    {
        if(data[i] >= item)
        {
            return false;
        }
    }

    return true;
}

template <class T>
bool is_le(const T data[], int n, const T& item)      //item <= all data[i]
{
    for(int i = 0; i < n; i++)
    {
        if(data[i] >= item)
        {
            return false;
        }
    }

    return true;
}

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list) //print vector list
{
    for(int i = 0; i < list.size(); i++)
    {
        outs << list[i] << " ";
    }

    return outs;

}

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme) //list.push_back addme
{
    list.push_back(addme);

    return list;
}


#endif //BTREE_ARRAY_FUNCTIONS_H