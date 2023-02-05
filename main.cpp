//compile with -O3 flag
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
  "A farmer went to a market and purchased a wolf, a goat, and a cabbage. On his way home, the farmer came to the bank of a river and rented a boat. But crossing the river by boat, the farmer could carry only himself and a single one of his purchases: the wolf, the goat, or the cabbage."

  This optimized program aims to solve this problem for an arbitrary amount of purchases and places on the boat for the purchases.

Below is the explanation of the theory. The implementation is explained in the code

===

Definitions:
  A: the number of purchases
  B: the number of places on the boat for his purchases

OVERVIEW
  The core algorithm is a graph discovery algorithm. It is optimized using bit manipulations.

STATE
  A state of the river bank can be represented by a list of 1s and 0s, 1 representing presence and 0 absence of the farmer and his purchases. A list of 1s and 0s is a bit string, or a number when it comes to computers. Hence by manipulating numbers at the bit level with binary operations (binary AND, OR, NOT, etc...), we can manage to solve this problem.
  The state of the river is A bits long. The most siginicant bit is the bit representing the presence of the farmer.

SAFE STATE
  A safe state is a state where no purchase gets eaten, assuming that the ith purchase eats the i+1th purchase. Checking whether a state is safe goes as following: for each purchase, if the next purchase is on the same bank, and not on the same bank as the farmer, then it is unsafe; else it is safe. The check is made using bit manipulation.

TRANSPORTATIONS
  A transportation is a bit string indicating which purchases should be bit-flipped, i.e brought to the other side. A transportation can only be applied on a state if all the flipped bits are equal (state AND transportation is equal to 0 or the transportation). Applying the transportation consists of XORing the state and the transportation, flipping the bits indicated by the transportation. 
  When a graph is initialized, a list of all possible transportation is generated. These transportations are all the possible n-Choose-k combinations with n=A and k ranging from 0 to B. They are generated using bit manipulation.

CORE ALGORITHM
  The core algorithm of this program is a Depth First Search graph discovery algorithm. A vertex in this graph represents a safe river bank state, and the adjacent vertices represent the next possible river bank states.
  The DFS search algorithm is recursive. Each recursion stage goes as following:
    1. if the current vertex is the desired end vertex, return true
    2. set the current vertex as visited
    3. for each adjacent vertex that is not yet visited,  execute DFS for that vertex. Return true if one of them returned true
    4. Else, return false

ADJACENCY LIST
  Previously, the program consisted of two stages: a complete graph generation stage and a search stage. However, this method was very wasteful, since only a fraction of the vertices were discovered during the search. Now, instead, the adjency list for a given vertex is generated during the DFS search, so no data gets wasted.
  The particularity of this DFS algorithm is in step 3. The adjacent vertices are found as following:
    1. For each possible transportation, check if the transportation is possible
    2. If so, check is the state tranformed by this transportation was visited or not
    3. If so, check if the state tranformed by this transportation is safe or not
    4. If so, then the state tranformed by this transportation is an adjacent vertex
The conditions are ordered from the least to most computationally expensive to save computation.
 
*/ 

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