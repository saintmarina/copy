//
//  main.c
//  copy
//
//  Created by anna.maniuk on 8/21/23.
//

#include <stdio.h>
#include <errno.h>

#define MAX_LEN 256

int main(int argc, const char * argv[]) {
    char source_file[MAX_LEN];
    char target_file[MAX_LEN];
    
    // Request source and target files from the user
    printf("Enter path of file you want to copy from: ");
    scanf("%s", source_file);
    
    printf("Enter path of file you want to paste to: ");
    scanf("%s", target_file);
    
    printf("source_file is %s! \n", source_file);
    printf("target_file is %s! \n", target_file);
    
    // Open & validate source and target files
    FILE *source_file_fp;
    FILE *target_file_fp;
    
    
    source_file_fp = fopen(source_file, "r");
    // Validate source file
    errno = 0;
    if (source_file_fp == NULL) {
        printf("fopen for source file failed, errno = %d\n", errno);
    } else {
        printf("fopen for source file succeded \n");
    }
    
    // Validate target file
    errno = 0;
    target_file_fp = fopen(target_file, "w");
    if (target_file_fp == NULL) {
        printf("fopen for target file failed, errno = %d\n", errno);
    } else {
        printf("fopen for target file succeded \n");
    }
    
    if (target_file_fp == NULL || source_file_fp == NULL) {
        return -1;
    }
    
    return 0;
}
