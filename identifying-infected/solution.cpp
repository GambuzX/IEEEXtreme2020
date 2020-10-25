#include <iostream> 
#include <list> 
#include <vector>
#include <unordered_map>
#include <chrono>
using namespace std; 
 
class Graph { 
    int V; // No. of vertices in graph 
    vector<list<int>> adj; // Pointer to an array containing adjacency lists 
  
    // A recursive function used by getAllPaths() 
    void getAllPathsUtil(int, int, bool[], int[], int&); 

    void resetPaths();

    unordered_map<int, size_t> paths;
    size_t numPaths;
  
public: 
    Graph(int V); // Constructor 
    void addEdge(int u, int v); 
    void getAllPaths(int s, int d); 
    unordered_map<int, size_t> getPaths() const {return paths;}
    size_t getNumPaths() const {return numPaths;}
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = vector<list<int>>(V, list<int>()); 
    numPaths = 0;
    for(int i = 0; i < V; i++){
        paths.insert(make_pair(i, 0));
    }
} 
  
void Graph::addEdge(int u, int v) 
{ 
    adj[u].push_back(v); // Add v to u’s list. 
} 
  
void Graph::resetPaths(){
    numPaths = 0;
    for(auto it = paths.begin(); it != paths.end(); it++)
    {
        (*it).second = 0;
    }
}

// gets all paths from 's' to 'd' 
void Graph::getAllPaths(int s, int d) 
{ 
    resetPaths();
    
    // Mark all the vertices as not visited 
    bool* visited = new bool[V]; 
  
    // Create an array to store paths 
    int* path = new int[V]; 
    int path_index = 0; // Initialize path[] as empty 
  
    // Initialize all vertices as not visited 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Call the recursive helper function to get all paths 
    getAllPathsUtil(s, d, visited, path, path_index); 
    
    delete path;
    delete visited;
} 
  
void Graph::getAllPathsUtil(int u, int d, bool visited[], 
                              int path[], int& path_index) 
{ 
    // Mark the current node and store it in path[] 
    visited[u] = true; 
    path[path_index] = u; 
    path_index++; 
  
    if (u == d) { 
        this->numPaths++;
        for (int i = 0; i < path_index; i++) 
            (*this->paths.find(path[i])).second++; 
    } 
    else // If current vertex is not destination 
    { 
        for (list<int>::iterator i = adj[u].begin(); i != adj[u].end(); ++i) 
            if (!visited[*i]) 
                getAllPathsUtil(*i, d, visited, path, path_index); 
    } 
  
    // Remove current vertex from path[] and mark it as unvisited 
    path_index--; 
    visited[u] = false; 
} 
  
// Driver program 
int main() 
{ 
    int n, m, x, y;
    cin >> n >> m;
    
    // Create a graph given in the above diagram 
    Graph g(n); 
    for(int i = 0; i < m; i++){
        cin >> x >> y;
        g.addEdge(x-1, y-1);
        g.addEdge(y-1, x-1);
    }
  
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        cin >> x >> y;


        g.getAllPaths(x-1, y-1); 

        size_t num = 0;
        if(g.getNumPaths() != 0){
            unordered_map<int, size_t> paths = g.getPaths();
            for(auto it = paths.begin(); it != paths.end(); it++){
                if((*it).second == g.getNumPaths()) num++;
            }
        }

        cout << num << endl;
    } 
  
    return 0; 
} 