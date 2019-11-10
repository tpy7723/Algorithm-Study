#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int map[26][26];
int cnt = 0;
int movedir[4][2] = { {1,0},{-1,0},{0,-1},{0,1} }; // 상하 좌우
int temp[500];
int n;

bool isindoor(int a, int b) {
	return (0 <= a && a < n) && (0 <= b && b < n);
}

void dfs(int a, int b, int key) {
	map[a][b] = key;

	for (int i = 0; i < 4; i++) {
		int dy = a + movedir[i][0];
		int dx = b + movedir[i][1];

		if (isindoor(dy, dx) && map[dy][dx] == 1) {
			dfs(dy, dx, key);
		}
	}
}

void Solution(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 1) {
				cnt++; // 단지 종류 개수
				dfs(i, j, cnt + 1); // 단지 ID 를 입력하고 DFS
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] > 1) {
				temp[map[i][j] - 2]++; // 단지별로 갯수 카운트
			}
		}
	}
}

int main(void) {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%1d", &map[i][j]);   //숫자 하나씩 입력 받습니다
		}
	}

	Solution(n);

	sort(temp, temp + cnt); // 단지 개수 정렬

	cout << cnt << endl;

	for (int i = 0; i < cnt; i++) {
		cout << temp[i] << endl;
	}

	return 0;
}