#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <string>

using namespace std;

deque<char> dq; // 앞뒤로 넣었다 뻈다 용이함
vector<string> v;
int T, N, K;
string A;

void move() { // 원형 이동
	int temp = dq.back();
	dq.pop_back();
	dq.push_front(temp);
}

// 16진수 문자열을 10진수 값으로 바꾸기
long long hexa2dec(string a) {
	long long sum = 0;
	int m = 1;
	int size_ = a.length() - 1; // 문자열 마지막 인덱스
	for (int i = size_; i >= 0; i--) {
		if (a[i] >= 'A') a[i] = (a[i] - 'A') + 10;
		else if (a[i] >= '0') a[i] = a[i] - '0';
		sum += (a[i] * m);
		m *= 16;
	}
	return sum;
}

int main() {
	cin >> T;

	int tc = 1;
	while (T--) {
		cin >> N >> K;
		cin >> A;

		int R = N / 4; // 회전해야하는 횟수, 한면의 값 개수

		for (int i = 0; i < A.length(); i++) {
			dq.push_back(A[i]);
		}

		for (int i = 0; i < R; i++) {
			move(); // 회전
			string temp;
			for (int j = 0; j < N; j++) {
				if (j % R == 0) {
					temp.clear();
				}
				temp.push_back(dq[j]);

				if (j%R == R-1) {
					v.push_back(temp);
				}
			}
		}

		sort(v.begin(), v.end());

		int cnt = 0;
		string select = "";
		//중복제거
		for (int i = v.size() - 1 ; i >= 0; i--) {
			if (v[i] == select) continue;
			select = v[i];
			cnt++;
			if (cnt == K) break;
		}

		cout << "#" << tc++ << " " << hexa2dec(select) <<endl;

		v.clear();
		dq.clear();
	}
	return 0;
}