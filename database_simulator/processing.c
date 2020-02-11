#include "include.h"

int create_master_file(void)
{
	data_t record;
	FILE* master;

	if ((master = fopen("master.txt", "at+")) == NULL)
	{
		fprintf(stderr, "입력 파일을 열 수 없습니다.\n");
		return 0;
	}

	memset(&record, 0x00, sizeof(record));

	printf("종료시 학번에 0 입력\n");

	while (TRUE)
	{
		printf("학번:");
		scanf("%8s", record.number);
		while (getchar() != '\n');

		if (strcmp(record.number, "0") == 0)
		{
			break;
		}

		record.delete = FALSE;
		record.mode = ADD;

		printf("이름:");
		scanf("%10s", record.name);
		while (getchar() != '\n');

		printf("학과:");
		scanf("%2s", record.major);
		while (getchar() != '\n');

		printf("학년:");
		scanf("%c", &record.grade);
		while (getchar() != '\n');

		printf("점수:");
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
		fprintf(stderr, "입력 파일을 열 수 없습니다.\n");
		return 0;
	}
	if ((error = fopen("transaction_error.txt", "at+")) == NULL)
	{
		fprintf(stderr, "입력 파일을 열 수 없습니다.\n");
		return 0;
	}

	memset(&record, 0x00, sizeof(record)); //구조체 초기화

	printf("종료시 0 입력\n");

	while (TRUE)
	{
		printf("종료 : 0, 추가 : 1, 수정 : 2, 삭제 : 3 \n입력 : ");
		scanf("%d", &record.mode);
		while (getchar() != '\n');

		if (record.mode == ADD)
		{
			break;
		}
		else if (record.mode < ADD || record.mode > DELETE)
		{
			printf("정의 되지 않은 입력입니다.\n");

			continue;
		}

		record.delete = FALSE;

		printf("(수정 할) 학번:");
		scanf("%8s", record.number);
		while (getchar() != '\n');

		if (record.mode != DELETE)
		{
			printf("1. 이름:");
			scanf("%10s", record.name);
			while (getchar() != '\n');

			printf("2. 학과:");
			scanf("%2s", record.major);
			while (getchar() != '\n');

			printf("3. 학년:");
			scanf("%c", &record.grade);
			while (getchar() != '\n');

			printf("4. 점수:");
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
		fprintf(stderr, "입력 파일을 열 수 없습니다.\n");
		return 0;
	}

	fseek(fp, 0, SEEK_SET);
	fread(&record, sizeof(record), 1, fp);

	if (feof(fp))
	{
		printf("저장된 데이터가 없습니다.\n");

		return 0;
	}

	printf("+------+----------+------------+------+------+------+\n");
	printf("| 순번 |   학번   |    이름    | 전공 | 학년 | 점수 |\n");
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
	printf("| 지금 까지 조회된 학생 레코드 : %4d 개            |\n", i);
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
		fprintf(stderr, "입력 파일을 열 수 없습니다.\n");
		return 0;
	}

	fread(&record, sizeof(record), 1, fp);

	if (feof(fp))
	{
		printf("저장된 데이터가 없습니다.\n");

		return 0;
	}

	printf("+------+------+----------+------------+------+------+------+\n");
	printf("| 순번 | 변경 |   학번   |    이름    | 전공 | 학년 | 점수 |\n");
	printf("+------+------+----------+------------+------+------+------+\n");

	while (!feof(fp))
	{
		if (record.delete == ZERO)
		{
			i++;

			printf("| %4d ", i);

			if (record.mode == INSERT)
			{
				printf("| %s ", "삽입");
			}
			else if (record.mode == EDIT)
			{
				printf("| %s ", "수정");
			}
			else if (record.mode == DELETE)
			{
				printf("| %s ", "삭제");
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
	printf("| 갱신되기 준비 중인 레코드 : %d개                          |\n", i);
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
		fprintf(stderr, "입력 파일을 열 수 없습니다.\n");
		return 0;
	}
	if ((transaction = fopen("transaction.txt", "rb")) == NULL)
	{
		fprintf(stderr, "먼저 트랜잭션 레코드를 입력하시기 바랍니다.\n");
		return 0;
	}
	if ((error = fopen("master_error.txt", "at+")) == NULL)
	{
		fprintf(stderr, "입력 파일을 열 수 없습니다.\n");
		return 0;
	}

	memset(&master_record, 0x00, sizeof(master_record)); //구조체 초기화
	memset(&transaction_record, 0x00, sizeof(transaction_record)); //구조체 초기화

	fseek(transaction, 0, SEEK_SET);
	fread(&transaction_record, sizeof(data_t), 1, transaction);

	//트랜잭션이 다 읽을때 까지
	while (!feof(transaction))
	{
		flag = FALSE;
		master_line = 0;
		fseek(master, 0, SEEK_SET);
		fread(&master_record, sizeof(data_t), 1, master);

		if (transaction_record.mode != INSERT)
		{
			//트랜잭션 레코드 한 줄이 마스터 레코드가 읽을 때 까지
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

	remove("transaction.txt"); //트랜잭션 다 처리하면 지운다.
	return 0;
}

int view_master_error(void)
{
	int i = 0;
	FILE* fp;
	data_t record;

	if ((fp = fopen("master_error.txt", "rt")) == NULL)
	{
		fprintf(stderr, "입력 파일을 열 수 없습니다.");
	}

	fread(&record, sizeof(record), 1, fp);

	if (feof(fp))
	{
		printf("저장된 데이터가 없습니다.\n");

		return 0;
	}

	printf("+------+----------+------------+------+------+------+\n");
	printf("| 순번 |   학번   |    이름    | 전공 | 학년 | 점수 |\n");
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
	printf("| 마스터 파일 오류 레코드 : %4d 개                 |\n", i);
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
		fprintf(stderr, "입력 파일을 열 수 없습니다.");
	}

	fread(&record, sizeof(record), 1, fp);

	if (feof(fp))
	{
		printf("저장된 데이터가 없습니다.\n");

		return 0;
	}

	printf("+------+------+----------+------------+------+------+------+\n");
	printf("| 순번 | 변경 |   학번   |    이름    | 전공 | 학년 | 점수 |\n");
	printf("+------+------+----------+------------+------+------+------+\n");

	while (!feof(fp))
	{
		i++;

		printf("| %4d ", i);

		if (record.mode == INSERT)
		{
			printf("| %s ", "삽입");
		}
		else if (record.mode == EDIT)
		{
			printf("| %s ", "수정");
		}
		else if (record.mode == DELETE)
		{
			printf("| %s ", "삭제");
		}

		printf("| %8s ", record.number);
		printf("| %10s ", record.name);
		printf("|  %2s  ", record.major);
		printf("|  %2c  ", record.grade);
		printf("| %3s  |\n", record.score);

		fread(&record, sizeof(record), 1, fp);
	}

	printf("+------+------+----------+------------+------+------+------+\n");
	printf("| 트랜잭션 오류 레코드 : %4d 개                           |\n", i);
	printf("+----------------------------------------------------------+\n");

	fclose(fp);
	return 0;
}