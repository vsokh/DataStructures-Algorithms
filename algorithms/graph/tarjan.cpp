#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> toAdj(
		vector<vector<int>> const& edges,
		int V,
		bool directed = false)
{
	vector<vector<int>> adj(V);

	for (auto uv : edges) {
		adj[uv[0]].push_back(uv[1]);
		if (!directed)
			adj[uv[1]].push_back(uv[0]);
	}
	return adj;
}

void printAdj(vector<vector<int>> const& adj)
{
	for (int u = 0; u < adj.size(); ++u) {
		cout << u << ": ";
		for (int v = 0; v < adj[u].size(); ++v) {
			cout << adj[u][v] << " ";
		}
		cout << endl;
	}
}

void strongconnect(
		int v,
		int& idx,
		vector<vector<int>> const& adj,
		vector<int>& index,
		vector<int>& lowlink,
		vector<int>& visited,
		vector<int>& onStack,
		vector<int>& stack,
		vector<int>& SCC,
		vector<vector<int>>& SCCS)
{
	index[v]=lowlink[v]=idx++;
	onStack[v]=visited[v]=true;
	stack.push_back(v);

	for (int w : adj[v]) {
		if (!visited[w]) {
			strongconnect(w, idx, adj, index, lowlink, visited, onStack, stack, SCC, SCCS);
			lowlink[v] = min(lowlink[v], lowlink[w]);
		}
		else if (onStack[w]) {
			lowlink[v] = min(lowlink[v], index[w]);
		}
	}

	if (lowlink[v] == index[v]) {
		while (!stack.empty()) {
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
vector<vector<int>> tarjan(vector<vector<int>> edges, int V)
{
	vector<vector<int>> adj = toAdj(edges, V, true);

	vector<vector<int>> SCCS; vector<int> SCC;
	vector<int> stack, index(V), lowlink(V), onStack(V), visited(V);
	int idx = 0;
	for (int v = 0; v < V; ++v) {
		if (!visited[v]) {
			strongconnect(v, idx, adj, index, lowlink, visited, onStack, stack, SCC, SCCS);
		}
	}
	return SCCS;
}

int main()
{
	cout << "\nTarjan.\n";
	/*
	 * 0<-----1<-----4<---->5
	 * ^    ^ ^      ^      ^
	 * |  /   |      |      |
	 * |/     |      |      |
	 * 2<-----3<---->6<-----7<---
	 *                      |   |
	 *                      -----
	 */
	cout << "0<-----1<-----4<---->5\n";
	cout << "|    ^ ^      ^      ^\n";
	cout << "|  /   |      |      |\n";
	cout << "v/     |      |      |\n";
	cout << "2<-----3<---->6<-----7<---\n";
	cout << "                     |   |\n";
	cout << "                     -----\n";
	int V = 8;
	vector<vector<int>> edges =
		{{0,2},{2,1},{1,0},{3,2},{3,1},{3,6},{6,3},{6,4},{4,1},{4,5},{5,4},{7,6},{7,5},{7,7}};
	cout << "SCC: \n";
	vector<vector<int>> SCC = tarjan(edges, V);
	printAdj(SCC);
	return 0;
}

