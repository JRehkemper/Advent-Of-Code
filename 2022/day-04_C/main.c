#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processPair(char *line, int *elf1_start, int *elf1_end, int *elf2_start, int *elf2_end) {
    printf("input: %s", line);
    char *elf1;
    char *elf2;
    elf1 = strsep(&line, ",");
    elf2 = line;


    char *end;
    /* *elf1_start = strtol(elf1, &end, 10);
    *elf1_end = strtol(&elf1[2], &end, 10);
    *elf2_start = strtol(elf2, &end, 10);
    *elf2_end = strtol(&elf2[2], &end, 10);*/

    /* TODO: Fix pointers...*/
    char *part;
    part = strsep(&elf1, "-");
    printf("part: %s\n", part);
    *elf1_start = strtol(part, &end, 10);
    printf("rest: %s\n", elf1);
    elf1_end = elf1;

    char *part2;
    part2 = strsep(&elf2, "-");
    printf("part2: %s\n", part2);
    *elf2_start = strtol(part2, &end, 10);
    elf2_end = elf2;
    printf("start: %d\n", *elf1_start);
    printf("end: %d\n", elf1_end);
}

int compareRanges(int *elf1_start, int *elf1_end, int *elf2_start, int *elf2_end) {
    // elf1 contains elf2
    if (*elf1_start <= *elf2_start) {
        if (*elf1_end >= *elf2_end) {
            return 1;
        }
        else {
            return 0;
        }
    }
    // elf2 contains elf1
    else if (*elf2_start <= *elf1_start) {
        if (*elf2_end >= *elf1_end) {
            return 1;
        }
        else {
            return 0;
        }
    }

    return 0;
}

void readFile(int *duplicateCounter) {
    FILE *file_ptr = fopen("example-input.txt", "r");

    if (file_ptr == NULL) {
        printf("Unable to read file");
        return;
    }
    
    /* Buffer to read one line at a time */
    char buffer[255];

    /* read into bufffer, maximum of 255 Bytes from file_ptr*/
    while(fgets(buffer, 255, file_ptr) != NULL) {
        int elf1_start;
        int elf2_start;
        int elf1_end;
        int elf2_end;
        processPair(buffer, &elf1_start, &elf1_end, &elf2_start, &elf2_end);
        if (compareRanges(&elf1_start, &elf1_end, &elf2_start, &elf2_end) == 1) {
            printf("true\n");
            *duplicateCounter += 1;
        }
    }

    fclose(file_ptr);
}

int main() {
    int duplicateCounter = 0;
    readFile(&duplicateCounter);
    printf("Number of duplicates: %d\n", duplicateCounter);
    return 0;
}