#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

void nightgame_init(void);
void move_manual_nightgame(key_t key);
void move_random_nightgame(int i, int dir);
void move_tail_nightgamme(int i, int nx, int ny);
void nightgame_I_respon(void);
int find_min_dis(int);
int compare_num(int, int);
void goto_min_root(int i, int root);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기
int arr_I_X[4] = { 0 };
int arr_I_Y[4] = { 0 };

int dis_x[4] = { 0 };
int dis_y[4] = { 0 };
int min_sqrt[4] = { 0 };

int nx, ny;
void nightgame_init(void) {
	map_init(15, 40);
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// 같은 자리가 나오면 다시 생성
		do {
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}

	tick = 0;
}



void nightgame_I_respon(void) {
	int I_X, I_Y;
	int n_I = randint(1, 4);
	
	for(int i=0;i<n_I;i++){
		do {
			I_X = randint(1, N_ROW - 2);
			I_Y = randint(1, N_COL - 2);
			
		} while (!placable(I_X, I_Y));
		back_buf[I_X][I_Y] = 'I';
		arr_I_X[i] = I_X;//I의 x값 저장
		arr_I_Y[i] = I_Y;//I의 y값 저장
	}
	
}

void move_manual_nightgame(key_t key) {
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// 움직여서 놓일 자리
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}

	move_tail(0, nx, ny);
}

// 0 <= dir < 4가 아니면 랜덤
void move_random_nightgame(int player, int dir) {
	int p = player;  // 이름이 길어서...
	int nx, ny;  // 움직여서 다음에 놓일 자리

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	

	do {
		nx = px[p] + randint(-1, 1);
		ny = py[p] + randint(-1, 1);
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

// back_buf[][]에 기록
void move_tail_nightgame(int player, int nx, int ny) {
	int p = player;  // 이름이 길어서...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}


int find_min_dis(int i) {

	for (int k = 0; k < n_I; k++) {
		if (dis_x[k] != 0 && dis_y[k] != 0) {
			dis_x[k] =arr_I_X[k] - px[i];
			dis_y[k] =arr_I_Y[k] - py[i];
		}
	}

	min_sqrt[0] = INT_MAX;
	int min, count_j=0;

	for (int j = 0; j < 4; j++) {
		min_sqrt[j] = sqrt(dis_x[j] * dis_x[j] + dis_y[j] * dis_y[j]);
		if (min_sqrt[j] > min_sqrt[j + 1]) {
			min = min_sqrt[j + 1];
			count_j = j;
		}
	}
	return count_j;
}



void goto_min_root(int i, int root) {
	//i = player ,root = I(최단 경로에 있는);
	int fast_root_x = abs(px[i] - arr_I_X[root]);
	int fast_root_y = abs(px[i] - arr_I_Y[root]);
	//조건이 하나 더 필요함
	//아이템이 존재하는가 아닌가에 대한 조건.
	//아이템이 존재하지 않을시 아이템을 지닌 플에이어한테 가야함.
	if (fast_root_x > fast_root_y) {//왼쪽 or 오른쪽 이동.
		if (px[i] > arr_I_X[root]) {//왼쪽으로 이동.
			nx = px[i]--;
			ny = py[i];
			move_tail_nightgame(i, nx, ny);
			back_buf[nx][ny];
		}
		else if (px[i] < arr_I_X[root]) {//오른쪽으로 이동.
			nx = px[i]++;
			ny = py[i];
			move_tail_nightgame(i, nx, ny);
			back_buf[nx][ny];
		}
	}
	else if (fast_root_x < fast_root_y) {//위 or 아래.
		if (py[i] > arr_I_Y[root]) {//위쪽으로 이동.
			ny = py[i]--;
			nx = px[i];
			move_tail_nightgame(i, nx, ny);
			back_buf[nx][ny];
		}
		else if (py[i] < arr_I_Y[root]) {//아래로 이동.
			ny = py[i]++;
			nx = px[i];
			move_tail_nightgame(i, nx, ny);
			back_buf[nx][ny];
		}
	}
}

void nightgame(void) {
	nightgame_init();
	nightgame_I_respon();
	system("cls");
	display();
	while (1) {
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual_nightgame(key);
		}

		// player 1 부터는 랜덤으로 움직임(8방향)
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
				int root = find_min_dis(i);
				goto_min_root(i, root);
			}
		}

		display();
		Sleep(10);
		tick += 10;
		char message[4] = "초";
		dialog(message);
	}
}