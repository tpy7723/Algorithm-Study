#include <iostream>

#define endl "\n"

using namespace std;

int N, M;
int curr, curc;
int map[50][50];
int curd; // 0123 �ϵ�����
int dir[4][2] = { {0,-1},{-1,0},{0,1},{1,0} }; // �������ΰ��� �迭
int go[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} }; // �����ΰ��� �迭
int back[4][2] = { {1,0}, {0,-1}, {-1,0}, {0,1} }; // �ڷΰ��� �迭
int cnt;

void clean() {
	while (1) {
		if (map[curr][curc] == 0) {
			map[curr][curc] = 2; // ���� ��ġ û��
			cnt++;
		}
		int tempr = curr;
		int tempc = curc;
		int tempd = curd;
		for (int i = 0; i < 4; i++) { // �� ����
			if (map[curr + dir[curd][0]][curc + dir[curd][1]] == 0) { // ���� ���⿡ û������ ���� ������ ����
				curd = (curd + 3) % 4; // �� �������� ȸ���� ����
				curr += go[curd][0];
				curc += go[curd][1];
				break;
			}
			else {
				curd = (curd + 3) % 4; // ���� ���⿡ û���� ������ ���ٸ� ȸ���� ��
			}
		}
		if (tempd == curd && tempr == curr && tempc == curc) { // �� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���� ���
			if (map[curr + back[curd][0]][curc + back[curd][1]] == 1) { // �ڰ� ��
				break;
			}
			// ����
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

