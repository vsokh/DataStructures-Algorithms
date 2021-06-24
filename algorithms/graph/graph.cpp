#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define vvi vector<vi>

// ============= Utility ===============
vvi toAdj(vvi const& edges, int V) {
	vvi adj(V);

	for (auto uv : edges) {
		adj[uv[0]].push_back(uv[1]);
		adj[uv[1]].push_back(uv[0]);
	}
	return adj;
}

void printAdj(vvi const& adj) {
	for (int u = 0; u < adj.size(); ++u) {
		cout << u << ": ";
		for (int v = 0; v < adj[u].size(); ++v) {
			cout << adj[u][v] << " ";
		}
		cout << endl;
	}
}

vi makePath(vi const& path, int D)
{
	vi result;
	int v = D;
	while (v!=-1) {
		result.push_back(v);
		v = path[v];
	}
	reverse(result.begin(), result.end());
	return result;
}

void printV(vi v)
{ for (int i : v) {cout << i << " ";} cout << endl; }

void printQ(queue<int> q) {
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

// =====================================

// ============= Single Source ===============
vi BFS(vvi edges, int V, int S, int D) {
	vvi adj = toAdj(edges, V);

	vi path(V,-1);
	vi visited(V);

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

void DFSVisit(vvi const& adj, int u, int D, vi visited, vi stack, vi& path) {
	visited[u] = 1;
	stack.push_back(u);

	if (u == D) {
		path = path.empty() || stack.size() < path.size() ? stack : path;
		return;
	}

	for (int v : adj[u]) {
		if (!visited[v])
			DFSVisit(adj, v, D, visited, stack, path);
	}

	stack.pop_back();
}

vi DFS(vvi edges, int V, int S, int D) {
	vvi adj = toAdj(edges, V);

	vi visited(V);
	visited[S]=1;

	vi stack, path;
	DFSVisit(adj, S, D, visited, stack, path);

	return path;
}

vi IDFS(vvi edges, int V, int S, int D) {
	vvi adj = toAdj(edges, V);
	vi path, tmpPath;
	vi visited(V); visited[S]=1;
	vi stack; stack.push_back(S);
	while (!stack.empty()) {
		int u = stack.back();

		if (visited[u]==2) {
			stack.pop_back();
			continue;
		}

		tmpPath.push_back(u);
		if (u == D) {
			path = path.empty() || tmpPath.size() < path.size() ? tmpPath : path;
			tmpPath.clear();
			stack.pop_back();
			continue;
		}

		for (int v : adj[u]) {
			if (!visited[v]) {
				visited[v]=1;
				stack.push_back(v);
			}
		}
		visited[u]=2;
	}
	return path;
}
// ===========================================

int main() {
	int V = 8, S = 0, D = 5;
	vector<vi> edges = {{0,1},{7,0},{4,7},{1,4},{6,5},{3,5},{0,3},{2,1},{3,7}, {2,6}};
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
	  0: 1 7 3
	  1: 0 4 2
	  2: 1 6
	  3: 5 0 7
	  4: 7 1
	  5: 6 3
	  6: 5 2
	  7: 0 4 3
	*/

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
	vvi adj = toAdj(edges, V); printAdj(adj);

	cout << "\nBFS.\n";
	{
		vi path = BFS(edges, V, S, D);
		cout << "Path: ";
		for (int i : path) {cout << i << " ";} cout << endl;
	}

	cout << "\nDFS.\n";
	{
		vi path = DFS(edges, V, S, D);
		cout << "Path: ";
		for (int i : path) {cout << i << " ";} cout << endl;
	}

	cout << "\nIDFS.\n";
	{
		vi path = IDFS(edges, V, S, D);
		cout << "Path: ";
		for (int i : path) {cout << i << " ";} cout << endl;
	}

	//TODO:
	// 1. Bellman-Ford
	// 2. Dijkstra
	// 3. Floyd-Warshall
	// 4. Tarjan
	return 0;
}
