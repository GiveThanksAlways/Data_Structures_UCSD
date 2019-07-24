#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <limits>

using std::swap;
using std::pair;
using std::make_pair;
using namespace std;

using std::vector;
using std::cin;
using std::cout;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;
  vector< pair<int, long long> > minHeap_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
    
  }

  int leftChild(int i){
    return 2*i + 1;
  }
  int rightChild(int i){
    return 2*i + 2;
  }
  int parent(int i){
    return floor((i-1)/2);
  }
  void swimDown(int i){
    int minIndex = i;
    int l = leftChild(i);
    if(l <= minHeap_.size()-1 && minHeap_[l].second <= minHeap_[minIndex].second){
      if(minHeap_[l].second == minHeap_[minIndex].second){ // if processes have same time
        if(minHeap_[l].first < minHeap_[minIndex].first) // if left id is lower, then it is the minIndex
          minIndex = l;
      }
      else
        minIndex = l;
    }
    int r = rightChild(i);
    if(r <= minHeap_.size()-1 && minHeap_[r].second <= minHeap_[minIndex].second){
      if(minHeap_[r].second == minHeap_[minIndex].second){ // if processes have same time
        if(minHeap_[r].first < minHeap_[minIndex].first) // if right id is lower, then it is the minIndex
          minIndex = r;
      }
      else
        minIndex = r;
    }
    if(i != minIndex){
      swap(minHeap_[i], minHeap_[minIndex]);
      swimDown(minIndex);
    }
  }
  void peekMin(){
    int id = minHeap_[0].first;
    long long duration = minHeap_[0].second;
    assigned_workers_.push_back(id);
    start_times_.push_back(duration);
  }
  

  void AssignJobs() {
    
    // TODO: replace this code with a faster algorithm.
    /**assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }*/
    // make workers and ID's
    int start = 0;
    for(int i =0; i < num_workers_; i++){
      if(!(i < jobs_.size())){
        break;
      }
      minHeap_.push_back(make_pair(i,0));
      start++;
    }
    // make heap 
    /**int n = minHeap_.size();
    for(int i = (n-1)/2; i+1 != 0; i--){
      swimDown(i);
    }*/
    // process the rest of the jobs
    for (int i = 0; i < jobs_.size(); i++) {
      // write response
      peekMin();
      // assign new process
      minHeap_[0].second += jobs_[i];
      swimDown(0); // move new process to bottom
    }
    // print out the rest of the jobs 
    /**for(int i = 0; i < start; i++){
      // write response
      peekMin();
      minHeap_[0].second = std::numeric_limits<long long>::max(); // basically infinity moves it to bottom
      swimDown(0);
    }*/



  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
