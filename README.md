# Smart Quiz Maker

A console-based quiz management system written in C++. It has three roles (Admin, Teacher, Student), and all data is stored in plain text files, so no database or external library is needed.

Admins manage users, teachers create and manage quizzes, and students take timed quizzes and check their results.

## Features

### Admin
- Register new admins, teachers, and students (username and password are auto-generated)
- Search for a user
- Remove a user
- Update a user's information
- List all admins, teachers, or students

### Teacher
- Create a quiz for a subject, with a timer, number of questions, marks, degree program, and section
- Preview a quiz
- Edit a quiz: add, change, or remove questions, change requirements, or cancel the quiz
- Announce results
- Update personal information

### Student
- Take a quiz (only if eligible for their degree program and section, with a time limit)
- View results once the teacher has announced them
- Update personal information

## Concepts Used
- File handling with `ifstream` and `ofstream` for persistent storage
- String handling and parsing
- Random username and password generation with `rand()`
- Timed quizzes using `<ctime>`
- Role-based menus with `switch` and `do-while` loops
- Modular design, with one function per portal

## Requirements
- A C++ compiler with C++11 support or newer (g++, clang++, or MSVC)

## How to Compile and Run

**Linux / macOS**
```bash
g++ -std=c++11 SQM.cpp -o sqm
./sqm
```

**Windows (MinGW)**
```bash
g++ -std=c++11 SQM.cpp -o sqm.exe
sqm.exe
```

Run the program from a folder where it can create files, because it writes its data files into the current directory.

## First Run
On the first run, the program creates a default admin account so you can log in and register other users:

| Field    | Value   |
|----------|---------|
| Username | `Joker` |
| Password | `1234`  |

Log in as Admin, register a teacher and a student, then log in as each of them to try the full flow.

## Suggested Workflow
1. **Admin** registers a teacher and a student. The generated username and password are shown once, so note them down.
2. **Teacher** logs in and creates a quiz for a subject, degree program, and section.
3. **Student** logs in and takes the quiz within the time limit.
4. **Teacher** announces the results.
5. **Student** checks the result from the dashboard.

## Data Files
The program creates these text files while running:

| File | Purpose |
|------|---------|
| `adminsdata.txt` | Admin accounts |
| `teachersdata.txt` | Teacher accounts |
| `studentsdata.txt` | Student accounts |
| `<SUBJECT>_Quiz.txt` | Questions for a subject's quiz |
| `<SUBJECT>_verification.txt` | Quiz eligibility (degree, section, timer, marks) |
| `answersoresults.txt` | Student answers and results |

## Known Limitations
- Passwords are stored in plain text, which is fine for a learning project but not for real use.
- Inputs like names and subjects are read with `cin >>`, so they cannot contain spaces.
- Subject and quiz titles must be entered in capital letters.

## Future Improvements
- Hash passwords instead of storing them in plain text
- Split the code into multiple `.h` and `.cpp` files
- Add a GUI or a database backend

## Author
**Dayan Ahmed**
University CS student, learning C++, Python, and DSA, and aiming for ML/AI work.
