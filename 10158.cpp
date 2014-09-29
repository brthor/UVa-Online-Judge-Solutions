/* UVa Problem 10158
 *
 * War
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1099
 *
 * Author: Bryan Thornbury
*/

 #include <stdio.h>
 #include <set>
 #include <vector>


 using namespace std;

 #define REP(i,a,b) \
 	for(int i = int(a); i <= int(b); i++)

vector<int> pSet(1000);
void initSet(int _size) { pSet.resize(_size); REP(i,0,_size-1) pSet[i] = i; }
int findSet(int i) { return pSet[i] == i ? i : (pSet[i] = findSet(pSet[i]));}
void unionSets(int i , int j) { pSet[findSet(i)] = findSet(j); }
bool isSameSet(int i , int j) { return findSet(i) == findSet(j); }

vector<int> enemies(10000);

bool setEnemies(int i, int j);

bool areFriends(int i, int j){
	if(i==j) return true;
	return isSameSet(i,j);
}

bool areEnemies(int i, int j){
	return enemies[findSet(i)] == findSet(j) || enemies[findSet(j)] == findSet(i);
}

bool setFriends(int i, int j){
	if(areFriends(i,j)) return true;
	if(areEnemies(i,j)) return false;

	int rooti = findSet(i);
	int rootj = findSet(j);

	unionSets(i,j);

	int ni = findSet(i);
	int nj = findSet(j);

	if(rooti != ni && enemies[rooti] != -1){
		if(enemies[ni] != -1){
			setFriends(enemies[ni], enemies[rooti]);
		}
		enemies[ni] = findSet(enemies[rooti]);
		enemies[rooti] = -1;
	}

	if(rootj != ni && enemies[rootj] != -1){
		if(enemies[nj] != -1){
			setFriends(enemies[nj], enemies[rootj]);
		}
		enemies[nj] = findSet(enemies[rootj]);
		enemies[rootj] = -1;
	}

	return true;
}

bool setEnemies(int i, int j){
	if(areFriends(i,j)) return false;

	if(enemies[findSet(i)] != -1){
		setFriends(enemies[findSet(i)],j);
	}

	if(enemies[findSet(j)] != -1){
		setFriends(enemies[findSet(j)],i);
	}

	enemies[findSet(i)] = findSet(j);
	enemies[findSet(j)] = findSet(i);

	return true;
}



int main() {
	//freopen("input.txt", "r", stdin);
	int people = 0;

	scanf("%d", &people);
	initSet(people);

	REP(i,0,people-1){
		enemies.resize(people);
		enemies[i] = -1;
	}

	int op(0), p1(0), p2(0);

	bool result = false;
	int testcase = 0;
	int m = 0;

	while(scanf("%d %d %d", &op, &p1, &p2) == 3 && op > 0){
		
		if(op < 1 || op > 4 || p1 < 0 || p1 >= people || p2 < 0 || p2 >= people){
			printf("-1\n");
			continue;
		}

		if(op == 1){
			if(!setFriends(p1,p2)){
				printf("-1\n");
			}
		}else if(op == 2){
			if(!setEnemies(p1,p2)){
				printf("-1\n");
			}
		}else if(op == 3){
			if(areFriends(p1,p2)){
				printf("1\n");
			}else{
				printf("0\n");
			}
		}else if(op == 4){
			if(areEnemies(p1,p2)){
				printf("1\n");
			}else{
				printf("0\n");
			}
		}
	}
	return 0;
}



