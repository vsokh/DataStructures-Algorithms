#include <iostream>

#include <vector>
#include <queue>

void printPath(std::vector<int> v)
{
	for (int i : v)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void printQ(std::queue<int> q)
{
	std::cout << "[";
	while (!q.empty())
	{
		int e = q.front(); q.pop();
		if (q.empty())
			std::cout << e;
		else
			std::cout << e << " ";
	}
	std::cout << "]\n";
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

std::vector<int> makePath(std::vector<int> const& path, int D)
{
	std::vector<int> result;
	while (D!=-1)
	{
		result.push_back(D);
		D = path[D];
	}
	reverse(result.begin(), result.end());
	return result;
}

std::vector<int> bfs(
		std::vector<std::vector<int>> const& edges,
		int V, int S, int D)
{
	auto const adj = toAdj(edges, V);

	std::vector<int> path(V,-1);
	std::vector<int> visited(V);

	std::queue<int> q; q.push(S);

	while (!q.empty())
	{
		int u = q.front(); q.pop();

		if (u == D) break;
		if (visited[u]) continue;

		for (int v : adj[u])
		{
			if (!visited[v])
			{
				if (path[v]==-1)
					path[v]=u;
				q.push(v);
			}
		}
		visited[u]=1;
	}

	return makePath(path, D);
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

	std::cout << "\nBFS.\n";
	std::vector<std::vector<int>> const edges =
		{{0,1},{7,0},{4,7},{1,4},{6,5},{3,5},{0,3},{2,1},{3,7},{2,6}};
	int V = 8, S = 0, D = 5;

	auto adj = toAdj(edges, V);
	std::cout << "Adj: \n"; printAdj(adj);

	auto path = bfs(edges, V, S, D);
	std::cout << "Path: "; printPath(path);

	return 0;
}

