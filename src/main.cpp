#include <iostream>
#include "QueryLanguage.hpp"
#include "Utils.hpp"
#include "Database.hpp"

using namespace std;

#define MAX_QUERY_LEN 100

int main(){
    //string dataset_path = "datasets/dataset.csv";
    //Database db(dataset_path);
    QueryLanguage ql; 
    string query;
    while(true){
        cout << "Enter query: ";
        getline(cin, query);
        if(query == "exit") break;
        string result = resultToString(ql.executeQuery(query));
        cout << "Result: " << result << endl;
    }
    return 0;
}