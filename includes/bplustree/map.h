#ifndef MAP_H
#define MAP_H

using namespace std;
#include "../bplustree/bplustree.h"

template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V())
    {
        key = k;
        value = v;
    }

    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me)
    {
        outs << "(" << print_me.key << ", " << print_me.value << ")";
        return outs;
    }

    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key == rhs.key;
    }

     friend bool operator !=(const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key != rhs.key;
    }

    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key < rhs.key;
    }

    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key > rhs.key;
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key <= rhs.key;
    }
    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key >= rhs.key;
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return Pair<K, V>(lhs.key, lhs.value + rhs.value);
    }
};

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;

    class Iterator{
        public:
            friend class Map;

            Iterator(typename map_base::Iterator it)
            {
                _it = it;
            }

            Iterator():_it(NULL){}

            Iterator operator ++(int unused)
            {
                return ++_it;
            }
            Iterator operator ++()
            {
                return _it++;
            }

            Pair<K, V> operator *()
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

    Map():key_count(0){}

//  Iterators
    Iterator begin()
    {
        return map.begin();
    }

    Iterator end()
    {
        return map.end();
    }

//  Capacity
    int size()
    {
        return map.size();
    }

    bool empty() const
    {
        return map.empty();
    }

//  Element Access
    V& operator[](const K& key)
    {

        Pair<K, V> p(key);
        
        if(!map.contains(p))
        {
            map.insert(p);
            key_count++;
        }

        return map.get(p).value;

        
    }

    const V& operator[] (const K& key) const
    {
        Pair<K, V> p(key);
        
        return map.get(p).value;
    }

    V& at(const K& key)
    {
        Pair<K, V> p(key);

        if(!map.contains(p))
        {
            map.insert(p);
            key_count++;
        }

        return map.get(p).value;
    }

    const V& at(const K& key) const
    {
        Pair<K, V> p(key);

        return map.get(p).value;
    }


//  Modifiers
    void insert(const K& k, const V& v)
    {
        Pair<K, V> p(k, v);
        map.insert(p);
        key_count++;
    }

    void erase(const K& key)
    {
        Pair<K, V> p(key);

        if(map.contains(p))
        {
            map.remove(p);
            key_count--;
        }
       
    }
    
    void clear()
    {
        map.clear_tree();
        key_count = 0;
    }

    V get(const K& key)
    {
        Pair<K, V> p(key);
        
        return map.get(p).value;


    }

//  Operations:
    Iterator find(const K& key)
    {
        Pair<K, V> p(key);
        Iterator it = map.begin();

        while(it != map.end())
        {
            if(*it == key)
            {
                return it;
            }

            it++;
        }

        return end();
    }
    bool contains(const Pair<K, V>& target)
    {
        Pair<K, V> p(target.key, target.value);

        return map.contains(target);
    }

    int count(const K& key)
    {
        Pair<K, V> p(key);
        Iterator it;

        it = map.begin();

        int count = 0;
        while(it != map.end())
        {
            if(*it == key)
            {
                count++;
            }

            it++;
        }

        return count;
    }

    Iterator lower_bound(const K& key)
    {
        return map.lower_bound(key);
    }

    Iterator upper_bound(const K& key)
    {
        return map.upper_bound(key);
    }


    // I have not writtent hese yet, but we will need them:
    
    //    equal_range:

    bool is_valid(){return map.is_valid();}

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:
    int key_count;

    BPlusTree<Pair<K, V> > map;
};





#endif