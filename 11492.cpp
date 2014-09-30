/* UVa Problem 11492
 *
 * Babel
 * http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2487
 *
 * Author: Bryan Thornbury
*/
/*
 map lang to vector of tuple<wordid, initial letter, length> (sorted by length)
array of tuple<word(string), vector languages> (index is wordID)

find shortest path from each of the initial language words to each of the target language words and take the one with minimal cost

Instead of doing path from each initial to each target, start with smallest words in each language as initial and target. Change initial and target based on lowest increase in cost. First found is the minimum path. GREEDY
*/

#include <stdio.h>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <string>

using namespace std;

#define REP(i,a,b) \
	for(int i = int(a); i<=int(b); i++)

typedef pair<int, int> ii;

map<string, vector<ii > > lang; //cost, wordid

pair<string, vector<string> > words[2005];

int dist[2005]; //cost

void initialize(int wordCount){
	REP(i,0,wordCount-1) dist[i] = -1;
}

int findShortestPath(int totalCount, string iLang, string tLang){
	initialize(totalCount);

	vector<ii >::iterator it;
	vector<string>::iterator sIt;


	priority_queue<ii, vector<ii>, greater<ii> > next; //cost, wordID

	for(it = lang[iLang].begin(); it != lang[iLang].end(); ++it){
		dist[(*it).second] = (*it).first;
		next.push(ii(dist[(*it).second],(*it).second));
	}

	string cLang = iLang;
	int cost(0), word(0);

	while(!next.empty()){
		ii top = next.top(); next.pop();
		cost = top.first;
		word = top.second;
		char initial = words[word].first.at(0);

		for(sIt = words[word].second.begin(); sIt != words[word].second.end(); ++sIt)
		{
			if(*sIt != cLang){
				cLang = *sIt;
				break;
			}
		}


		int nextWord(0), nextCost(0);
		char nextInitial = '0';

		//printf("it %s %d %d \n", words[word].first.c_str(), words[word].first.size(), dist[word]);

		if(find(words[word].second.begin(), words[word].second.end(), tLang) != words[word].second.end()){
			break;
		}

		if(cost == dist[word]){
			for(sIt = words[word].second.begin(); sIt != words[word].second.end(); ++sIt){
				for(it = lang[*sIt].begin(); it !=  lang[*sIt].end(); ++it){
					nextWord = (*it).second;
					nextCost = (*it).first;
					nextInitial = words[nextWord].first[0];

					//Only to words without the same initial character
					if(nextInitial != initial){
						if(dist[nextWord] == -1 || dist[nextWord] > (dist[word] + nextCost)){
							//printf("This word: %s, Cost %s %d\n", words[word].first.c_str(), words[nextWord].first.c_str(), dist[nextWord]);
							dist[nextWord] = dist[word] + nextCost;
							//printf("This word: %s, Cost %s %d\n", words[word].first.c_str(), words[nextWord].first.c_str(), dist[nextWord]);
							next.push(ii(dist[nextWord], nextWord));
						}
					}
				}
			}
		}
	}

	if(find(words[word].second.begin(), words[word].second.end(), tLang) != words[word].second.end()){
		return dist[word];
	}else{
		return -1;
	}
}


int main(){
	//freopen("input.txt", "r", stdin);

	char lang1[52], lang2[52], word[52];
	int count;
	string iLang, tLang;

	while(scanf("%d", &count) == 1 && count > 0){
		lang.clear();
		int wId = 0;
		scanf("%s %s", lang1, lang2);
		string iLang(lang1), tLang(lang2);

		REP(i,1,count){
			scanf("%s %s %s", lang1, lang2, word);
			string l1(lang1), l2(lang2), w(word);

			vector<string> v;
			v.push_back(l1);
			v.push_back(l2);
			words[wId] = make_pair(w, v);
			lang[lang1].push_back(ii(w.size(), wId));
			lang[lang2].push_back(ii(w.size(), wId));
			wId ++;
		}

		//sort vector in map
		map<string, vector<ii > >::iterator it;
		for(it = lang.begin(); it != lang.end(); ++it){
			sort(lang[(*it).first].begin(), lang[(*it).first].end());
		}

		int d = findShortestPath(count, iLang, tLang);
		if(d != -1){
			printf("%d\n", d);
		}else{
			printf("impossivel\n");
		}
	}
}