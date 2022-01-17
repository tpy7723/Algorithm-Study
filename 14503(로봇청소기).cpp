#include <iostream>

#define endl "\n"

using namespace std;

int N, M;
int curr, curc;
int map[50][50];
int curd; // 0123 북동남서
int dir[4][2] = { {0,-1},{-1,0},{0,1},{1,0} }; // 왼쪽으로가는 배열
int go[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} }; // 앞으로가는 배열
int back[4][2] = { {1,0}, {0,-1}, {-1,0}, {0,1} }; // 뒤로가는 배열
int cnt;

void clean() {
	while (1) {
		if (map[curr][curc] == 0) {
			map[curr][curc] = 2; // 현재 위치 청소
			cnt++;
		}
		int tempr = curr;
		int tempc = curc;
		int tempd = curd;
		for (int i = 0; i < 4; i++) { // 네 방향
			if (map[curr + dir[curd][0]][curc + dir[curd][1]] == 0) { // 왼쪽 방향에 청소하지 않은 공간이 존재
				curd = (curd + 3) % 4; // 그 방향으로 회전한 다음
				curr += go[curd][0];
				curc += go[curd][1];
				break;
			}
			else {
				curd = (curd + 3) % 4; // 왼쪽 방향에 청소할 공간이 없다면 회전만 함
			}
		}
		if (tempd == curd && tempr == curr && tempc == curc) { // 네 방향 모두 청소가 이미 되어있거나 벽인 경우
			if (map[curr + back[curd][0]][curc + back[curd][1]] == 1) { // 뒤가 벽
				break;
			}
			// 후진
			curr += back[curd][0];
			curc += back[curd][1];
		}
	}
}

int main() {
	cin >> N >> M;
	cin >> curr >> curc >> curd;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	clean();

	cout << cnt << endl;
	return 0;
}

