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
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;


	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;

		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
	// empty constructor
}

Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}

bool Trie_node::member( std::string const &str, int depth ) const {
    
    int i;
    i = tolower(str[depth]) - 'a'; // makes the character uppercase
  
    // if the end of the string is reched return the value of is_terminal
    if(str.length() == depth) {
        return is_terminal;
    }
    //children are null or the child i is null then return false
    if(children == nullptr || children[i] == nullptr){
        return false;
    }
    //recurse the Trie by incrementing depth
    depth++;
	return children[i]->member(str, depth);
}

bool Trie_node::insert( std::string const &str, int depth ) {
   
    int i;
    i = tolower(str[depth]) - 'a'; // makes the character uppercase
    // checks if at the end of the string
    if(depth == str.length()) {
      // if the string already exists return false
        if(is_terminal){
            return false;
        }
     // else return true i.e. string inserted
        else{
            is_terminal = true;
            return is_terminal;
        }
        
    }
   // if no children then initialize children
    if(children == nullptr){
        children = new Trie_node * [CHARACTERS];
        int j=0;
        while(j<CHARACTERS){
            children[j] = nullptr;
            j++;
        }
    }
   // if child[i] is null then new node
    if (children[i] == nullptr){
        children[i] = new Trie_node;
    }
	  //recurse the Trie by incrementing depth
    depth++;
    return children[i]->insert(str, depth);

}

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {

    int i = tolower(str[depth]) - 'a';
    // stores the result to recusion
    // initialize first to false
    bool result_erase = false;
   
    // base case
    // if we reach the end of the string
    if (depth == str.length()){
        //if the node has children then check if child i is not null
        if (this -> children){
            int j = 0;
            while(j < CHARACTERS){
                //if child i is null then set is_terminal to false
                if(this->children[j] != nullptr){
                    is_terminal = false;
                    return true;
                }
                j++;
            }
            
        }
        // delete children and point ptr_to_this to nullptr
        delete[] this -> children;
        delete this;
        ptr_to_this = nullptr;
        return true;
    }
    
    else {
        // until we reach the end of the string we recurse into the tree
        depth++;
        result_erase = children[i] -> erase(str,depth,children[i]);
    }
    // if result_erase is true
    if (result_erase){
        
        if(is_terminal){
            return true;
        }
        // if is_terminal was set to false previously
        
        int i = 0;
        while(i < CHARACTERS){
            if(this->children[i] != nullptr){
                return true;
            }
            i++;
        }
        delete[] this -> children;
        delete this;
        ptr_to_this = nullptr;
        
        return true;
    }
   // if result_erase remains false then return false
    else {
        return false;
    }
}

void Trie_node::clear() {
    //if children are not null then delete the children and their chidren and make children point to null after deleting
    if (children != nullptr){
        int i = 0;
        while(i < CHARACTERS){
            if(children[i] != nullptr){
                //recursively clear the children of children and so on
                children[i]->clear();
                delete children[i];
                children[i]=nullptr;
            }
            i++;
        }
    }

    delete [] children;
    children = nullptr;
    
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
