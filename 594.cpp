/**
 * uVA Online Judge Problem 594
 * 
 *
*/
#include <iostream>
#include <bitset>
#include "stdio.h"

#define REP(i, a, b) \
 	for(int i = a; i<=b; i++)

using namespace std;

int getOtherEndian(int original) {
	bitset<32> b(original);
	bool t;
	int k = 24;
	REP(i, 0, 7) {
		t = b[i];
		b[i] = b[k+i];
		b[k+i] = t;
	}

	k = 16;
	REP(i, 8, 15){
		t = b[i];
		b[i] = b[k+i];
		b[k+i] = t;
	}

	return (int)b.to_ulong();
}

int main(){
	int n = 0;
	bitset<32> h (16777216);
	cout << h<< endl;
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	while(scanf("%d", &n) > 0){
		printf("%d converts to %d\n",n,  getOtherEndian(n));
	}
	return 0;
}