#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"
using namespace std;
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
  _table = NULL;
  _capacity = 0;
  _size = 0;
  totalSuccesfulProbe=0;
  int p=0;
  int oldCap=rhs.Capacity();
  Bucket* old=rhs._table;
  Resize(oldCap);
  while (p < oldCap) {
      for (int i = 0; i < 3; i++)
      {
        if(old[p].entries[i].Active) {
            Insert(old[p].entries[i].Key,old[p].entries[i].Value);
            if(old[p].entries[i].Deleted) Delete(old[p].entries[i].Key);
            //std::cout<<"reconnecting"<<old[p].entries[i].Key<<"\n";
        }
      }
      p++;
  }

// TODO: COPY CONSTRUCTOR

}

template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& rhs) {
  if(this==&rhs) return *this;
  else {
    delete []_table;
    _table = NULL;
    _capacity = 0;
    _size = 0;
    totalSuccesfulProbe=0;
    int p=0;
    int oldCap=rhs.Capacity();
    Bucket* old=rhs._table;
    Resize(oldCap);
    while (p < oldCap) {
        for (int i = 0; i < 3; i++)
        {
          if(old[p].entries[i].Active) {
              Insert(old[p].entries[i].Key,old[p].entries[i].Value);
              if(old[p].entries[i].Deleted) Delete(old[p].entries[i].Key);
              //std::cout<<"reconnecting"<<old[p].entries[i].Key<<"\n";
          }
        }
        p++;
      }
  }
// TODO: OPERATOR=

}

template <class T>
HashTable<T>::~HashTable() {
  Bucket* old=_table;
  _table=NULL;
  delete []old;


// TODO: DESTRUCTOR
}

template <class T>
void HashTable<T>::Insert(std::string key, const T& value) {
// TODO: IMPLEMENT THIS FUNCTION.
// INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
// IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
// THE ALREADY EXISTING ONE. IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
// RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    if(_capacity==0) Resize(NextCapacity(_capacity));
    Entry* p = findEntry(key);
    int pBucket=Hash(key)%_capacity,starting=pBucket;
    int  successfulProbe = 0,i=1;
    if (p) {
        p->Key = key;
        p->Value = value;
        p->Deleted = false;
        p->Active = true;
        return;
    }
    else {
        if ((double)_size / ((_capacity)*3) > 0.5) {
        //  std::cout << "new cap--" <<_capacity<< '\n';
            Resize(NextCapacity(_capacity));
            Insert(key, value);
        }
        else {
            do {
                successfulProbe++;
            //std::cout <<"size="<<_size<< "hash="<<Hash(key)%_capacity<<"pBucket="<<pBucket<<"probe="<<successfulProbe <<"total="<<totalSuccesfulProbe<< '\n';
              for (int j = 0; j < 3; j++) {
                if(!_table[pBucket].entries[j].Active){
                  _table[pBucket].entries[j].Key=key;
                  _table[pBucket].entries[j].Value=value;
                  _table[pBucket].entries[j].Active = true;
                  _table[pBucket].entries[j].Deleted = false;
                  if (!_table[pBucket].entries[j].Deleted) {
                    _size++;
                    totalSuccesfulProbe+=successfulProbe;
                  }
                  return;
                }
              }
                //std::cout << "i=" <<i<<"start"<<starting<<"square"<<i*i<< '\n';
                pBucket = (starting + (i*i))  % _capacity;
                i++;
            } while (1);
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
      //  std::cout << _size <<"--"<<a <<'\n';
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
//  std::cout << "resizing to" <<newCapacity<< '\n';
// TODO: IMPLEMENT THIS FUNCTION. AFTER THIS FUNCTION IS EXECUTED
// THE TABLE CAPACITY MUST BE EQUAL TO newCapacity AND ALL THE
// EXISTING ITEMS MUST BE REHASHED ACCORDING TO THIS NEW CAPACITY.
// WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY
    int oldCap=_capacity;
    _size=0;
    //std::cout << "resizing from" <<_capacity<<"with size"<<_size<<"to--"<<newCapacity<< '\n';
    Bucket* old = _table;
    _table = new Bucket[newCapacity];
    _capacity = newCapacity;
    int p = 0;
    while (p < oldCap) {
        for (int i = 0; i < 3; i++)
        {
          if(old[p].entries[i].Active) {
              Insert(old[p].entries[i].Key,old[p].entries[i].Value);
              //std::cout<<"reconnecting"<<old[p].entries[i].Key<<"\n";
          }
        }
        p++;
    }
    delete []old;
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
            res++;
            x++;
            for (int j = 0; j < 3; j++)
            {
                if (!_table[p].entries[j].Active&&!_table[p].entries[j].Deleted){
                  flag = true;
                  break;
                }

            }
            if (flag) break;
            p = (i + (x * x)) % _capacity;
        } while (1);
    }
    return (double)res / _capacity;
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
            if(_table[p].entries[i].Active&&!_table[p].entries[i].Deleted){
              if(_table[p].entries[i].Key==key) return _table[p].entries+i;
            }else if(!_table[p].entries[i].Active&&!_table[p].entries[i].Deleted){
              return NULL;
            }
        }
        p = (start + (k * k))%_capacity;
    } while (1);

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
          if(_table[p].entries[i].Active&&!_table[p].entries[i].Deleted){
            if(_table[p].entries[i].Key==key){
              q=k;
              return _table[p].entries+i;
            }
          } else if(!_table[p].entries[i].Active&&!_table[p].entries[i].Deleted){
            q = k;
            return NULL;
          }
        }
        p = (start + (k * k))%_capacity;
    } while (1);
}
#endif
