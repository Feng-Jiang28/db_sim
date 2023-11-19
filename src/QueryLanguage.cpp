// QueryLanguage.cpp
#include "QueryLanguage.hpp"
#include <sstream>
#include <iostream>

using namespace std;

QueryLanguage::QueryLanguage(Database& db) : db_(db) {}

vector<unordered_map<string, string>> QueryLanguage::executeQuery(const string& query) {
    istringstream ss(query);
    string table, operation, details;

    // Parse the query
    getline(ss, operation, ' '); // Assuming the first word is the operation type
    getline(ss, table, ' '); // Assuming the second word is the table name
    getline(ss, details); // Rest of the query

    if(operation == "CREATE"){
        Table newTable = parseCreateTableDetails(table, details);
        db_.createTable(newTable);
        return{}; // Return empty result for CREATE operation
    }else if(operation == "ALTER"){
        return{};
    }else if(operation == "DROP"){
        return{};
    }else if(operation == "SELECT"){
        
        // Handle SELECT queries
        string columns, condition;
        istringstream detailStream(details);
        getline(detailStream, columns, ':');
        getline(detailStream, condition);
        return db_.getDataWhere(columns, condition);
    }else{
        throw runtime_error("Unsupported operation");
    }
}

Table QueryLanguage::parseCreateTableDetails(const string& tableName, const string& details){
    vector<Column> columns;
    istringstream detailStream(details);
    string columnDetail;

    while(getline(detailStream, columnDetail, ',')){
        size_t colonPos = columnDetail.find(':');
        if(colonPos != string::npos){
            string columnName = columnDetail.substr(0, colonPos);
            string columnType = columnDetail.substr(colonPos + 1);
            columns.push_back(Column{columnName, columnType});
        }else{
            throw std::runtime_error("Invalid column detail format");
        }
    }
    return Table(tableName, columns);
}
