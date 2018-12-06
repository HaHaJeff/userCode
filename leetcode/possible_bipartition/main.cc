#include <vector>
#include <iostream>
#include <map>
using namespace std;

class Solution {
public:
	bool possibleBipartition(int N, vector<vector<int>>& dislikes) {


		for (auto edge : dislikes) {
			graph[edge[0]].push_back(edge[1]);
		//	graph[edge[1]].push_back(edge[0]);
		}

		for (auto p : graph) {
			if (visited.find(p.first) == visited.end() && !dfs(p.first, 0)) {
				return false;
			}
		}

		return true;
	} 

	bool dfs(int node, int color) {
		if (visited.find(node) != visited.end()) {
			return visited[node] == color;
		}

		//标记为已经访问过
		visited[node] = color;
		// 判断每一条边
		for (auto eNode : graph[node]) {
			if (!dfs(eNode, 1^color)) {
				return false;
			}
		}
		return true;
	}

private:
	// first means nodeid, second means edge
	std::map<int, vector<int>> graph;
	// first means nodeid, second means color
	std::map<int, int> visited;
};

int main()
{
	Solution sol;

	vector<vector<int>> dislikes = { { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 1, 5 } };

	std::cout << sol.possibleBipartition(5, dislikes) << std::endl;
}
