#include <iostream>
#include <deque>
#include <vector>

#define endl "\n"
#define MAX 100
using namespace std;

int N, K, L;
int MAP[MAX][MAX];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

vector<pair<int, char>> change_dir; // 방향 변환 정보

void Input() {
	// 보드 크기 N
	cin >> N;

	// 사과 갯수 K
	cin >> K;
	
	// 사과의 위치들 (행, 열)
	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		MAP[x][y] = 1;
	}

	// 방향 변환 횟수 L
	cin >> L;

	// 방향 변환 정보 (X초 후에, D방향으로)
	for (int i = 0; i < L; i++) {
		int X;
		char D;
		cin >> X >> D;
		change_dir.push_back(make_pair(X, D));
	}
}

int Change_Dir(int d, char c) {
	// d: 현재 머리 방향 
	// c: L이면 왼쪽, D면 오른쪽으로 90도 회전
	// 0=위, 1=아래, 2=오른쪽, 3=왼쪽
	if (c == 'L') {
		if (d == 0) return 3;
		else if (d == 1) return 2;
		else if (d == 2) return 0;
		else if (d == 3) return 1;
	}
	
	else if (c == 'D') {
		if (d == 0) return 2;
		else if (d == 1) return 3;
		else if (d == 2) return 1;
		else if (d == 3) return 0;
	}
}

void PlayGame() {
	deque<pair<int, int>> Snake; //(x좌표, y좌표)
	int x = 0, y = 0, d = 0; // 시작위치 (0,0), 시작방향 오른쪽
	int Time = 0;
	int Idx = 0;
	Snake.push_back(make_pair(x, y));
	MAP[x][y] = 2;

	while (1) {
		Time++;

		int next_x = x + dx[d];
		int next_y = y + dy[d];

		// 1. 종료조건 (머리가 몸이랑 닿거나, 머리가 벽에 닿거나)
		if ((MAP[next_x][next_y] == 2 || next_x < 0 || next_y < 0 || next_x >= N || next_y >= N)) {
			break;
		}

		// 2. 머리가 갈 다음 블록에 사과가 없나 
		else if (MAP[next_x][next_y] == 0) {
			// 맵에 표시
			MAP[next_x][next_y] = 2;
			MAP[Snake.back().first][Snake.back().second] = 0;
			
			// 뱀 관리
			Snake.push_front(make_pair(next_x, next_y));
			Snake.pop_back();
		}

		// 3. 머리가 갈 다음 블록에 사과가 있나
		else if (MAP[next_x][next_y] == 1) {
			// 맵에 표시
			MAP[next_x][next_y] = 2;

			// 뱀 관리
			Snake.push_front(make_pair(next_x, next_y));
		}

		// 4. 방향 전환을 할 때인가 → 방향전환
		if (Idx < change_dir.size()) {
			if (Time == change_dir[Idx].first) {
				d = Change_Dir(d, change_dir[Idx].second);
				Idx++;
			}
		}

		x = next_x;
		y = next_y;
	}

	cout << Time << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Input();
	PlayGame();

	return 0;
}