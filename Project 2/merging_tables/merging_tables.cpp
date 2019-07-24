#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		// find parent and compress path
    int theParent = sets[table].parent;
    
    while( theParent !=  sets[theParent].parent){
      theParent = sets[theParent].parent;
    }
    // now cmpress path with real parent
    int RealParent = theParent;
    theParent = sets[table].parent;
    while( theParent !=  sets[theParent].parent){
      theParent = sets[theParent].parent;
      sets[theParent].parent = RealParent; // update parent to real parent 
      
    }

    return RealParent;
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		if (realDestination != realSource) {
			// merge two components
			// use union by rank heuristic
      if( sets[realDestination].rank > sets[realSource].rank){
        // then realDestination has greater rank so put smaller rank tree underneath
        sets[realSource].parent = realDestination;
        sets[realDestination].size += sets[realSource].size; // update size of columns

      }else{
        sets[realDestination].parent = realSource;
        sets[realSource].size += sets[realDestination].size; // update size of columns
        if(sets[realDestination].rank == sets[realSource].rank){
          sets[realSource].rank += 1;
        }
      }
      max_table_size = max( max(max_table_size, sets[realDestination].size) , sets[realSource].size);
                        // update max_table_size
		}		
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
                --destination;
                --source;
		
		tables.merge(destination, source);
	        cout << tables.max_table_size << endl;
	}

	return 0;
}
