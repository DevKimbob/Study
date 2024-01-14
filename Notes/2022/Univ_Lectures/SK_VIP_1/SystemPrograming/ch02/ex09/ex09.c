// getcwd가 오류를 낼 수 있는 상황인지가 의문이라
// chdir가 오류를 내는 상황을 가정하여 코딩

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char *cwd;
    char choice;

    cwd = getcwd(NULL, BUFSIZ);
    printf("1.Current Directory : %s\n", cwd);

    if (chdir("bit") == -1) {
        perror("bit");
        printf("Make new dir \"bit\"? [Y/n] : ");
        scanf("%c", &choice);
        
        switch (choice) {
            case 'Y':
            case 'y':
                if (mkdir("bit", 0755) == -1){
                    perror("bit");
                    exit(1);
                }
                
                chdir("bit");
                break;
            case 'n':
            default :
                exit(1);
        }
    }

    cwd = getcwd(NULL, BUFSIZ);
    printf("2.Current Directory : %s\n", cwd);

    free(cwd);
}