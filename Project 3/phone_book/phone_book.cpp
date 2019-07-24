#include <iostream>
#include <vector>
#include <string>


using std::string;
using std::vector;
using std::cin;
using std::cout;
using namespace std;

struct Query {
    string type, name;
    int number;
};

void printVector(vector<Query> &vector1){
  for(int i = 0; i < vector1.size(); i++){
    if(vector1[i].name != "")
      cout << vector1[i].name << "(i=" << i << ")  ";
  }
  cout << endl;
}

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query> &queries) {
    vector<string> result;
    int m = 9999999;
    vector<Query> contacts;
    contacts.resize(m);
	
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") { // process add

          contacts[queries[i].number] = queries[i];
          
        } else if (queries[i].type == "del") { // process del
          //cout << "deleted: " << queries[i].number << endl;
          //contacts.erase(contacts.begin()+queries[i].number-1);
          contacts[queries[i].number].name = "";
          

        } else { // process find 
            //cout << endl << "find" << endl;
            //printVector(contacts);
            //cout << "m: " << contacts.size() << endl << endl;
            string response = "not found";
            if(contacts[queries[i].number].name != "")
              response = contacts[queries[i].number].name;
            result.push_back(response);
        }
    //printVector(contacts);
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}