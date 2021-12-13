/*1. cat과 유사한 명령어 구현하기
- 아래와 같이 cate 파일을 실행하면 ^D를 누를때까지 사용자 입력을 파일에 저장하는 프로그램 구현
>cate file_name
Hello world
Good
^D
>more file_name
2. 파일 내에서 특정 문자열이 포함된 문장 출력
- 아래 예제와 같이 file_name과 찾을 문자열을 지정하면 파일을 검색하여 그 문자열이 포함된 문장을 출력할 것
- 단 저수준 입출력 함수를 사용해야 하며, 파일 내에 검색할 문자열이 여러 개이면 여러 문장을 출력해야 함
>find file_name Hel
Hello world
>*/


#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* fp;
    int c;

    fp = fopen(argv[1], "w+");

    if (fp != NULL) {
        while ((c = getchar()) != EOF) {
            fputc(c, fp);
        }


        fclose(fp);
    }
}
[min@ming9z 2018301076]$ cat find.c
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {

    char buffer[256];
    char word[256];
    int line = 0;


    int fd;
    mode_t mode;

    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    fd = open(argv[1], O_CREAT, mode);

    while (fgets(buffer, 256, fd))
    {
        line++;
        if (strstr(buffer, word))
            printf("%s", word);
    }

    close(fd);

    return 0;

}
