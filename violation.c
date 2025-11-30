#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "violation.h"

void loadData(Record *list, int *size) {
    FILE *f = fopen("data.txt", "r");
    if (!f) return;
    *size = 0;
    while (fscanf(f, "%s %[^;];%f %d %d",
                  list[*size].plate,
                  list[*size].type,
                  &list[*size].fine,
                  &list[*size].paid,
                  &list[*size].repeat_count) == 5) {
        (*size)++;
    }
    fclose(f);
}

void saveData(Record *list, int size) {
    FILE *f = fopen("data.txt", "w");
    for (int i = 0; i < size; i++) {
        fprintf(f, "%s %s; %.2f %d %d\n",
                list[i].plate,
                list[i].type,
                list[i].fine,
                list[i].paid,
                list[i].repeat_count);
    }
    fclose(f);
}

void addRecord(Record *list, int *size) {
    char plate[20], type[60];
    float base;

    printf("Plate: ");
    scanf("%s", plate);

    printf("Offense type: ");
    scanf(" %[^\n]", type);

    printf("Base fine: ");
    scanf("%f", &base);

    int found = -1;
    for (int i = 0; i < *size; i++) {
        if (strcmp(list[i].plate, plate) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        strcpy(list[*size].plate, plate);
        strcpy(list[*size].type, type);
        list[*size].fine = base;
        list[*size].paid = 0;
        list[*size].repeat_count = 1;
        (*size)++;
    } else {
        list[found].repeat_count++;
        list[found].fine += base * 0.5;
        strcpy(list[found].type, type);
        list[found].paid = 0;
    }

    saveData(list, *size);
}

void listRecords(Record *list, int size) {
    printf("\n--- Records ---\n");
    for (int i = 0; i < size; i++) {
        printf("%d) %s | %s | %.2f | %s | %d\n",
               i + 1,
               list[i].plate,
               list[i].type,
               list[i].fine,
               list[i].paid ? "PAID" : "UNPAID",
               list[i].repeat_count);
    }
}

void payFine(Record *list, int size) {
    char plate[20];
    printf("Enter plate: ");
    scanf("%s", plate);

    for (int i = 0; i < size; i++) {
        if (strcmp(list[i].plate, plate) == 0) {
            list[i].paid = 1;
            saveData(list, size);
            return;
        }
    }
}

void summaryReport(Record *list, int size) {
    float total = 0;
    int unpaid = 0;
    int repeat = 0;

    for (int i = 0; i < size; i++) {
        total += list[i].fine;
        if (!list[i].paid) unpaid++;
        if (list[i].repeat_count > 1) repeat++;
    }

    printf("\nTotal Revenue: %.2f\n", total);
    printf("Unpaid Violations: %d\n", unpaid);
    printf("Repeat Offenders: %d\n", repeat);
}
