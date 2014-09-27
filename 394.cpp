/* UVa Problem 394
 *
 * MapMaker
 *
 * Author: Bryan Thornbury
*/

#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

typedef map<string, int> msi;

struct Array {
	int dim;
	int base;
	int size;
	// char name[15];
	string name;
	int U[10];
	int L[10];
	int C0;
	int C[10];
};

int main(){
	//freopen("input.txt", "r", stdin);

	int N(0), R(0);

	//scanf("%d %d", &N, &R);
	cin >> N >> R;

	msi nameIndexMap;
	vector<Array> arrays;
	struct Array arr = {};

	for (int i = 0; i < N; i++){
		
		//scanf("%s %d %d %d", &(arr.name), &(arr.base), &(arr.size), &(arr.dim));
		cin >> arr.name;
		cin	>> arr.base >> arr.size >> arr.dim;
		
		for (int d = 0; d < arr.dim; d++)
			//scanf("%d %d", &(arr.L[d]), &(arr.U[d]));
			cin >> arr.L[d] >> arr.U[d];

		//calculate constants
		arr.C[arr.dim-1] = arr.size;
		arr.C0 = arr.base - (arr.C[arr.dim-1]*arr.L[arr.dim-1]);
		for (int j = arr.dim - 2; j >= 0; j--){
			arr.C[j] = (arr.C[j+1])*(arr.U[j+1] - arr.L[j+1] + 1);
			arr.C0 = arr.C0 - (arr.C[j] * arr.L[j]);
		}
		
		//string n(arr.name);
		nameIndexMap[arr.name] = i;
		arrays.push_back(arr);
	}

	string arrName;
	int indice(0);
	long long address(0);
	for (int i = 0; i < R; i++){
		//scanf("%s", name);
		//string n(name);
		cin >> arrName;
		indice = nameIndexMap[arrName];

		//printf("%s[", name);
		cout << arrName << "[";

		arr = arrays[indice];
		address = arr.C0;
		for (int j = 0; j < arr.dim; j++){
			//scanf("%d", &(indice));
			cin >> indice;
			address += arr.C[j] * indice;

			cout << indice;
			if (j != (arr.dim - 1)){
				//printf("%d, ", indice);
				cout << ", ";

			}
			else{
				//printf("%d]", indice);
				cout << "]";
			}
		}

		//rintf(" = %lld\r\n", address);
		cout << " = " << address << endl;

	}

	return 0;
}