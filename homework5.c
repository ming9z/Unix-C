/*1. data.txt ���Ͽ��� ���ڿ� ���ڰ� ���� ����Ǿ� �ִ�.
�ڽ� ���μ������� �� ������ ������ �����ϸ�, �ڽ��� �� ���Ͽ��� ����, ����, ������ ������ ���� ��� �θ𿡰� �����ϴ� �ڵ带 �ۼ��Ͻÿ�.

2. �Ʒ� ������ �����ϴ� ���� �ƴ϶�, ������ ������ �����غ�����.
named pipe�� �̿��Ͽ� ����-Ŭ���̾�Ʈ �ڵ带 ������ ex9_7s.c�� ex9_7c.c�� �ִ�.
�� �ڵ忡���� �θ� �ڽĿ��� ���ڿ��� �����ϱ⸸ �Ѵ�.
���� 1���� �θ� 2�� �̻��� �ڽĵ鿡�� ������ ���ڿ��� ������ ����� ������?*/


#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main() {

	int n;
	int fd; // ���� ����.
	int fd1[2], fd2[2];
	pid_t pid;
	char buf[257];
	int len, status;
	int length = 0, biglen;
	char temp = '\0';
	int i = 0;

	int jcount = 0, mcount = 0, numcount = 0;

	if (pipe(fd1) == -1) {
		perror("pipe");
		exit(1);

	}

	if (pipe(fd2) == -1) {
		perror("pipe");
		exit(1);


	}

	switch (pid = fork()) {

	case -1:
		perror("fork");
		exit(1);
		break;

	case 0:   //�ڽ�
		close(fd1[1]); // fd1[0] �θ𿡰� �����͸� �޾ƾ���
		close(fd2[0]); // fd2[1] �θ𿡰� ����,����,���� ���� ��������

		len = read(fd1[0], buf, 256);
		write(1, buf, len);

		printf("�θ𿡰� ����:%s\n", buf);

		for (i = 0; i < strlen(buf); i++) {

			temp = buf[i];

			if (temp < 'A' || temp > 'Z') {
				++numcount;
			}

			else if (temp == 'A' || temp == 'E' || temp == 'O' || temp == 'U' || temp == 'I') {
				++mcount;
			}

			else
				++jcount;

		}

		printf("����:%d\n", numcount);  // �������� ������
		printf("����:%d\n", jcount);
		printf("����:%d\n", mcount);

		strcpy(buf, "����,���,����\n");
		biglen = write(fd2[1], &jcount, sizeof(int));
		biglen = write(fd2[1], &mcount, sizeof(int));
		biglen = write(fd2[1], &numcount, sizeof(int));


	defalut: // �θ�
		close(fd1[0]); // fd1[1] �ڽĿ��� �����͸� ����
		close(fd2[1]); // fd2[0] �ڽĿ��� ����,����,���� ������ �޾ƾ���

		fd = open("data5.txt", O_RDWR);
		if (fd == -1) {
			perror("open");
			exit(1);

		}

		n = read(fd, buf, 50);

		if (n == -1) {
			perror("Read");
			exit(1);

		}
		printf("%s", buf);

		write(fd1[1], buf, 6);
		len = read(fd2[0], buf, 256);

		printf("�ڽĿ��� ����:%d\n", biglen);

		while (wait(&status) != pid)
			continue;

		break;


	}

	return 0;

}
