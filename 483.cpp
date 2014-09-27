/* UVa Problem 483
 *
 * Word Scramble
 *
 * Author: Bryan Thornbury
*/

#include "stdio.h"
#include <stack>

using namespace std;

stack<char> pStack;


void printStack(){
	while(!pStack.empty()){
		printf("%c", pStack.top());
		pStack.pop();
	}
}

int main() {
	char inp;
	char out;
	while(scanf("%c", &inp) > 0){
		if(inp != ' ' && inp != '\n' && inp != '\t'){
			pStack.push(inp);
		}else{
			printStack();
			printf("%c", inp);
		}
	}

	printStack();

	return 0;
}
