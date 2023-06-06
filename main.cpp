//compile with -O3 flag
#include <iostream>
#include <bits/stdc++.h>

using namespace std;


class ProblemGraph {
public:
  ProblemGraph(int a, int b);
  bool DFS(int v);
private:
  int A;
  int B;
  map<int, bool> visited;
  list<int> transporters;
  bool safe(int x);
};
ProblemGraph::ProblemGraph(int a, int b) {
  A = a;
  B = b;
  
  int n=0;
  int x;
  //generate nCk combinations for n smaller then B
  while (n<B) {
    n++;
    //set x the smallest number with n bits set
    x = (1<<n)-1;
    //generate combinations smaller then 2^A, the largest number of bit length A-1
    while (x<(1<<A)){
      //since the most significant bit is the farmer, it will always get flipped, so we add 2^A to the combination
      transporters.push_back(x+(1<<A));
      //set x to the next combination https://realtimecollisiondetection.net/blog/?p=78
      x = (x+(x&-x))|(int)(((x^(x+(x&-x)))>>2)/(x&-x)); 
    }
  }
  transporters.push_back(1<<A);
}
bool ProblemGraph::DFS(int v=0) {
  //if the current vertex is the end vertex, i.e 2^A - 1
  if (v==(1<<(A+1))-1) {cout<<v<<'\n';return true;}
  //set the current vertex to visited
  visited[v] = true; 
  //for each transporter
  for (auto t=transporters.begin(); t!=transporters.end(); t++) {
    //if transporter AND vertex is equal to the transporter or 0
    if ((*t&v)==*t || !(*t&v))
    //if transporter XOR vertex is not visited
    if (!visited[*t^v])
    //if transporter XOR vertex is safe
    if (safe(*t^v))
    if (DFS(*t^v)) {cout<<v<<'\n';return true;}
  } return false;
}
bool ProblemGraph::safe(int x) {
  //i is a "slider", selecting the ith bit by ANDing it with the state. It is initally 1 bitshifted left A times, selecting the most significant bit.
  int i = (1<<A);
  //iterate until i is the before-least significant bit
  while (i != 0b10) {
    //bit shift right i by 1
    i >>= 1;
    //check whether the ith bit is equal to the i+1th bit (i shifted right by 1 again) AND that the ith bit is equal to the most signicant bit.
    if (!!(x&i)==!!(x&(i>>1)) && !!(x&i)!=!!(x&(1<<A))) return false;
  } return true;
}

int main() {
  //Solving the original problem; A=3 and B=1
  ProblemGraph* G = new ProblemGraph(3, 1);
  cout << G->DFS();
  delete G;
}
