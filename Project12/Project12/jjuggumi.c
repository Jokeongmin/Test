#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"
int count_alive_players();
int intro() {
	printf("    _         _           _    _                                               _  \n");
	Sleep(70);
	printf("   (_)       (_)         | |  | |                                             | | \n");
	Sleep(70);
	printf("    _   ___   _  _ __    | |_ | |__    ___       _ __   __ _  _ __ ___  ___   | | \n");
	Sleep(70);
	printf("   | | / _ \  | || '_ \    | __|| '_ \   /          |/ _` || '_ ` _\ / _          | | \n");
	Sleep(70);
	printf("   | || (_) || || | | |  |   |_ | | | ||__/      |(_| || (_| || | | | |||__/  |_|\n");
	Sleep(70);
	printf("   | |  \___/ |_||_| |_|    \__||_| |_|  \___|       \__,||\__,_||_| |_| |_|  \__|  (_)\n");
	Sleep(70);
	printf("  _/ |                                            __/ |                           \n");
	Sleep(70);
	printf("  |__/                                           |___/                            \n");

	Sleep(3000);
	return 0;
}

int jjuggumi_init(void);

// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));
	
	FILE* fp;
	fopen_s(&fp, DATA_FILE, "r");
	if (fp == NULL) {
		return -1;
	}

	//�÷��̾� ������ load
	fscanf_s(fp, "%d", &n_player);
	for (int i = 0; i < n_player; i++) {
		PLAYER* p = &player[i];

		fscanf_s(fp, "%s%d%d", p-> name, (unsigned int)sizeof(p->name),
			&(p->intel), (&p->str));
		p->stamina = 100;

		p->is_alive = true;
		p->hasitem = false;
		//(*p).hasitem 
	}

	fscanf_s(fp, "%d", &n_item);
	for (int i = 0; i < n_item; i++) {
		fscanf_s(fp, "%s%d%d%d",
			item[i].name, (unsigned int)sizeof(item[i].name),
			&(item[i].intel_buf),
			&(item[i].str_buf),
			&(item[i].stamina_buf));
	}

	fclose(fp);
	return 0;
}

int winner;
int alive_players = 0;
int dead_players = 0;
int count_alive_players() {//������ ���� ���� �Լ�.
	
	for (int p = 0; p < n_player; p++) {
		if (*&player[p].is_alive==1) {
			//if (*&player[p].is_alive == 0) { winner = p; }
			alive_players++;
			int memmory_p = p;
		}
		else {
			dead_players++;
		}
		if (n_alive == 1) {
			winner = p;
		}
	}
	
	return alive_players, dead_players;
}

void ending() {
	system("cls");
	int n_pass = 0, n_dead = 0;
	n_pass, n_dead = count_alive_players();
	if (n_pass == 1 && n_dead == 5) {
		printf("..3\n");
		Sleep(1000);
		printf("..2\n");
		Sleep(1000);
		printf("..1\n");
		Sleep(1000);
		printf("����ڴ�~~~~~~\n");
		Sleep(1000);
		printf("%d�÷��̾�!!\n", winner);
	}
	else if (n_pass >= 1 && n_pass == n_alive || n_pass == 0){
		printf("����ڸ� ������ ���߽��ϴ�.\n");
	}



}
int main(void) {
	jjuggumi_init();
	//intro();
	//sample();
	//mugunghwa();
	//ending();
	nightgame();
	//juldarigi();
	//jebi();
	return 0;
}