#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processPair(char *line, int *elf1_start, int *elf1_end, int *elf2_start, int *elf2_end) {
    printf("\ninput: %s", line);
    char *elf1;
    char *elf2;
    elf1 = strsep(&line, ",");
    elf2 = line;

    char *end;

    char *part;
    /* split string at - */
    part = strsep(&elf1, "-");

    /* convert string to int */
    *elf1_start = atoi(part);
    *elf1_end = atoi(elf1);

    char *part2;
    /* split string at - */
    part2 = strsep(&elf2, "-");
    /* convert string to int */
    *elf2_start = strtol(part2, &end, 10);
    *elf2_end = atoi(elf2);
}

int compareRangesPart1(int *elf1_start, int *elf1_end, int *elf2_start, int *elf2_end) {
    printf("elf1_start: %d \n", *elf1_start);
    printf("elf1_end: %d \n", *elf1_end);
    printf("elf2_start: %d \n", *elf2_start);
    printf("elf2_end: %d \n", *elf2_end);

    // elf1 contains elf2
    if (*elf1_start <= *elf2_start && *elf1_end >= *elf2_end) {
        return 1;
    }
    else if (*elf2_start <= *elf1_start && *elf2_end >= *elf1_end) {
        return 1;
    }
    else { 
        return 0;
    }
}

int compareRangesPart2(int *elf1_start, int *elf1_end, int *elf2_start, int *elf2_end) {
    if (*elf1_start <= *elf2_start && *elf1_end >= *elf2_start) {
        return 1;
    }
    else if (*elf2_start <= *elf1_start && *elf2_end >= *elf1_start) {
        return 1;
    }
    else {
        return 0;
    }
}

void readFile(int *duplicateCounter) {
    FILE *file_ptr = fopen("input.txt", "r");

    if (file_ptr == NULL) {
        printf("Unable to read file");
        return;
    }
    
    /* Buffer to read one line at a time */
    char buffer[255];
    int lines_number = 0;

    /* read into bufffer, maximum of 255 Bytes from file_ptr*/
    while(fgets(buffer, 255, file_ptr) != NULL) {
        lines_number += 1;
        int elf1_start;
        int elf2_start;
        int elf1_end;
        int elf2_end;
        processPair(buffer, &elf1_start, &elf1_end, &elf2_start, &elf2_end);
        int answer = compareRangesPart2(&elf1_start, &elf1_end, &elf2_start, &elf2_end);
        if (answer == 1) {
            printf("true\n");
            *duplicateCounter += 1;
            printf("%d\n", *duplicateCounter);
        }
    }

    printf("lines: %d\n", lines_number);

    fclose(file_ptr);
}

int main() {
    int duplicateCounter = 0;
    readFile(&duplicateCounter);
    printf("Number of duplicates: %d\n", duplicateCounter);
    return 0;
}
