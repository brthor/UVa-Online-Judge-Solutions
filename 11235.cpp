/* UVa Problem 11235
 *
 * Frequent Values
 * http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2176
 *
 * Author: Bryan Thornbury
*/

#include <vector>
#include <math.h>
#include <stdio.h>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;

#define log2(n) log(double(n))/log(2.0)
#define MAX 200005
#define REP(i,a,b) for(int i = int(a); i<=int(b); ++i)

int start[MAX];
int ends[MAX];
int freq[MAX];
int actual[MAX];

vector<int > segmentTree; //index of max

void initSegmentTree(int _size){
	int tSize = 2*pow(2, floor(log2(_size)) + 1);
	segmentTree.resize(tSize, 0);
}

void buildSegmentTree(int arr[], int node, int left, int right){
	if(left == right){
		segmentTree[node] = left;
	}else{
		//recursively find left and right subtrees (2*i + 2*i+1 nodes)
		//go left -> left = left, right = left+right/2
		//go right -> right = right, left = left+right/2 + 1

		int leftIndex = 2*node;
		int rightIndex = 2* node + 1;
		int mid = (left+right)/2;

		buildSegmentTree(arr, 2*node, left, mid);
		buildSegmentTree(arr, 2*node +1, mid+1, right);

		int leftContent = arr[leftIndex];
		int rightContent = arr[rightIndex];

		segmentTree[node] = arr[segmentTree[2*node+1]] > arr[segmentTree[2*node]] ? segmentTree[2*node+1] : segmentTree[2*node];
	}
}

int queryTree(int arr[], int rl, int rr, int node, int left, int right){
	if(left > rr || right < rl) return -1;
	if(left >= rl && right <= rr) return segmentTree[node];

	int mid = (left + right)/2;

	int v1 = queryTree(arr, rl, rr, 2*node, left, mid);
	int v2 = queryTree(arr, rl, rr, 2*node+1, mid+1, right);

	if(v1 == -1) return v2;
	if(v2 == -1) return v1;

	return arr[v2] > arr[v1] ? v2 : v1;
}

int main(){
	//freopen("input.txt", "r", stdin);
	int n(0), q(0), e(0), p(0), f(0), pStart(0), r(0), l(0);

	while(scanf("%d %d", &n, &q) == 2){
		initSegmentTree(n);

		REP(i, 0, n-1){
			scanf("%d", &e);
			actual[i] = e;
			if(i == 0){ p = e; f = 0;}
			if(e == p) f+= 1;
			if(e != p || i == n-1){
				for(int j = i-1; j >= pStart; j--){
					ends[j] = i-1;
					freq[j] = f;
				}
				if(i == n-1){
					if(e==p) freq[i] = f;
					else freq[i] = 1;
				} 
				f = 1;
				pStart = i;
			}
			start[i] = pStart;	
			p = e;
		}

		buildSegmentTree(freq, 1, 0, n-1);

		REP(i,0,q-1){
			scanf("%d %d", &l, &r);
			r--; l--;

			if(actual[l] == actual[r]){
				printf("%d\n", r-l + 1);
				continue;
			}
			int f1 = ends[l] - l + 1;
			int f2 = r - start[r] + 1;
			int f3 = -1;
			if((start[r] - 1) > ends[l]) f3 = freq[queryTree(freq, ends[l] + 1, start[r] - 1, 1, 0, n-1)];
			printf("%d\n", max(f3,max(f1, f2)));
		}
	}

	return 0;
}