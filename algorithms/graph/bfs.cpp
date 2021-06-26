#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void printPath(vector<int> v)
{ for (int i : v) {cout << i << " ";} cout << endl; }

void printQ(queue<int> q)
{
	cout << "[";
	while (!q.empty()) {
		int e = q.front(); q.pop();
		if (q.empty())
			cout << e;
		else
			cout << e << " ";
	}
	cout << "]\n";
}

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

vector<int> makePath(vector<int> const& path, int D)
{
	vector<int> result;
	while (D!=-1) {
		result.push_back(D);
		D = path[D];
	}
	reverse(result.begin(), result.end());
	return result;
}

vector<int> bfs(vector<vector<int>> const& edges, int V, int S, int D)
{
	vector<vector<int>> adj = toAdj(edges, V);

	vector<int> path(V,-1);
	vector<int> visited(V);

	queue<int> q; q.push(S);

	while (!q.empty()) {
		int u = q.front(); q.pop();

		if (u == D) break;
		if (visited[u]) continue;

		for (int v : adj[u]) {
			if (!visited[v]) {
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

	vector<vector<int>> adj = toAdj(edges, V);
	cout << "Adj: \n"; printAdj(adj);

	cout << "\nBFS.\n";
	vector<int> path = bfs(edges, V, S, D);
	cout << "Path: "; printPath(path);

	return 0;
}
