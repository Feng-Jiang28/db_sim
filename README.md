DatabaseSystem/
│
├── src/
│   ├── main.cpp
│   ├── Database.cpp
│   └── QueryLanguage.cpp
│
├── include/
│   ├── Database.hpp
│   └── QueryLanguage.hpp
│
├── datasets/
│   └── example_dataset.csv
│
├── Makefile
│
└── README.md

A simple database system implemented in C++
## Build
To build the project, run:
make

To run the project 
./main 

Explanation
Database.hpp/cpp: handles data storage, retrieval, and manipulation.
QueryLanguage.hpp/cpp: Parses and executes queries from the user. 
main.cpp: Main entry point, handles user input/output and main loop.
Makefile: Simplifies the build process.
README.md: Provides basic documentation for your project.

DML:
Query Format for CREATE TABLE
CREATE TABLE Name column1:type1,column2,type2,column3,type3,...
CREATE Students id:int,name:string,age:int,grade:float


Feng SQL is like:
[table] : [columns] : [condition]



# db_sim
