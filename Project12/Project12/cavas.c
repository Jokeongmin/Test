#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"

#define DIALOG_DURATION_SEC		4

void draw(void);
void print_status(void);

// (zero-base) row��, col���� Ŀ�� �̵�
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row��, col���� ch ���
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

void map_init(int n_row, int n_col) {
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
		back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
		}
	}
}

// back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
bool placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// ��ܿ� ����, �ϴܿ��� ���� ���¸� ���
void display(void) {
	draw();
	gotoxy(N_ROW + 4, 0); // �߰��� ǥ���� ������ ������ �ʰ� ����â ������ �� ������ ���
	print_status();
}

void draw(void) {
	//���� ����.
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void print_status(void) {
	printf("no. of players left: %d\n", n_alive);
	gotoxy(N_ROW + 5, 19);
	printf("intl");
	gotoxy(N_ROW + 5, 29);
	printf("str");
	gotoxy(N_ROW + 5, 39);
	printf("stm");
	gotoxy(N_ROW + 6, 0);
	for (int p = 0; p < n_player; p++) {
		
		printf("player %2d: ", p); 
		char AorD[100];
		if (*&player[p].is_alive == 0) {
			printf("%5s", "DEAD");
		}
		else {
			printf("%5s", "alive");
		}
		printf("    %d(+%d)          %d(+%d)          %d%\n", *&player[p].intel,0, *&player[p].str,0, *&player[p].stamina);

	}


}


int rmt = DIALOG_DURATION_SEC;
int high_map_size;


void dialog(char message[]) {
	//ǥ�� �� ��� ���� ���� ����. 
	int show_dialog_col = 10;
	int show_dialog_row = 3;


	while (rmt > 0) {//ī��Ʈ �ٿ��� ���� 0�� �Ǳ� �������� ����Ǵ� while�ݺ���. 
		// gotoxy�� �̿��ؼ� Ŀ���� ��ġ��Ű�� 
		gotoxy(show_dialog_col, show_dialog_row);
		printf("***************");//����Ʈ �Լ��� �̿��ؼ� �� ��ġ�� ��½�Ű��.
		gotoxy(show_dialog_col + 1, show_dialog_row);
		printf("%d", rmt); printf("%s", message);
		gotoxy(show_dialog_col + 2, show_dialog_row);
		printf("***************");
		Sleep(1000);

		rmt--;//ī��Ʈ �ٿ�


		//�� �ҷ�����
		for (int row = 0; row < N_ROW; row++) {
			for (int col = 0; col < N_COL; col++) {

				printxy(back_buf[row][col], row, col);

			}
		}
	}
}