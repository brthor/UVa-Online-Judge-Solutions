/* UVa Problem 352
 *
 * The Seasonal War
 *
 * Author: Bryan Thornbury
*/
#include <stdio.h>
#include <map>
#include <vector>

using namespace std;

#define REP(i,a,b) \
	for(int i = int(a); i<=int(b); i++)





void floodfill(pair<int, int> v, vector<pair<int, int> > e[][25], int pixels[][25], int color){
	pixels[v.first][v.second] = color;

	for (vector<pair<int, int> >::iterator it = e[v.first][v.second].begin(); it != e[v.first][v.second].end(); ++it){
		pair<int, int> p = (*it);
		if (pixels[it-> first][it-> second] == 1)
			floodfill((*it), e,pixels, color);
	}
}

int main() {
	//freopen("input.txt", "r", stdin);

	int dim =0;
	int in = 0;
	int testCase = 0;
	while (scanf("%d", &dim) > 0){
		//if(testCase > 0) printf("\n");

		int pixels[25][25] = { 0 };
		REP(i, 0, dim - 1){
			REP(j, 0, dim - 1){
				scanf("%1d", &in);
				pixels[i][j] = in;
			}
		}

		///Construct adjacency list
		vector<pair<int, int> > adj[25][25];
		REP(i, 0, dim - 1){
			REP(j, 0, dim - 1){
				adj[i][j] = vector<pair<int, int> >(2);
				if (pixels[i][j]){
					if (i > 0){
						//up?
						if (pixels[i - 1][j])
							adj[i][j].push_back(make_pair(i - 1, j));

						//up-left? + left?
						if (j > 0){
							if (pixels[i - 1][j - 1])
								adj[i][j].push_back(make_pair(i - 1, j - 1));

							
						}

						//up-right + right?
						if (j < (dim - 1)){
							if (pixels[i - 1][j + 1])
								adj[i][j].push_back(make_pair(i - 1, j + 1));

							
						}
					}

					//left
					if(j > 0){
						if (pixels[i][j - 1])
								adj[i][j].push_back(make_pair(i, j - 1));
					}

					//right
					if(j < (dim-1)){
						if (pixels[i][j + 1])
								adj[i][j].push_back(make_pair(i, j + 1));
					}

					//down
					if (i < (dim - 1)){
						if (pixels[i + 1][j]){
							adj[i][j].push_back(make_pair(i + 1, j));
						}
						if (j > 0){
							if (pixels[i + 1][j - 1])
								adj[i][j].push_back(make_pair(i + 1, j - 1));
						}

						if (j < (dim - 1)){
							if (pixels[i + 1][j + 1])
								adj[i][j].push_back(make_pair(i + 1, j + 1));
						}
					}
				}
			}
		}
		

		//END Construct adj
		int cCount = 0;

		REP(i, 0, dim - 1){
			REP(j, 0, dim - 1){
				if (pixels[i][j] == 1){
					floodfill(make_pair(i, j), adj,pixels, (++cCount) + 2);
					//printf("%d %d\n", i,j);
				}
			}
		}

		printf("Image number %d contains %d war eagles.\n", ++testCase, cCount);
	}
	return 0;
}