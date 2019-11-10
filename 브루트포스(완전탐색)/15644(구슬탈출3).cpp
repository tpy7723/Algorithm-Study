#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

struct state {
	int rx, ry, bx, by, d; // 빨강 파랑 좌표 , 횟수
};

int n, m;
char a[10][10];
bool visit[10][10][10][10];
queue<state> q;
state path[10][10][10][10]; // 이전정보 저장
char direct[] = { 'U', 'R', 'D', 'L' };
int dx[] = { -1, 0, 1, 0 }, dy[] = { 0, 1, 0, -1 }; // 상하좌우 모든 방향

//call by reference
void move(int &x, int &y, int &c, int dx, int dy) { // c는 이동거리 dx dy 상하좌우 정보
	while (a[x + dx][y + dy] != '#' && a[x][y] != 'O') { // 다음 위치가 벽이 아니고 현재 위치가 구멍이 아니면 계속 이동
		x += dx; // x증가
		y += dy; // y증가
		c += 1; // 이동 거리
	}
}

void bfs() {
	while (!q.empty()) {
		// 빨간 좌표
		int rx = q.front().rx;
		int ry = q.front().ry;
		// 파란 좌표
		int bx = q.front().bx;
		int by = q.front().by;
		// 횟수
		int d = q.front().d;

		q.pop();

		if (d >= 10) break; // 10회 이하로 성공 못한 경우 -1 출력하고 끝

		for (int i = 0; i < 4; i++) { // 상하좌우 네방향 체크
			int next_rx = rx; 
			int next_ry = ry;
			int next_bx = bx;
			int next_by = by;
			int next_d = d + 1; // 횟수 1 증가

			int rc = 0; // 빨강 이동 거리 
			int bc = 0; // 파랑 이동 거리
			
			move(next_rx, next_ry, rc, dx[i], dy[i]); // 빨강 이동 -> 좌표값바뀜
			move(next_bx, next_by, bc, dx[i], dy[i]); // 파랑 이동 -> 좌표값바뀜

			if (a[next_bx][next_by] == 'O') continue; // 파랑이 구멍에 들어가면 무시

			if (a[next_rx][next_ry] == 'O') { // 빨강이 구멍에 들어가면 끝
				vector<char> p; // 문자 저장 벡터
				p.push_back(direct[i]); // Current direct
				state b = path[rx][ry][bx][by]; // 이전 상황 불러옴

				while (b.rx != 0) {
					int past_rx = b.rx, past_ry = b.ry, past_bx = b.bx, past_by = b.by;
					p.push_back(direct[b.d]); // Go backward previous position.
					b = path[past_rx][past_ry][past_bx][past_by];
				}
				cout << next_d << endl;

				for (int k = 0; k < p.size(); k++) { // Print in reverse order.
					cout << p[p.size() - k - 1]; // 거꾸로 출력
				}
				cout << endl;
				return;
			}

			if (next_rx == next_bx && next_ry == next_by) { // 이동한 곳이 겹치는 경우 
				// 이동거리가 더 큰 것이 한 칸 이전으로 감
				if (rc > bc) next_rx -= dx[i], next_ry -= dy[i]; 
				else next_bx -= dx[i], next_by -= dy[i];
			}
			if (!visit[next_rx][next_ry][next_bx][next_by]) {
				visit[next_rx][next_ry][next_bx][next_by] = true; // 이미 나오지 않았던 상황이면 방문처리
				q.push({ next_rx, next_ry, next_bx, next_by, next_d }); // 다음 상태를 큐에 입력해 줌
				path[next_rx][next_ry][next_bx][next_by] = { rx, ry, bx, by, i }; // 이전정보 저장 + 방향
			}
			
		}
	}
	cout << -1 << endl;
}

int main() {
	cin >> n >> m; // 세로 가로

	int rx,ry,bx,by; // 빨강 파랑 xy 좌표

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];

			if (a[i][j] == 'R') { 
				rx = i;
				ry = j;
			} // 빨강 좌표 저장
			else if (a[i][j] == 'B') {
				bx = i;
				by = j;
			} // 파랑 좌표 저장
		}
	}

	q.push({ rx, ry, bx, by, 0 }); // 초기 상태 queue 삽입

	visit[rx][ry][bx][by] = true; // 방문 배열

	bfs();

	return 0;
}
