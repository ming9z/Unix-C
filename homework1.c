/*1. cat�� ������ ��ɾ� �����ϱ�
- �Ʒ��� ���� cate ������ �����ϸ� ^D�� ���������� ����� �Է��� ���Ͽ� �����ϴ� ���α׷� ����
>cate file_name
Hello world
Good
^D
>more file_name
2. ���� ������ Ư�� ���ڿ��� ���Ե� ���� ���
- �Ʒ� ������ ���� file_name�� ã�� ���ڿ��� �����ϸ� ������ �˻��Ͽ� �� ���ڿ��� ���Ե� ������ ����� ��
- �� ������ ����� �Լ��� ����ؾ� �ϸ�, ���� ���� �˻��� ���ڿ��� ���� ���̸� ���� ������ ����ؾ� ��
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
