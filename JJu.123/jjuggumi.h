#pragma once
#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>

#define PLAYER_MAX		10

bool player[PLAYER_MAX];  // �⺻�� true, Ż���ϸ� false
int n_player, n_alive;
int tick;  // �ð�

// �̴ϰ���
void sample(void);
//void mugunghwa(void);
//void mugunghwa(void);
//void nightgame(void);
//void juldarigi(void);
//void jebi(void);

int randint(int low, int high);

#endif