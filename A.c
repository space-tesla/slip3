Q.1) Print the type of file and inode number where file name accepted through Command Line

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;
    if (stat(argv[1], &fileStat) == 0) {
        printf("File: %s\n", argv[1]);
        printf("Inode number: %ld\n", fileStat.st_ino);

        if (S_ISDIR(fileStat.st_mode)) {
            printf("File Type: Directory\n");
        } else if (S_ISREG(fileStat.st_mode)) {
            printf("File Type: Regular File\n");
        } else if (S_ISLNK(fileStat.st_mode)) {
            printf("File Type: Symbolic Link\n");
        } else {
            printf("File Type: Other\n");
        }
    } else {
        perror("stat failed");
    }

    return 0;
}

Output:
File: testfile.txt
Inode number: 123456
File Type: Regular File