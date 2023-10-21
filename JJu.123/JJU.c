#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"


#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);

// low 이상 high 이하 난수를 발생시키는 함수
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("플레이어 수: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}

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


	return 0;
}

int main(void) {
	intro();
	jjuggumi_init();
	sample();
	//mugunghwa();
	//nightgame();
	//juldarigi();
	//jebi();
	//ending();
	return 0;
}