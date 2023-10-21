#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"
#include <string.h>

#define DIALOG_DURATION_SEC		4

void map_init(int n_row, int n_col);
void draw(void);
void print_status(void);
int high_map_size;

// (zero-base) row행, col열로 커서 이동
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row행, col열에 ch 출력
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

void map_init(int n_row, int n_col) {
	
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
		back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
		}
	}
}

// back_buf[row][col]이 이동할 수 있는 자리인지 확인하는 함수
bool placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// 상단에 맵을, 하단에는 현재 상태를 출력
void display(void) {
	draw();
	gotoxy(N_ROW + 4, 0);  // 추가로 표시할 정보가 있으면 맵과 상태창 사이의 빈 공간에 출력
	print_status();
}

void draw(void) {
	
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
	

}
void temp(void) {
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			
				printxy(front_buf[row][col], row, col);
			}
		}
	
}
void print_status(void) {
	printf("no. of players left: %d\n", n_alive);
	for (int p = 0; p < n_player; p++) {
		printf("player %2d: %5s\n", p, player[p] ? "alive" : "DEAD");
	}
}

void new_buf(char plz_buf[][COL_MAX],char buf[][COL_MAX]) {
	for (int row = 0; row < ROW_MAX; row++) {
		for (int col = 0; col < COL_MAX; col++) {
			plz_buf[row][col] = buf[row][col];
		}
	}
}


/*void creat_buf[int n_col][{
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
			}
		}
	}
}*/



void dialog(char message[]) {

	// 새로 맵 버퍼를 만들고 back buf 저장
	/*for (int row = 0; row < ROW_MAX; row++) {
		for (int col = 0; col < COL_MAX; col++) {
			new_buf[row][col] = back_buf[row][col];
		}
	}*/
	int rmt = DIALOG_DURATION_SEC;

	int show_dialog_col = 5;
	int show_dialog_row = 3;



	while (true) {
		if (rmt >= 1) {
			gotoxy(show_dialog_col, show_dialog_row);
			printf("***************");//프린트 함수를 이용해서 그 위치에 출력시키기.
			gotoxy(show_dialog_col + 1, show_dialog_row);
			printf("%d", rmt); printf("%s", message);
			gotoxy(show_dialog_col + 2, show_dialog_row);
			printf("***************");
			Sleep(1000);

			rmt--;

		}
		else if (rmt == 0) {
			system("cls");
			// front_buf를 초기화시키기
			for (int row = 0; row < N_ROW; row++) {
				for (int col = 0; col < N_COL; col++) {
					front_buf[row][col] = ' ';
				}
			}

			// 맵 버퍼를 백 버퍼에 저장시키기

			draw();
			/*for (int row = 0; row < N_ROW; row++) {
				for (int col = 0; col < N_COL; col++) {
					if (front_buf[row][col] != back_buf[row][col]) {
						back_buf[row][col];
					}
				}
			}
			for (int row = 0; row < N_ROW; row++) {
				for (int col = 0; col < N_COL; col++) {
					printxy(back_buf[row][col], row, col);
				}
			}*/
			break;
		}
	
	}
}



	

		
	
	
