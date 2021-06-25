#include <vector>
#include <queue>
#include <iostream>

using namespace std;

#define vi vector<int>
#define vvi vector<vi>

// ============= Utility ===============
vvi toAdj(vvi const& edges, int V, bool directed = false) {
	vvi adj(V);

	for (auto uv : edges) {
		adj[uv[0]].push_back(uv[1]);
		if (!directed)
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

vi makePath(vi const& path, int D) {
	vi result;
	while (D!=-1) {
		result.push_back(D);
		D = path[D];
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

// =================SCC=======================
void strongconnect(
		int v,
		int& idx,
		vvi const& adj,
		vi& index,
		vi& lowlink,
		vi& visited,
		vi& onStack,
		vi& stack,
		vi& SCC,
		vvi& SCCS)
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
vvi tarjan(vvi edges, int V) {
	vvi adj = toAdj(edges, V, true);

	vvi SCCS; vi SCC;
	vi stack, index(V), lowlink(V), onStack(V), visited(V);
	int idx = 0;
	for (int v = 0; v < V; ++v) {
		if (!visited[v]) {
			strongconnect(v, idx, adj, index, lowlink, visited, onStack, stack, SCC, SCCS);
		}
	}
	return SCCS;
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
	vector<vi> edges = {{0,1},{7,0},{4,7},{1,4},{6,5},{3,5},{0,3},{2,1},{3,7},{2,6}};

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

	cout << "\nTarjan.\n";
	{
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
		vvi edges = {{0,2},{2,1},{1,0},{3,2},{3,1},{3,6},{6,3},{6,4},{4,1},{4,5},{5,4},{7,6},{7,5},{7,7}};
		cout << "SCC: \n";
		vvi SCC = tarjan(edges, V);
		printAdj(SCC);
	}

	return 0;
}
