#include <iostream>
#include <algorithm>
#include <string>

#define endl "\n"

using namespace std;

int N;
bool flag = 0;

//좋은 수열인지 판별하는 함수
bool check(string s) {
	int s_len = s.length() - 1; // 마지막 원소 인덱스

	for (int i = 0; i < s.length() / 2; i++) {
		string str1 = s.substr(((s_len - i) - (i + 1)), i + 1);
		string str2 = s.substr(s_len - i, i + 1);
		if (str1 == str2) return false; //str1하고 str2가 같으면 무시
	}
	return true;
}

void dfs(string s) {
	if (flag == 0) { // 가장 작은 값을 찾기 위해서
		if (s.length() == N) { // N글자 완성
			flag = 1; // 한번만 실행 됨
			cout << s;
			return;
		}

		for (char i = '1'; i <= '3'; i++) {
			s.push_back(i);
			if (check(s)) {
				dfs(s);
			}
			s.pop_back();
		}
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	dfs("1");

	check("123123213");
	return 0;
}