// 디렉터리의 내용을 읽는 위치 파악하기

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *dp;
    struct dirent *dent;
    long loc;

    dp = opendir(".");

    printf("Start Position : %ld\n", telldir(dp));
    while ((dent = readdir(dp))) {
        printf("Read : %10s -> ", dent->d_name);
        // printf("Read : %s -> ", dent->d_name);
        printf("Cur Position : %ld\n", telldir(dp));
    }

    printf("** Directory Position Rewind **\n");
    rewinddir(dp);
    printf("Cur Position : %ld\n", telldir(dp));

    printf("** Move Directory Pointer **\n");
    readdir(dp);
    readdir(dp);
    loc = telldir(dp);
    rewinddir(dp);
    seekdir(dp, loc);
    printf("Cur Position : %ld\n", telldir(dp));

    dent = readdir(dp);
    printf("Read : %10s \n", dent->d_name);
    // printf("Read : %s \n", dent->d_name);

    closedir(dp);
}