#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template <class T>
class HashTable {
    struct Entry {
        std::string Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[3];
    };

    int _capacity; // INDICATES THE SIZE OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket* _table; // HASH TABLE

    // You can define private methods and variables

public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    HashTable(const HashTable<T>& rhs);
    HashTable<T>& operator=(const HashTable<T>& rhs);
    ~HashTable();

    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE.
    // IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(std::string key, const T& value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, JUST RETURN FROM THE FUNCTION
    // HINT: YOU SHOULD UPDATE ACTIVE & DELETED FIELDS OF THE DELETED ENTRY.
    void Delete(std::string key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THIS FUNCTION MUST RETURN T()
    T Get(std::string key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY
    void Resize(int newCapacity);

    // TODO: IMPLEMENT THIS FUNCTION.
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR SUCCESSFUL SEARCH
    double getAvgSuccessfulProbe();

    // TODO: IMPLEMENT THIS FUNCTION.
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR UNSUCCESSFUL SEARCH
    double getAvgUnsuccessfulProbe();

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const;
    int Size() const;
private:
    HashTable::Entry*  findEntry(std::string key)const;
    HashTable::Entry*  findEntry(std::string key,int &p)const;
    int totalSuccesfulProbe ;
};



template <class T>
HashTable<T>::HashTable() {
    _table = NULL;
    _capacity = 0;
    _size = 0;
    totalSuccesfulProbe=0;

}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& rhs) {
// TODO: COPY CONSTRUCTOR

}

template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& rhs) {
// TODO: OPERATOR=

}

template <class T>
HashTable<T>::~HashTable() {
// TODO: DESTRUCTOR
if (_table) {
  /* code */
  delete _table;
}

}

template <class T>
void HashTable<T>::Insert(std::string key, const T& value) {
// TODO: IMPLEMENT THIS FUNCTION.
// INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
// IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
// THE ALREADY EXISTING ONE. IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
// RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    std::string str=key;
    if(_capacity==0) Resize(2);

    Entry* p = findEntry(str);
    int pBucket=Hash(str)%_capacity,starting=pBucket;
    int  successfulProbe = 0,i=1;
    if (p) {
        p->Key = key;
        p->Value = value;
        p->Deleted = false;
        p->Active = true;

    }
    else {
        if ((double)_size / ((_capacity)*3) >= 0.5) {
            Resize(NextCapacity(_capacity));
            Insert(str, value);
        }
        else {
            do {
                successfulProbe++;
                if (!_table[pBucket].entries[0].Active) {
                    _table[pBucket].entries[0].Key = new std::string(str));
                    _table[pBucket].entries[0].Value = value;
                    _table[pBucket].entries[0].Active = true;
                    _table[pBucket].entries[0].Deleted = false;
                    _size++;
                    totalSuccesfulProbe += successfulProbe;
                    return;
                }
                else if (!_table[pBucket].entries[1].Active) {
                    _table[pBucket].entries[1].Key = new std::string(str);
                    _table[pBucket].entries[1].Value = value;
                    _table[pBucket].entries[1].Active = true;
                    _table[pBucket].entries[1].Deleted = false;
                    _size++;
                    totalSuccesfulProbe += successfulProbe;
                    return;
                }
                else if (!_table[pBucket].entries[2].Active) {
                    _table[pBucket].entries[2].Key = new std::string(str);
                    _table[pBucket].entries[2].Value = value;
                    _table[pBucket].entries[2].Active = true;
                    _table[pBucket].entries[2].Deleted = false;
                    _size++;
                    totalSuccesfulProbe += successfulProbe;
                    return;
                }
                else {
                    pBucket = (pBucket + (i ^ 2)) % _capacity;
                    i++;
                }
            } while (pBucket != starting);
        }
    }
}

template <class T>
void HashTable<T>::Delete(std::string key) {
// TODO: IMPLEMENT THIS FUNCTION.
// DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
// IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, JUST RETURN FROM THE FUNCTION
// HINT: YOU SHOULD UPDATE ACTIVE & DELETED FIELDS OF THE DELETED ENTRY.
    int a = 0;
    HashTable<T>::Entry* p = findEntry(key,a);
    if (p) {
        _size--;
        p->Deleted = true;
        p->Active = false;
        totalSuccesfulProbe -= a;
    }
}

template <class T>
T HashTable<T>::Get(std::string key) const {
// TODO: IMPLEMENT THIS FUNCTION. IT SHOULD RETURN THE VALUE THAT
// IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
// IF THE KEY DOES NOT EXIST, THIS FUNCTION MUST RETURN T()
    Entry* p = findEntry(key);
        if (p) return p->Value;
        else return T();
}

template <class T>
void HashTable<T>::Resize(int newCapacity) {
// TODO: IMPLEMENT THIS FUNCTION. AFTER THIS FUNCTION IS EXECUTED
// THE TABLE CAPACITY MUST BE EQUAL TO newCapacity AND ALL THE
// EXISTING ITEMS MUST BE REHASHED ACCORDING TO THIS NEW CAPACITY.
// WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY
    Bucket* old = _table;
    _table = new Bucket[newCapacity];
    int p = 0;
    while (p < _capacity) {
        for (int i = 0; i < 3; i++)
        {   if(old[p].entries[i].Active) Insert(old[p].entries[i].Key,old[p].entries[i].Value);
        }
        p++;
    }
    _capacity = NextCapacity(_capacity);
    if (old) {
      /* code */
      delete old;
    }

}


template <class T>
double HashTable<T>::getAvgSuccessfulProbe() {
// TODO: IMPLEMENT THIS FUNCTION.
// RETURNS THE AVERAGE NUMBER OF PROBES FOR SUCCESSFUL SEARCH
    return (double)(totalSuccesfulProbe) / _size;
}

template <class T>
double HashTable<T>::getAvgUnsuccessfulProbe() {
// TODO: IMPLEMENT THIS FUNCTION.
// RETURNS THE AVERAGE NUMBER OF PROBES FOR UNSUCCESSFUL SEARCH
    if(_size==0) return 0;
    int res = 0;
    for (int i = 0; i < _capacity; i++)
    {
        int p = i;
        int x = 0;
        bool flag = false;
        do
        {
            for (int j = 0; j < 3; j++)
            {
                if (!_table[p].entries[j].Active) break;
                flag = true;
            }
            if (flag) break;
            x++;
            p = (p + (x ^ 2)) % _capacity;
        } while (p!=i);
        res += x;
    }
    return (double)res / _size;
}

template <class T>
int HashTable<T>::Capacity() const {
    return _capacity;
}

template <class T>
int HashTable<T>::Size() const {
    return _size;
}

template<class T>
inline typename HashTable<T>::Entry* HashTable<T>::findEntry(std::string key) const
{
    int p = Hash(key) % _capacity;
    int start = p,k=0;
    do
    {   k++;
        for (int i = 0; i < 3; i++)
        {
            if(_table[p].entries[i].Active);
        }
        p = p + (k ^ 2);
    } while (p!=start);

    return NULL;
}

template<class T>
inline typename HashTable<T>::Entry* HashTable<T>::findEntry(std::string key, int& q) const
{
    int p = Hash(key) % _capacity;
    int start = p, k = 0;
    do
    {
        k++;
        for (int i = 0; i < 3; i++)
        {
            if (_table[p].entries[i].Active);
        }
        p = p + (k ^ 2);
    } while (p != start);
    q = k;
    return NULL;
}


#endif
