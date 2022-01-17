#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct shark {
	int s, d, z; // 스피드 방향 크기
};

int r, c, m, ans; // 행 열 상어수 답
shark a[101][101]; // 상어가 위치한 맵

const int dx[4] = {-1, 1, 0, 0 }, dy[4] = {0, 0, 1, -1 }; // 좌우상하

void solve() {
	for (int t = 1; t <= c; t++) { // 열 한칸씩 이동
		shark b[101][101] = { 0 }; // 상어의 이동 맵 초기화
		// Fishing a shark
		for (int i = 1; i <= r; i++) {
			if (a[i][t].z) { // 해당 열 맨 위
				ans += a[i][t].z; // 상어 잡음
				a[i][t] = { 0, 0, 0 }; // 상어 삭제
				break;
			}
		}
		// Sharks move
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				if (a[i][j].z) { // 상어가 존재하고
					if (a[i][j].d < 3) { // Up, Down
						int s = a[i][j].s % ((r - 1) * 2); // 나머지
						int d = a[i][j].d; // 방향
						int ni = i; // 행
						while (s--) { // 나머지를 이동
							if (ni == 1 && d == 1) d = 2; // 1 인덱스에 부딪칠때 방향전환
							if (ni == r && d == 2) d = 1; // r 인덱스에 부딪칠때 방향전환
							ni += dx[d-1]; // 행 값 변화
						}
						if (a[i][j].z > b[ni][j].z) b[ni][j] = { a[i][j].s, d, a[i][j].z }; // 잡아먹기
					}
					else { // Right, Left
						int s = a[i][j].s % ((c - 1) * 2);
						int d = a[i][j].d;
						int nj = j; //열
						while (s--) {
							if (nj == 1 && d == 4) d = 3; // 왼쪽 경계에 부딪칠떄
							if (nj == c && d == 3) d = 4; // 오른쪽 경계에 부딪칠 때
							nj += dy[d-1]; // 열 값 변화
						}
						if (a[i][j].z > b[i][nj].z) b[i][nj] = { a[i][j].s, d, a[i][j].z }; // 잡아먹기
					}
					a[i][j] = { 0, 0, 0 }; // 이동했으니 삭제
				}
			}
		}
		memcpy(a, b, sizeof(b)); // a에 b를 복사함
	}
}

int main() {
	cin >> r >> c >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, s, d, z;
		cin >> x >> y >> s >> d >> z;
		a[x][y] = { s, d, z }; // 상어 정보 저장
	}
	solve();
	cout << ans << endl;
	return 0;
}