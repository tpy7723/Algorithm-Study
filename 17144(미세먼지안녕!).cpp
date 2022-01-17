#include <iostream>
#include <cstring>
using namespace std;

int R, C, T, Answer;
pair<int, int> Air_Cleaner[2]; // 공기청정기 배열 (두 좌표가 저장)

int MAP[50][50]; // 맵
int C_MAP[50][50]; // 맵 복사본

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 }; // 상하 우좌

void Dust_Expansion() { // 먼지 확산
	memcpy(C_MAP, MAP, sizeof(MAP));

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) { // 모든 원소에 대해
			if (MAP[i][j] != 0 && MAP[i][j] != -1) { // 미세먼지가 있고, 공기청정기가 아니면
				int Cnt = 0;
				int Value = MAP[i][j] / 5; // 확산될 양
				for (int k = 0; k < 4; k++) { // 상하 좌우 확인
					int nx = i + dx[k]; // 다음 x좌표
					int ny = j + dy[k]; // 다음 y좌표
					if (nx >= 0 && ny >= 0 && nx < R && ny < C) { // 다음 xy좌표가 배열 내부이고
						if (MAP[nx][ny] != -1) { // 공기청정기가 아니면
							C_MAP[nx][ny] += Value; // 확산
							Cnt++;
						}
					}
				}
				C_MAP[i][j] -= (Cnt * Value); // 자신이 확산한 양을 빼줌
			}
		}
	}
	// 모든 원소에 대해 다 끝나면 
	memcpy(MAP, C_MAP, sizeof(MAP)); // 복사본을 원본에 복사
}

void Move_Dust() { // 이동
	for (int Idx = 0; Idx < 2; Idx++) {
		if (Idx == 0) { // 반시계 회전
			// 1. 공기청정기 위에서부터 (0, 0)까지 모든 값 떙겨주기 (아래쪽)
			for (int i = Air_Cleaner[Idx].first - 1; i > 0; i--)
			{
				MAP[i][0] = MAP[i - 1][0];
			}
			// 2. 가장 윗줄 땡겨주기 (왼쪽)
			for (int i = 0; i < C - 1; i++)
			{
				MAP[0][i] = MAP[0][i + 1];
			}
			// 3. 오른쪽 세로라인 땡겨주기 (위)
			for (int i = 1; i <= Air_Cleaner[Idx].first; i++)
			{
				MAP[i - 1][C - 1] = MAP[i][C - 1];
			}
			// 4. 공기청정기 라인 땡겨주기 (오른쪽)
			for (int i = C - 1; i > 1; i--)
			{
				MAP[Air_Cleaner[Idx].first][i] = MAP[Air_Cleaner[Idx].first][i - 1];
			}
			MAP[Air_Cleaner[Idx].first][1] = 0;
		}
		else { // 시계 회전
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

int Count_Dust() { // 전체 먼지 양
	int Sum = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] == -1) continue; // 공기청정기는 무시
			Sum += MAP[i][j];
		}
	}
	return Sum;
}


int main(void)
{
	cin >> R >> C >> T; // 세로 가로 시간

	int Idx = 0; // 공기청정기 index
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == -1) { // 공기청정기 위치 인덱스가0인게 위에칸 1인게 아래칸
				Air_Cleaner[Idx] = make_pair(i, j);
				Idx++;
			}
		}
	}

	for (int i = 0; i < T; i++){
		Dust_Expansion(); // 먼지 확산
		Move_Dust(); // 공기 청정기에 의한 이동
	}

	cout << Count_Dust();  // 전체 먼지 양 출력

	return 0;
}
