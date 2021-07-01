#include <iostream>
#include <vector>
#include <list>

auto toAdj(
		std::vector<std::vector<int>> const& edges,
		int V,
		bool directed = false)
{
	std::vector<std::vector<int>> adj(V);

	for (auto uv : edges)
	{
		adj[uv[0]].push_back(uv[1]);
		if (!directed)
			adj[uv[1]].push_back(uv[0]);
	}
	return adj;
}

void dfs(
		std::vector<std::vector<int>> const& adj,
		int u,
		std::vector<int>& visited,
		std::list<int>& sorted)
{
	visited[u]=true;
	for (auto v : adj[u])
	{
		if (!visited[v])
			dfs(adj, v, visited, sorted);
	}
	sorted.push_front(u);
}

auto topologicalSort(std::vector<std::vector<int>> const& edges, int V)
{
	auto adj = toAdj(edges, V, true);
	std::vector<int> visited(V);
	std::list<int> sorted;
	for (int u = 0; u < V; ++u)
	{
		if (!visited[u])
			dfs(adj, u, visited, sorted);
	}
	return sorted;
}

int main()
{
	std::cout << "Graph: \n";
	auto const graph =
		"0 ---  1\n"
		"|    | |   4\n"
		"v    v v\n"
		"2 --> 3\n"
		"|\n"
		"|  --- 6\n"
		"| |    |\n"
		"| |    v\n"
		"v v    7\n"
		" 5 --  |\n"
		"     | |\n"
		"     v v\n"
		"      8\n";
	std::cout << graph;

	std::cout << "\nTopological sort.\n";
	std::vector<std::vector<int>> edges =
		{{0,2},{0,3},{1,3},{2,3},{2,5},{6,5},{6,7},{5,8},{7,8}};
	int const V = 9;

	auto sortedGraph = topologicalSort(edges, V);
	for (auto u : sortedGraph)
		std::cout << u << " ";
	std::cout << std::endl;
	return 0;
}
