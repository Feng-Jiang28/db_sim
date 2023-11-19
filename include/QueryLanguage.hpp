#pragma once

#include "Database.hpp"
#include <string>
#include <vector>

using namespace std;

class QueryLanguage{
public:
    QueryLanguage();
    vector<unordered_map<string, string>> executeQuery(const string& query);
    Table parseCreateTableDetails(const string& tableName, const string& details);
private:
    Database& db_;
};