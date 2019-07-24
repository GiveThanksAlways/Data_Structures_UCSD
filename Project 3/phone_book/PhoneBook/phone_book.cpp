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
    //Query contacts [10000000];
    //Query* array = new Query[1000000];
    vector<string> contacts;
    contacts.resize(10000000);
	
    for (size_t i = 0; i < queries.size(); ++i){
      /**if(queries[i].number > contacts.size())
        contacts.resize(queries[i].number+1);*/
         
        if (queries[i].type == "add") { // process add
        int hash = queries[i].number;
          contacts[hash] = queries[i].name;
          
          
        } else if (queries[i].type == "del") { // process del
            
                int delHash = queries[i].number;
                //if(contacts[delHash].number == queries[i].number){
                contacts[delHash] = ""; // deleted
                //}
         
         
        } else { // process find 
            
            string response = "not found";
            int findhash = queries[i].number;
            if(contacts[findhash] != ""){
            	response = contacts[findhash];
            }
             // if element, then add number, else not there
            result.push_back(response);
        }
    }
	//printVector(contacts);
    return result;
    
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
