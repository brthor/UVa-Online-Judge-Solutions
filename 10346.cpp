/* UVa Problem 10346
 *
 * Peter's Smokes
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1287
 *
 * Author: Bryan Thornbury
*/

#include <stdio.h>

using namespace std;

int main(){
	//freopen("input.txt", "r", stdin);
	long long n(0),k(0);
	while(scanf("%lld %lld", &n, &k) == 2){
		long long cigs = n;
		long long ncigs = 0;
		long long butts = n;
		while(butts >= k){
			ncigs = butts / k;
			butts = butts % k + ncigs;
			cigs += ncigs;
		}
		printf("%lld\n", cigs);
	}
	return 0;
}

