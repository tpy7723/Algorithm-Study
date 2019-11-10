#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
	int n, v; // 숫자, 개수>

	bool operator <(const node &a) const {
		if (v == a.v) { //v 가 같다면
			return n < a.n; // n이 큰게 크다
		}
		else return v < a.v; // v 가 큰게 크다.
	}
};

int r, c, k;
int A[101][101];
int CA[101][101];
int num[101];
int max_r, max_c;
vector<node> v;

void R_search() {
	// 행탐색
	int count = 0;
	memset(CA, 0, sizeof(CA));
	for (int i = 1; i <= max_r; i++) {
		memset(num, 0, sizeof(num));

		// 해당 행의 숫자들을 카운트 함
		for (int j = 1; j <= max_c; j++) {
			num[A[i][j]]++;
		}
		// 숫자와 갯수를 벡터에 넣음
		for (int k = 1; k < 101; k++) {
			if (num[k] != 0) {
				v.push_back({ k,num[k] });
			}
		}
		// 정렬
		sort(v.begin(), v.end());

		int size_ = v.size();
		count = max(count, size_); // 최대 길이 저장
		int idx = 1;
		for (int k = 0; k < v.size(); k++) {
			CA[i][idx] = v[k].n;
			CA[i][idx + 1] = v[k].v;
			idx += 2;
		}
		v.clear();
	}

	memcpy(A, CA, sizeof(CA));
	max_c = 2 * count;
}

void C_search() {
	// 열탐색
	int count = 0;
	memset(CA, 0, sizeof(CA));
	for (int i = 1; i <= max_c; i++) {
		memset(num, 0, sizeof(num));

		for (int j = 1; j <= max_r; j++) {
			num[A[j][i]]++;
		}
		for (int k = 1; k < 101; k++) {
			if (num[k] != 0) {
				v.push_back({ k,num[k] });
			}
		}
		sort(v.begin(), v.end());
		int size_ = v.size();
		count = max(count, size_);
		int idx = 1;
		for (int k = 0; k < v.size(); k++) {
			CA[idx][i] = v[k].n;
			CA[idx + 1][i] = v[k].v;
			idx += 2;
		}
		v.clear();
	}

	memcpy(A, CA, sizeof(CA));
	max_r = 2 * count;
}

// 해당 칸이 K 인지 확인하는 함수
bool check() {
	return (CA[r][c] == k);
}

int main() {
	cin >> r >> c >> k;

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> A[i][j];
		}
	}

	memcpy(CA, A, sizeof(A)); // 배열 복사

	// 현재 행과 열의 길이
	max_r = 3;
	max_c = 3;

	int result = 0;

	while (!check()) { // K가 나올때까지
		result++; // 횟수
		if (result > 100) { // 100이 넘으면 -1 출력
			cout << -1 << endl;
			return 0;
		}
		if (max_r >= max_c) {  // 행의개수 >= 열의 개수
			R_search(); // R연산
		}
		else { // 행의개수 <= 열의 개수
			C_search(); // C연산
		}
	}
			
	cout << result << endl;

	return 0;
}