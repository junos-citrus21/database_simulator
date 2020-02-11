#include "include.h"

int help(void)
{
	printf("+---------------------------+\n");
	printf("| ����                    |\n");
	printf("+---------------------------+\n"); 
	printf("| 1.���������� ���         |\n");
	printf("| 2.Ʈ��������� �Է�       |\n");
	printf("| 3.Ʈ��������� ���       |\n");
	printf("| 4.����                    |\n");
	printf("| 5.���������� ���� ���    |\n");
	printf("| 6.Ʈ��������� ���� ���  |\n");
	printf("+---------------------------+\n");
	printf("| 7.���������� �Է�         |\n");
	printf("| 8.����                  |\n");
	printf("| 0.����                    |\n");
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
			printf("���� ���� ���� �Է��Դϴ�.\n");
			continue;
		}

		(fp)[choice]();
	}

	return 0;
}