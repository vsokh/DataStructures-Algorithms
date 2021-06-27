#include <vector>
#include <iostream>

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

void printAdj(std::vector<std::vector<int>> const& adj)
{
	for (int u = 0; u < adj.size(); ++u) {
		std::cout << u << ": ";
		for (int v = 0; v < adj[u].size(); ++v) {
			std::cout << adj[u][v] << " ";
		}
		std::cout << std::endl;
	}
}

void strongconnect(
		int v,
		int& idx,
		std::vector<std::vector<int>> const& adj,
		std::vector<int>& index,
		std::vector<int>& lowlink,
		std::vector<int>& visited,
		std::vector<int>& onStack,
		std::vector<int>& stack,
		std::vector<int>& SCC,
		std::vector<std::vector<int>>& SCCS)
{
	index[v]=lowlink[v]=idx++;
	onStack[v]=visited[v]=true;
	stack.push_back(v);

	for (int w : adj[v])
	{
		if (!visited[w])
		{
			strongconnect(w, idx, adj, index, lowlink, visited, onStack, stack, SCC, SCCS);
			lowlink[v] = std::min(lowlink[v], lowlink[w]);
		}
		else if (onStack[w])
		{
			lowlink[v] = std::min(lowlink[v], index[w]);
		}
	}

	if (lowlink[v] == index[v])
	{
		while (!stack.empty())
		{
			int w = stack.back(); stack.pop_back();
			onStack[w]=false;

			SCC.push_back(w);

			if (w == v) break;
		}
		SCCS.push_back(SCC);
		SCC.clear();
	}
}

// https://www.wikiwand.com/en/Tarjan%27s_strongly_connected_components_algorithm
auto tarjan(std::vector<std::vector<int>> edges, int V)
{
	auto adj = toAdj(edges, V, true);

	std::vector<std::vector<int>> SCCS; std::vector<int> SCC;
	std::vector<int> stack, index(V), lowlink(V), onStack(V), visited(V);
	int idx = 0;
	for (int v = 0; v < V; ++v)
	{
		if (!visited[v])
			strongconnect(v, idx, adj, index, lowlink, visited, onStack, stack, SCC, SCCS);
	}
	return SCCS;
}

int main()
{
	std::cout << "Graph: \n";
	auto const graph =
		"0<-----1<-----4<---->5\n"
		"|    ^ ^      ^      ^\n"
		"|  /   |      |      |\n"
		"v/     |      |      |\n"
		"2<-----3<---->6<-----7<---\n"
		"                     |   |\n"
		"                     -----\n";
	std::cout << graph;

	std::cout << "\nTarjan.\n";
	std::vector<std::vector<int>> edges =
		{{0,2},{2,1},{1,0},{3,2},{3,1},{3,6},{6,3},{6,4},{4,1},{4,5},{5,4},{7,6},{7,5},{7,7}};
	int const V = 8;

	std::cout << "SCC: \n";
	auto SCCS = tarjan(edges, V); printAdj(SCCS);

	return 0;
}

