w/* UVa Problem 336
 * A Node Too Far
*/

#include <stdio.h>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

#define REP(i,a,b) \
	for(int i = a; i<=b; i++)

int main(){
	//freopen("input.txt", "r", stdin);

	int NC = 0;
	int testcase = 0;
	while (true){
		scanf("%d", &NC);
		if (NC == 0)
			break;

		int nodeId = 0;
		//node num -> id
		map<int, pair<int, int>> idmap;

		//id -> node num
		map<int, pair<int,int>> nodemap;

		map<int, pair<int, int>>::iterator it;
		int numNodes = 0;

		bool edgeGraph[30][30] = { false };

		int n1, n2, id1, id2;
		REP(i, 1, NC){
			scanf("%d %d", &n1, &n2);

			it = idmap.find(n1);
			if (idmap.find(n1) != idmap.end()){
				//contains
				id1 = it->second.first;
			}
			else{
				id1 = nodeId++;
				idmap[n1] = make_pair(id1, n1);
				nodemap[id1] = make_pair(id1, n1);
				numNodes++;
			}

			it = idmap.find(n2);
			if (idmap.find(n2) != idmap.end()){
				//contains
				id2 = it->second.first;
			}
			else{
				id2 = nodeId++;
				idmap[n2] = make_pair(id2, n2);
				nodemap[id2] = make_pair(id2, n2);
				numNodes++;
			}

			edgeGraph[id1][id2] = true;
			edgeGraph[id2][id1] = true;
		}

		//Queries
		int startNode(0), ttl(0);
		while (true){
			scanf("%d %d", &startNode, &ttl);

			if (startNode == 0 && ttl == 0)
				break;

			//(nodeId, actualNum), ttl at that node
			queue<pair<pair<int, int>, int>> bfs;
			
			//visited nodes
			set<int> visited;

			bfs.push(make_pair(idmap[startNode], ttl));

			pair<pair<int, int>, int> current;
			while (!bfs.empty()){
				current = bfs.front();
				bfs.pop();

				visited.insert(current.first.first);

				if (current.second > 0){
					REP(i, 0, 29){
						if (edgeGraph[current.first.first][i] && visited.find(i) == visited.end()){
							bfs.push(make_pair(nodemap[i], current.second -1));
						}
					}
				}
			}

			printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n", ++testcase, numNodes - visited.size(), startNode, ttl);
		}

	}
	
}