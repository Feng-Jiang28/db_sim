// Database.hpp
#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <map>


using namespace std;

struct Column{
    string name;
    string type;
};

enum class AlterType{
    Add,
    Remove,
    Modify
};

class Table{
public:
    string name;
    vector<Column> columns;
    vector<unordered_map<string, string>> data; // Each row is a map of column name to value

    Table(const string& name, const vector<Column>& columns): name(name), columns(columns){}
};

class Database{
public:
    Database() = default;

    void createTable(const Table& table);
    void alterTable(const string& tableName, AlterType alterType, const Column& column);
    void loadCSV(const string& tableName, const string& filePath); // Load data from CSV file
    void saveCSV(const string& tableName, const string& filePath); // Save data to CSV file

    vector<unordered_map<string, string>> getDataWhere(
        const string& tableName,
        const string& columns, 
        const string& condition
    ) const;

    //std::string resultToString(const std::vector<std::unordered_map<std::string, std::string>>& result);
private: 
   map<string, Table> tables; // Maps table names to Table objects
};