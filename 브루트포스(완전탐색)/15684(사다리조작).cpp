#include <iostream>

using namespace std;

int n, m, h, ans = 4;
bool a[30][10];

bool ladder() {
	for (int j = 0; j < n; j++) {
		int k = j; // 시작점
		for (int i = 0; i < h; i++) {
			if (a[i][k]) k += 1;
			else if (a[i][k - 1]) k -= 1;
		}
		if (j != k) return false; // 시작점과 다름
	}
	return true;
}

void solve(int cnt, int x, int y) {
	if (ans <= cnt) return; // 최소값보다큰거 제외
	if (ladder()) {
		if (ans > cnt) ans = cnt; // 최소값저장
		return;
	}
	if (cnt == 3) return; // 3개까지만 놓음 이해잘해야댐
	for (int i = x; i < h; i++, y = 0) {
		for (int j = y; j < n - 1; j++) { // 그 다음높이에서부터는 0부터 탐색
			if (a[i][j]) { // 이미 사다리가 있는 경우
				j += 1; // 1개를 추가해야 위에 j++ 떄문에 두칸을 이동함
			}
			else {
				a[i][j] = 1; // 사다리 놓기
				solve(cnt + 1, i, j + 2); // 두개 증가
				a[i][j] = 0;
			}
		}
	}
}

int main() {

	cin >> n >> m >> h;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		a[x - 1][y - 1] = 1;
	}
	solve(0, 0, 0);
	cout << (ans < 4 ? ans : -1) << endl;
	return 0;
}