# Algorithms-DataStructures
Algorithms and Data Structures I have coded in some of my college degree courses

<p align="center">
<img src="https://user-images.githubusercontent.com/71342016/184548120-e11c03ae-8122-41dc-9eac-cdacb2105569.png" width="700px" />
</p>

## How to use

To clone and run this projects at least you need `Git`, a C++ compiler like `g++`, and `Python3` with `pip` installed on your computer.

Clone this repository
```
https://github.com/samueldiaz1004/Algorithms-DataStructures.git
```
Change directory
```
cd LinkedList
```
Compile all the `cpp` files in the directory
```
g++ -o linkedList.exe MyLinkedList.cpp main.cpp 
```
Run the executable created
```
./linkedList.exe
```

## Table of contents

* [Annealing](https://www.geeksforgeeks.org/simulated-annealing/)
  * A probabilistic technique for approximating the optimal solution for NP-hard problems, in this case for the traveling salesman problem.
* [BST](https://www.geeksforgeeks.org/binary-search-tree-data-structure/)
  * Implementation of a binary search tree that can perform basic insertion, traversal and searching operations.
* [Backpack](https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/)
  * A solution of the 0-1 Knapsack problem using dinamic programming.
* [CoinChange](https://www.geeksforgeeks.org/understanding-the-coin-change-problem-with-dynamic-programming/)
  * Implementation and comparison of the dynamic and greedy algorithm to solve the coin change problem.
* Compilation1
  * Substring search between two strings using the Knuth-Morris-Pratt algorithm.
  * Find the longest palindrome in a string using the Manacher algorithm.
  * Use dynamic programming to find the longest common substring between a pair of strings.
* Compilation2
  * Find the minimum spanning tree in a completly connected graph without cicles using Prim's algorithm.
  * An approach to solve the traveling salesman problem using the Repetitve Nearest Neighbor technique.
  * Calculate the max flux from a starting to an ending node in a directed graph via the Ford-Fulkerson algorithm.
  * Map a collection of points in a 2d space and generate a Voronoi graph to determine the closest point to a new entry. 
* [FaceTriangulation](https://blog.devgenius.io/voronoi-graph-and-delaunay-triangulation-visually-explained-1df842640c55)
  * Application to map a subjects face from a face detection model and then represent using Voronoi graph and Delaunay triangulation.
* [Graph](https://www.geeksforgeeks.org/graph-and-its-representations/)
  * A directed graph represented by a 2d array with DFS and BFS traversal options.
* [HashTable](https://en.wikipedia.org/wiki/Hash_table)
  * Implementation of a hash table using using a linked list to store keys and values, it can perform read and write operations and rehash in function of a load factor.
* [Heap](https://www.geeksforgeeks.org/heap-data-structure/)
  * Implementation of a max heap using an array that can expand periodically.
* [LinkedList](https://www.tutorialspoint.com/data_structures_algorithms/linked_lists_algorithm.htm)
  * Implementation of a single linked list that can perform basic insertion, traversal and searching operations.
* [Maze](https://www.geeksforgeeks.org/difference-between-backtracking-and-branch-n-bound-technique/)
  * Implementation and comparison of the backtracking and branch and bound technique to find the solution to a maze.
* [ShortestPath](https://www.baeldung.com/cs/dijkstra-vs-floyd-warshall)
  * Implementation and comparison of the Dijkstra and Floyd algorithm to find the shortest path between vertices.
* [Sort&Search](https://msatechnosoft.in/blog/searching-sorting-data-structure-algorithms/)
  * Implementation of some of the most common searching (lineal and binary) and sorting (insertion, bubble and merge) algorithms.
  
## Troubleshooting
Some projects like `FaceTriangulation` and `Compilation2` require the installation of extra libraries, notably [CGAL](https://www.cgal.org/). You can install it via a C/C++ package manager and added the necesary libraries to the project using [Cmake](https://cmake.org/) or [Visual Studio](https://www.youtube.com/watch?v=FeBzSYiWkEU)  (recommended for Windows users).
