#pragma once
#include <unordered_map>
#include <vector>
/*
	"How would I store input data"
	A map for each node as each node must be unique.
	If desired for this to be GPU processed, it would have to be an array/vector with understanding there will be useless array space sent to GPU.
	Nothing about the problem said the edges were unique or not.
	If they must be unique, the std::vector<int> can be replaced with std::set<int> here after including the <set> header file.
	Otherwise, for GPU processing, std::array would alias well to a GPU like std::Vector
*/
typedef std::unordered_map<int, std::vector<int>> EdgeGraph;
/*
	Map can efficiently store elements without needing explicit order to entered entries.
	otherwise, with understanding there will be unused space, a vector can be used in it's place if a security check for resizing it added.
*/
typedef std::unordered_map<int, bool> VisitMap; // std::vector<bool> is a C++ sin and we have no way of telling if nodes entered will begin from 0 as well.


class EdgePathSolver
{
public:
	EdgePathSolver();
	~EdgePathSolver();

	EdgePathSolver& add(int i, int j);
	/*
	*	Solution
	*/
	bool Solve();

private:
	void SearchAndMark_DFS(int i);

	/*
	*	Observed pattern with odd edge nodes
	*	Web-Searching confirms the pattern
	*/
	int TotalOddEdgeNodes();

	/*
	*	Check for Stray Graph Nodes
	*/
	bool IsConnected();
	EdgeGraph Graph; // "How would I store input data"
	VisitMap Visited; // Map that stores nodes visited.
};