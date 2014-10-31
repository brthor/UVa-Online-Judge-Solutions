/* UVa Problem 11402
 *
 * Ahoy Pirates
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2397
 *
 * Author: Bryan Thornbury
*/
#include <stdio.h>
#include <cmath>
#include <vector>

#define MAX 2048000
#define REP(i,a,b) for(int i = int(a); i<= int(b); ++i)
#define log2(a) log(double(a))/log(2.0)

#define FLIP 2
#define DEFAULT -1

using namespace std;

vector<int> sTree;
vector<int> lazy;

void initTree(int _size){
	int count = 2 * pow(2, floor(log2(_size)) + 1);

	sTree.resize(count);
	lazy.resize(count, DEFAULT);
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

int queryTree(int rangeLeft, int rangeRight, int searchLeft, int searchRight, int node){
	int mid = (searchLeft + searchRight) / 2;
	int leftIndex = 2 * node;
	int rightIndex = 2 * node + 1;

	//If this node needs to be updated, update it
	if(lazy[node] > DEFAULT){
		if(searchLeft != searchRight){
			if(lazy[leftIndex] == FLIP && lazy[node] == FLIP)
				lazy[leftIndex] = DEFAULT;
			else if(lazy[node] == FLIP && lazy[leftIndex] > DEFAULT)
				lazy[leftIndex] = 1 - lazy[leftIndex];
			else
				lazy[leftIndex] = lazy[node];

			if(lazy[rightIndex] == FLIP && lazy[node] == FLIP)
				lazy[rightIndex] = DEFAULT;
			else if(lazy[node] == FLIP && lazy[rightIndex] > DEFAULT)
				lazy[rightIndex] = 1 - lazy[rightIndex];
			else
				lazy[rightIndex] = lazy[node];
		}

		if(lazy[node] == FLIP){
			sTree[node] = (searchRight - searchLeft + 1) - sTree[node];
		}else{
			sTree[node] = lazy[node] * (searchRight - searchLeft + 1);
		}

		lazy[node] = DEFAULT;
	}

	if(searchLeft > rangeRight || searchRight < rangeLeft) return 0;
	if(searchLeft >= rangeLeft && searchRight <= rangeRight){
		return sTree[node];
	}

	int leftVal = queryTree(rangeLeft, rangeRight, searchLeft, mid, leftIndex);
	int rightVal = queryTree(rangeLeft, rangeRight, mid + 1, searchRight, rightIndex);

	return leftVal + rightVal;
}

void updateTree(int rangeLeft, int rangeRight, int searchLeft, int searchRight, int set, int node){
	int mid = (searchLeft + searchRight)/2;

	int leftIndex = 2 * node;
	int rightIndex = 2 * node + 1;

	//If this node needs to be updated, update it
	if(lazy[node] > DEFAULT){
		if(searchLeft != searchRight){
			if(lazy[leftIndex] == FLIP && lazy[node] == FLIP)
				lazy[leftIndex] = DEFAULT;
			else if(lazy[node] == FLIP && lazy[leftIndex] > DEFAULT)
				lazy[leftIndex] = 1 - lazy[leftIndex];
			else
				lazy[leftIndex] = lazy[node];

			if(lazy[rightIndex] == FLIP && lazy[node] == FLIP)
				lazy[rightIndex] = DEFAULT;
			else if(lazy[node] == FLIP && lazy[rightIndex] > DEFAULT)
				lazy[rightIndex] = 1 - lazy[rightIndex];
			else
				lazy[rightIndex] = lazy[node];
		}

		if(lazy[node] == FLIP){
			sTree[node] = (searchRight - searchLeft + 1) - sTree[node];
		}else{
			sTree[node] = lazy[node] * (searchRight - searchLeft + 1);
		}

		lazy[node] = DEFAULT;
	}

	//Out of range
	if(searchLeft > rangeRight || searchRight < rangeLeft) return;

	//Leaf Node
	if(searchLeft == searchRight){
		if(set == FLIP){
			sTree[node] = 1 - sTree[node];
		}else{
			sTree[node] = set;
		}
		return;
	}

	//Interval node in range
	if(searchLeft >= rangeLeft && searchRight <= rangeRight){
		//Set children as lazy
		if(lazy[leftIndex] == FLIP && set == FLIP)
			lazy[leftIndex] = DEFAULT;
		else if(set == FLIP && lazy[leftIndex] > DEFAULT)
			lazy[leftIndex] = 1 - lazy[leftIndex];
		else
			lazy[leftIndex] = set;

		if(lazy[rightIndex] == FLIP && set == FLIP)
			lazy[rightIndex] = DEFAULT;
		else if(set == FLIP && lazy[rightIndex] > DEFAULT)
			lazy[rightIndex] = 1 - lazy[rightIndex];
		else
			lazy[rightIndex] = set;


		if(set == FLIP){
			sTree[node] = (searchRight - searchLeft + 1) - sTree[node];
		}else{
			sTree[node] = set * (searchRight - searchLeft + 1);
		}

		return;
	}


	updateTree(rangeLeft, rangeRight, searchLeft, mid, set, leftIndex);
	updateTree(rangeLeft, rangeRight, mid+1, searchRight, set , rightIndex);

	sTree[node] = sTree[leftIndex] + sTree[rightIndex];
}

bool pirates[MAX + 5];

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int T(0), M(0), p(0), Q(0), l(0), r(0),sT(0);
	char op = '0';
	char pStr[1005];

	scanf("%d", &T);

	REP(caseNum, 1, T){
		scanf("%d", &M);

		int index = 0;
		while(M-- > 0){
			scanf("%d %s", &sT, pStr);

			REP(j,0,sT-1){
				REP(i,0,1000){
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
				updateTree(l, r, 0, size-1, 1, 1);
			}else if(op == 'E'){
				//l - r to 0
				updateTree(l, r, 0, size-1, 0, 1);
			}else if(op == 'I'){
				//l - r flip
				updateTree(l, r, 0, size-1, FLIP, 1);
			}else if(op == 'S'){
				//l - r sum
				if(queries > 0) printf("\n");
				printf("Q%d: %d", ++queries, queryTree(l, r, 0, size-1, 1));
			}
		}
	}
	return 0;
}