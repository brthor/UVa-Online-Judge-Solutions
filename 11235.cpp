/* UVa Problem 11235
 *
 * Frequent Values
 * http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2176
 *
 * Author: Bryan Thornbury
*/

#include <vector>
#include <cmath>
#include <stdio.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii > vii;

#define MAX 200000
#define log2(n) log(double(n))/log(2.0)
#define REP(i,a,b) for(int i = int(a); i<=int(b); ++i)

int start[MAX];
int elemEnd[MAX];

vector<int> sTree;

void initTree(int _size){
	int count = 2*pow(2,floor(log2(_size)) + 1);
	sTree.resize(count);
}

void buildTree(vector<int> &values, int lb, int rb, int node){
	if(lb == rb){
		sTree[node] = lb;
		return;
	}

	int mid = (lb + rb)/2;

	int leftIndex = node*2;
	int rightIndex = node*2 + 1;

	buildTree(values, lb, mid, leftIndex);
	buildTree(values, mid+1, rb, rightIndex);

	int leftValue = values[sTree[leftIndex]];
	int rightValue = values[sTree[rightIndex]];

	sTree[node] = leftValue > rightValue ? sTree[leftIndex] : sTree[rightIndex];
}

int rangeMaxQuery(vector<int> &values, int rangeLeft, int rangeRight, int searchLeft, int searchRight, int node){
	if(rangeLeft > searchRight || rangeRight < searchLeft) return -1;
	if(searchLeft >= rangeLeft && searchRight <= rangeRight) return sTree[node];

	int mid = (searchLeft + searchRight)/2;

	int leftIndex = node*2;
	int rightIndex = node*2 + 1;

	int leftMax = rangeMaxQuery(values, rangeLeft, rangeRight, searchLeft, mid, leftIndex);
	int rightMax = rangeMaxQuery(values, rangeLeft, rangeRight, mid+1, searchRight, rightIndex);

	if(leftMax == -1) return rightMax;
	if(rightMax == -1) return leftMax;

	int leftValue = values[leftMax];
	int rightValue = values[rightMax];

	return leftValue > rightValue ? leftMax : rightMax;
}

int main() {
	//freopen("input.txt", "r", stdin);
	int n(0), q(0), c(0), p(0), f(0);

	while(scanf("%d %d", &n, &q) == 2 && n != 0){
		vector<int> fArr(n);
		vector<int> values(n);
		REP(i,0,n-1){
			scanf("%d", &c);

			values[i] = c;

			if(i == 0){
				start[i] = i;
			}else if(c != p){
				for(int j = i-1; j >= start[i-1]; j--){
					fArr[j] = f;
					elemEnd[j] = i-1;
				}
				f = 0;
				start[i] = i;
			}else{
				start[i] = start[i-1];
			}
			f+=1;
			p = c;

			if(i == n-1){
				for(int j = i; j >= start[i]; j--){
					fArr[j] = f;
					elemEnd[j] = i;
				}
			}
		}

		initTree(n);
		buildTree(fArr,0,n-1, 1);

		REP(i,0,q-1){
			//re use p and f
			scanf("%d %d", &p, &f);
			f--;p--;
			//Case 1, same element
			if(values[p] == values[f]){
				printf("%d\n", f-p + 1);
			}

			else{
				int segment1 = elemEnd[p] - p + 1;
				int segment2 = f - start[f] + 1;

				if(start[f] - elemEnd[p] > 1){
					int segment3 = fArr[rangeMaxQuery(fArr,elemEnd[p] + 1, start[f] - 1, 0, n-1, 1)];
					printf("%d\n", max(segment3, max(segment1, segment2)));
				}else{
					printf("%d\n", (segment2 > segment1 ? segment2 : segment1));
				}
			}
		}
	}
}