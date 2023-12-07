#pragma once
#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>

#define PLAYER_MAX		10
#define ITEM_MAX        10
#define ITEM_N_MAX      4
int n_player, n_alive,n_player,n_item,n_I;
int tick;  // 시계

// 미니게임
void sample(void);
//void mugunghwa(void);
//void mugunghwa(void);
//void nightgame(void);
//void juldarigi(void);
//void jebi(void);

int randint(int low, int high);

//아이템을 장착하면 스탯 증가
typedef struct {
	char name[100];
	int intel_buf, str_buf, stamina_buf;
}ITEM;

ITEM item[ITEM_MAX];
#endif

typedef struct {
	int id;
	char name[100];

	//능력치: 지능,힘,스태미나
	int intel, str, stamina;

	//현재 상태
	bool is_alive;
	bool hasitem;
	ITEM item;
}PLAYER;

PLAYER player[PLAYER_MAX];
