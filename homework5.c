/*1. data.txt 파일에는 문자와 숫자가 섞여 저장되어 있다.
자식 프로세스에서 이 파일의 내용을 전달하면, 자식은 그 파일에서 자음, 모음, 숫자의 개수를 각각 세어서 부모에게 전달하는 코드를 작성하시오.

2. 아래 내용은 구현하는 것이 아니라, 본인의 생각을 정리해보세요.
named pipe를 이용하여 서버-클라이언트 코드를 구현한 ex9_7s.c와 ex9_7c.c이 있다.
이 코드에서는 부모가 자식에게 문자열을 전달하기만 한다.
만약 1개의 부모가 2개 이상의 자식들에게 동일한 문자열을 전달할 방법이 있을까?*/


#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main() {

	int n;
	int fd; // 파일 읽음.
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

	case 0:   //자식
		close(fd1[1]); // fd1[0] 부모에게 데이터를 받아야함
		close(fd2[0]); // fd2[1] 부모에게 자음,모음,숫자 갯수 보내야함

		len = read(fd1[0], buf, 256);
		write(1, buf, len);

		printf("부모에게 받음:%s\n", buf);

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

		printf("숫자:%d\n", numcount);  // 무슨값이 나오나
		printf("자음:%d\n", jcount);
		printf("모음:%d\n", mcount);

		strcpy(buf, "자음,모움,숫자\n");
		biglen = write(fd2[1], &jcount, sizeof(int));
		biglen = write(fd2[1], &mcount, sizeof(int));
		biglen = write(fd2[1], &numcount, sizeof(int));


	defalut: // 부모
		close(fd1[0]); // fd1[1] 자식에게 데이터를 보냄
		close(fd2[1]); // fd2[0] 자식에게 자음,모음,숫자 갯수를 받아야함

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

		printf("자식에게 받음:%d\n", biglen);

		while (wait(&status) != pid)
			continue;

		break;


	}

	return 0;

}
