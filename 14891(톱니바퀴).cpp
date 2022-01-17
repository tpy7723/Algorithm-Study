<iostream>
#include <string>
#include <vector>

#define endl "\n"

using namespace std;
string s;
vector<string> v;
int K;
int num, d;
int result;
bool check[3];

void check_func() { // 상태 체크
	if (v[1][2] == v[2][6]) check[0] = true;
	else check[0] = false;
	if (v[2][2] == v[3][6]) check[1] = true;
	else check[1] = false;
	if (v[3][2] == v[4][6]) check[2] = true;
	else check[2] = false;
}

void rotate(int num, int d) {
	if (d == 1) { //시계방향 회전
		char temp = v[num][7];
		v[num].pop_back();
		v[num].insert(v[num].begin(), temp);
	}
	else { // 반시계방향 회전
		char temp = v[num][0];
		v[num].erase(v[num].begin());
		v[num].push_back(temp);
	}
}

int main() {
	v.push_back(""); // 0번 인덱스 사용 X
	for (int i = 0; i < 4; i++) {
		cin >> s;
		v.push_back(s);
	}
	cin >> K;

	for (int i = 0; i < K; i++) {
		cin >> num >> d;

		int tempnum = num;
		int tempd = d;

		check_func(); // 확인
		rotate(num, d); // 회전
		while (2 <= tempnum && tempnum <= 4) {
			if (check[tempnum - 2] == false) { // 왼쪽과 극이 다른 경우
				tempd *= -1;
				tempnum -= 1;
				rotate(tempnum, tempd);
				continue;
			}
			break;
		}

		tempnum = num;
		tempd = d;
		while (1 <= tempnum && tempnum <= 3) {
			if (check[tempnum - 1] == false) { // 오른쪽과 극이 다른 경우
				tempd *= -1;
				tempnum += 1;
				rotate(tempnum, tempd);
				continue;
			}
			break;
		}
	}

	// 점수계산
	if (v[1][0] == '1') result += 1;
	if (v[2][0] == '1') result += 2;
	if (v[3][0] == '1') result += 4;
	if (v[4][0] == '1') result += 8;

	cout << result << endl;

	return 0;
}