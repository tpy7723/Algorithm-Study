#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

bool cmp(pair<int,int> a, pair<int,int> b) { 
	return a.first > b.first; 
}

struct info { // is는 현재 이기고, 무승부, 진것에 대한 offset
	int fight[2]; // 겨루는 두 팀
	double WDL[3]; // WDL 확률
	int is;
};

string team[4], input;
double ans[4];
info buffer[6]; // 6경기에 대한 정보 저장

// 완전탐색
void dfs(int num){
	if (num == 6)	{
		// 각 국의 승점 및 확률 계산
		int win_point[4] = { 0, };
		double ret = 1;

		for (int i = 0; i < 6; i++) // 6경기
		{
			int cur = buffer[i].is; // WDL 각 경기에 대한 선택
			ret *= buffer[i].WDL[cur]; // 경우의 수 마다 확률을 구함
			if (cur == 0) // W
				win_point[buffer[i].fight[0]] += 3; // A팀에 3점 더함
			else if (cur == 2) // L
				win_point[buffer[i].fight[1]] += 3; // B팀에 3점 더함
			else // D
			{
				win_point[buffer[i].fight[0]] += 1; // A팀에 1점 더함
				win_point[buffer[i].fight[1]] += 1; // B팀에 1점 더함
			}
		}
		if (ret == 0) return;
		// 동점자 계산 및 각 국에 확률 더해주기
		vector<pair<int,int>> vp;

		for (int i = 0; i < 4; i++)
			vp.push_back({ win_point[i],i });

		int cnt = 2; // 2등까지 뽑을거라 남은 자리수
		while (cnt > 0)	{
			int num = 0, max_x;
			sort(vp.begin(), vp.end(), cmp); // 승점을 기준으로 내림차순 정렬
			max_x = vp.front().first; // 최고 승점 

			for (int i = 0; i < 4; i++) {
				if (vp[i].first == max_x) {
					num++; // 최고 승점 동점자 수
				}
			}
			
			for (int i = 0; i < num; i++){
				double add = cnt > num ? ret : ret * ((float)cnt / num); // 동점일경우 확률 분배
				ans[vp[i].second] += add; // 확률을 더해준다
				vp[i].first = -1; // 방문처리
			}

			cnt -= min(cnt, num);
		}
		return;
	}
	// 완탐 검색
	for (int i = 0; i < 3; i++)	{ // WDL 012
		buffer[num].is = i;
		dfs(num + 1);
	}
}
int main(){
	for (int i = 0; i < 4; i++) { // 4개 팀
		cin >> team[i];
	}
		
	for (int i = 0; i < 6; i++){ // 6가지 겨루기가 나옴
		for (int j = 0; j < 2; j++){
			cin >> input;
			for (int p = 0; p < 4; p++)
				if (team[p].compare(input) == 0) // 입력한 문자열과 같으면
					buffer[i].fight[j] = p; // 해당 인덱스 저장
		}

		for (int j = 0; j < 3; j++)
			cin >> buffer[i].WDL[j]; // WDL 입력
	}

	dfs(0);

	for (int i = 0; i < 4; i++) {
		cout.precision(10);
		cout << ans[i] << endl;
	}

	return 0;
}