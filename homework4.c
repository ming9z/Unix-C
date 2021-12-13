/*�θ�� �ڽ� ���μ����� ���� ������ �Ѵ�.�Ʒ��� ��Ģ�� �޸� ���� ����� ���� �����Ͻÿ�.

���� int value �� 0���� �ʱ�ȭ�Ǿ� �ִ�.
�� ���μ����� �ڱ� ���ʰ� �Ǹ� 1 - 3������ ������ ���ڸ� �ϳ� ������ �� value ���� ���� ���Ѵ�.
���� ���� �� value�� 20�� ������ �� ���μ����� ���� �ȴ�.
(��)
�θ� value �ڽ�
0
2 2
5 3
1 6
9 3
. . .
2 18
20 2 < -�ڽ� ���μ����� ���ӿ� ���� ��
	*/

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]) {

	int fd;
	pid_t pid, pidn;
	caddr_t addr;
	struct stat statbuf;

	char str[10];

	int status;
	int turn = 0;   // turn 0 par    turn 1 child
	int total = 0;

	int num1 = 0;
	int num2 = 0;

	srand((unsigned)time(NULL));

	if (argc != 2) {

		fprintf(stderr, "Usage : %s filename\n", argv[0]);
		exit(1);

	}

	if (stat(argv[1], &statbuf) == -1) {

		perror("stat");
		exit(1);

	}

	if ((fd = open(argv[1], O_RDWR)) == -1) {

		perror("open");
		exit(1);

	}

	addr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);

	if (addr == MAP_FAILED) {

		perror("mmap");
		exit(1);

	}


	close(fd);

	while (total <= 20) {
		pidn = wait(&status);
		switch (pid = fork()) {

		case -1:
			perror("fork");
			exit(1);
			break;

		case 0: // child
			num1 = (rand() % 3) + 1;
			total = total + num1;

			addr[4] = atoi(&num1);
			addr[2] = atoi(&total);

			printf("     %d  %d\n", (int)(addr[2] - '0'), (int)(addr[4] - '0'));
			break;

		default:

			num2 = (rand() % 3) + 1;
			total = total + num2;

			addr[0] = atoi(&num2);
			addr[2] = atoi(&total);

			printf("%d  %d\n", (int)(addr[0] - '0'), (int)(addr[2] - '0'));
			break;

		}

	}
	return 0;

}
