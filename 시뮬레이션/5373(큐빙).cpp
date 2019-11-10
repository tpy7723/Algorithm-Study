#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int n; // 회전 횟수
string a; // 회전 입력
char temp[3], t[3][3];
char cube[6][3][3]; // [면 번호] [서브 사각형 Y좌표] [서브 사각형 X좌표] 
const char color[] = "wyrogb"; // 위 아 앞 뒤 왼 오

void cw(int d) { // d면 시계방향 회전
	memcpy(t, cube[d], sizeof(cube[d])); // d면 현재 상태를 t로 복사
	cube[d][0][0] = t[2][0];
	cube[d][0][1] = t[1][0];
	cube[d][0][2] = t[0][0];
	cube[d][1][0] = t[2][1];
	cube[d][1][2] = t[0][1];
	cube[d][2][0] = t[2][2];
	cube[d][2][1] = t[1][2];
	cube[d][2][2] = t[0][2];
}

void ccw(int d) { // d면 반시계방향 회전
	memcpy(t, cube[d], sizeof(cube[d])); // d면 현재 상태를 t로 복사
	cube[d][0][0] = t[0][2];
	cube[d][0][1] = t[1][2];
	cube[d][0][2] = t[2][2];
	cube[d][1][0] = t[0][1];
	cube[d][1][2] = t[2][1];
	cube[d][2][0] = t[0][0];
	cube[d][2][1] = t[1][0];
	cube[d][2][2] = t[2][0];
}

void rotateU(int k) {
	for (int i = 0; i < 3; i++) temp[i] = cube[4][k][i];
	for (int i = 0; i < 3; i++) cube[4][k][i] = cube[2][k][i];
	for (int i = 0; i < 3; i++) cube[2][k][i] = cube[5][k][i];
	for (int i = 0; i < 3; i++) cube[5][k][i] = cube[3][k][i];
	for (int i = 0; i < 3; i++) cube[3][k][i] = temp[i];
}

void rotateD(int k) {
	for (int i = 0; i < 3; i++) temp[i] = cube[4][k][i];
	for (int i = 0; i < 3; i++) cube[4][k][i] = cube[3][k][i];
	for (int i = 0; i < 3; i++) cube[3][k][i] = cube[5][k][i];
	for (int i = 0; i < 3; i++) cube[5][k][i] = cube[2][k][i];
	for (int i = 0; i < 3; i++) cube[2][k][i] = temp[i];
}

void rotateF(int k) {
	int j = k == 0 ? 2 : 0; // k가 0이면 뒷면 반시계 회전
	for (int i = 0; i < 3; i++) temp[i] = cube[0][k][i];
	for (int i = 0; i < 3; i++) cube[0][k][i] = cube[4][2 - i][k];
	for (int i = 0; i < 3; i++) cube[4][i][k] = cube[1][j][i];
	for (int i = 0; i < 3; i++) cube[1][j][i] = cube[5][2 - i][j];
	for (int i = 0; i < 3; i++) cube[5][i][j] = temp[i];
}

void rotateB(int k) {
	int j = k == 0 ? 2 : 0;
	for (int i = 0; i < 3; i++) temp[i] = cube[0][k][i];
	for (int i = 0; i < 3; i++) cube[0][k][i] = cube[5][i][j];
	for (int i = 0; i < 3; i++) cube[5][i][j] = cube[1][j][2 - i];
	for (int i = 0; i < 3; i++) cube[1][j][i] = cube[4][i][k];
	for (int i = 0; i < 3; i++) cube[4][i][k] = temp[2 - i];
}

void rotateL(int k) {
	int j = k == 0 ? 2 : 0;
	for (int i = 0; i < 3; i++) temp[i] = cube[0][i][k];
	for (int i = 0; i < 3; i++) cube[0][i][k] = cube[3][2 - i][j];
	for (int i = 0; i < 3; i++) cube[3][i][j] = cube[1][2 - i][k];
	for (int i = 0; i < 3; i++) cube[1][i][k] = cube[2][i][k];
	for (int i = 0; i < 3; i++) cube[2][i][k] = temp[i];
}

void rotateR(int k) {
	int j = k == 0 ? 2 : 0;
	for (int i = 0; i < 3; i++) temp[i] = cube[0][i][k];
	for (int i = 0; i < 3; i++) cube[0][i][k] = cube[2][i][k];
	for (int i = 0; i < 3; i++) cube[2][i][k] = cube[1][i][k];
	for (int i = 0; i < 3; i++) cube[1][i][k] = cube[3][2 - i][j];
	for (int i = 0; i < 3; i++) cube[3][i][j] = temp[2 - i];
}

void solve() {
	switch (a[0]) {
	case 'U':
		if (a[1] == '+') {
			cw(0); // 해당면 시계회전
			rotateU(0); // 맨 윗면에 붙은 옆면들 시계방향으로 회전
		}
		else {
			ccw(0); // 해당면 반시계회전
			rotateD(0); // 맨 윗면에 붙은 옆면들 반시계방향으로 회전
		}
		break;
	case 'D':
		if (a[1] == '-') {
			ccw(1);
			rotateU(2); // 맨 아래면에 붙은 옆면들 시계방향으로 회전
		}
		else {
			cw(1);
			rotateD(2); // 맨 아래면에 붙은 옆면들 반시계방향으로 회전
		}
		break;
	case 'F':
		if (a[1] == '+') {
			cw(2);
			rotateF(2);
		}
		else {
			ccw(2);
			rotateB(2);
		}
		break;
	case 'B':
		if (a[1] == '-') {
			ccw(3);
			rotateF(0);
		}
		else {
			cw(3);
			rotateB(0);
		}
		break;
	case 'L':
		if (a[1] == '+') {
			cw(4);
			rotateL(0);
		}
		else {
			ccw(4);
			rotateR(0);
		}
		break;
	case 'R':
		if (a[1] == '-') {
			ccw(5);
			rotateL(2);
		}
		else {
			cw(5);
			rotateR(2);
		}
		break;
	default:
		break;
	}
}

int main() {
	int t;
	cin >> t;

	while (t--) {
		// 큐브 초기상태 만들기
		for (int i = 0; i < 6; i++) { // 위 아 앞 뒤 왼 오 
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					cube[i][j][k] = color[i];
				}
			}
		}

		// 회전
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> a;
			solve();
		}

		// 결과 출력
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << cube[0][i][j];
			}
			cout << endl;
		}
	}

	return 0;
}
