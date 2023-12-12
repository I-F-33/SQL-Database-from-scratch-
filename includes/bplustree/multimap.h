#ifndef MULTIMAP_H
#define MULTIMAP_H

#include<vector>
#include "bplustree.h"
using namespace std;

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K())
    {
        key = k;

        value_list = vector<V>();
    }

    MPair(const K& k, const V& v)
    {
        key = k;
        value_list.push_back(v);
    }

    MPair(const K& k, const vector<V>& vlist)
    {
        key = k;
        value_list = vlist;
    }
    //--------------------------------------------------------------------------------


    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        for(int i = 0; i < print_me.value_list.size(); i++)
        {
            if(i == 0)
            {
                outs  << print_me.key << ": [" << print_me.value_list[i];
            }
            else
            {
                outs << " " << print_me.value_list[i];
            }
        }
            outs << "]";
        return outs;
    }
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator !=(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key != rhs.key;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key < rhs.key;
    }

    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key <= rhs.key;
    }

    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key >= rhs.key;
    }

    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key > rhs.key;
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        vector<V> new_vector;

        new_vector.reserve( lhs.value_list.size() + rhs.value_list.size() ); // preallocate memory
        new_vector.insert( new_vector.end(), lhs.value_list.begin(), lhs.value_list.end() );
        new_vector.insert( new_vector.end(), rhs.value_list.begin(), rhs.value_list.end() );

        return MPair<K, V>(lhs.key, new_vector);
    }
};


template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;

    class Iterator{
    public:
        friend class MMap;

        Iterator(typename map_base::Iterator it)
        {
            _it = it;
        }

        Iterator()
        {
            _it = NULL;
        }

        Iterator operator ++(int unused)
        {
            return _it++;
        }
        Iterator operator ++()
        {
            return ++_it;
        }

        MPair<K, V> operator *()
        {
            return *_it;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it != rhs._it;
        }


    private:
        typename map_base::Iterator _it;
    };

    MMap(){};

//  Iterators
    Iterator begin()
    {
        return mmap.begin();
    }

    Iterator end()
    {
        return mmap.end();
    }

//  Capacity
    int size()
    {
        return mmap.size();
    }

    bool empty() const
    {
        return mmap.empty();
    }

//  Element Access
    const vector<V>& operator[](const K& key) const
    {
        return mmap.get(MPair<K, V>(key)).value_list;
    }

    vector<V>& operator[](const K& key)
    {

        MPair<K, V> p(key);

        if(!mmap.contains(p))
        {
            mmap.insert(p);
        }
        
        return mmap.get(p).value_list;
    }

    vector<V>& at(const K& key)
    {
        MPair<K, V> p(key);

        if(mmap.empty() || !mmap.contains(p))
        {
            mmap.insert(p);
        }

        return mmap.get(p).value_list;
    }

    const vector<V>& at(const K& key) const
    {
        MPair<K, V> p(key);

        return mmap.get(p).value_list;
    }

//  Modifiers
    void insert(const K& k, const V& v)
    {
        MPair<K, V> p(k, v);

        mmap.insert(p);
    }



    void erase(const K& key)
    {
        mmap.remove(MPair<K, V>(key));
    }

    void clear()
    {
        mmap.clear_tree();
    }

//  Operations:
    const bool contains(const K& key) 
    {
        MPair<K, V> p(key);

        return mmap.contains(p);
    }

    vector<V> &get(const K& key)
    {
        return mmap.get(MPair<K, V>(key)).value_list;
    }

    Iterator find(const K& key)
    {
        return mmap.find(MPair<K, V>(key));
    }

    int count(const K& key)
    {
        return mmap.count(MPair<K, V>(key));
    }
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    Iterator lower_bound(const K& key)
    {
        return mmap.lower_bound(key);
    }

    Iterator upper_bound(const K& key)
    {
        return mmap.upper_bound(key);
    }

    vector<V> equal_range(Iterator lowerb, Iterator upperb)
    {
        vector<V> v;
        
        while(lowerb != upperb)
        {
            MPair<K, V> m = *lowerb;

            if(upperb == Iterator())
            {
                 for(V element : m.value_list)
                {
                    v.push_back(element);
                }
            }
            else 
            {
                MPair<K, V> m2 = *upperb;

                if(m.key < m2.key)
                {
                    for(V element : m.value_list)
                    {
                        v.push_back(element);
                    }
                }
                else
                {
                    break;
                }

            }
            
            

            lowerb++;
        }

        return v;
    }


    bool is_valid()
    {
        return mmap.is_valid();
    }

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

    void print_lookup()
    {
        Iterator it = begin();

        for(;it != end(); it++)
        {
            MPair<K,V> mpair = *it;

            cout << right << setw(10) << mpair.key << " :   " << mpair.value_list << endl;
        }
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

#endif