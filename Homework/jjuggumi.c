// 2023-2 ������α׷��� ����: �޲ٹ� ����
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

	printf("�÷��̾� ��: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}

int winner;
int count_alive_players(void) {
	int alive_players = 0;
	for (int p = 0; p < n_player; p++) {
		if (player[p]) {
			if (alive_players == 0) { winner = p; }
			alive_players++;

		}
	}

	return alive_players;
}

void ending() {
	system("cls");

	if (count_alive_players() == 1) {
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
	else {
		printf("����ڸ� ������ ���߽��ϴ�.\n");
	}



}
int main(void) {
	jjuggumi_init();
	intro();
	//sample();
	mugunghwa();
	ending();
	//nightgame();
	//juldarigi();
	//jebi();
	return 0;
}
