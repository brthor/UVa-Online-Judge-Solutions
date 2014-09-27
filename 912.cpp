/* UVa problem 912
 * 
 * Live From Mars
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=853
 *
 * Author: Bryan Thornbury
*/

#include <stdio.h>
#include <vector>

using namespace std;

#define REP(i,a,b) \
 	for(int i = int(a); i<=int(b); i++)

vector<int> pSet(1000);
void initSet(int _size) {pSet.resize(_size); REP(i,0,_size-1) pSet[i] = i;}
int findSet(int element) {return pSet[element] == element ? element : (pSet[element] = findSet(pSet[element]));}
void unionSet(int i1, int i2) {pSet[findSet(i1)] = findSet(i2);}
bool isSameSet(int i1, int i2) {return findSet(i1) == findSet(i2);}

int main() {
	//freopen("input.txt","r", stdin);

	int size = 0;

	int A[202] = {0};
	int B[202] = {0};
	
	int testCase = 0;
	while(scanf("%d", &size) > 0){
		initSet(202);
		if(testCase > 0) printf("\n");
		testCase ++;

		//input
		int in = 0;
		char ccin = 0;
		REP(i,0,size-1){
			if(scanf("%d", &in) > 0){
				A[i] = in + 4;
			}else{
				scanf("%c", &ccin);
				if(ccin == 'A')
					A[i] = 0;
				else if(ccin == 'B')
					A[i] = 1;
				else if(ccin == 'C')
					A[i] = 2;
				else if(ccin == 'D')
					A[i] = 3;
				else{
					//printf("Fuck %c\n", ccin);
				}
			}
		}
		bool s = true;
		REP(i,0,size-1){
			if(scanf("%d", &in) > 0){
				B[i] = in + 4;
			}else{
				scanf("%c", &ccin);
				if(ccin == 'A'){
					B[i] = 0;
					//printf("is A\n");
				}
				else if(ccin == 'B'){
					B[i] = 1;
					//printf("is B\n");
				}
				else if(ccin == 'C')
					B[i] = 2;
				else if(ccin == 'D')
					B[i] = 3;
				else{
					//printf("Fuck %c\n", ccin);
				}
			}

			if(!isSameSet(A[i], B[i])){
				//if we have a natural to mutant match union sets
				if(findSet(A[i]) < 4 && findSet(B[i]) >= 4){
					unionSet(B[i], A[i]);
					//printf("Union %d, %d at index %d \n", A[i], B[i], i);
				}

				else if(findSet(B[i]) < 4 && findSet(A[i]) >= 4){
					unionSet(A[i], B[i]);
					//printf("Union %d, %d at index %d \n", A[i], B[i], i);
				}

				//if we have mutant to mutant union those
				else if(findSet(A[i]) > 4 && findSet(B[i]) > 4){
					unionSet(A[i], B[i]);
					//printf("Union %d, %d at index %d \n", A[i], B[i], i);
				}

				//natural to natural is a mis-match!
				else{
					s = false;
					//break;
				}
			}
		}

		if(s){
			int sn = 0;
			char cn='0';
			printf("YES\n");
			for(int i=4;i<pSet.size();i++){
				sn = findSet(i);
				if(sn < 4){
					if(sn == 0)
						cn='A';
					if(sn == 1)
						cn='B';
					if(sn == 2)
						cn='C';
					if(sn == 3)
						cn='D';

					printf("%d %c\n", i-4, cn);
				}
			}
		}else{
			printf("NO\n");
		}

	}



}