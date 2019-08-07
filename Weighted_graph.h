#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include "Exception.h"

/*****************************************
 * UW User ID:  P8AGRAWA
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

class Weighted_graph {
	private:
		static const double INF;
		// your choice
    int num_edges;
    int mst_size;
    int num_vertices; // number of vertices
    double **graph_matrix; // adjacency matrix
    int *degree_array;
    
    void dfs(int, bool[]) const;
    int minKey(double[], bool[]) const;
    void clear();
    
	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int ) const;
		bool is_connected() const;

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};
const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph( int n_vertices ):
num_vertices(n_vertices),
num_edges( 0 ),
degree_array(new int[num_vertices]){
    // adjacency matrix
    graph_matrix = new double*[num_vertices];
    
    for (int i = 0; i < num_vertices; i++) {
        graph_matrix[i] = new double[num_vertices];
       
    }
     // initialize each val in adjacency matrix to inf
    for(int i=0; i<num_vertices; i++){
        for(int j=0; j<num_vertices; j++){
            graph_matrix[i][j] = INF;
        }
    }
  
    // intialize degree of each node to 0
    for(int j=0; j<num_vertices; j++){
        degree_array[j] = 0;
    }

}

Weighted_graph::~Weighted_graph() {
    clear();
}

void Weighted_graph::clear(){
 // deallocate memory
    for (int i = 0; i < num_vertices; i++) {
        delete[] graph_matrix[i];
    }
    delete[] graph_matrix;
    delete[] degree_array;
}




// Enter definitions for all public functions here

int Weighted_graph::degree(int n) const{
    if(n >= num_vertices || n < 0)
        throw illegal_argument();
    //return degree of vertex n
    return degree_array[n];
}

int Weighted_graph::edge_count() const{
    //keeps track of number of edges in the graph
    return num_edges;
}

// Returns the weight of the edge between the nodes
double Weighted_graph::adjacent(int m, int n) const{
    if(m<0 || n<0 || n>=num_vertices || m>=num_vertices){
        throw illegal_argument();
    }
    else if(n==m){
        return 0;
    }
    else{
        return graph_matrix[m][n];
    }
    
}

// Returns the minimum value of the key from the set of nodes that aren't in the mst
int Weighted_graph::minKey(double key[], bool in_mst []) const{
    // Initialize min value
    double min = INF;
    int min_index = -1;
    
    for (int v = 0; v < num_vertices; v++){
       // std::cout<<min<<key[v]<<std::endl;
        // checks if the node is not in mst and the value of its key is less than min
        if (in_mst[v] == false && key[v] < min){
            min = key[v];
            min_index = v;
        }
    }
    
    return min_index;
}

double Weighted_graph::minimum_spanning_tree(int r) const{
    
    if( r>=num_vertices || r<0 ){
        throw illegal_argument();
    }
    
    if(edge_count()==0){
        return 0.0;
    }
  
    
    double mst_sum = 0;
    // keeps track of key values which later helps to pick the minimum key value
    double key[num_vertices];
    // keeps track if a vertice is in the mst
    bool in_mst[num_vertices];

    // Initialize all keys as inf
    for (int i = 0; i < num_vertices; i++){
        key[i] = INF;
        in_mst[i] = false;
    }
    
    // initialize node r's key as zero so that it is picked first to be included in the mst
    key[r] = 0;
   // for (int i = 0; i < num_vertices; i++){
     //   std::cout<<key[i]<<std::endl;
    //}
    
    for (int count = 0; count < num_vertices; count++){
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, in_mst);
        //std::cout<<" index is "<< u <<":"<<key[u]<<std::endl;
        //if all vertices are included in the mst return the sum or mst size
        if( u == -1){
            return mst_sum;
        }
        mst_sum += key[u];
       //std::cout<<u<<":"<<mst_sum<<std::endl;
        // Add the picked vertex to the MST Set
        in_mst[u] = true;
        // modify the the key values of the adjacent node(which are not in the mst) of u
        for (int v = 0; v < num_vertices; v++){
            if (graph_matrix[u][v] && in_mst[v] == false && graph_matrix[u][v] < key[v]){
                key[v] = graph_matrix[u][v];
            }
        }
    }
    return mst_sum;
    
    }


// use depth first search to traverse the graph and mark nodes visited
void Weighted_graph::dfs(int v, bool visited[]) const{
    if(visited[v] == true)
        return;
    else
        visited[v] = true;
    for(int i=0; i<num_vertices; i++){
        if( graph_matrix[v][i] != INF ){
            if(visited[i] == false)
            {
                dfs(i,visited);
            }
        }
    }
}

bool Weighted_graph::is_connected() const{
    
    bool visited[num_vertices];// keep track of visited nodes
    for(int i=0; i<num_vertices; i++){
        visited[i]=false;
    }
    // use depth first search to traverse the graph and mark nodes visited
    dfs(0, visited);
    for(int i=0; i<num_vertices; i++){
        if(visited[i] == false) // dfs did not reach this node
        {
            //std::cout<<i<<std::endl;
            return false;
        }
    }
    return true;
}

void Weighted_graph::insert(int m, int n, double w){
   // ckeck for illegal arguments
    if( w<0 || w==INF ){
        throw illegal_argument();
    }
    if(n==m || m<0 || n<0 || n>=num_vertices || m>=num_vertices){
        throw illegal_argument();
    }
    //basically deleting an edge
    if( w == 0 ){
        // do something only if an edge exists between m&n
        if(graph_matrix[m][n] != INF){
        graph_matrix[m][n] = INF;
        graph_matrix[n][m] = INF;
        degree_array[m]--;
        degree_array[n]--;
        num_edges--;
        }
    }
   
  // inserting edges and update degree of the nodes and the number of edges
    else{
        graph_matrix[m][n] = w;
        graph_matrix[n][m] = w;
        degree_array[m]++;
        degree_array[n]++;
        num_edges++;
    }
    
    
}


std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	return out;
}



#endif
