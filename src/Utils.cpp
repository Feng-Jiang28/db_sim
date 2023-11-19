#include "Utils.hpp"

string resultToString(const vector<unordered_map<string, string>>& result) {
    string result_str;
    for (const auto& row : result) {
        for (const auto& [key, value] : row) {
            result_str += key + ": " + value + ", ";
        }
        result_str.pop_back();  // Remove the last comma
        result_str.pop_back();  // Remove the last space
        result_str += "\n";     // Add a newline to separate rows
    }
    return result_str;
}
