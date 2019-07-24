#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using std::string;
typedef unsigned long long ull;
using namespace std;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

size_t PolyHash(const string& s,long long prime, long long multiplier) {
    //static const size_t multiplier = 263;
    //static const size_t prime = 1000000007;
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = (((hash * multiplier + s[i]) % prime) + prime) % prime;
    //hash = (((hash * x + (long)s[i])% p) + p) % p;
    //hash = (hash * multiplier + s[i]) % prime;
    return hash ;//% bucket_count;
}

std::vector<long long> precomputeHashes(string T, long long P,long long prime, long long x){
  int Tlen = T.length();
  vector<long long> H;
  H.resize(Tlen-P+1);
  string s = T.substr(Tlen-P,Tlen-1);
  H[Tlen-P] = PolyHash(s, prime, x);
  long long y = 1;
  for(int i=1; i <= P; i++){
    y = (y*x) % prime;
  }
  for(size_t i = Tlen-P-1; i != -1; i--){
    H[i] = (x*H[i+1] + T[i] - y*T[i+P]) % prime;
  }

  return H;
}

bool AreEqual(string T, string P, int from, int to){
    int i = 0;
    for(size_t j = from; j < to; j++){
      if(T[j] != P[i])
        return false;

      i++;
    }
    return true;
}

std::vector<int> RabinKarp(string T,string P){
  long long prime = 1000000007;
  long long x = rand() % prime;// 263;//random(1,prime-1)
  vector<int> result;
  long long pHash = PolyHash(P, prime, x);// pattern hash
  vector<long long> H = precomputeHashes(T, P.length(), prime, x);
  for(size_t i = 0; i < H.size(); i++){
    if(pHash != H[i])
      continue;
    if(AreEqual(T,P,i,i+P.length()-1))
      result.push_back(i);
  }
  return result;
}

std::vector<int> get_occurrences(const Data& input) {
    //precomputeHashes(input.text, input.pattern.length(),1000000007, 263);

    return RabinKarp(input.text, input.pattern);
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
