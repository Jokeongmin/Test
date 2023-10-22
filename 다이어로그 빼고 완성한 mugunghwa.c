//영희통과아직다못함

#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_UP		0//y축 대칭 1
#define DIR_DOWN	1//y축 대칭 0
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
int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기
void map_init_m(int n_row, int n_col) {
	// 두 버퍼를를 완전히 비우기
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// 대입문 이렇게 쓸 수 있는데 일부러 안 가르쳐줬음
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
	map_init_m(10, 40); // 맵 만들기 
	int x, y;
	for (int i = 0; i < n_player; i++) {
		//같은 자리가 나오면 다시 생성
		do {
			x = randint(1, N_ROW - 2);
			y = N_COL - 2;
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(80, 100);

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

	int p = player;  // 이름이 길어서...
	// 움직여서 다음에 놓일 자리
	int rx = 0, ry = 0;

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	

	if (dir == 2) {//왼쪽으로 가는 경우  x축y 축 
		rx = 0; ry = -1;
	}
	else if (dir == 1) {//아래로 가는경우
		rx = 1; ry = 0;
	}
	else if (dir == 3) {//위쪽으로 가는 경우
		rx = -1; ry = 0;
	}
	else {				//제자리 일 경우
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
	//표기 될 행과 열의 길이 선언. 
	int show_dialog_col = 4;
	int show_dialog_row = 3;

	

	while (rmt > 0) {//카운트 다운이 들어가고 0이 되기 전까지만 실행되는 while반복문. 
		// gotoxy를 이용해서 커서를 위치시키고 
		gotoxy(show_dialog_col, show_dialog_row);
		printf("***************");//프린트 함수를 이용해서 그 위치에 출력시키기.
		gotoxy(show_dialog_col + 1, show_dialog_row);
		printf("%d", rmt); printf("%s", message);
		gotoxy(show_dialog_col + 2, show_dialog_row);
		printf("***************");
		Sleep(1000);
		if (rmt > 0) {
			rmt--;//카운트 다운
		}

		//맵 불러오기
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
		per[i] = randint(1, 100);

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
		printf("무");
		count = 0;//#표시 
		print_yunghee();
	}

	if (tick == 300) {
		gotoxy(11, 2);
		printf(" 궁");
	}
	if (tick == 600) {
		gotoxy(11, 6);
		printf(" 화");
	}
	if (tick == 1000) {
		gotoxy(11, 10);
		printf(" 꽃");
	}
	if (tick == 1500) {
		gotoxy(11, 14);
		printf(" 이");
	}
	if (tick == 2000) {
		gotoxy(11, 18);
		printf(" 피");
	}
	if (tick == 2500) {
		gotoxy(11, 22);
		printf(" 었");
	}
	if (tick == 2900) {
		gotoxy(11, 26);
		printf(" 습");
	}
	if (tick == 3300) {
		gotoxy(11, 30);
		printf(" 니");
	}
	if (tick == 3500) {
		gotoxy(11, 34);
		printf(" 다");
		gotoxy(3, 1);
		count = 1;//@ 표시 
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
/*
void yunghee_watching(void) {

	for (int i = 0; i < n_player; i++) {
		gotoxy(i+20, 0);
		printf("\n");
		printf("%d player y 값 %d, x 값 %d", i, px[i], py[i]);
		a = n_player;

		if (py[i] == py[i + 1]) {
			for (int j = 0; j < n_player; j++) {
				if (px[j] > px[j + 1]) {

					if (px[j] == a) {

					}
				}
			}
		}
	}


	// 가장 작은 x 값을 가진 플레이어는 탈락되지 않도록 복원
	
}
*/


int status = 0;
void mugunghwa(void) {
	mugunghwa_init();

	system("cls");


	display();
	yunghee_1();
	count = 0;

	while (1) {

		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
			if (count == 0) {//무궁화 꽃 어쩌고 진행중 

				p0_x = px[0];
				p0_y = py[0];

			}
			else if (count == 1) {//3초 기다리는 동안 
				
				if ((p0_x != px[0]) || (p0_y != py[0])) {
					
					status = 0;

					for (int j = 1; j < n_player; j++) {//앞에 누가 있는지를 확인 
						//player[j] == 0 죽은사람을 스킵하지 않으면 죽은사람도 status 1로 만들어줌 보이진 않지만 x,y값이 바뀜.
						if (player[j] == 0) {
							continue;
						}

						if (px[0] == px[j] && py[j]<py[0]) {
							status = 1;//가려진 상태 
						}
					}

					if (status == 0) {//가려지지 않은 상태라면 
						player[0] = 0;//die
						back_buf[px[0]][py[0]] = ' ';//화면에서 안보임 처리 
						n_alive--;//생존자수 1줄어들음 
					}

					p0_x = px[0];
					p0_y = py[0];
				}
			}
		}

		// player 1 부터는 랜덤으로 움직임(3방향+제자리)
		for (int i = 1; i < n_player; i++) {
			
			count_message += 1;
			if (count == 0) {
				if (tick % period[i] == 0) {
					dir = dir_randonm();
					move_random_m(i, dir);

				}
			}
			else if (count == 1) {
				per[i] = player_per();
				if (1 <= per[i] && per[i] <= 10) {//10 퍼센트 확률로 움직인 다면. 
					if (tick % period[i] == 0) {
						//죽은 사람 player[i] ==0 스킵
						if (player[i] == 0) {
							continue;
						}

						status = 0;//가려지지 않은 상태

						for (int j = 0; j < n_player; j++) {
							//player[j] == 0 죽은사람을 스킵하지 않으면 죽은사람도 status 1로 만들어줌 보이진 않지만 x,y값이 바뀜.
							if (player[j] == 0) {
								continue;
							}

							if (px[i] == px[j] && py[j] < py[i]) {
								status = 1;//가려진 상태 
							}
						}

						dir = dir_randonm();
						move_random_m(i, dir);

						if (status == 0) {
							player[i] = 0;
							back_buf[px[i]][py[i]] = ' ';
							n_alive=n_alive-1;
						}

					}
				}
			}
		}





		for (int i = 0; i < n_player; i++) {
			if (player_pass(i) == 1) {
				back_buf[py[i]][px[i]] = ' ';
			}
		}
		int num_alive_players = count_alive_players();
		if (num_alive_players == 1) {
			break;
		}

		Sleep(10);
		tick += 10;
		display();
		//yunghee_1();
		say_m();
		int count_message = 0;
		char message[4] = "초";
		
		//dialog_m(message);





	}

}
