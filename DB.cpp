#include "DB.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>

using namespace std;


bool validateInput(int id, int age, const char* name) {
    if (id <= 0) return false;
    if (age <= 0 || age > 120) return false;
    if (strlen(name) == 0 || strlen(name) >= 40) return false;
    return true;
}

void createIndex(const char* fName) {

    ifstream empFile(fName);
    ofstream out("index.txt");
    /*adafaefa*/

    if (!empFile.is_open())
    {
        cout << "Failed opening the file.\n";
        return;
    }
    else if (!out.is_open())
    {
        cout << "Failed opening the file.\n";
        return;
    }

    int indexNum = 0;
    string empRecord;

    while (getline(empFile, empRecord)) 
    {
        int empID;
        sscanf(empRecord.c_str(), "%d", &empID);
        out << empID << " " << indexNum << endl;
        indexNum = indexNum + empRecord.length() + 1;
    }

    out.close();
    empFile.close();
}

int searchIndex(int empID) {
    ifstream indexFile("index.txt");
    string empRecord;
    int employeeID;
    int indexNum;

    if (!indexFile.is_open()) {
        cout << "Failed opening the file.\n";
        return -1;
    }

    while (getline(indexFile, empRecord)) 
    {
        sscanf(empRecord.c_str(), "%d %d", &employeeID, &indexNum);
        if (employeeID== empID) 
        {
            return indexNum;
        }
    }

    indexFile.close();

    return -1;
}

void insertRecord(const char* fName) {
    int empID;
    int empAge;
    char empName[40];

    cout << "Enter Employee ID.\n";
    cin >> empID;

    ofstream createFile(fName, ios::app);
    createFile.close();

    ifstream empFile(fName);
    ofstream temp("temp.txt");


    if (!empFile.is_open())
    {
        cout << "Failed opening the file.\n";
        return;
    }
    else if (!temp.is_open())
    {
        cout << "Failed opening the file.\n";
        return;
    }

    bool exist = false;
    string line;
    while (getline(empFile, line)) {
        int studentId;
        sscanf(line.c_str(), "%d", &studentId);
        if (studentId == empID) {
            exist = true;
            cout << "The ID is already exist.\n";
            break;
        }
        temp << line << endl;
    }

    empFile.close();
    temp.close();

    if (!exist) {
        cout << "Enter Employee name: ";
        cin.ignore();
        cin.getline(empName, 40);
        cout << "Enter Employee age: ";
        cin >> empAge;

        if (!validateInput(empID, empAge, empName)) {
            cout << "Invalid input! Please check:\n";
            cout << "- ID must be positive\n";
            cout << "- Age must be between 1-120\n";
            cout << "- Name must not be empty or exceed 39 characters\n";
            return;
        }

        ofstream out(fName, ios::app);
        if (!out.is_open()) {
            cout << "Failed opening file.\n" ;
            return;
        }

        out << empID << " " << empName << " " << empAge << endl;
        cout << "Added successfully.\n";
    }

    remove("temp.txt");
}

void updateRecord(const char* fName) {
    int empID;
    int UpdatedAge;
    char UpdatedName[40];

    cout << "Enter employee ID.\n";
    cin >> empID;

    int indexNum = searchIndex(empID);

    if (indexNum == -1) 
    {
        cout << "ID does not exists.\n";
        return;
    }

    cout << "Enter new name <Press Enter to keep old one>:";
    cin.ignore();
    cin.getline(UpdatedName, 40);

    cout << "Enter new age (Enter 0 to keep old age): ";
    cin >> UpdatedAge;

    ifstream empFile(fName);
    ofstream temp("temp.txt");

    if (!empFile.is_open())
    {
        cout << "Failed opening the file.\n";
        return;
    }
    else if (!temp.is_open())
    {
        cout << "Failed opening the file.\n";
        return;
    }

    string empRecord;
    bool exist = false;
    while (getline(empFile, empRecord)) {
        int employeeID;
        sscanf(empRecord.c_str(), "%d", &employeeID);
        if (employeeID == empID) {
            stringstream str;
            str << empID << " ";
            if (UpdatedName[0]) {
                str << UpdatedName << " ";
            }
            else {
                int sp = empRecord.find(" ") + 1;
                int ep = empRecord.find(" ", sp);
                str << empRecord.substr(sp, ep - sp) << " ";
            }
            if (UpdatedAge != 0) {
                str << UpdatedAge;
            }
            else {
                int sp = empRecord.find_last_of(" ") + 1;
                str << empRecord.substr(sp);
            }

            temp << str.str() << endl;
            exist = true;
        }

        else 
        {
            temp << empRecord << endl;
        }
    }

    empFile.close();
    temp.close();

    if (exist == false) {
        cout << "Can't find this Record.\n" ;
        remove("temp.txt");
        return;
    }

    remove(fName);
    rename("temp.txt", fName);

    cout << "Updated successfully.\n" ;
}


