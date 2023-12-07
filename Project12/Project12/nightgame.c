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

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�
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
		// ���� �ڸ��� ������ �ٽ� ����
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
		arr_I_X[i] = I_X;//I�� x�� ����
		arr_I_Y[i] = I_Y;//I�� y�� ����
	}
	
}

void move_manual_nightgame(key_t key) {
	// �� �������� ������ �� x, y�� delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // ������ ����(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// �������� ���� �ڸ�
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}

	move_tail(0, nx, ny);
}

// 0 <= dir < 4�� �ƴϸ� ����
void move_random_nightgame(int player, int dir) {
	int p = player;  // �̸��� ��...
	int nx, ny;  // �������� ������ ���� �ڸ�

	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	

	do {
		nx = px[p] + randint(-1, 1);
		ny = py[p] + randint(-1, 1);
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

// back_buf[][]�� ���
void move_tail_nightgame(int player, int nx, int ny) {
	int p = player;  // �̸��� ��...
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
	//i = player ,root = I(�ִ� ��ο� �ִ�);
	int fast_root_x = abs(px[i] - arr_I_X[root]);
	int fast_root_y = abs(px[i] - arr_I_Y[root]);
	//������ �ϳ� �� �ʿ���
	//�������� �����ϴ°� �ƴѰ��� ���� ����.
	//�������� �������� ������ �������� ���� �ÿ��̾����� ������.
	if (fast_root_x > fast_root_y) {//���� or ������ �̵�.
		if (px[i] > arr_I_X[root]) {//�������� �̵�.
			nx = px[i]--;
			ny = py[i];
			move_tail_nightgame(i, nx, ny);
			back_buf[nx][ny];
		}
		else if (px[i] < arr_I_X[root]) {//���������� �̵�.
			nx = px[i]++;
			ny = py[i];
			move_tail_nightgame(i, nx, ny);
			back_buf[nx][ny];
		}
	}
	else if (fast_root_x < fast_root_y) {//�� or �Ʒ�.
		if (py[i] > arr_I_Y[root]) {//�������� �̵�.
			ny = py[i]--;
			nx = px[i];
			move_tail_nightgame(i, nx, ny);
			back_buf[nx][ny];
		}
		else if (py[i] < arr_I_Y[root]) {//�Ʒ��� �̵�.
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
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual_nightgame(key);
		}

		// player 1 ���ʹ� �������� ������(8����)
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
				int root = find_min_dis(i);
				goto_min_root(i, root);
			}
		}

		display();
		Sleep(10);
		tick += 10;
		char message[4] = "��";
		dialog(message);
	}
}