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

void printAdj(std::vector<std::vector<std::vector<int>>> const& adj)
{
	for (int u = 0; u < adj.size(); ++u) {
		std::cout << u << ": ";
		for (auto vw : adj[u]) {
			std::cout << "(" << vw[0] << ", "<< vw[1] << ") ";
		}
		std::cout << std::endl;
	}
}

// https://www.wikiwand.com/en/Dijkstra%27s_algorithm
auto toAdj(std::vector<std::vector<int>> const& edges, int V)
{
	std::vector<std::vector<std::vector<int>>> adj(V);
	for (auto const& uvw : edges)
	{
		adj[uvw[0]].push_back({uvw[1], uvw[2]});
		adj[uvw[1]].push_back({uvw[0], uvw[2]});
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

auto makePath(std::vector<int> const& path, int D)
{
	std::vector<int> result;
	while (D!=-1) {
		result.push_back(D);
		D = path[D];
	}
	reverse(result.begin(), result.end());
	return result;
}

auto dijkstra(std::vector<std::vector<int>> const& edges,
		int V, int S, int D)
{
	int const INF = 1e9;
	auto adj = toAdj(edges, V);
	std::vector<int> d(V, INF); d[S]=0;
	std::vector<int> path(V, -1);
	std::vector<int> visited(V, 0);
	std::queue<int> q; q.push(S);
	while (!q.empty())
	{
		auto u = q.front(); q.pop();
		if (u == D) break;
		if (visited[u]) continue;

		visited[u]=true;
		for (auto vw : adj[u])
		{
			if (!visited[vw[0]])
			{
				if (d[vw[0]] > d[u] + vw[1])
				{
					d[vw[0]] = d[u] + vw[1];
					path[vw[0]]=u;
				}
				q.push(vw[0]);
			}
		}
	}
	return makePath(path, D);
}

int main()
{
	std::cout << "Graph: \n";
	auto const graph =
		"5 ------- 4 -\n"
		"| \\           \\\n"
		"|   -- |       |\n"
		"|      2 ----- 3\n"
		"|   -- |       |\n"
		"| /           /\n"
		"0 ------- 1 -\n";
	std::cout << graph;

	std::cout << "\nDijkstra.\n";
	std::vector<std::vector<int>> const edges = {
		{0, 1, 1},
		{0, 2, 9},
		{0, 5, 14},
		{1, 2, 10},
		{1, 3, 15},
		{3, 2, 11},
		{3, 4, 6},
		{4, 5, 9},
		{5, 2, 2},
	};
	int const V = 6, S = 0, D = 4;

	auto adj = toAdj(edges, V);
	std::cout << "Adj: \n"; printAdj(adj);

	// 0 2 5 4
	auto path = dijkstra(edges, V, S, D);
	std::cout << "Path: "; printPath(path);
	return 0;
}
