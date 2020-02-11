#include "include.h"

int create_master_file(void)
{
	data_t record;
	FILE* master;

	if ((master = fopen("master.txt", "at+")) == NULL)
	{
		fprintf(stderr, "�Է� ������ �� �� �����ϴ�.\n");
		return 0;
	}

	memset(&record, 0x00, sizeof(record));

	printf("����� �й��� 0 �Է�\n");

	while (TRUE)
	{
		printf("�й�:");
		scanf("%8s", record.number);
		while (getchar() != '\n');

		if (strcmp(record.number, "0") == 0)
		{
			break;
		}

		record.delete = FALSE;
		record.mode = ADD;

		printf("�̸�:");
		scanf("%10s", record.name);
		while (getchar() != '\n');

		printf("�а�:");
		scanf("%2s", record.major);
		while (getchar() != '\n');

		printf("�г�:");
		scanf("%c", &record.grade);
		while (getchar() != '\n');

		printf("����:");
		scanf("%s", record.score);
		while (getchar() != '\n');

		fwrite(&record, sizeof(record), 1, master);
	}

	fclose(master);
	return 0;
}

int create_transaction_file(void)
{
	data_t record;
	FILE* transaction;
	FILE* error;

	if ((transaction = fopen("transaction.txt", "at+")) == NULL)
	{
		fprintf(stderr, "�Է� ������ �� �� �����ϴ�.\n");
		return 0;
	}
	if ((error = fopen("transaction_error.txt", "at+")) == NULL)
	{
		fprintf(stderr, "�Է� ������ �� �� �����ϴ�.\n");
		return 0;
	}

	memset(&record, 0x00, sizeof(record)); //����ü �ʱ�ȭ

	printf("����� 0 �Է�\n");

	while (TRUE)
	{
		printf("���� : 0, �߰� : 1, ���� : 2, ���� : 3 \n�Է� : ");
		scanf("%d", &record.mode);
		while (getchar() != '\n');

		if (record.mode == ADD)
		{
			break;
		}
		else if (record.mode < ADD || record.mode > DELETE)
		{
			printf("���� ���� ���� �Է��Դϴ�.\n");

			continue;
		}

		record.delete = FALSE;

		printf("(���� ��) �й�:");
		scanf("%8s", record.number);
		while (getchar() != '\n');

		if (record.mode != DELETE)
		{
			printf("1. �̸�:");
			scanf("%10s", record.name);
			while (getchar() != '\n');

			printf("2. �а�:");
			scanf("%2s", record.major);
			while (getchar() != '\n');

			printf("3. �г�:");
			scanf("%c", &record.grade);
			while (getchar() != '\n');

			printf("4. ����:");
			scanf("%3s", record.score);
			while (getchar() != '\n');
		}

		if (record.mode == DELETE)
		{
			fwrite(&record, sizeof(record), 1, transaction);
		}
		else if (atoi(record.score) < ZERO || atoi(record.score) > HUNDRED)
		{
			fwrite(&record, sizeof(record), 1, error);
		}
		else if (record.grade <= ZERO + ASCII_ZERO || record.grade > FOUR + ASCII_ZERO)
		{
			fwrite(&record, sizeof(record), 1, error);
		}
		else if (strcmp(record.major, "CE") != 0 &&
			strcmp(record.major, "IE") != 0 &&
			strcmp(record.major, "ME") != 0 &&
			strcmp(record.major, "EE") != 0 &&
			strcmp(record.major, "AR") != 0)
		{
			fwrite(&record, sizeof(record), 1, error);
		}
		else
		{
			fwrite(&record, sizeof(record), 1, transaction);
		}
	}

	fclose(transaction);
	fclose(error);
	return 0;
}

int view_master_file(void)
{
	int i = 0;
	FILE* fp;
	data_t record;

	if ((fp = fopen("master.txt", "rt")) == NULL)
	{
		fprintf(stderr, "�Է� ������ �� �� �����ϴ�.\n");
		return 0;
	}

	fseek(fp, 0, SEEK_SET);
	fread(&record, sizeof(record), 1, fp);

	if (feof(fp))
	{
		printf("����� �����Ͱ� �����ϴ�.\n");

		return 0;
	}

	printf("+------+----------+------------+------+------+------+\n");
	printf("| ���� |   �й�   |    �̸�    | ���� | �г� | ���� |\n");
	printf("+------+----------+------------+------+------+------+\n");

	while (!feof(fp))
	{
		if (record.delete == ZERO)
		{
			i++;

			printf("| %4d ", i);
			printf("| %8s ", record.number);
			printf("| %10s ", record.name);
			printf("|  %2s  ", record.major);
			printf("|  %2c  ", record.grade);
			printf("| %3s  |\n", record.score);
		}

		fread(&record, sizeof(record), 1, fp);
	}

	printf("+------+----------+------------+------+------+------+\n");
	printf("| ���� ���� ��ȸ�� �л� ���ڵ� : %4d ��            |\n", i);
	printf("+---------------------------------------------------+\n");

	fclose(fp);
	return 0;
}

