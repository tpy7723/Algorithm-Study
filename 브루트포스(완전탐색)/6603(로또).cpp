#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool desc(int a, int b) {
	return a > b;
}

void combi(vector<int> *n) {
	vector<int> ind;

	int k = 6;

	for (int i = 0; i < k; i++) {
		ind.push_back(1);
	}
	
	for (int i = 0; i < n->size() - k; i++) {
		ind.push_back(0);
	}

	// 정렬
	sort(ind.begin(), ind.end(), desc);

	//순열
	do {
		//// 출력
		for (int i = 0; i < ind.size(); i++) {
			if (ind[i] == 1) {
				printf("%d ", ((*n)[i]));
			}
		}
		printf("\n");
	} while (prev_permutation(ind.begin(), ind.end()));
}

int main() {
	int k;
	while (cin >> k && k != 0) {
		vector<int> *v = new vector<int>;
		int value;

		for (int i = 0; i < k; i++) {
			scanf("%2d", &value);
			v->push_back(value);
		}

		combi(v);

		delete v;
		cout << endl;
	}
	
	return 0;
}