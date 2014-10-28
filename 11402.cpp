/* UVa Problem 11402
 *
 * Frequent Values
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2397
 *
 * Author: Bryan Thornbury
*/
#include <stdio.h>
#include <cmath>
#include <vector>

#define MAX 1024000
#define REP(i,a,b) for(int i = int(a); i<= int(b); ++i)
#define log2(a) log(double(a))/log(2.0)

using namespace std;

vector<int> sTree;

void initTree(int _size){
	int count = 2 * pow(2, floor(log2(_size)) + 1);

	sTree.resize(count);
}

void buildTree(bool arr[], int lb, int rb, int node){
	if(lb == rb){
		sTree[node] = arr[lb];
		return;
	}

	int leftIndex = 2 * node;
	int rightIndex = 2 * node + 1;

	int mid = (lb + rb) / 2;

	buildTree(arr, lb, mid, leftIndex);
	buildTree(arr, mid + 1, rb, rightIndex);

	//range sum
	sTree[node] = sTree[leftIndex] + sTree[rightIndex];

	return;
}

int queryTree(bool arr[], int rangeLeft, int rangeRight, int searchLeft, int searchRight, int node){
	if(searchLeft > rangeRight || searchRight < rangeLeft) return 0;
	if(searchLeft >= rangeLeft && searchRight <= rangeRight){
		return sTree[node];
	}

	int mid = (searchLeft + searchRight) / 2;
	int leftIndex = 2 * node;
	int rightIndex = 2 * node + 1;

	int leftVal = queryTree(arr, rangeLeft, rangeRight, searchLeft, mid, leftIndex);
	int rightVal = queryTree(arr, rangeLeft, rangeRight, mid + 1, searchRight, rightIndex);

	return leftVal + rightVal;
}

void updateTree(bool arr[], int rangeLeft, int rangeRight, int searchLeft, int searchRight, bool flip, bool set, int node){
	if(searchLeft > rangeRight || searchRight < rangeLeft) return;

	if(searchLeft == searchRight){
		if(flip){
			sTree[node] = !arr[searchLeft];
			arr[searchLeft] = !arr[searchLeft];
		}else{
			sTree[node] = (int)set;
			arr[searchLeft] = set;
		}
		return;
	}

	int mid = (searchLeft + searchRight)/2;

	int leftIndex = 2 * node;
	int rightIndex = 2 * node + 1;

	updateTree(arr, rangeLeft, rangeRight, searchLeft, mid, flip, set, leftIndex);
	updateTree(arr, rangeLeft, rangeRight, mid+1, searchRight, flip, set, rightIndex);

	sTree[node] = sTree[leftIndex] + sTree[rightIndex];
}

bool pirates[MAX + 5];

int main() {
	//freopen("input.txt", "r", stdin);
	int T(0), M(0), p(0), Q(0), l(0), r(0),sT(0);
	char op = '0';
	char pStr[55];

	scanf("%d", &T);

	REP(caseNum, 1, T){
		scanf("%d", &M);

		int index = 0;
		while(M-- > 0){
			scanf("%d %s", &sT, pStr);

			REP(j,0,sT-1){
				REP(i,0,49){
					if(pStr[i] == '\0') break;
					pirates[index] = (pStr[i] == '1');
					index += 1;
				}
			}
		}

		int size = index;

		initTree(size);
		buildTree(pirates, 0, size - 1, 1);

		scanf("%d", &Q);
		int queries = 0;

		printf("Case %d:\n", caseNum);
		REP(i,1, Q){
			scanf(" %c %d %d", &op, &l, &r);

			if(op == 'F'){
				//l - r to 1
				updateTree(pirates, l, r, 0, size-1, false, true, 1);
			}else if(op == 'E'){
				//l - r to 0
				updateTree(pirates, l, r, 0, size-1, false, false, 1);
			}else if(op == 'I'){
				//l - r flip
				updateTree(pirates, l, r, 0, size-1, true, true, 1);
			}else if(op == 'S'){
				//l - r sum
				printf("Q%d: %d\n", ++queries, queryTree(pirates, l, r, 0, size-1, 1));
			}
		}
	}
	return 0;
}