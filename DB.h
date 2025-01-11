#ifndef DB_H
#define DB_H

struct Employee {
    int EmpID;
    int EmpAge;
    char EmpName[40];
};

void createIndex(const char* fName);
int searchIndex(int empID);
void insertRecord(const char* fName);
void updateRecord(const char* fName);
void deleteRecord(const char* fName);
void searchRecord(const char* filename);
void displayAllRecords(const char* fName);
void backupDatabase(const char* fName);
bool validateInput(int id, int age, const char* name);
void sortRecords(const char* fName, int sortField);
void displayMenu();

#endif
