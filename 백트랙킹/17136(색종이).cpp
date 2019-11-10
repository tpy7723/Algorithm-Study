#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int papercnt[6] = {0,5,5,5,5,5};
int ans;

// 2차원 배열 복사
void mapcopy(int paper[10][10], int newpaper[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			newpaper[i][j] = paper[i][j];
		}
	}
}

//종이를 k크기만큼 덮는다
void cover(int x, int y, int k, int paper[10][10]) {
	for (int i = x; i < x + k; i++) {
		for (int j = y; j < y + k; j++) {
			paper[i][j] = 0;
		}
	}
}

//k*k크기의 색종이를 덮을 수 있는지 검사한다. 불가능할 경우 바로 false를 리턴
bool usePaper(int x, int y, int k, int paper[10][10]) {
	for (int i = x; i < x + k; i++) {
		for (int j = y; j < y + k; j++) {
			//종이 범위 를 넘어가면 false
			if (i >= 10 || j >= 10) return false;

			//0이 있는 자리에는 색종이를 놓을 수 없다
			if (paper[i][j] == 0) return false;
		}
	}
	return true;
}

void solve(int paper[10][10], int usingnum) { // 사용개수
	if (usingnum >= ans) return;

	//색종이가 안덮인 곳을 찾는다.
	bool flag = false;
	int x, y;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (paper[i][j] == 1) {
				x = i;
				y = j;
				flag = true;
				break;
			}
		}
		if (flag) break;
	}

	//종이를 다 붙였다
	if (!flag) {
		if (ans > usingnum) ans = usingnum; // 최소 개수 저장
		return;
	}

	//큰 색종이부터 대본다.
	//각각의 종류의 색종이를 사용하는 경우를 모두 구해준다
	for (int k = 5; k > 0; k--) {
		//해당 색종이가 없다
		if (papercnt[k] == 0) continue;

		//해당 종이로 채울 수 없다
		if (!usePaper(x, y, k, paper)) continue;

		//새로운 배열을 만들고 복사한다.
		int newpaper[10][10];
		mapcopy(paper, newpaper);

		//덮는다
		cover(x, y, k, newpaper);

		//종이 사용
		papercnt[k] -= 1;

		//k*k색종이를 사용한 경우에 대해서 새로 탐색을 해준다.
		//색종이 사용 횟수 증가
		solve(newpaper, usingnum + 1);

		//다른 색종이를 사용하는 경우를 위해서 종이 다시 증가
		papercnt[k] += 1;
	}

}

int main() {
	int paper[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> paper[i][j];
		}
	}

	//최솟값을 찾기 위해 정답을 최댓값으로 초기화
	ans = 26;

	solve(paper, 0);

	//ans값이 초기값이라면 1을 모두 덮는 것이 불가능한 경우다.
	if (ans == 26) cout << -1 << endl;
	else cout << ans << endl;

	return 0;
}
