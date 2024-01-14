// symlink() 함수로 심벌릭 링크 생성하기

#include <unistd.h>

int main() {
    symlink("linux.txt", "linux.sym");
}