# BitwiseWGC
A uselessly over-engineered solution to the simple riddle, "The wolf, the goat and the cabbage".

## The problem

The original riddle goes as follows: 

> "A farmer went to a market and purchased a wolf, a goat, and a cabbage. On his way home, the farmer came to the bank of a river and rented a boat. But crossing the river by boat, the farmer could carry only himself and a single one of his purchases: the wolf, the goat, or the cabbage."


This optimized program aims to solve this problem for an arbitrary amount of purchases and places on the boat for the purchases, where every purchase has a single prey except the last.

## The solution

### Definitions
Let **A** be the number of purchases
Let **B** be the number of places on the boat for his purchases

#### State
  A state of the river bank can be represented by a list of 1s and 0s, 1 representing presence and 0 absence of the farmer and his purchases. A list of 1s and 0s is a bit string, or a number when it comes to computers. Hence by manipulating numbers at the bit level with binary operations (binary AND, OR, NOT, etc...), we can manage to solve this problem.
  The state of the river is A bits long. The most siginicant bit is the bit representing the presence of the farmer.

#### Safe state
  A safe state is a state where no purchase gets eaten, assuming that the ith purchase eats the i+1th purchase. Checking whether a state is safe goes as following: for each purchase, if the next purchase is on the same bank, and not on the same bank as the farmer, then it is unsafe; else it is safe. The check is made using bit manipulation.

#### Transportation
  A transportation is a bit string indicating which purchases should be bit-flipped, i.e brought to the other side. A transportation can only be applied on a state if all the flipped bits are equal (state AND transportation is equal to 0 or the transportation). Applying the transportation consists of XORing the state and the transportation, flipping the bits indicated by the transportation. 
  When a graph is initialized, a list of all possible transportation is generated. These transportations are all the possible n-Choose-k combinations with n=A and k ranging from 0 to B. They are generated using bit manipulation.

### The algorithm
  The core algorithm of this program is a Depth First Search graph discovery algorithm. A vertex in this graph represents a safe river bank state, and the adjacent vertices represent the next possible river bank states.
  The DFS search algorithm is a normal recursive DFS. Each recursion stage goes as following:
  1. if the current vertex is the desired end vertex, return true
  2. set the current vertex as visited
  3. for each adjacent vertex that is not yet visited,  execute DFS for that vertex. Return true if one of them returned true
  4. Else, return false

#### Adjacency list
  Previously, the program consisted of two stages: a complete graph generation stage and a search stage. However, this method was very wasteful, since only a fraction of the vertices were discovered during the search. Now, instead, the adjency list for a given vertex is generated during the DFS search, so no data gets wasted.
  The particularity of this DFS algorithm is in step 3. The adjacent vertices are found as following:
   1. For each possible transportation, check if the transportation is possible
   2. If so, check if the state tranformed by this transportation was visited or not
   3. If so, check if the state tranformed by this transportation is safe or not
   4. If so, then the state tranformed by this transportation is an adjacent vertex
  
The conditions are ordered from the least to most computationally expensive to save computation.

## Footnote
This project is useless as mentioned previously. There is a much simpler analytic solution to the problem solved in the algorithm above.






