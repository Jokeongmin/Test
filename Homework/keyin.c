#include <conio.h>
#include <stdbool.h>
#include "keyin.h"

// �̸� ���ص��� ���� Ű�� �ԷµǸ� �����ϱ� ���� �Լ�
bool is_valid(key_t key) {
	// keyin.h�� �ִ� ��ϰ� �Ȱ��� �������(K_UNDEFINED ����)
	static key_t key_list[] = {
		K_UP,
		K_DOWN,
		K_LEFT,
		K_RIGHT,
		K_QUIT
	};

	for (int i = 0; i < N_KEY; i++) {
		if (key_list[i] == key) {
			return true;
		}
	}
	return false;
}

// Ű���忡�� �Է� ���� Ű�� ���� Ű���� �����ؼ� ����
key_t get_key(void) {
	if (!_kbhit()) {
		return K_UNDEFINED;
	}

	int key = _getch();
	if (key == K_ARROW) {
		key = _getch();
	}

	if (is_valid(key)) {
		return key;
	}
	else {
		return K_UNDEFINED;
	}
}
