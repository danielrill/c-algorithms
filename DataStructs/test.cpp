#ifndef TEST_CPP
#define TEST_CPP


#include "mySharedPtr.h"
#include "myArray.h"
#include "linked_list.h"
#include <iostream>
#include <string>



void arrayTest(){
    std::cout << "Testing Array Class ..." << '\n' << std::endl;
	myArray<int,4> a = {10,20,33,40};

	for (unsigned i = 0; i < a.size(); i++)
	{
		std::cout << i << ": " << a[i] << std::endl;
	}

	myArray<std::string, 5> b = {"This", "is", "a" , "String", "Array"};
	for (unsigned i = 0; i < b.size(); i++) {
		std::cout << i << ": " << b[i] << std::endl;
	}
	std::cout << '\n' << "terminated Succesfully" << '\n' << std::endl;
}

void sharedPtrTest() {
    std::cout << "Testing sharedPtr Class ..." << '\n' << std::endl;
    mySharedPtr<int> p {new int{123}};  // use count = 1
    
    auto q = p; // copy
    
    if (q == p) {
        std::cout << "*p = *q = *"
                       << q.get() << '('  << q.use_count() << ") = " << *q << '\n';
                       
                       
         mySharedPtr<int> r;
         if( r != q )
         {
                r = q; // use count++
                std::cout << "*p = *q = *r = *"
                               << r.get() << '(' << r.use_count() << ") = " << *r << '\n';
         }
    }   // Destructor r: use_count--
    
    auto r = std::move(q);
    if (!q)
    {
        std::cout << "q = " << q.get() << '\n';
    }
    
    if (r)
    {
        std::cout << "*p = *r = *"
                       << r.get() << '(' << r.use_count() << ") = " << *r << '\n';
    }
  	std::cout << '\n' << "terminated Succesfully" << '\n' << std::endl;
}

void linkedlistTest() {
    node<int> p;
    linked_list list();
   
    
    //list.insert(test);
    
    //node<int> *e = new node<int>();
}

#endif

int main(){


	//arrayTest();
	//sharedPtrTest();
}
