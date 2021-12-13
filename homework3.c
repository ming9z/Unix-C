/*※ 파일 처리를 수행해야 할 경우, 반드시 저수준 함수를 이용하시오.그리고 코드 설명과 실행 결과까지 모두 한글에 작성하시고, 파일 이름은 "학번_이름_중간과제.hwp"로 하세요.

1) count 프로그램을 파일명을 인자로 받아서 그 파일의 크기(파일내에 포함된 문자의 개수)나 파일의 내용을 출력하는 기능을 가진다.단 반드시 하나의 파일명을 주어야 하며, -s 옵션을 사용할 경우 파일의 크기 대신 파일의 내용을 화면에 3줄씩 출력합니다.또한 코드는 하나 이상의 동적 메모리 할당 코드를 수행하여야 합니다.
사용예 > count ↲
Error !You should enter one file name .
> count data.txt ↲
data.txt : 180
> count –s data.txt
The file contains . . .
. . .
// 3줄 이상일 경우, enter를 치면 계속 출력하고 q를 누르면 종료
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>

size_t file_size_check(char* filename)
{
    struct stat data;
    if (stat(filename, &data) != 0) {
        perror("Error! You should enter one file name.\n");
    }
    return data.st_size;
}

int main(int argc, char* argv[])
{
    char* filename;
    size_t size;

    char ch;
    int fd;
    int n;
    char* buffer;

    buffer = malloc(sizeof(char) * 100);


    if (argc == 2 || argc == 3)
    {
        if (argc == 2) {

            argv[0] = "count";
            filename = argv[1];

            size = file_size_check(filename);
            printf("%s : %d\n", filename, size);

        }


        else if (argc == 3) {


            argv[0] = "count";
            argv[1] == "s";
            filename = argv[2];

            fd = open(argv[2], O_RDONLY);

            n = read(fd, buffer, 80);

            if (n == -1) {
                perror("Read");
                exit(1);
            }
            // while(ch=gethar()!="q")
            printf("%s\n", buffer);

        }

    }

    close(fd);
    free(buffer);

    return 0;
}
