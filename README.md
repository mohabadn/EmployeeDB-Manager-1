# EmployeeDB-Manager

A simple command-line employee database management system written in C++.

## Features

- Create, Read, Update, and Delete (CRUD) employee records
- Indexed file system for fast record retrieval
- Input validation for data integrity
- Display all employee records in a formatted table
- Automatic database backup functionality
- Error handling and user-friendly messages

## File Structure

```
EmployeeDB-Manager/
├── DB.cpp          # Main implementation file
├── DB.h           # Header file with declarations
├── Employees.txt  # Database file
└── README.md      # Documentation
```

## Usage

1. Compile the program:
```bash
g++ -o employee_db DB.cpp
```

2. Run the program:
```bash
./employee_db
```

3. Available operations:
   - Add new employee records
   - Update existing records
   - Delete records
   - Search records by ID
   - Display all records
   - Create database backup

## Data Format

Each employee record contains:
- Employee ID (positive integer)
- Name (up to 39 characters)
- Age (1-120)

## Requirements

- C++ compiler (g++ recommended)
- Basic file system permissions for read/write operations

## Error Handling

The program includes error handling for:
- File operations
- Invalid input validation
- Duplicate IDs
- Non-existent records

## Author

Mohab Haidaria