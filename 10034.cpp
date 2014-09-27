/* UVa Problem 10034
 *
 * Freckles
 *
 * Author: Bryan Thornbury
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,a,b) \
	for(int i = int(a); i <= int(b); i++)

typedef pair<double, double> ff;
typedef pair<int, int> ii;

// Union find disj set
vector<int> pset(100);
void initSet(int _size) { REP(i, 0, _size - 1) pset[i] = i; }
int findSet(int i) { return (pset[i] == i) ? i : (pset[i] = findSet(pset[i])); }
void unionSet(int i, int j) { pset[findSet(i)] = findSet(j); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

//sorted edge list
double dist(int x1, int y1, int x2, int y2){ return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); }


int main() {
	//freopen("input.txt", "r", stdin);
	int cases = 0;

	scanf("%d", &cases);

	for (int c = 1; c <= cases; c++){
		double distance = 0;
		int freckles = 0;
		scanf("%d", &freckles);
		initSet(freckles);

		vector<pair<double, ii>> edges;
		vector<ff> coords;
		double x = 0, y = 0;
		for (int f = 0; f < freckles; f++){
			scanf("%lf %lf", &x, &y);
			coords.push_back(make_pair(x, y));

			for (int j = 0; j < f;j++){
				edges.push_back(make_pair(dist(x, y, coords[j].first,coords[j].second), make_pair(f,j)));
			}
		}

		sort(edges.begin(), edges.end());

		for (vector<pair<double, ii>>::iterator it = edges.begin(); it != edges.end(); ++it){
			if (findSet(it->second.first) != findSet(it->second.second)){
				distance += it->first;
				unionSet(it->second.first, it->second.second);
			}
		}

		printf("%.2lf\n", distance);
		if(c < cases) printf("\n");
	}
	return 0;
}