#include <iostream>
#include <vector>

void printPath(std::vector<int> v)
{
	for (int i : v)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

std::vector<std::vector<int>> toAdj(
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

void printAdj(std::vector<std::vector<int>> const& adj)
{
	for (int u = 0; u < adj.size(); ++u)
	{
		std::cout << u << ": ";
		for (int v = 0; v < adj[u].size(); ++v)
		{
			std::cout << adj[u][v] << " ";
		}
		std::cout << std::endl;
	}
}

void dfsVisit(
		std::vector<std::vector<int>> const& adj,
		int u,
		int D,
		std::vector<int> visited,
		std::vector<int> stack,
		std::vector<int>& path)
{
	visited[u] = 1;
	stack.push_back(u);

	if (u == D)
	{
		path = path.empty() || stack.size() < path.size() ? stack : path;
		return;
	}

	for (int v : adj[u])
	{
		if (!visited[v])
			dfsVisit(adj, v, D, visited, stack, path);
	}

	stack.pop_back();
}

std::vector<int> dfs(std::vector<std::vector<int>> const& edges,
		int V, int S, int D)
{
	std::vector<std::vector<int>> adj = toAdj(edges, V);

	std::vector<int> visited(V);
	visited[S]=1;

	std::vector<int> stack, path;
	dfsVisit(adj, S, D, visited, stack, path);

	return path;
}

int main()
{
	std::cout << "Graph: \n";
	auto const graph =
		"4------7--\n"
		"|      |   \\\n"
		"|      |    |\n"
		"1------0----3\n"
		"|           |\n"
		"2--         5\n"
		"    \\       |\n"
		"      ------6\n";
	std::cout << graph;

	std::cout << "\nDFS.\n";
	std::vector<std::vector<int>> const edges =
		{{0,1},{7,0},{4,7},{1,4},{6,5},{3,5},{0,3},{2,1},{3,7},{2,6}};
	int V = 8, S = 0, D = 5;

	auto adj = toAdj(edges, V);
	std::cout << "Adj: \n"; printAdj(adj);

	auto path = dfs(edges, V, S, D);
	std::cout << "Path: "; printPath(path);

	return 0;
}

