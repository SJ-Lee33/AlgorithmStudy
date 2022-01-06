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

vector<pair<int, char>> change_dir; // ���� ��ȯ ����

void Input() {
	// ���� ũ�� N
	cin >> N;

	// ��� ���� K
	cin >> K;
	
	// ����� ��ġ�� (��, ��)
	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		MAP[x][y] = 1;
	}

	// ���� ��ȯ Ƚ�� L
	cin >> L;

	// ���� ��ȯ ���� (X�� �Ŀ�, D��������)
	for (int i = 0; i < L; i++) {
		int X;
		char D;
		cin >> X >> D;
		change_dir.push_back(make_pair(X, D));
	}
}

int Change_Dir(int d, char c) {
	// d: ���� �Ӹ� ���� 
	// c: L�̸� ����, D�� ���������� 90�� ȸ��
	// 0=��, 1=�Ʒ�, 2=������, 3=����
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
	deque<pair<int, int>> Snake; //(x��ǥ, y��ǥ)
	int x = 0, y = 0, d = 0; // ������ġ (0,0), ���۹��� ������
	int Time = 0;
	int Idx = 0;
	Snake.push_back(make_pair(x, y));
	MAP[x][y] = 2;

	while (1) {
		Time++;

		int next_x = x + dx[d];
		int next_y = y + dy[d];

		// 1. �������� (�Ӹ��� ���̶� ��ų�, �Ӹ��� ���� ��ų�)
		if ((MAP[next_x][next_y] == 2 || next_x < 0 || next_y < 0 || next_x >= N || next_y >= N)) {
			break;
		}

		// 2. �Ӹ��� �� ���� ��Ͽ� ����� ���� 
		else if (MAP[next_x][next_y] == 0) {
			// �ʿ� ǥ��
			MAP[next_x][next_y] = 2;
			MAP[Snake.back().first][Snake.back().second] = 0;
			
			// �� ����
			Snake.push_front(make_pair(next_x, next_y));
			Snake.pop_back();
		}

		// 3. �Ӹ��� �� ���� ��Ͽ� ����� �ֳ�
		else if (MAP[next_x][next_y] == 1) {
			// �ʿ� ǥ��
			MAP[next_x][next_y] = 2;

			// �� ����
			Snake.push_front(make_pair(next_x, next_y));
		}

		// 4. ���� ��ȯ�� �� ���ΰ� �� ������ȯ
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