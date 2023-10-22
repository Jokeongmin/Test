
#pragma once
#ifndef _CIO_H_
#define _CIO_H_

#include <stdbool.h>

// ȭ�� ũ��(�� ũ��x. �� + ����â)
#define ROW_MAX		40
#define COL_MAX		80

// ���� ���۸�
// back_buf[][]�� ���̰�, 
// front_buf[][]�� ȭ�鿡 ����ϱ� ���� ����
// ����: https://codevang.tistory.com/39
// ������API�ε� ����: https://game-happy-world.tistory.com/46
char front_buf[ROW_MAX][COL_MAX];
char back_buf[ROW_MAX][COL_MAX];

// �� ũ��(���� buf�� �ؽ�Ʈ���� ������ ĵ���� ũ��)
int N_ROW, N_COL;

void map_init(int n_row, int n_col);
void dialog(char message[]);
bool placable(int row, int col);
void display(void);
void gotoxy(int x, int y);
void printxy(char ch, int row, int col);

#endif