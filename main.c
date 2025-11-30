#include <stdio.h>
#include <stdlib.h>
#include "violation.h"

int main() {
    Record list[200];
    int size = 0;
    int choice;

    loadData(list, &size);

    while (1) {
        printf("\n1 Add Record\n2 List Records\n3 Pay Fine\n4 Summary Report\n5 Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) addRecord(list, &size);
        else if (choice == 2) listRecords(list, size);
        else if (choice == 3) payFine(list, size);
        else if (choice == 4) summaryReport(list, size);
        else if (choice == 5) break;
    }
    return 0;
}
