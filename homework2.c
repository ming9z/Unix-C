/*
다음과 같은 내용을 모두 구현한 코드를 제출하시오.
1) data.txt 파일에는 다음과 같이 학번, 성적이 100개 저장되어 있다.
2020301001 98
2020301002 87
2020301003 75
. . .
2) programming2.c 파일에서
- 자식 프로세스를 2개 생성한다.
- 첫번째 자식프로세스에게 data.txt와 1, 50이라는 데이터를 전달한다.
두번째 자식프로세스에게 data.txt와 51, 100이라는 데이터를 전달한다.
- 자식 프로세스는 child라는 실행 파일을 수행한다(exec 함수 이용)
자식은 앞서 알게된 파일 데이터를 이용하여 자신이 맡은 부분의 학생 성적을 읽어 총합을 계산한다.
최종적으로 첫번째 자식은 데이터 파일에서 50명의 학생 성적 총합을 계산하여 result1.txt 에 저장한다.두번째 자식은 result2.txt에 총합을 저장한다.
- 부모 프로세스는 자식들이 모두 종료한 후 result1.txt와 result2.txt 파일을 읽어 전체 총합을 더한 후 평균을 출력한다

* 학생들은 한글 파일에 설명, 코드, 실행결과를 모두 넣으시오.즉, 각각을 따로따로 저장하지 마시오.
그리고 한글 파일의 이름은 "본인의 학번_이름_programming2.hwp"로 지정하시오.예를 들어 2020301001 홍길동 학생은 "2020301001_홍길동_programming2.hwp"로 저장하시오.
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
				printf("자식프로세스1 종료\n");
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
				printf("자식프로세스2종료\n");

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

	printf("평균=%f\n", avg);

	return 0;
}
