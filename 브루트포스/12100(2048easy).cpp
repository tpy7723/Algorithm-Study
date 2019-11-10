#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int N;
int map[20][20];
int max_value = -1000000;

// 맵을 시계방향 90도 회전하는 함수
void rotate() {
	int Cmap[20][20];

	for (int i = N - 1; i >= 0; i--) {
		for (int j = 0; j < N; j++) {
			Cmap[j][i] = map[N - i - 1][j];
		}
	}
	memcpy(map, Cmap, sizeof(Cmap));
}

// 사이의 0 지우는 함수
void remove_zero() {
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (map[i][j] == 0) { // 해당 값이 0 이면
				int temp = i;
				while (map[++temp][j] == 0) {
				}
				int difference = temp - i;

				while (temp < N) { // 끌어 당기기
					map[temp - difference][j] = map[temp][j];
					map[temp][j] = 0;
					temp++;
				}
			}
		}
	}
}

// 같은 값 합치기
void combine() {
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N - 1; i++) {
			if (map[i][j] == map[i + 1][j]) { // 다음 값과 값이 같으면
				map[i][j] *= 2; // 2배
				map[i + 1][j] = 0; // 0으로 초기화
			}
		}
	}
}

void move() {
	remove_zero();
	combine();
	remove_zero();
}

// 맵을 회전하여 상하좌우 쉽게 구현
void solve(int d) { // 0123 상하좌우 이동
	switch (d)
	{
	case 0: //상
		move();
		break;

	case 1: //하
		rotate();
		rotate();
		move();
		rotate();
		rotate();
		break;
	case 2: //좌
		rotate();
		move();
		rotate();
		rotate();
		rotate();
		break;
	case 3: //우
		rotate();
		rotate();
		rotate();
		move();
		rotate();
		break;
	default:
		break;
	}
}

// 제일 큰 블록 찾기
int max_block() {
	int max_value2 = -10000000;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			max_value2 = max(max_value2, map[i][j]);
		}
	}
	return max_value2;
}
void Dfs(int depth)
{
	// 5번 이동했으면 최대값 저장
	if (depth == 5) {
		max_value = max(max_value, max_block());
		return;
	}

	int tmp_map[20][20];
	memcpy(tmp_map, map, sizeof(map)); // 원본 맵 저장

	for (int k = 0; k < 4; k++) {
		// 모든 방향으로 바꾼 경우 탐색
		solve(k);
		Dfs(depth + 1);
		// 원래 상태로 돌려준다
		memcpy(map, tmp_map, sizeof(map));
	}
}

int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	Dfs(0); // 조합으로 풀면 시간초과 및 모든 경우의 수를 안따지더라

	cout << max_value << endl;

	return 0;
}
