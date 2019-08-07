/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  p8agrawa @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    - jtparkin (test cases)
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    - no one
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
	private:
		int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;

		// You may wish to include a number of helper functions
		// in order to abstract out some operations
    
    int helper_entry_count(){
        
    }
    


	public:
		Dynamic_range_stack( int = 10 );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;

		
		void push( int const & );
		int pop();
		void clear();


	// Friends

	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ):
entry_count( 0 ),
min_count( 0 ),
max_count( 0 ),
initial_capacity( std::max( 1, n ) ),
current_capacity( initial_capacity ),
stack_array( new int[current_capacity] ),
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] ) {
	// empty constructor
}

Dynamic_range_stack::~Dynamic_range_stack() {
	// Enter your implementation here.
   
    delete[] stack_array;
    delete[] maximum_array;
    delete[] minimum_array;

}

int Dynamic_range_stack::top() const {
	// Enter your implementation here.
    if(empty()){
        throw underflow();
    }
// entry_count keeps trck of number of elements in the stack
// position of top in the stack would be size of array minus 1
    int top = stack_array[entry_count-1];
    
	return top;
}

int Dynamic_range_stack::maximum() const {
	// Enter your implementation here.
    if(empty()){
        throw underflow();
    }
    int top_max;
// Updates top of the maximum stack according to the max_count
    top_max = maximum_array[max_count-1];
	return top_max;
}

int Dynamic_range_stack::minimum() const {
// Enter your implementation here.
    if(empty()){
        throw underflow();
    }
// Updates top of the minimum stack according to the min_count
    int top_min;
    top_min = minimum_array[min_count-1];
    return top_min;
}

int Dynamic_range_stack::size() const {
// Enter your implementation here.
// entry_count keeps trck of number of elements in the stack
	return entry_count;
}

bool Dynamic_range_stack::empty() const {
	// Enter your implementation here.
// entry_count keeps trck of number of elements in the stack
// if entry_count = 0 then the stack is empty
    if (entry_count == 0)
        return true;
	return false;
}

int Dynamic_range_stack::capacity() const {
	// Enter your implementation here.
	return current_capacity;
}



void Dynamic_range_stack::push( int const &obj ) {
	// Enter your implementation here.
    
    if (entry_count>=current_capacity){
        
        int *temp_stack;
        int *temp_max;
        int *temp_min;
        temp_stack = new int[2*current_capacity];
        temp_max = new int[2*current_capacity];
        temp_min = new int[2*current_capacity];
        
        /* Copies contents of previous stacks to temporary stacks */
        for (int i=0;i<current_capacity; i++){
            temp_stack[i] = stack_array[i];
        }
        for (int i=0;i<current_capacity; i++){
            temp_max[i] = maximum_array[i];
        }
        for (int i=0;i<current_capacity; i++){
            temp_min[i] = minimum_array[i];
        }
        /* Deletes / deallocates memory for previous stacks */
        delete[] stack_array;
        delete[] maximum_array;
        delete[] minimum_array;
        
         /* Copies contents of previous stacks to new stacks of double size */
        stack_array = temp_stack;
        maximum_array = temp_max;
        minimum_array = temp_min;
        
        
        /*Push new element*/
        stack_array[entry_count++] = obj;
        
        // If element is larger than the current maximum then push the new maximum
        if(obj>maximum()){
            maximum_array[max_count++] = obj;
        }
        // If element is smaller than the current minimum then push the new minimum
        if(obj<minimum()){
            minimum_array[min_count++] = obj;
        }
        // double the current capacity variable
        current_capacity = 2*current_capacity;
    }
    else{
        
        /*Push new element*/
        // if min, max and stack_array are empty push the first element so that all three stacks have same 1st element
        if(max_count == 0){
           maximum_array[max_count++] = obj;
        }
        if(min_count == 0){
            minimum_array[min_count++] = obj;
        }
        stack_array[entry_count++] = obj;
       
        // If element is larger than the current maximum then push the new maximum
        if(obj>maximum()){
           maximum_array[max_count++] = obj;
        }
        // If element is smaller than the current minimum then push the new minimum
        if(obj<minimum()){
           minimum_array[min_count++] = obj;
        }

    }
    
}

int Dynamic_range_stack::pop() {
	// Enter your implementation here.
    if(empty()){
        throw underflow();
    }
    
    /* sets the index of top elements to the previous element and so pops the top*/
    int min = minimum();
    int max = maximum();
    int pop_elemnt = stack_array[--entry_count];


    if(pop_elemnt == min){
        min_count--;
    }

    if(pop_elemnt == max){
        max_count--;
    }
    
    
	return pop_elemnt;
}

void Dynamic_range_stack::clear() {
	// Enter your implementation here.
p8agrawa@ecelinux.uwaterloo.ca    if(current_capacity != initial_capacity){
        // deletes all 3 existing arrays
        delete[] stack_array;
        delete[] maximum_array;
        delete[] minimum_array;
        // declare new arrays with the initial size
        stack_array = new int[initial_capacity];
        maximum_array = new int[initial_capacity];
        minimum_array = new int[initial_capacity];
        
    }
    // resets all variables
    entry_count = 0;
    max_count = 0;
    min_count = 0;
    current_capacity = initial_capacity;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {
	// Print out your stacks

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
