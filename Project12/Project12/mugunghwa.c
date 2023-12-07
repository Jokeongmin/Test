
#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_UP		0//y�� ��Ī 1
#define DIR_DOWN	1//y�� ��Ī 0
#define DIR_LEFT	2
#define DIR_RIGHT	3
#define DIALOG_DURATION_SEC		4

void mugunghwa_init(void);
void move_random_m(int player, int dir);
void move_manual(key_t key);
void move_tail(int i, int nx, int ny);
void print_yunghee(void);
//void yunghee_watching(void);
int player_per(void);
//int player_pass(int player);
int count, dir;
int nx_p, ny_p;
int p0_x, p0_y;
int nx, ny;
int count_message = 0;
int buf_alive;
int d_player;
int pass_arr[10] = { 0 };
int n_alive = 6;
int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�
void map_init_m(int n_row, int n_col) {
	// �� ���۸��� ������ ����
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
		back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '*' : ' ';
		}
	}
}
void yunghee_1() {
	for (int i = 3; i < 7; i++) {
		back_buf[i][1] = '#';
	}
}
void yunghee_2() {
	for (int i = 3; i < 7; i++) {
		back_buf[i][1] = '@';
	}
}
void mugunghwa_init() {
	map_init_m(10, 40); // �� ����� 
	int x, y;
	for (int i = 0; i < n_player; i++) {
		//���� �ڸ��� ������ �ٽ� ����
		do {
			x = randint(1, N_ROW - 2);
			y = N_COL - 2;
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(70, 100);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}



	tick = 0;
}


int dir_randonm(void) {
	int N = randint(1, 100);
	if (1 <= N && N <= 70) {
		dir = 2;
	}
	else if (70 < N && N <= 80) {
		dir = 1;
	}
	else if (80 < N && N <= 90) {
		dir = 0;
	}
	else {
		dir = 3;
	}
	return dir;
}

void move_random_m(int player, int dir) {

	int p = player;  // �̸��� ��...
	// �������� ������ ���� �ڸ�
	int rx = 0, ry = 0;

	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	

	if (dir == 2) {//�������� ���� ���  x��y �� 
		rx = 0; ry = -1;
	}
	else if (dir == 1) {//�Ʒ��� ���°��
		rx = 1; ry = 0;
	}
	else if (dir == 3) {//�������� ���� ���
		rx = -1; ry = 0;
	}
	else {				//���ڸ� �� ���
		rx = 0; ry = 0;
	}

	nx = px[p] + rx;
	ny = py[p] + ry;

	if (placable(nx, ny)) {
		move_tail(p, nx, ny);
		int p = player;
		int x = px[p];
		int y = py[p];
		for (int i = 3; i <= 6; i++) {
			if ((nx == 2 && ny == i) || (nx == 1 && ny == 2) || (nx == 1 && ny == 7)) {
				back_buf[px[i]][py[i]] = ' ';
			}

		}
	}
}

int rmt;
int high_map_size;

void dialog_m(char message[]) {

	//ǥ�� �� ��� ���� ���� ����. 
	int show_dialog_col = 4;
	int show_dialog_row = 3;
	rmt = 4;
	
	
	while (rmt > 0) {//ī��Ʈ �ٿ��� ���� 0�� �Ǳ� �������� ����Ǵ� while�ݺ���. 
		// gotoxy�� �̿��ؼ� Ŀ���� ��ġ��Ű�� 
		gotoxy(show_dialog_col, show_dialog_row);
		printf("***************");//����Ʈ �Լ��� �̿��ؼ� �� ��ġ�� ��½�Ű��.
		gotoxy(show_dialog_col + 1, show_dialog_row);

		printf("%d", rmt); printf("%s",message);
		gotoxy(show_dialog_col + 2, show_dialog_row);
		printf("***************");
		Sleep(1000);
		if (rmt > 0) {
			rmt--;//ī��Ʈ �ٿ�
		}

		//�� �ҷ�����
		for (int row = 0; row < N_ROW; row++) {
			for (int col = 0; col < N_COL; col++) {

				printxy(back_buf[row][col], row, col);
				front_buf[row][col] = back_buf[row][col];
			}
		}
	}
}

void print_yunghee() {
	if (count == 0) {
		yunghee_1();
	}
	else if (count == 1) {
		yunghee_2();
	}
}
int per[] = { 0 };
int player_per(void) {
	for (int i = 1; i < n_player; i++) {
		per[i] = randint(1, 10);

		return per[i];
	}

}
int player_pass(int player) {
	int p = player;
	int x = px[p];
	int y = py[p];
	for (int i = 3; i <= 6; i++) {
		if ((y == 2 && x == i) || (y == 1 && x == 2) || (y == 1 && x == 7)) {
			return 1;
		}
	}
	return 0;
}

void say_m(void) {

	if (tick == 100) {
		gotoxy(11, 0);
		printf("��");
		count = 0;//#ǥ�� 
		print_yunghee();
	}

	if (tick == 300) {
		gotoxy(11, 2);
		printf(" ��");
	}
	if (tick == 600) {
		gotoxy(11, 6);
		printf(" ȭ");
	}
	if (tick == 1000) {
		gotoxy(11, 10);
		printf(" ��");
	}
	if (tick == 1500) {
		gotoxy(11, 14);
		printf(" ��");
	}
	if (tick == 2000) {
		gotoxy(11, 18);
		printf(" ��");
	}
	if (tick == 2500) {
		gotoxy(11, 22);
		printf(" ��");
	}
	if (tick == 2900) {
		gotoxy(11, 26);
		printf(" ��");
	}
	if (tick == 3300) {
		gotoxy(11, 30);
		printf(" ��");
	}
	if (tick == 3500) {
		gotoxy(11, 34);
		printf(" ��");
		gotoxy(3, 1);
		count = 1;//@ ǥ�� 
		print_yunghee();
		
	}

	if (tick > 6500) {
		tick = 0;
		system("cls");
		for (int row = 0; row < N_ROW; row++) {
			for (int col = 0; col < N_COL; col++) {

				printxy(back_buf[row][col], row, col);
			}
		}
		display();
		dir = 0;
		count = 0;
	}

}

int n_player, a;


char message[] = "player . dead!";
int status = 0;
int count_pass = 0;
void mugunghwa(void) {
	mugunghwa_init();

	system("cls");

	display();
	yunghee_1();
	count = 0;

	while (1) {

		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			if (pass_arr[0] != 1) {
				move_manual(key);
				if (count == 0) {//����ȭ �� ��¼�� ������ 

					p0_x = px[0];
					p0_y = py[0];

				}
				else if (count == 1) {//3�� ��ٸ��� ���� 

					if ((p0_x != px[0]) || (p0_y != py[0])) {

						status = 0;

						for (int j = 1; j < n_player; j++) {//�տ� ���� �ִ����� Ȯ�� 
							//player[j] == 0 ��������� ��ŵ���� ������ ��������� status 1�� ������� ������ ������ x,y���� �ٲ�.
							if (&player[j] == 0 || pass_arr[j] == 1) {
								*&player[j].is_alive = 0;
								continue;
							}

							if (px[0] == px[j] && py[j] < py[0]) {
								status = 1;//������ ���� 
							}
						}

						if (status == 0) {//�������� ���� ���¶�� 
							*&player[0].is_alive = 0;//die
							back_buf[px[0]][py[0]] = ' ';//ȭ�鿡�� �Ⱥ��� ó�� 
							n_alive--;//�����ڼ� 1�پ���� 

							message[7] = 0 + '0';
							dialog_m(message);
							display();

						}

						p0_x = px[0];
						p0_y = py[0];
					}
				}
			}	
		}
		

		// player 1 ���ʹ� �������� ������(3����+���ڸ�)
		for (int i = 1; i < n_player; i++) {
			if (pass_arr[i] != 1) {
				count_message += 1;
				if (count == 0) {
					if (tick % period[i] == 0) {
						dir = dir_randonm();
						move_random_m(i, dir);

					}
				}
				else if (count == 1) {

					per[i] = player_per();
					if (per[i] == 1 ) {//10 �ۼ�Ʈ Ȯ���� ������ �ٸ�. 
						if (tick % period[i] == 0) {
							//���� ��� player[i] ==0 ��ŵ
							if (*&player[i].is_alive == 0 || pass_arr[i] == 1) {
								continue;
							}

							status = 0;//�������� ���� ����

							for (int j = 0; j < n_player; j++) {
								//player[j] == 0 ��������� ��ŵ���� ������ ��������� status 1�� ������� ������ ������ x,y���� �ٲ�.
								if (*&player[j].is_alive == 0 || pass_arr[j] == 1) {
									continue;
								}

								if (px[i] == px[j] && py[j] < py[i]) {
									status = 1;//������ ���� 
								}
							}

							dir = dir_randonm();
							move_random_m(i, dir);

							if (status == 0) {
								*&player[i].is_alive = 0;
								back_buf[px[i]][py[i]] = ' ';
								n_alive = n_alive - 1;
								message[7] = i + '0';
								dialog_m(message);
							}
						}
					}
				}
			}
		}
		int count_n_alive = n_alive;
		//���� ����(����ִ� ����� ����� ����� ���� ������. or ����ִ� ��� 0
		if (count_pass == n_alive || n_alive ==0) {
			break;
		}

		for (int i = 0; i < n_player; i++) {//��� 
			if (player_pass(i) == 1) {
				back_buf[px[i]][py[i]] = ' ';
				pass_arr[i] = 1;
				count_pass++;
			}
			
		}
		/*int num_alive_players = count_alive_players(count_n_alive);
		if (num_alive_players == 1 || count_pass>1&& ) {
			break;
		}
		*/
		display();
		Sleep(10);
		tick += 10;
		
		say_m();
		int count_message = 0;

	}
}
