#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool inOrderRecursion(const vector<Node>& tree, int i, vector<int>& result){
	//cout << tree[i].key << endl;
	if(i == -1)
		return true; // hit null, so return
		
	if(! inOrderRecursion(tree, tree[i].left, result))
		return false;
		
	if(result.empty()){
		result.push_back(tree[i].key);
		//cout << tree[i].key << " " ;
	}else if(result.at(result.size()-1) < tree[i].key){
		result.push_back(tree[i].key);
		//cout << tree[i].key << " " ;
	}else{return false;}
	
		
	if(! inOrderRecursion(tree, tree[i].right, result))
		return false;
	
	return true;
}


bool IsBinarySearchTree(const vector<Node>& tree) {
  // Inorder DFS transversal
  vector<int> result;
  if(tree.size() == 0) // corner case where we have an empty tree
  	return true;
  	
  
  //cout << tree[0].left << endl;
  //return true;
  return inOrderRecursion(tree, 0, result);
    
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
