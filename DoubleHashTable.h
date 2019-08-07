#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  p8agrawa
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;
		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	// deallocates memory for array and array_state
    delete[] array;
    delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
    //returns count of number of elements
    
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    // returns the size of the array
	return array_size;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
    // if the count of number of elements is zero then return true for empty()
    if(count == 0){
       return true;
    }
    
    return false;
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	// Hash function 1
    int m = array_size;
    // conversion to int
    int element = static_cast<int>(obj);
    int temp;
    temp = element % m;
    if(temp < 0){
        temp = temp + m;
    }
    //returns integer value
    return temp;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	// Hash function 2
    int m = array_size;
    //conversion to int
    int element = static_cast<int>(obj);
    int temp;
    temp = (element/m) % m;
    if(temp < 0){
        temp = temp + m;
    }
    if(temp % 2 == 0){
        temp += 1;
    }
    //returns integer value
    return temp;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
   
    if(array_state[h1(obj)] == OCCUPIED && array[h1(obj)] == obj){
       // std::cout<<std::endl<<"if 1"<<std::endl;
        return true;
    }
    
    if(array_state[h1(obj)] == DELETED && array[h1(obj)] == obj){
     //   std::cout<<std::endl<<"if 2"<<std::endl;
        return false;
    }
    
    
    if (array_state[h1(obj)] == EMPTY){
    //    std::cout<<std::endl<<"if 3"<<std::endl;
        return false;
    }
    
    
    else
    {
        int initial_index = h1(obj);
        int offset = h2(obj);
        int i = 1;
        while (1)
        {
            if(i>array_size){
                return false;
            }
            // get newIndex
            int h = (initial_index + i * offset) % array_size;
            
            // if no collision occurs, store
            // the key
            if(array_state[h] == EMPTY){
                
            //    std::cout<<std::endl<<"if 4"<<std::endl;
                return false;
            }
            if(array_state[h] == DELETED && array[h] == obj){
            //    std::cout<<std::endl<<"if 5"<<std::endl;
                return false;
            }
            if (array_state[h] == OCCUPIED && array[h] == obj)
            {
           //     std::cout<<std::endl<<"if 6"<<std::endl;
                return true;
            }
            i++;
        }
    }

}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    
    if(empty()){
        throw underflow();
    }
    T bin_entry = array[n];
	return bin_entry;
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	 
    if( count == array_size){
        throw overflow();
    }
    int h; //declaring the hash function h 
    //std::cout<<h1(obj)<<std::endl;
    // if no collision occurs then insert obj
    
    if(array_state[h1(obj)] == EMPTY || array_state[h1(obj)] == DELETED){
       h = h1(obj);
        array[h] = obj;
        
        count++;
        array_state[h] = OCCUPIED;
        return;
    }
    
    
    // if collision occurs
    if (array_state[h1(obj)] == OCCUPIED)
    {
        int initial_index = h1(obj);
        int offset = h2(obj);
        int i = 1;
        while (1)
        {
        
            // get the hash function h
            int h = (initial_index + i * offset) % array_size;
            
            // if no collision occurs then insert obj
            if (array_state[h] == EMPTY || array_state[h] == DELETED)
            {
                array[h] = obj;
                count++;
                array_state[h] = OCCUPIED;
                break;
            }
            i++;
        }
    }
    return;
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	 // enter your implemetation here
  
    if(!member(obj)){
        return false;
    }
    
        int initial_index = h1(obj);
        int offset = h2(obj);
        int i = 1;
        while (1)
        {
            // get hash function h1+ih2
            int h = (initial_index + i * offset) % array_size;
            
            // if obj found, delete it
            if (array_state[h] == OCCUPIED && array[h] == obj)
            {
                array_state[h] = DELETED;
                count--;
                return true;
            }
            i++;
        }
}

template<typename T >
void DoubleHashTable<T >::clear() {
	 // enter your implemetation here
    delete[] array;
    delete[] array_state;
    array = new T[array_size];
    array_state = new state[array_size];
    count = 0;
    
    for ( int i = 0; i < array_size; ++i ) {
        array_state[i] = EMPTY;
    }
    
	 return;
}

//Print function won't be tested
template<typename T >
void DoubleHashTable<T >::print() const {
      // enter your implemetation here
    std::cout<<"index"<<" - "<<"element"<<" - "<<"state"<<std::endl;
    for(int i=0; i< array_size; i++){
        std::cout<<i<<" - "<<array[i]<<" - "<<array_state[i]<<std::endl;
    }
	return;
}

#endif
