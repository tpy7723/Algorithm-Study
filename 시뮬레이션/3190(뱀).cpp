#include <iostream>
#include <deque>
#include <vector>

#define endl "\n"

using namespace std;

struct node {
	int r, c;
};

struct change {
	int t, r;
};

int N, K;
int tr, tc;
int tn;
int t;
char r;
int time;
int result;
int d; // 0123 우하좌상
int dir[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
int curr = 1, curc = 1; // 뱀머리위치
int map[101][101];
vector<change> v;
deque<node> snake;

bool isindoor(int r, int c) {
	return (1 <= r && r <= N) && (1 <= c && c <= N);
}

int main() {
	cin >> N;
	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> tr >> tc;
		map[tr][tc] = 1; // 사과 위치
	}
	cin >> tn;
	for (int i = 0; i < tn; i++) {
		cin >> t >> r;
		v.push_back({ t,r });
	}

	map[1][1] = 2; // 뱀위치
	snake.push_back({ 1,1 });

	time = -1;
	while (1) {
		time++;
		// 방향 전환
		for (int i = 0; i < v.size(); i++) {
			if (time == v[i].t) {
				if (v[i].r == 'D') {
					d = (d + 1) % 4;
				}
				else if (v[i].r == 'L') {
					d = (d + 3) % 4; // 중요
				}
			}
		}
		curr += dir[d][0];
		curc += dir[d][1];
		if (!isindoor(curr, curc)) break; // 벽
		if (map[curr][curc] == 2) break; // 뱀

		snake.push_back({ curr, curc }); // 뱀 머리 추가

		if (map[curr][curc] == 0) {
			int temp_r = snake.front().r;
			int temp_c = snake.front().c;
			snake.pop_front(); // 꼬리부분 제거
			map[temp_r][temp_c] = 0; // 꼬리부분 제거
		}
		map[curr][curc] = 2; // 뱀이 있는 곳 표시
	}

	cout << time + 1;
	return 0;
}