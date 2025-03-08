#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Part record structure
typedef struct {
    int partNumber;
    char partName[50];
    float partSize;
    char partSizeMetric[10];
    float partCost;
} Part;

// Function declarations
void printRecords(Part* db, int count);
void printRecordCount(int count);
void printDbSize(int count);
Part* addRecord(Part* db, int* count);
Part* deleteRecord(Part* db, int* count);

int main() {
    Part* db = NULL;
    int recordCount = 0;
    int choice;

    do {
        // Show menu
        printf("\nMENU\n=======\n");
        printf("1. Print all records\n");
        printf("2. Print number of records\n");
        printf("3. Print size of database\n");
        printf("4. Add records\n");
        printf("5. Delete record\n");
        printf("6. Exit\n");
        printf("\nChoice: ");

        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                printRecords(db, recordCount);
                break;
            case 2:
                printRecordCount(recordCount);
                break;
            case 3:
                printDbSize(recordCount);
                break;
            case 4:
                db = addRecord(db, &recordCount);
                break;
            case 5:
                db = deleteRecord(db, &recordCount);
                break;
            case 6:
                printf("Exiting...\n");
                if (db != NULL) {
                    free(db);
                    db = NULL;
                }
                break;
            default:
                printf("Invalid option!\n");
        }
    } while (choice != 6);

    return 0;
}
    
// Print all database records
void printRecords(Part* db, int count) {
    if (count == 0) {
        printf("No records to display.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nRecord #%d:\n", i + 1);
        printf("Part Number: %d\n", db[i].partNumber);
        printf("Part Name: %s\n", db[i].partName);
        printf("Size: %.2f %s\n", db[i].partSize, db[i].partSizeMetric);
        printf("Cost: $%.2f\n", db[i].partCost);
    }
}

// Print number of records
void printRecordCount(int count) {
    printf("Number of records: %d\n", count);
}

// Print database size in bytes
void printDbSize(int count) {
    printf("Database size: %zu bytes\n", count * sizeof(Part));
}

// Add a new record
Part* addRecord(Part* db, int* count) {
    Part* newDb;

    // Allocate new memory
    if (*count > 0) {
        newDb = malloc((*count + 1) * sizeof(Part));
        if(!newDb) {
            printf("Memory allocation failed!\n");
            return db;
        }

        // Copy existing records
        for (int i = 0; i < *count; i++) {
            newDb[i] = db[i];
        }

        // Free old memory 
        free(db);  
    } else {
        newDb = malloc(sizeof(Part));
        if (!newDb) {
            printf("Memory allocation failed!\n");
            return NULL;
        }
    }

    // Get new record data 
    printf("\nEnter part information:\n");

    printf("Part Number: ");
    scanf("%d", &newDb[*count].partNumber);
    getchar();

    printf("Part Name: ");
    fgets(newDb[*count].partName, 50, stdin);
    newDb[*count].partName[strcspn(newDb[*count].partName, "\n")] = 0;

    printf("Part Size: ");
    scanf("%f", &newDb[*count].partSize);
    getchar();

    printf("Size Metric (mm, cm, etc): ");
    fgets(newDb[*count].partSizeMetric, 10, stdin);
    newDb[*count].partSizeMetric[strcspn(newDb[*count].partSizeMetric, "\n")] = 0;

    printf("Part Cost: ");
    scanf("%f", &newDb[*count].partCost);
    getchar();

    (*count)++;
    printf("Record added.\n");

    return newDb;
}

// Delete the last record
Part* deleteRecord(Part* db, int* count) {
    if (*count <= 0) {
        printf("No records to delete.\n");
        return db;
    }

    (*count)--;

    // If we've deleted the last record
    if (*count == 0) {
        free(db);
        printf("Last record deleted.\n");
        return NULL;
    }

    // create new smaller database
    Part* newDb = malloc(*count * sizeof(Part));
    if (!newDb) {
        printf("Memory allocation failed!\n");
        (*count)++; // Restore count on failure
        return db;
    }

    // Copy records except the last one
    for (int i = 0; i < *count; i++) {
        newDb[i] = db[i];
    }

    free(db);
    printf("Record deleted.\n");

    return newDb;
}