/*
������ ���� ������ ��� ������ �ڵ带 �����Ͻÿ�.
1) data.txt ���Ͽ��� ������ ���� �й�, ������ 100�� ����Ǿ� �ִ�.
2020301001 98
2020301002 87
2020301003 75
. . .
2) programming2.c ���Ͽ���
- �ڽ� ���μ����� 2�� �����Ѵ�.
- ù��° �ڽ����μ������� data.txt�� 1, 50�̶�� �����͸� �����Ѵ�.
�ι�° �ڽ����μ������� data.txt�� 51, 100�̶�� �����͸� �����Ѵ�.
- �ڽ� ���μ����� child��� ���� ������ �����Ѵ�(exec �Լ� �̿�)
�ڽ��� �ռ� �˰Ե� ���� �����͸� �̿��Ͽ� �ڽ��� ���� �κ��� �л� ������ �о� ������ ����Ѵ�.
���������� ù��° �ڽ��� ������ ���Ͽ��� 50���� �л� ���� ������ ����Ͽ� result1.txt �� �����Ѵ�.�ι�° �ڽ��� result2.txt�� ������ �����Ѵ�.
- �θ� ���μ����� �ڽĵ��� ��� ������ �� result1.txt�� result2.txt ������ �о� ��ü ������ ���� �� ����� ����Ѵ�

* �л����� �ѱ� ���Ͽ� ����, �ڵ�, �������� ��� �����ÿ�.��, ������ ���ε��� �������� ���ÿ�.
�׸��� �ѱ� ������ �̸��� "������ �й�_�̸�_programming2.hwp"�� �����Ͻÿ�.���� ��� 2020301001 ȫ�浿 �л��� "2020301001_ȫ�浿_programming2.hwp"�� �����Ͻÿ�.
*/




#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc, char* argv[]) {

	pid_t pids[2], pid;
	int runprocess = 0;
	int state;
	int allsum = 0;
	int sum1, sum2;
	float avg;
	int count = 100;

	while (runprocess < 2) {

		pid = wait(&state);
		pids[runprocess] = fork();

		if (pids[runprocess] < 0) {
			return -1;
		}

		else if (pids[runprocess] == 0) {

			if (pids[0] == 0) {

				execl("/2018301076/programming2.c", "child", NULL);

				int sum = 0;
				int n;
				int s;
				int i;

				FILE* fp = fopen("data.txt", "r");
				FILE* fp2 = fopen("result1.txt", "w+");

				for (i = 0; i < 50; i++) {
					fscanf(fp, "%d", &s);
					sum += s;
				}

				fprintf(fp2, "%d\n", sum);

				fclose(fp);
				fclose(fp2);

				sleep(5);
				printf("�ڽ����μ���1 ����\n");
				exit(0);

			}


			else if (pids[1] == 0) {

				execl("/2018301076/programming2.c", "child", NULL);


				int sum = 0;
				int n;
				int s;
				int i;

				FILE* fp = fopen("data.txt", "r");
				FILE* fp2 = fopen("result2.txt", "w+");

				for (i = 51; i < 100; i++) {
					fscanf(fp, "%d", &s);
					sum += s;
				}

				fprintf(fp2, "%d\n", sum);

				fclose(fp);
				fclose(fp2);

				sleep(5);
				printf("�ڽ����μ���2����\n");

				exit(0);

			}

		}

		else {
			printf("parents process // child process wait\n");

			FILE* fp1 = fopen("result1.txt", "r");
			FILE* fp2 = fopen("result2.txt", "r");

			fscanf(fp1, "%d", &sum1);
			fscanf(fp2, "%d", &sum2);
			allsum = sum1 + sum2;
			avg = (float)allsum / count;

			fclose(fp1);
			fclose(fp2);

		}

		runprocess++;

	}

	printf("���=%f\n", avg);

	return 0;
}