int view_transaction_file(void)
{
	int i = 0;
	FILE* fp;
	data_t record;

	if ((fp = fopen("transaction.txt", "rt")) == NULL)
	{
		fprintf(stderr, "�Է� ������ �� �� �����ϴ�.\n");
		return 0;
	}

	fread(&record, sizeof(record), 1, fp);

	if (feof(fp))
	{
		printf("����� �����Ͱ� �����ϴ�.\n");

		return 0;
	}

	printf("+------+------+----------+------------+------+------+------+\n");
	printf("| ���� | ���� |   �й�   |    �̸�    | ���� | �г� | ���� |\n");
	printf("+------+------+----------+------------+------+------+------+\n");

	while (!feof(fp))
	{
		if (record.delete == ZERO)
		{
			i++;

			printf("| %4d ", i);

			if (record.mode == INSERT)
			{
				printf("| %s ", "����");
			}
			else if (record.mode == EDIT)
			{
				printf("| %s ", "����");
			}
			else if (record.mode == DELETE)
			{
				printf("| %s ", "����");
			}

			printf("| %8s ", record.number);
			printf("| %10s ", record.name);
			printf("|  %2s  ", record.major);
			printf("|  %2c  ", record.grade);
			printf("| %3s  |\n", record.score);
		}

		fread(&record, sizeof(record), 1, fp);
	}

	printf("+------+------+----------+------------+------+------+------+\n");
	printf("| ���ŵǱ� �غ� ���� ���ڵ� : %d��                          |\n", i);
	printf("+----------------------------------------------------------+\n");

	fclose(fp);
	return 0;
}

int renew(void)
{
	int i, j;
	int master_line = 0;
	int transaction_line = 0;
	int flag = FALSE;
	data_t master_record;
	data_t transaction_record;
	data_t temp_record;
	FILE* master;
	FILE* transaction;
	FILE* error;

	if ((master = fopen("master.txt", "rb+")) == NULL)
	{
		fprintf(stderr, "�Է� ������ �� �� �����ϴ�.\n");
		return 0;
	}
	if ((transaction = fopen("transaction.txt", "rb")) == NULL)
	{
		fprintf(stderr, "���� Ʈ����� ���ڵ带 �Է��Ͻñ� �ٶ��ϴ�.\n");
		return 0;
	}
	if ((error = fopen("master_error.txt", "at+")) == NULL)
	{
		fprintf(stderr, "�Է� ������ �� �� �����ϴ�.\n");
		return 0;
	}

	memset(&master_record, 0x00, sizeof(master_record)); //����ü �ʱ�ȭ
	memset(&transaction_record, 0x00, sizeof(transaction_record)); //����ü �ʱ�ȭ

	fseek(transaction, 0, SEEK_SET);
	fread(&transaction_record, sizeof(data_t), 1, transaction);

	//Ʈ������� �� ������ ����
	while (!feof(transaction))
	{
		flag = FALSE;
		master_line = 0;
		fseek(master, 0, SEEK_SET);
		fread(&master_record, sizeof(data_t), 1, master);

		if (transaction_record.mode != INSERT)
		{
			//Ʈ����� ���ڵ� �� ���� ������ ���ڵ尡 ���� �� ����
			while (strcmp(transaction_record.number, master_record.number) != SAME)
			{
				master_line++;
				fseek(master, master_line * sizeof(data_t), SEEK_SET);
				fread(&master_record, sizeof(data_t), 1, master);

				if (feof(master))
				{
					fseek(error, 0, SEEK_END);
					fwrite(&transaction_record, sizeof(data_t), 1, error);
					flag = TRUE;
					break;
				}
			}
		}

		if (flag != TRUE)
		{
			if (transaction_record.mode == INSERT)
			{
				fseek(master, 0, SEEK_END);
				fwrite(&transaction_record, sizeof(data_t), 1, master);
			}
			else if (transaction_record.mode == EDIT)
			{
				fseek(master, master_line * sizeof(data_t), SEEK_SET);
				fwrite(&transaction_record, sizeof(data_t), 1, master);
			}
			else if (transaction_record.mode == DELETE)
			{
				master_record.delete = TRUE;
				fseek(master, master_line * sizeof(data_t), SEEK_SET);
				fwrite(&transaction_record, sizeof(data_t), 1, master);
			}
		}

		transaction_line++;
		fseek(transaction, transaction_line * sizeof(data_t), SEEK_SET);
		fread(&transaction_record, sizeof(data_t), 1, transaction);
	}

	for (i = 0; !feof(master); i++)
	{
		for (j = 0; j < i; j++)
		{
			fseek(master, j * sizeof(data_t), SEEK_SET);
			fread(&master_record, sizeof(data_t), 1, master);

			fseek(master, (j + 1) * sizeof(data_t), SEEK_SET);
			fread(&transaction_record, sizeof(data_t), 1, master);

			if (feof(master))
			{
				break;
			}

			if (atoi(master_record.number) > atoi(transaction_record.number))
			{
				temp_record = master_record;
				master_record = transaction_record;
				transaction_record = temp_record;
			}
			else
			{
				continue;
			}

			fseek(master, j * sizeof(data_t), SEEK_SET);
			fwrite(&master_record, sizeof(data_t), 1, master);

			fseek(master, (j + 1) * sizeof(data_t), SEEK_SET);
			fwrite(&transaction_record, sizeof(data_t), 1, master);
		}
	}

	_fcloseall();

	remove("transaction.txt"); //Ʈ����� �� ó���ϸ� �����.
	return 0;
}

