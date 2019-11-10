#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

#define endl "\n"

using namespace std;

int L, C;
char A[16];
vector<int> ind;
int aeiou[16];

bool check() {
	int cnt = 0; // 모음 개수
	int cnt2 = 0; // 자음 개수
	for (int i = 0; i < ind.size(); i++) {
		if (ind[i] == 1) {
			if (aeiou[i] == 0) { //자음
				cnt2++;
			}
			else { // 모음
				cnt++;
			}
		}
	}

	if (cnt >= 1 && cnt2 >= 2) { // 만족 조건
		return true;
	}
	else {
		return false;
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> L >> C;

	for (int i = 0; i < C; i++) {
		cin >> A[i];
	}

	sort(A, A + C);

	for (int i = 0; i < C; i++) {
		if (A[i] == 'a' || A[i] == 'e' || A[i] == 'i' || A[i] == 'o' || A[i] == 'u') {
			aeiou[i] = 1; // 모음 체크
		}
	}

	for (int i = 0; i < L; i++) {
		ind.push_back(1);
	}

	for (int i = 0; i < C - L; i++) {
		ind.push_back(0);
	}

	//sort(ind.begin(), ind.end());

	do {
		if (check()) { // 모음 1개이상 자음 2개이상
			for (int i = 0; i < ind.size(); i++) {
				if (ind[i] == 1) {
					cout << A[i];
				}
			}
			cout << endl;
		}

	} while (prev_permutation(ind.begin(), ind.end()));

}