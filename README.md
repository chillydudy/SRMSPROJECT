# SRMSPROJECT

Simple Student Record Management System in C.

## Overview

This is a minimal command-line Student Record Management System (SRMS) implemented in C. It stores student records in a plain text file and provides role-based access (ADMIN, STAFF, USER) with simple username/password credentials stored in `usersinfo.txt`.

## Features

- Role-based login (ADMIN, STAFF, USER)
- Add, display, search, update, delete single student records (ADMIN and STAFF where applicable)
- Delete all student records (ADMIN only)
- Persistent storage in `students.txt` and `usersinfo.txt`

## Files

- `SRMS.c` - Main program implementing the SRMS
- `students.txt` - Data file created at runtime to store student records
- `usersinfo.txt` - Credential file (auto-created with default users if missing)

## Default Credentials

- admin / admin123 (role: ADMIN)  
- staff / staff123 (role: STAFF)  
- user  / user123  (role: USER)

## Build

To compile:

    gcc SRMS.c -o srms

## Run

    ./srms

The program will create `usersinfo.txt` with default users if it does not exist.

## Notes & Improvements

- This is a simple demonstration and is not secure for production use (plaintext passwords, no input validation, simple file-based storage).
- Potential improvements: better input validation, support for names with spaces, hashing passwords, using a proper CSV or database backend, and adding unit tests.

## License

MIT License