int view_master_error(void)
{
	int i = 0;
	FILE* fp;
	data_t record;

	if ((fp = fopen("master_error.txt", "rt")) == NULL)
	{
		fprintf(stderr, "�Է� ������ �� �� �����ϴ�.");
	}

	fread(&record, sizeof(record), 1, fp);

	if (feof(fp))
	{
		printf("����� �����Ͱ� �����ϴ�.\n");

		return 0;
	}

	printf("+------+----------+------------+------+------+------+\n");
	printf("| ���� |   �й�   |    �̸�    | ���� | �г� | ���� |\n");
	printf("+------+----------+------------+------+------+------+\n");

	while (!feof(fp))
	{
		i++;

		printf("| %4d ", i);
		printf("| %8s ", record.number);
		printf("| %10s ", record.name);
		printf("|  %2s  ", record.major);
		printf("|  %2c  ", record.grade);
		printf("| %3s  |\n", record.score);

		fread(&record, sizeof(record), 1, fp);
	}

	printf("+------+----------+------------+------+------+------+\n");
	printf("| ������ ���� ���� ���ڵ� : %4d ��                 |\n", i);
	printf("+---------------------------------------------------+\n");

	fclose(fp);
	return 0;
}

int view_transaction_error(void)
{
	int i = 0;
	FILE* fp;
	data_t record;

	if ((fp = fopen("transaction_error.txt", "rt")) == NULL)
	{
		fprintf(stderr, "�Է� ������ �� �� �����ϴ�.");
	}

	fread(&record, sizeof(record), 1, fp);

	if (feof(fp))
	{
		printf("����� �����Ͱ� �����ϴ�.\n");

		return 0;
	}

	printf("+------+------+----------+------------+------+------+------+\n");
	printf("| ���� | ���� |   �й�   |    �̸�    | ���� | �г� | ���� |\n");
	printf("+------+------+----------+------------+------+------+------+\n");

	while (!feof(fp))
	{
		i++;

		printf("| %4d ", i);

		if (record.mode == INSERT)
		{
			printf("| %s ", "����");
		}
		else if (record.mode == EDIT)
		{
			printf("| %s ", "����");
		}
		else if (record.mode == DELETE)
		{
			printf("| %s ", "����");
		}

		printf("| %8s ", record.number);
		printf("| %10s ", record.name);
		printf("|  %2s  ", record.major);
		printf("|  %2c  ", record.grade);
		printf("| %3s  |\n", record.score);

		fread(&record, sizeof(record), 1, fp);
	}

	printf("+------+------+----------+------------+------+------+------+\n");
	printf("| Ʈ����� ���� ���ڵ� : %4d ��                           |\n", i);
	printf("+----------------------------------------------------------+\n");

	fclose(fp);
	return 0;
}