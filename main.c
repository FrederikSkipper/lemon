#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Function to update the "Ledighed" field
void updateLedighed(sqlite3 *db, int parkeringspladsnummer, int newLedighed) {
    char *errMsg = 0;
    char sqlUpdate[256];

    snprintf(sqlUpdate, sizeof(sqlUpdate), "UPDATE Parking SET Ledighed = %d WHERE Parkeringspladsnummer = %d;", newLedighed, parkeringspladsnummer);

    int rc = sqlite3_exec(db, sqlUpdate, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Ledighed updated successfully\n");
    }
}

// Function to handle user input to update Ledighed
void handleUserInput(sqlite3 *db) {
    int parkeringspladsnummer, newLedighed;

    printf("Enter Parkeringspladsnummer to update: ");
    scanf("%d", &parkeringspladsnummer);
    printf("Enter new Ledighed value (0 or 1): ");
    scanf("%d", &newLedighed);

    updateLedighed(db, parkeringspladsnummer, newLedighed);
}

int main(int argc, char* argv[]) {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("Parking.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    // Loop to handle multiple user inputs
    char continueInput = 'y';
    while (continueInput == 'y' || continueInput == 'Y') {
        handleUserInput(db);
        printf("Do you want to update another Ledighed? (y/n): ");
        scanf(" %c", &continueInput);
    }

    sqlite3_close(db);
    return 0;
}
