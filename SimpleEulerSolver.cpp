
#include "SimpleEulerSolver.hpp"

#include <iostream>
#include <map>
#include <vector>




EdgePathSolver::EdgePathSolver()
{
}

EdgePathSolver::~EdgePathSolver()
{
}

EdgePathSolver& EdgePathSolver::add(int i, int j)
{
	Graph[i].emplace_back(j); // link up each graph element.
	Graph[j].emplace_back(i);
	Visited[i] = false;
	Visited[j] = false;
	return *this; // method chaining to add easy test case generation
}

void EdgePathSolver::SearchAndMark_DFS(int i)
{
	Visited[i] = true; // check if element touched once.
	for (auto element : Graph[i])
	{
		if (!Visited[element]) // if an element hasn't been visited, go to it recursively.
		{
			SearchAndMark_DFS(element);
		}
	}
	// optimization -> Use a deque instead to remove recursion
}

int EdgePathSolver::TotalOddEdgeNodes()
{
	int result = 0;
	for (const auto& element : Graph)
	{
		if (element.second.size() % 2 != 0)
		{
			result++;
		}
	}
	return result;
}

bool EdgePathSolver::IsConnected()
{
	for (const auto& element : Graph)
	{
		if (Graph[element.first].size() > 0) // want nodes where a node has more than 0 edges
		{
			SearchAndMark_DFS(element.first); // start mark here and break.
			break;
		}
	}
	for (const auto& element : Graph)
	{
		if (!Visited[element.first] && Graph[element.first].size() > 0) // check if node hasn't been visited yet and it has edges
		{
			return false; // this means the graph is probably disjointed, there were connected nodes DFS couldn't access
		}
	}
	return true;
}

bool EdgePathSolver::Solve()
{
	if (Graph.size() == 0)
	{
		return true; // if no nodes, then yes, we can find a path between all edges because there are no edges to travel through.
	}
	int totalOdd = TotalOddEdgeNodes(); // web-searching reveals the pattern noticed is a thing
	if (IsConnected() && (totalOdd == 2 || totalOdd == 0)) // **Eulerian** Path detected
	{
		return true; // a path can be formed
	}
	return false; // a path cannot be formed

}
int main()
{
	std::vector<EdgePathSolver> TestCase;

	TestCase.push_back(EdgePathSolver().add(0, 1).add(1, 2).add(2, 3).add(3, 4).add(4, 1).add(4, 5));
	TestCase.push_back(EdgePathSolver().add(1, 2).add(2, 3).add(3, 4).add(4, 1));
	TestCase.push_back(EdgePathSolver().add(1, 2).add(2, 3).add(3, 4));
	TestCase.push_back(EdgePathSolver().add(1, 2));
	TestCase.push_back(EdgePathSolver().add(3, 4).add(1, 2));

	const int totalCases = TestCase.size();
	for (int i = 0; i < totalCases; i++)
	{
		std::cout << i << ": ";
		if (TestCase[i].Solve())
		{
			std::cout << "A path can be formed traversing through all edges once" << std::endl;
		}
		else
		{
			std::cout << "A path cannot be formed traversing through all edges once" << std::endl;
		}
	}

	return 0;
}