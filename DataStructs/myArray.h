// myArray.h

#ifndef MYARRAY_H
#define MYARRAY_H


template<typename T, unsigned N>
class myArray final {


    public:
        T a[N];     // Static Array
        
        /*
        // Rule of 5 not needed
        
        myArray() = default;
        ~myArray() = default;
        myArray(const myArray&) = default;
        myArray(myArray&&) = default;
        myArray& operator=(const myArray&) = default;
        myArray& operator = (myArray&&) = default;
        */
        
        unsigned size() const {
            return N;
        }
        
        T& operator[] (unsigned idx) {
            return this-> a[idx];
        }
        
        const T& operator[] (unsigned idx) const {
            return this->a[idx];
        }
};

#endif
