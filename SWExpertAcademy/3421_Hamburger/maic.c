//MK: 수제 버거 장인 문제 해결 코드
//MK: 모든 방법을 다 찾아보고 문제를 해결하는 방법

#include <stdio.h>

//MK: Visual Studio를 사용시 scanf 에러 제거함
#pragma warning(disable:4996)

#define MAXCOM 400

int inputSize;
int numCom;
int combination[MAXCOM];

int main(void)
{
	int testCase;
	//MK: input.txt 파일에서 입력 읽기
	//freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d", &testCase);
	for (int m = 1; m <= testCase; m++)
	{
		scanf("%d %d", &inputSize, &numCom);
		for (int i = 0; i < numCom; i++) {
			int tmp1, tmp2;
			scanf("%d %d", &tmp1, &tmp2);
			combination[i] = (1 << tmp1-1) | (1 << tmp2-1);
		}
		//MK: 모든 가능한 조합을 찾아보고 조합이 안되는 부분은 제거하는 코드
		int ret = 1 << inputSize;
		for (int i = 0; i < (1 << inputSize); i++) {
			for (int j = 0; j < numCom; j++) {
				int tmp = i & combination[j];
				if (tmp == combination[j]) {
					ret--;
					break;
				}
			}
		}
		printf("#%d %d\n", m, ret);
	}
	return 0;
}