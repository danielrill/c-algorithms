#include "Hashmap.h"

template<class Key,class Value> Hashmap<Key,Value>::Hashmap(){
mappedElementCount = 0;
}
template<class Key,class Value> Hashmap<Key,Value>::~Hashmap(){
printf("\nDestroying the base Hashmap object!\n");
}

template<class Key,class Value> void Hashmap<Key,Value>::test(){
printf("The size of our Key is %i and the size of our Value is
    %i\n",sizeof(Key),sizeof(Value));
}


template<class Key,class Value> int Hashmap<Key,Value>::hash(Key* k_ptr){

    unsigned int hashval = 0;



    return hashval % mappedElementCount;

}

template<class Key,class Value> std::vector<Key>* Hashmap<Key,Value>::getKeys(){

return keys;    
}

template<class Key,class Value> std::vector<Value>* Hashmap<Key,Value>::getValues(){

return values;  
}

template<class Key,class Value> int* Hashmap<Key,Value>::getSize(){
return &mappedElementCount;
}

template<class Key,class Value> void Hashmap<Key,Value>::putKVPair(Key* k, Value* v){

    int tempHash = hash(k);


    mappedElementCount++;
}



template<class Key,class Value> void Hashmap<Key,Value>::clearMap(){

}