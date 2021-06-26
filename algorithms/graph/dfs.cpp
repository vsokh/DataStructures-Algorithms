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

void dfsVisit(
		vector<vector<int>> const& adj,
		int u,
		int D,
		vector<int> visited,
		vector<int> stack,
		vector<int>& path) {

	visited[u] = 1;
	stack.push_back(u);

	if (u == D) {
		path = path.empty() || stack.size() < path.size() ? stack : path;
		return;
	}

	for (int v : adj[u]) {
		if (!visited[v])
			dfsVisit(adj, v, D, visited, stack, path);
	}

	stack.pop_back();
}

vector<int> dfs(vector<vector<int>> edges, int V, int S, int D) {
	vector<vector<int>> adj = toAdj(edges, V);

	vector<int> visited(V);
	visited[S]=1;

	vector<int> stack, path;
	dfsVisit(adj, S, D, visited, stack, path);

	return path;
}

int main() {
	/*
	 * 4------7--
	 * |      |   \
	 * |      |    |
	 * 1------0----3
	 * |           |
	 * 2--         5
	 *    \        |
	 *     \       |
	 *      \------6
	 */

	/*
	 * 0: 1 7 3
	 * 1: 0 4 2
	 * 2: 1 6
	 * 3: 5 0 7
	 * 4: 7 1
	 * 5: 6 3
	 * 6: 5 2
	 * 7: 0 4 3
	 */

	int V = 8, S = 0, D = 5;
	vector<vector<int>> edges =
		{{0,1},{7,0},{4,7},{1,4},{6,5},{3,5},{0,3},{2,1},{3,7},{2,6}};

	cout << "Graph:" << endl;
	cout <<"4------7--" << endl;
	cout <<"|      |   \\" << endl;
	cout <<"|      |    |" << endl;
	cout <<"1------0----3" << endl;
	cout <<"|           |" << endl;
	cout <<"2--         5" << endl;
	cout <<"    \\       |" << endl;
	cout <<"      ------6" << endl;
	cout << "Adj: \n";
	vector<vector<int>> adj = toAdj(edges, V); printAdj(adj);

	cout << "\nDFS.\n";
	vector<int> path = dfs(edges, V, S, D);
	cout << "Path: ";
	for (int i : path) {cout << i << " ";} cout << endl;
	return 0;
}
