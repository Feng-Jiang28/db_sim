#include "Database.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void Database::createTable(const Table& table){
    // Check if the table already exists
    ifstream readSchema("datasets/schema.csv");
    string line;
    bool tableExists = false;

    while(getline(readSchema, line)){
        if(line.substr(0, line.find(',')) == table.name){
            tableExists = true;
            break;
        }
    }

    readSchema.close();

    if(tableExists){
        cerr << "Table '" << table.name << "' already exists." << endl;
        return;
    }

    ofstream schemaFile("datasets/schema.csv",  ios::app);
    if(!schemaFile.is_open()){
        cerr << "Failed to open schema file." << endl;
        return;
    }
    schemaFile << table.name;

    for(const auto& column : table.columns){
        schemaFile << "," << column.name << ":" << column.type;
    }

    schemaFile << "\n";
    schemaFile.close();

    // Create a new CSV file for the table
    string fileName = "datasets/" + table.name + ".csv";
    ofstream tableFile(fileName);
    if(!tableFile.is_open()){
        cerr << "Failed to create table file: " << fileName << endl;
        return;
    }

    // Write column headers to the CSV file
    for(size_t i = 0; i < table.columns.size(); ++i){
        tableFile << table.columns[i].name;
        if(i<table.columns.size() - 1){
            tableFile << ",";
        }
    }  
    tableFile << "\n";
    tableFile.close();
}
   
void Database::alterTable(const string& tableName, AlterType alterType, const Column& column){
    ifstream schemaFile("schema.csv");
    ofstream tempFile("temp.csv");
    string line;
    bool tableFound = false;

    if(!schemaFile.is_open() || !tempFile.is_open()){
        cerr << "Error opening files." << endl;
        return;
    }

    while(getline(schemaFile, line)){
        istringstream iss(line);
        string currentTableName;
        getline(iss, currentTableName, ',');

        if(currentTableName == tableName){
            tableFound = true;
            tempFile << currentTableName;

            vector<string> columns;
            string col;
            while(getline(iss, col, ',')){
                columns.push_back(col);
            }
            switch (alterType)
            {
                case AlterType::Add:
                    columns.push_back(column.name + ":" + column.type);
                    break;
                case AlterType::Remove:
                    for(auto it = columns.begin(); it != columns.end();){
                        if(it->find(column.name + ".") == 0){
                            it = columns.erase(it);
                        }else{
                            ++it;
                        }
                    }
                    break;
                case AlterType::Modify:
                    for(auto& c :columns){
                        if(c.find(column.name + ":") == 0){
                            c = column.name + ":" + column.type;
                        }
                    }
                    break;
            }

            for(const auto& col : columns){
                tempFile << "," << col;
            }
            tempFile << "\n";
        }else{
            tempFile << line << "\n";
        }
    }
    schemaFile.close();
    tempFile.close();

    if(!tableFound){
        cerr << "Table not found: " << tableName << endl;
        return;
    }
    remove("shema.csv");
    rename("temp.csv", "schema.csv");
}


vector<unordered_map<string, string>> Database::getDataWhere(
    const string& tableName, 
    const string& columns, 
    const string& condition
) const {
    vector<unordered_map<string, string>> result;
    ifstream file("datasets/" + tableName + ".csv");

    if (!file.is_open()) {
        cerr << "Failed to open table file: " << tableName << endl;
        return result;
    }

    string line;
    getline(file, line); // Read header line
    istringstream headerStream(line);
    vector<string> headers;
    string header;
    while (getline(headerStream, header, ',')) {
        headers.push_back(header);
    }

    while (getline(file, line)) {
        istringstream lineStream(line);
        string cell;
        unordered_map<string, string> row;
        size_t columnIndex = 0;
        bool conditionMet = true; // Assume condition is met, implement actual condition checking logic

        while (getline(lineStream, cell, ',')) {
            row[headers[columnIndex]] = cell;
            // Implement condition checking logic here
            columnIndex++;
        }

        if (conditionMet) {
            unordered_map<string, string> filteredRow;
            if (columns == "*") {
                filteredRow = row;
            } else {
                istringstream colStream(columns);
                string col;
                while (getline(colStream, col, ',')) {
                    filteredRow[col] = row[col];
                }
            }
            result.push_back(filteredRow);
        }
    }

    return result;
}