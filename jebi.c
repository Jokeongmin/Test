#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <string.h>

#define DIR_LEFT	-1
#define DIR_RIGHT	1
void move_random_m(int player, int dir);
int result[PLAYER_MAX];
int map_row = 30;
int map_col = 5;
int current_pos;
int aa;
int q = 0;
int player_turn;
int round_round;
int round = 0;
int pass_arr[10] = { 0 };
int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];
int count, dir;
int p0_x, p0_y;
int count_message = 0;
int n_player;



void concatStrings(const char* str1, const char* str2, char* result) {
	int i, j;

	
	for (i = 0; str1[i] != '\0'; ++i) {
		result[i] = str1[i];
	}

	
	for (j = 0; str2[j] != '\0'; ++j, ++i) {
		result[i] = str2[j];
	}

	result[i] = '\0';  // 문자열의 끝에 NULL 문자 추가
}


void reverse(char str[], int length) {
	int start = 0;
	int end = length - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

char* intToStr(int num, char* str) {
	int i = 0;
	bool isNegative = false;
	
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// 음수인 경우를 처리
	if (num < 0) {
		isNegative = true;
		num = -num;
	}

	// num을 문자열로 변환
	while (num != 0) {
		int rem = num % 10;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / 10;
	}

	
	if (isNegative) {
		str[i++] = '-';
	}

	str[i] = '\0'; // 문자열 끝에 NULL 문자 추가

	
	reverse(str, i);

	return str;
}

void jebi_init() {
	player_turn = 0;
	round_round = 0;
	aa = n_alive;


	while (player[player_turn] == false) {
		player_turn += 1;

	}




	current_pos = 0;
	map_init(map_col, map_row);

	for (int i = 0; i < aa; i++) {
		result[i] = 0;
	}

	result[randint(0, aa - 1)] = 1;

	int row = 2;
	for (int col = 3; col < aa + 3; col++) {
		if (col == 3) {
			back_buf[row][col * 2] = '@';
		}
		else {
			back_buf[row][col * 2] = '?';
		}
	}

}
void next_jebi() {
	player_turn += 1;
	round_round += 1;


	while (player[player_turn] == false) {
		player_turn += 1;

	}


	current_pos = 0;
	map_init(map_col, map_row);
	for (int i = 0; i < aa - round_round; i++) {
		result[i] = 0;
	}

	result[randint(0, aa - round_round - 1)] = 1;

	int row = 2;
	for (int col = 3; col < aa - round_round + 3; col++) {
		if (col == 3) {
			back_buf[row][col * 2] = '@';
		}
		else {
			back_buf[row][col * 2] = '?';
		}
	}
}


void buf_jebi(int x) {
	current_pos += x;

	int row = 2;
	for (int col = 3; col < aa - round_round + 3; col++) {
		if (col - 3 == current_pos) {
			back_buf[row][col * 2] = '@';
		}
		else {
			back_buf[row][col * 2] = '?';
		}
	}
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

void sel_jebi(key_t key) {
	int dir = 0;  // 움직일 방향(0~3)
	switch (key) {
	case K_LEFT: dir += -1; break;
	case K_RIGHT: dir += 1; break;
	default: return;
	}
	if (current_pos + dir == -1 || current_pos + dir == aa - round_round) {
		return;
	}
	else {
		buf_jebi(dir);

	}
}
int per[] = { 0 };
int player_per(void) {
	for (int i = 1; i < n_player; i++) {
		per[i] = randint(1, 10);

		return per[i];
	}

}
/**int get_result() {
	char str1[] = "player ";
	char str2[10];
	char str3[] = " fail!";
	char str4[] = " pass!";

	intToStr(player_turn, str2);

	char str12[sizeof(str1) + sizeof(str2) - 1];
	concatStrings(str1, str2, str12);
	if (result[current_pos] == 1) {
		char str123[sizeof(str12) + sizeof(str3) - 1];
		concatStrings(str12, str3, str123);
		dialog(str123);

		player[player_turn] = false;
		n_alive -= 1;
		return 1;
	}
	else {
		char str124[sizeof(str12) + sizeof(str4) - 1];
		concatStrings(str12, str4, str124);
		dialog(str124);
		return 0;
	}

}*/

void reset_buf() {
	int row = 2;
	for (int col = 3; col < aa + 3; col++) {
		back_buf[row][col * 2] = ' ';

	}
}


int rmt = 0;
int status;
void dialog_m(char message[]) {

	//표기 될 행과 열의 길이 선언. 
	int show_dialog_col = 4;
	int show_dialog_row = 3;
	rmt = 4;


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
void reset_isboll() {
	for (int i = 0; i < n_player; i++)
	{
		player[i].is_alive = !player[i].is_dead;
	}
}
char message[] = "pass . fail!";
void jebi() {
	int n_alive = 0;

	for (int i = 0; i < n_player; i++)
	{
		if (player[i].is_alive == true)
		{
			n_alive++;
		}
	}
	int cur_x = 3;
	int cur_y = 4;
	while (n_alive > 1) {
		round += 1;
		if (q == 1) {
			break;
		}

		system("cls");
		jebi_init();
		display();
		while (1) {

			// player 0만 손으로 움직임(4방향)
			key_t key = get_key();
			if (key == K_QUIT) {
				break;
			}
			else if (key != K_UNDEFINED) {
				if (pass_arr[0] != 1) {
					move_manual(key);
					if (count == 0) {

						p0_x = px[0];
						p0_y = py[0];

					}
					else if (count == 1) {//3초 기다리는 동안 

						if ((p0_x != px[0]) || (p0_y != py[0])) {

							status = 0;

							for (int j = 1; j < n_player; j++) {
								//player[j] == 0 
								if (player[j] == 0 || pass_arr[j] == 1) {
									continue;
								}

								if (px[0] == px[j] && py[j] < py[0]) {
									status = 1;//가려진 상태 
								}
							}

							if (status == 0) {//가려지지 않은 상태라면 
								player[0] = 0;//die
								back_buf[px[0]][py[0]] = ' ';//화면에서 안보임 처리 
								n_alive--;//생존자수 1줄어들음 

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


			// player 1 부터는 랜덤으로 움직임(3방향+제자리)
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
						if (per[i] == 1) {//10 퍼센트 확률로 움직인 다면. 
							if (tick % period[i] == 0) {
								//죽은 사람 player[i] ==0 스킵
								if (player[i] == 0 || pass_arr[i] == 1) {
									continue;
								}

								status = 0;//가려지지 않은 상태

								for (int j = 0; j < n_player; j++) {
									//player[j] == 0 죽은사람을 스킵하지 않으면 죽은사람도 status 1로 만들어줌 보이진 않지만 x,y값이 바뀜.
									if (player[j] == 0 || pass_arr[j] == 1) {
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
									n_alive = n_alive - 1;
									message[7] = i + '0';
									dialog_m(message);
								}
							}
						}
					}
				}

			}


			for (int i = 0; i < n_player; i++) {
				if (player_pass(i) == 1) {
					back_buf[px[i]][py[i]] = ' ';
					pass_arr[i] = 1;
				}

			}
			int num_alive_players = count_alive_players();
			if (num_alive_players == 1) {
				break;
			}
			display();
			Sleep(10);
			tick += 10;

			
			int count_message = 0;

		}
		

	}

}


