#include <stdio.h>
 
//MK: Visual Studio를 사용시 scanf 에러 제거함.
#pragma warning(disable:4996)
 
#define MAXSIZE 1000001
 
int cache[MAXSIZE];
 
//MK: 최대 Input에 대한 모든 Repeatless 번호를 생성하는 부분
void init() {
	int i = 1;
	int ptr = 1;
	while (i < MAXSIZE) {
		int tmp = ptr;
		int visited = 0;
		while (tmp > 0) {
			int reminder = tmp % 10;
			//MK: 나머지 값들을 확인하여 이전에 나온 숫자인지 확인함
			if ((visited & (1 << reminder)) == 0) {
				visited |= (1 << reminder);
			}
			else {
				break;
			}
			tmp /= 10;
		}
		if (tmp == 0) {
			cache[i] = ptr;
			i++;
		}
		ptr++;
	}
}
 
int main() {
	//freopen("input.txt", "r", stdin);
 
	init();
	while (1) {
		int tmp;
		scanf("%d", &tmp);
		if (tmp == 0) {
			break;
		}
		printf("%d\n", cache[tmp]);
	}
	return 0;
}