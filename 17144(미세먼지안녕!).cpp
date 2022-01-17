#include <iostream>
#include <cstring>
using namespace std;

int R, C, T, Answer;
pair<int, int> Air_Cleaner[2]; // ����û���� �迭 (�� ��ǥ�� ����)

int MAP[50][50]; // ��
int C_MAP[50][50]; // �� ���纻

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 }; // ���� ����

void Dust_Expansion() { // ���� Ȯ��
	memcpy(C_MAP, MAP, sizeof(MAP));

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) { // ��� ���ҿ� ����
			if (MAP[i][j] != 0 && MAP[i][j] != -1) { // �̼������� �ְ�, ����û���Ⱑ �ƴϸ�
				int Cnt = 0;
				int Value = MAP[i][j] / 5; // Ȯ��� ��
				for (int k = 0; k < 4; k++) { // ���� �¿� Ȯ��
					int nx = i + dx[k]; // ���� x��ǥ
					int ny = j + dy[k]; // ���� y��ǥ
					if (nx >= 0 && ny >= 0 && nx < R && ny < C) { // ���� xy��ǥ�� �迭 �����̰�
						if (MAP[nx][ny] != -1) { // ����û���Ⱑ �ƴϸ�
							C_MAP[nx][ny] += Value; // Ȯ��
							Cnt++;
						}
					}
				}
				C_MAP[i][j] -= (Cnt * Value); // �ڽ��� Ȯ���� ���� ����
			}
		}
	}
	// ��� ���ҿ� ���� �� ������ 
	memcpy(MAP, C_MAP, sizeof(MAP)); // ���纻�� ������ ����
}

void Move_Dust() { // �̵�
	for (int Idx = 0; Idx < 2; Idx++) {
		if (Idx == 0) { // �ݽð� ȸ��
			// 1. ����û���� ���������� (0, 0)���� ��� �� �����ֱ� (�Ʒ���)
			for (int i = Air_Cleaner[Idx].first - 1; i > 0; i--)
			{
				MAP[i][0] = MAP[i - 1][0];
			}
			// 2. ���� ���� �����ֱ� (����)
			for (int i = 0; i < C - 1; i++)
			{
				MAP[0][i] = MAP[0][i + 1];
			}
			// 3. ������ ���ζ��� �����ֱ� (��)
			for (int i = 1; i <= Air_Cleaner[Idx].first; i++)
			{
				MAP[i - 1][C - 1] = MAP[i][C - 1];
			}
			// 4. ����û���� ���� �����ֱ� (������)
			for (int i = C - 1; i > 1; i--)
			{
				MAP[Air_Cleaner[Idx].first][i] = MAP[Air_Cleaner[Idx].first][i - 1];
			}
			MAP[Air_Cleaner[Idx].first][1] = 0;
		}
		else { // �ð� ȸ��
			for (int i = Air_Cleaner[Idx].first + 1; i < R - 1; i++)
			{
				MAP[i][0] = MAP[i + 1][0];
			}
			for (int i = 0; i < C - 1; i++)
			{
				MAP[R - 1][i] = MAP[R - 1][i + 1];
			}
			for (int i = R - 1; i >= Air_Cleaner[Idx].first; i--)
			{
				MAP[i][C - 1] = MAP[i - 1][C - 1];
			}
			for (int i = C - 1; i > 1; i--)
			{
				MAP[Air_Cleaner[Idx].first][i] = MAP[Air_Cleaner[Idx].first][i - 1];
			}
			MAP[Air_Cleaner[Idx].first][1] = 0;
		}
	}
}

int Count_Dust() { // ��ü ���� ��
	int Sum = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] == -1) continue; // ����û����� ����
			Sum += MAP[i][j];
		}
	}
	return Sum;
}


int main(void)
{
	cin >> R >> C >> T; // ���� ���� �ð�

	int Idx = 0; // ����û���� index
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == -1) { // ����û���� ��ġ �ε�����0�ΰ� ����ĭ 1�ΰ� �Ʒ�ĭ
				Air_Cleaner[Idx] = make_pair(i, j);
				Idx++;
			}
		}
	}

	for (int i = 0; i < T; i++){
		Dust_Expansion(); // ���� Ȯ��
		Move_Dust(); // ���� û���⿡ ���� �̵�
	}

	cout << Count_Dust();  // ��ü ���� �� ���

	return 0;
}
