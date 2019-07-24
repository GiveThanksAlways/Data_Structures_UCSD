#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  int troot = 0;
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
    if (parent_index == -1)
      troot = child_index;
  }
  //cout << endl << "root: " << troot << endl << endl;
 
  /**int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  }
    
  std::cout << maxHeight << std::endl;*/
  if(n == 0){return 0;}
  queue<int> maxhqueue;
  maxhqueue.push(troot);
  int maxheight = 0;
  int nextlevel = 0;
  int pops = -1;
  while(!maxhqueue.empty() ){
    Node current = nodes[maxhqueue.front()];
    if(!maxhqueue.empty()){
      maxhqueue.pop();
      pops++;
    }
    
    for(int i = 0; i < current.children.size(); i++){
      int temp = current.children[i]->key;
      //cout << temp << " ";
      maxhqueue.push(temp);
    }
    
    if(pops == nextlevel){
      pops = 0;
      nextlevel = maxhqueue.size();
      //cout << "nextlevel " << nextlevel <<endl;
      maxheight++;
    }
    //cout << " children of: " << current.key << endl;
    
  }
  cout << maxheight;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
