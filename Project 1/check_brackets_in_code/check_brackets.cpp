#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
    //text = "foo(bar[(i);";
    bool pass = true;

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next,position)); 
        }

        if (next == ')' || next == ']' || next == '}') {
            if(opening_brackets_stack.empty()){
              cout << position + 1;
              pass = false;
              break;
            }

            if(!opening_brackets_stack.top().Matchc(next)){// if false, if it does not match
              cout << position + 1;
              pass = false;
              break;
            }
            opening_brackets_stack.pop();

        }

    }
    if(!opening_brackets_stack.empty() && pass){
      pass = false;
      cout << opening_brackets_stack.top().position + 1;
    }
      

    if(pass)
      cout << "Success";

    return 0;
}
