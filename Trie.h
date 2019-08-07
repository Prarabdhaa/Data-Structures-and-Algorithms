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
 * Calender Term of Submission:  (Winter) 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {
    clear();
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
    if (trie_size != 0)
        return false;
    else
        return true;
    
}

Trie_node *Trie::root() const {
	return root_node;
}

bool Trie::member( std::string const &str ) const {
   // check for characters that are not alphabets and throw illegal_arguments error
    int len = str.length();
    int i =0;
    while(i<len) {
        if(!isalpha(str[i])){
            throw illegal_argument();
        }
        i++;
    }
    // if the trie is empty return false
    if(empty()) {
        return false;
    }
    
    //call member function of Trie_node
    else
    {
        return (root_node->member(str,0));
    }

    
}

bool Trie::insert( std::string const &str ) {
    // check for characters that are not alphabets and throw illegal_arguments error
    int len = str.length();
    
    int i =0;
    while(i<len){
        if(!isalpha(str[i])){
            throw illegal_argument();
        }
        i++;
    }
    // if the string already exists then return falses
    if(member(str)){
        return false;
    }
    //the root is null initialize new node as root
    if (root_node == nullptr)
    {
        root_node = new Trie_node;
    }
    
    //call the insert function of Trie_node
    bool ret_val = root_node->insert(str,0);
    
    // when ret_val is true; new string is inserted so incremet trie size by 1
    if(ret_val){
      trie_size++;
    }
    
	return ret_val;
}

bool Trie::erase( std::string const &str ) {
   // check for characters that are not alphabets and throw illegal_arguments error
    int len = str.length();
    
    int i =0;
    while(i<len) {
        if(isalpha(str[i]) == 0){
            throw illegal_argument();
        }
        i++;
    }
    // if the Trie is empty or the string is not in the Trie then return false
    if(empty() || !member(str)) {
        return false;
    }
    // if the root is null then return false
    if(root_node == nullptr){
        return false;
    }
    // call the erace function of Trie_node and decrement tree size if it returns true
    int ret_val = root_node->erase(str, 0, root_node);
    
    if(ret_val){
        trie_size--;
    }
    
    if(empty()){
        delete root_node;
        root_node = nullptr;
    }
    
    return ret_val;
    }
    


void Trie::clear() {
    // if the trie is already not empty call the Trie_node function clear and then delete the root node
    // and point it to null
    // lastly decrement Trie size
    if(!empty()){
        root_node->clear();
        delete root_node;
        trie_size=0;
    }
    root_node = nullptr;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
