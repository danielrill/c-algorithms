#ifndef HASHMAP_H
#define HASHMAP_H

template <class Key, class Value>
class Hashmap{
private:

int mappedElementCount;



public:
explicit Hashmap();
virtual ~Hashmap();


virtual void test();

virtual int hash(Key*);

int* getSize();

void putKVPair(Key*,Value*);

void clearMap();


//When we use these methods, we'll want a linear vector of keys and values to 
    //iterate over, so vector is good here
std::vector<Key>* getKeys();
std::vector<Value>* getValues();   
};

#endif