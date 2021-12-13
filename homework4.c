/*부모와 자식 프로세스가 서로 게임을 한다.아래의 규칙을 메모리 매핑 기법을 통해 구현하시오.

변수 int value 는 0으로 초기화되어 있다.
각 프로세스는 자기 차례가 되면 1 - 3사이의 임의의 숫자를 하나 생성한 후 value 변수 값과 더한다.
만약 더한 값 value가 20이 넘으면 그 프로세스는 지게 된다.
(예)
부모 value 자식
0
2 2
5 3
1 6
9 3
. . .
2 18
20 2 < -자식 프로세스가 게임에 지게 됨
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
