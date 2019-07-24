#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using namespace std;

struct StackNode {
	long long min;
	int index;
	long long max;
	
	StackNode() : min(-100000), index(0), max(100000) {}
  	StackNode(long long min_, int index_, long long max_) : min(min_),index(index_), max(max_) {}
};

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

int max(int a, int b){
	if(a > b)
		return a;
	return b;
}

int min(int a, int b){
	if(a < b)
		return a;
	return b;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  //cout << endl << numeric_limits<int>::min() << "   " << numeric_limits<int>::max() << endl << endl;
	if(tree.size() <= 1)// empty, or one node
		return true;
	vector<StackNode> theStack;
	theStack.push_back(StackNode(numeric_limits<long long>::min() , 0, numeric_limits<long long>::max() ) ); // push back default constructor with -Inf, 0, Inf
	
	while(! theStack.empty()){
	StackNode temp = theStack.at(theStack.size()-1);
	theStack.pop_back();
	//cout << tree[temp.index].key << " < " << temp.min << "    " << tree[temp.index].key << " >= " << temp.max << endl;
	
	if( tree[temp.index].key < temp.min || tree[temp.index].key >= temp.max ) //not a BST
		return false;
	
	if( tree[temp.index].left != -1)
		theStack.push_back( StackNode(temp.min,tree[temp.index].left,tree[temp.index].key)) ;
	
	if( tree[temp.index].right != -1)
		theStack.push_back( StackNode(tree[temp.index].key,tree[temp.index].right,temp.max)) ;
	
	}
		
  return true;
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