void deleteRecord(const char* fName) {

    int empID;
    int indexNum;

    cout << "Enter Employee ID.\n";
    cin >> empID;

    indexNum = searchIndex(empID);

    if (indexNum == -1) 
    {
        cout << "ID does not exists.\n";
        return;
    }

    ifstream empFile(fName);
    ofstream temp("temp.txt");

    if (!empFile.is_open()) 
    {
        cout << "Failed opening the file.\n";
        return;
    }
    else if (!temp.is_open())
    {
        cout << "Failed opening the file.\n";
        return;
    }

    string empRecord;
    int currentIndexNum = 0;

    while (getline(empFile, empRecord))
    {
        if (currentIndexNum != indexNum)
        {
            temp << empRecord << endl;
        }
        currentIndexNum += empRecord.length() + 1; 
    }

    temp.close();
    empFile.close();

    remove(fName);
    rename("temp.txt", fName);


    cout << "Deleted successfully." << endl;

}

void searchRecord(const char* filename) {
    int empID;

    cout << "Enter Employee ID.\n";
    cin >> empID;

    int indexNum = searchIndex(empID);

    if (indexNum== -1) {
        cout << "ID does not exists.\n" ;
        return;
    }

    ifstream empFile(filename);

    if (!empFile.is_open()) {
        cout << "Failed opening the file.\n";
        return;
    }

    empFile.seekg(indexNum, ios::beg);
    string empRecord;
    
    if(indexNum!=0)
    getline(empFile, empRecord);

    if (getline(empFile, empRecord)) {
        cout << "The Record with ID "<< empID <<": \n" << empRecord << endl;
    }
    else 
    {
        cout << "Failed Finding The record.\n" ;
    }

    empFile.close();
}

void displayAllRecords(const char* fName) {
    ifstream empFile(fName);
    string line;
    
    if (!empFile.is_open()) {
        cout << "Failed opening the file.\n";
        return;
    }
    
    cout << "\nAll Employee Records:\n";
    cout << "ID\tName\t\tAge\n";
    cout << "------------------------\n";
    
    while (getline(empFile, line)) {
        cout << line << endl;
    }
    empFile.close();
}

void backupDatabase(const char* fName) {
    string backupName = string(fName) + ".backup";
    ifstream src(fName, ios::binary);
    ofstream dst(backupName, ios::binary);
    
    dst << src.rdbuf();
    
    cout << "Backup created successfully: " << backupName << endl;
}

int main() {

    int c;
    const char* fName = "Employees.txt";
    
    // Create files if they don't exist
    ofstream createFile(fName, ios::app);
    createFile.close();
    createIndex(fName);

    do {
        cout << "\nEmployee Database Management\n";
        cout << "----------------------------\n";
        cout << "1- Add a new record\n";
        cout << "2- Update an existing record\n";
        cout << "3- Delete an existing record\n";
        cout << "4- Search a record (By ID)\n";
        cout << "5- Display all records\n";
        cout << "6- Backup database\n";
        cout << "7- Exit\n";
        cout << "\nEnter choice: ";
        
        if (!(cin >> c)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (c)
        {
        case 1: insertRecord(fName);
                createIndex(fName);
                break;

        case 2: updateRecord(fName);
                break;
        
        case 3: deleteRecord(fName);
                createIndex(fName);
                break;
        
        case 4: searchRecord(fName);
                break; 
            
        case 5: 
                displayAllRecords(fName);
                break;
            
        case 6:
                backupDatabase(fName);
                break;
            
        case 7:
                cout << "Thank you for using Employee Database Management System.\n";
                break;

        default:
            cout << "Invalid number, please choose from 1-7.\n";
        }    
       
    } while (c != 7);

    return 0;
}