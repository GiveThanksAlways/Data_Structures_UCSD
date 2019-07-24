#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

struct Element {
    string s;
    Element* next;
    Element* prev;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<Element> buckets;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (((hash * multiplier + s[i]) % prime) + prime) % prime;
        //hash = (((hash * x + (long)s[i])% p) + p) % p;
        //hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }
    /**
    check - go to buckets[query.ind] , if Element (s != "") then print Element and print the nodes it may point to

    find - hash = hash_func[query.s], then go to that buckets[hash]
      check all strings there ie buckets[hash].s == query.s ? and while next* != null, next -> s == query.s?
      if found, then print \n or endl

    add to chain - so when we add, the added element becomes head of chain at buckets[hash]
      0 element - just add (0 elements if buckets[i] = "") 
      0> element - make old-head prev* point to inserted element (inserted next* becomes old-head)

    del 
      0 elements - string = "" 
      0> elements - walk linked list until you find the one to delete
                    set the left node next* to deleted nodes next*
                    set the right node prev* to deleted prev*
      use delete *Element to delete from the heap

    
    */
    void find(const Query& query){
      long long hash = hash_func(query.s);
      if(buckets[hash].s == ""){ // no element in bucket
        writeSearchResult(false);
      }else if(buckets[hash].s == query.s){ // found it 
        writeSearchResult(true);
      }else{// keep going
        Element* nextElm;
        nextElm = buckets[hash].next;
        while(nextElm != NULL){// go until we hit the null,(end of doubly linked list)
          if(nextElm -> s == query.s){// found it
            writeSearchResult(true);
            return; // we found it in the bucket, we are done looking so we return from the function and pop it from the stack
          }
          nextElm = nextElm -> next; // change pointer to next until we hit null

        }// end of while
        // if you made it here, that means you didn't find it, so print failure
        writeSearchResult(false);
      }
    }

    void check(const Query& query){
      long long hash = query.ind;
      if(buckets[hash].s != ""){// if no empty string, then we have elements, lets go
        cout << buckets[hash].s << " ";
        Element* nextElm = buckets[hash].next;
        while(nextElm != NULL){// keep going until we hit null
          cout << nextElm -> s << " ";
          nextElm = nextElm -> next; // keep going 
        }
        cout <<  endl;
      }else{// empty bucket so we print a new ling \n or endl
        cout << endl;
      }
    }

    void add(const Query& query){
      long long hash = hash_func(query.s);
      if(buckets[hash].s == ""){ // no element in bucket
        buckets[hash].s = query.s;
      }else if(buckets[hash].s != query.s){ // if it matches, then we ignore and skip this else if part. Doesn't match means we need to check others and if no match, then we add, if we ever find it then we don't do anything
        // check to see if element is one of the elements in the bucket
        Element* nextElm;
        nextElm = buckets[hash].next;
        while(nextElm != NULL){// go until we hit the null,( end of doubly linked list)
          if(nextElm -> s == query.s){
            return; // we found it in the bucket, we are done looking so we return from the function and pop it from the stack
          }
          nextElm = nextElm -> next; // change pointer to next until we hit null

        }// end of while
        // if we make it here, that means we did not find the element. So we then can add it to the bucket
        // change the pointers to reflect this
        Element* oldHead = new Element;// create element on Heap for long term storage instead of stack
        oldHead -> s = buckets[hash].s; // old head of doubly linked list
        oldHead -> next = buckets[hash].next;
        if(oldHead -> next != NULL){// if not null, then we need to update the prev part of the first right node to point to old head 
          oldHead -> next -> prev = oldHead; // the 3rd element now points to the second who is the old head
        }
        // reset
        buckets[hash].s = query.s;
        buckets[hash].next = oldHead;
        // point back the oldHead now
        oldHead -> prev = &buckets[hash]; // points back to the head now

        // query ---> oldHead
      }
    }

    void del(const Query& query){
      long long hash = hash_func(query.s);
      if(buckets[hash].s == query.s){ // found it, delete the head of doubly linked list
        // delete the head of the linked list
        if(buckets[hash].next != NULL){// we have a chain to deal with
          Element* right = buckets[hash].next;
          //newHead->s = buckets[hash].next -> s;
          //newHead->next = buckets[hash].next -> next;
          if(right -> next != NULL)
            right -> next -> prev = &buckets[hash]; // make third element point back to head because right is the new head
          buckets[hash].s = right -> s;
          buckets[hash].next = right -> next;
          buckets[hash].prev = NULL;// used to be to the head of list, now null because it is the head of the list
          delete right; // node not needed anymore. Remove from the heap
        }else{// no chains in bucket so just erase
          buckets[hash].s = "";
          //buckets[hash].next = NULL;
          //buckets[hash].prev = NULL;
        }
        
      }else { // keep going until we find what to delete
        Element* nextElm; 
        nextElm = buckets[hash].next;
        while(nextElm != NULL){// go until we hit the null or we find match
          if(nextElm -> s == query.s){// we found match!!
            Element* right;
            Element* left;
            right = nextElm -> next;
            left = nextElm -> prev;
            // delete
            if(left != NULL) //if it is NULL, no need to change it
              left -> next = nextElm -> next;// left see the next guy
            if(right != NULL) // if it is NULL, no need to change it
              right-> prev = nextElm -> prev;// right has to see back over
            delete nextElm; // remove from heap, its gone
            return; // we are done. Exit the function
          }
          nextElm = nextElm -> next; // change pointer to next until we hit null

        }// end of while
      
      }// end of else
    }


    void processQuery(const Query& query) {

        if (query.type == "check") {
            check(query);
        } else {
            
            if (query.type == "find")
              find(query);
            else if (query.type == "add") 
              add(query);
            else if (query.type == "del")
              del(query);
            
              
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        buckets.resize(bucket_count); // make vector the amount of buckets
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
