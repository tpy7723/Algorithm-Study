#include <iostream>
#define endl "\n"

using namespace std;

int N, M, x, y, K;
int map[20][20];
int order;

// 0 1  2 3  4 5
// 상하 앞뒤 좌우 
int cube[6] = { 0,0,0,0,0,0 };
int r, c; // 현재위치

bool isindoor(int r, int c) {
	return (0 <= r && r < N) && (0 <= c && c < M);
}

void turn(int d) {
	int temp;
	switch (d)
	{
	case 1: // 동
		// 동 => 상이 우 우가 하 하가 좌 좌가 상
		c++;
		if (!isindoor(r, c)) break;

		temp = cube[0];
		cube[0] = cube[4];
		cube[4] = cube[1];
		cube[1] = cube[5];
		cube[5] = temp;
		break;
	case 2: // 서
		// 서 => 상이 좌 좌가 하 하가 우 우가 상
		c--;
		if (!isindoor(r, c)) break;
		temp = cube[0];
		cube[0] = cube[5];
		cube[5] = cube[1];
		cube[1] = cube[4];
		cube[4] = temp;
		break;
	case 3: // 북
		// 북 => 상이 뒤 뒤가 하 하가 앞 앞이 상
		r--;
		if (!isindoor(r, c)) break;

		temp = cube[0];
		cube[0] = cube[2];
		cube[2] = cube[1];
		cube[1] = cube[3];
		cube[3] = temp;
		break;
	case 4: // 남
		r++;
		if (!isindoor(r, c)) break;
		// 남 => 상이 앞 앞이 하 하가 뒤 뒤가 상
		temp = cube[0];
		cube[0] = cube[3];
		cube[3] = cube[1];
		cube[1] = cube[2];
		cube[2] = temp;
		break;
	default:
		break;
	}
}

int main() {
	cin >> N >> M >> r >> c >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	// 0 1  2 3  4 5
	// 상하 앞뒤 좌우 


	for (int i = 0; i < K; i++) {
		cin >> order;
		int tempr = r;
		int tempc = c;

		turn(order);
		if (!isindoor(r, c)) {
			r = tempr;
			c = tempc;
			continue; // 범위초과
		}

		if (map[r][c] == 0) {
			map[r][c] = cube[1];
		}
		else {
			cube[1] = map[r][c];
			map[r][c] = 0;
		}

		cout << cube[0] << endl;
	}

	return 0;
}