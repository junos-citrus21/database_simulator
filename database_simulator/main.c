#include "include.h"

int help(void)
{
	printf("+---------------------------+\n");
	printf("| 도움말                    |\n");
	printf("+---------------------------+\n"); 
	printf("| 1.마스터파일 출력         |\n");
	printf("| 2.트랜잭션파일 입력       |\n");
	printf("| 3.트랜잭션파일 출력       |\n");
	printf("| 4.갱신                    |\n");
	printf("| 5.마스터파일 오류 출력    |\n");
	printf("| 6.트랜잭션파일 오류 출력  |\n");
	printf("+---------------------------+\n");
	printf("| 7.마스터파일 입력         |\n");
	printf("| 8.도움말                  |\n");
	printf("| 0.종료                    |\n");
	printf("+---------------------------+\n");

	return 0;
}

int end(void)
{
	exit(0);
	return 0;
}

int main(void)
{
	int choice;
	int (*fp[])(void) = { end, view_master_file, create_transaction_file, view_transaction_file, renew, view_master_error, view_transaction_error, create_master_file, help};

	help();

	while (TRUE)
	{
		printf(">>>");

		scanf("%d", &choice);

		if (choice < 0 || choice > 8)
		{
			printf("정의 되지 않은 입력입니다.\n");
			continue;
		}

		(fp)[choice]();
	}

	return 0;
}