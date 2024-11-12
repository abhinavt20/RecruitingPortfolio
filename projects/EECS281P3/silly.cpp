// C0F4DFE8B340D81183C208F70F9D2D797908754D

// Include standard and project-specific headers
#include <getopt.h>
// Include standard and project-specific headers
#include <iostream>
// Include standard and project-specific headers
#include <string>
// Include standard and project-specific headers
#include <vector>
// Include standard and project-specific headers
#include <algorithm>
// Include standard and project-specific headers
#include <stack>
// Include standard and project-specific headers
#include <queue>
// Include standard and project-specific headers
#include <deque>
// Include standard and project-specific headers
#include <utility>
// Include standard and project-specific headers
#include <map>
// Include standard and project-specific headers
#include "TableEntry.h"
// Include standard and project-specific headers
#include <unordered_map>
// Include standard and project-specific headers
#include "xcode_redirect.hpp"


using namespace std;

// Declaration of class Table
class Table {
public:
    
    friend class Database;
    
    string name;
    vector<EntryType> createTypes;
    vector<string> createNames;
    
    vector<vector<TableEntry>> insert2DVec;

    
private:

};

// Declaration of class Database
class Database {
public:
    
    friend class Table;

    bool quietStatus = false;
    void getMode(int argc, char * argv[]);
    void readIn();
    
    int numCol = 0;

    
    void createFunc();
    void removeFunc();
    void insertFunc();
    void printFunc();
    
    void printAll();
    void printWhere();

    
    void joinFunc();
    void deleteFunc();
    void generateFunc();
    
    
    
    TableEntry convertToTableEntry(EntryType type);

    
    int totalNumRows = 0;
    
    int startIndexForInsert = 0;
    
//    string tableName;
//    int numCol = 0;

    unordered_map<string, Table> mapOfTables;

    
private:

};


// Declaration of class CompareLess
class CompareLess {
    size_t newDistIndex;
    TableEntry newTableEntryVal;
public:
    CompareLess(size_t distIndex, TableEntry &tableEntryVal) :
    newDistIndex(distIndex), newTableEntryVal(tableEntryVal) {}
    
    bool operator()(vector<TableEntry> &tempCompareVec) {
        return tempCompareVec[newDistIndex] < newTableEntryVal;
    }
};

// Declaration of class CompareEqual
class CompareEqual {
    size_t newDistIndex;
    TableEntry newTableEntryVal;
public:
    CompareEqual(size_t distIndex, TableEntry &tableEntryVal) :
    newDistIndex(distIndex), newTableEntryVal(tableEntryVal) {}
    
    bool operator()(vector<TableEntry> &tempCompareVec) {
        return tempCompareVec[newDistIndex] == newTableEntryVal;
    }
};

// Declaration of class CompareGreater
class CompareGreater {
    size_t newDistIndex;
    TableEntry newTableEntryVal;
public:
    CompareGreater(size_t distIndex, TableEntry &tableEntryVal) :
    newDistIndex(distIndex), newTableEntryVal(tableEntryVal) {}
    
    bool operator()(vector<TableEntry> &tempCompareVec) {
        return tempCompareVec[newDistIndex] > newTableEntryVal;
    }
};




//____________________________________________________________________________________
// database functions

void Database::getMode(int argc, char * argv[]) {
    opterr = false; // Let us handle all error output for command line options
    
    int choice;
    int option_index = 0;
    option long_options[] = {
        // ******check no argument vs required argument I AM UNSURE
        //**** single or double quotes
        { "quiet", no_argument,         nullptr, 'q'},
        { "help", no_argument,         nullptr, 'h'},
        { nullptr, 0,                 nullptr, '\0' }
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "qh", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'h':
            cout << "-q, --quiet: This causes the program to run in quiet mode. In quiet mode, your program will run very similarly to normal, except that it will print only numerical summaries of the rows affected by the command, not any of the actual data. Quiet mode exists so that we may stress test your program without overloading the autograder with too much output. This flag only affects the JOIN and PRINT commands, and specific instructions for quiet mode output is given for these commands. Otherwise, if there is no mention of quiet mode with respect to a given piece of output, you may assume it is always printed. You can implement this feature last; with a well-built project, adding this functionality should be very simple. \n";
            
            exit(0);
            break;

        case 'q':
            quietStatus = true;
            break;
        
        default:
            cerr << "Unknown command line option\n";
            exit(1);
        } // switch
    } // while

    
return;
    
} // getMode()

void Database::readIn() {
    string cmd;
    string junk;
    
    do {
        cout << "% ";
        cin >> cmd;
        char firstChar = cmd[0];
        
        switch (firstChar) {
            case '#': {
                getline(cin, junk);
                break;
            }
            case 'C': {
                createFunc();
                break;
            }
            case 'R': {
                removeFunc();
                break;
            }
                
            case 'I': {
                insertFunc();
                break;
            }
            case 'P': {
                printFunc();
                break;
            }
            case 'D': {
                deleteFunc();
                break;
            }
            case 'G': {
                generateFunc();
                break;
            }
            case 'J': {
                joinFunc();
                break;
            }
        }
    
        // if there is an error use getline
    } while (cmd != "QUIT");
    
    cout << "Thanks for being silly! \n";
}


void Database::createFunc(){
    string readInType;
    string readInName;
    string tableName;
    string junk;
    
    cin >> tableName >> numCol;
    
    // if table already exists
    if (mapOfTables.find(tableName) == mapOfTables.end()){
        cout << "Error during CREATE: Cannot create already existing table " << tableName << "\n";
        getline(cin, junk);
        return;
    }
    
//    Table * tableObj = new Table;
    
    //add table to unordered map of tables
    mapOfTables.emplace(tableName, Table());

    mapOfTables[tableName].createTypes.reserve(numCol);
    mapOfTables[tableName].createNames.reserve(numCol);
    

    //adds col types to vector
    for (int i = 0; i < numCol; i++){
        cin >> readInType;
        if (readInType == "string"){
            mapOfTables[tableName].createTypes[i] = EntryType::String;
        }
        else if (readInType == "double"){
            mapOfTables[tableName].createTypes[i] = EntryType::Double;
        }
        else if (readInType == "int"){
            mapOfTables[tableName].createTypes[i] = EntryType::Int;
        }
        else if (readInType == "bool"){
            mapOfTables[tableName].createTypes[i] = EntryType::Bool;
        }
    }
    
    cout << "New table " << tableName << " with column(s) ";
    
    //adds col names to vector
    for (int i = 0; i < numCol; i++){
        cin >> readInName;
        mapOfTables[tableName].createNames[i] = readInName;
        cout << readInName << " ";
    }
    
    cout << "created \n";

}

void Database::removeFunc(){
    string removeTable;

    cin >> removeTable;
    
    if (mapOfTables.find(removeTable) == mapOfTables.end()){
        cout << "Error during REMOVE: " << removeTable << " does not name a table in the database \n";
        return;
    }
    
    //removes the table at the specified index
    mapOfTables.erase(mapOfTables.find(removeTable));
    
    cout << "Table " << removeTable << " deleted \n";
}

TableEntry Database::convertToTableEntry(EntryType type){
    if (type == EntryType::String){
        string temp;
        cin >> temp;
        return TableEntry(temp);
    }
    else if (type == EntryType::Double){
        double temp;
        cin >> temp;
        return TableEntry(temp);
    }
    else if (type == EntryType::Int){
        int temp;
        cin >> temp;
        return (TableEntry(temp));
    }
    else {
        bool temp;
        cin >> temp;
        return TableEntry(temp);
    }
}


//___________________________________________________________________________________
// table functions


void Database::insertFunc(){
    string into;
    string tableName;
    string junk;
    int numRows = 0;
    string rows;
    
    cin  >> into >> tableName >> numRows >> rows;
        
    //handles errors (if table DNE)
    if (mapOfTables.find(tableName) == mapOfTables.end()){
        cout << "Error during INSERT: " << tableName << " does not name a table in the database \n";
        
        for (int i = 0; i < numRows; i++){
            getline(cin, junk);
        }
        return;
    }
    
    //keeps track of how many rows there are in insert2DVec
    totalNumRows += numRows;
    
    //resizes vector to needed number of rows and columns
    //***** TODO: finish reserving the 2d vector better
//    mapOfTables[tableName].insert2DVec.reserve(numRows);
    
    vector<TableEntry> tempRow;
    tempRow.reserve(numCol);
    
    int startIndexingRow = totalNumRows - numRows;
    for (int i = startIndexingRow; i < totalNumRows; i++){
        for (int j = 0; j < numCol; j++){
            EntryType type = mapOfTables[tableName].createTypes[j];
            TableEntry insertVal = convertToTableEntry(type);
            
            tempRow.emplace_back(insertVal);
                        
        } //for
        mapOfTables[tableName].insert2DVec.emplace_back(tempRow);
        tempRow.clear();
    } // for
    
    cout << "Added " << numRows << " rows to " << tableName << " from position " << startIndexingRow << " to " << (totalNumRows - 1) << "\n";
}


void Database::deleteFunc(){
    string from;
    string tableName;
    string where;
    string colName;
    char op;
    string value;
    
    string junk;
    
    cin >> from >> tableName;
    
    // checks if tableName is in the database
    if (mapOfTables.find(tableName) == mapOfTables.end()){
        cout << "Error during DELETE: " << tableName << " does not name a table in the database \n";
        getline(cin, junk);
        return;
    }
    
    //whats the name of the column
    //does that column exisit
    
    cin >> where >> colName >> op;
    //returns pointer to colName or points to end if DNE
    //vector<string>::iterator it;
    auto it = std::find(mapOfTables[tableName].createNames.begin(), mapOfTables[tableName].createNames.end(), colName);
    
    // essentially if the colName does not exist
    if(it == mapOfTables[tableName].createNames.end()){
        cout << "Error during DELETE: " << colName << " does not name a column in " << tableName << "\n";
        getline(cin, junk);
        return;
    }
    
    //whats the type of that column
    size_t distIndex = std::distance(mapOfTables[tableName].createNames.begin(), it);
    EntryType type = mapOfTables[tableName].createTypes[distIndex];
    TableEntry tableEntryVal = convertToTableEntry(type);
    
    if (op == '<'){
        auto removeIndex = remove_if(mapOfTables[tableName].insert2DVec.begin(), mapOfTables[tableName].insert2DVec.end(), CompareLess(distIndex, tableEntryVal));
        size_t numDeletedRows = distance(removeIndex, mapOfTables[tableName].insert2DVec.end());
        mapOfTables[tableName].insert2DVec.erase(removeIndex, mapOfTables[tableName].insert2DVec.end());
        cout << "Deleted " << numDeletedRows << " from " << tableName << "\n";
        totalNumRows -= numDeletedRows;
    }
    
    else if (op == '='){
        auto removeIndex = remove_if(mapOfTables[tableName].insert2DVec.begin(), mapOfTables[tableName].insert2DVec.end(), CompareEqual(distIndex, tableEntryVal));
        size_t numDeletedRows = distance(removeIndex, mapOfTables[tableName].insert2DVec.end());
        mapOfTables[tableName].insert2DVec.erase(removeIndex, mapOfTables[tableName].insert2DVec.end());
        cout << "Deleted " << numDeletedRows << " from " << tableName << "\n";
        totalNumRows -= numDeletedRows;
    }
    
    else if (op == '>'){
        auto removeIndex = remove_if(mapOfTables[tableName].insert2DVec.begin(), mapOfTables[tableName].insert2DVec.end(), CompareGreater(distIndex, tableEntryVal));
        size_t numDeletedRows = distance(removeIndex, mapOfTables[tableName].insert2DVec.end());
        mapOfTables[tableName].insert2DVec.erase(removeIndex, mapOfTables[tableName].insert2DVec.end());
        cout << "Deleted " << numDeletedRows << " from " << tableName << "\n";
        totalNumRows -= numDeletedRows;
    }
    
}

void Database::printFunc(){
    string whereOrAll;
    string from;
    string tableName;
    string colName;
    string junk;
    int num = 0;
    string rows;
    
    vector<string> printColumnsVec;
    vector<size_t> printColumnsIndexVec;

    
    cin >> from >> tableName;
    
    if (mapOfTables.find(tableName) == mapOfTables.end()){
        cout << "Error during PRINT: " << tableName << " does not name a table in the database \n";
        getline(cin, junk);
        return;
    }
    
    cin >> num;
    
    for (int i = 0; i < num; i++){
        cin >> colName;
        
        auto it = std::find(mapOfTables[tableName].createNames.begin(), mapOfTables[tableName].createNames.end(), colName);
        if(it == mapOfTables[tableName].createNames.end()){
            cout << "Error during PRINT: " << colName << " does not name a column in " << tableName << "\n";
            getline(cin, junk);
            return;
        }
        
        //push back column name into a vector
        printColumnsVec.push_back(colName);
        
        size_t distIndex = std::distance(mapOfTables[tableName].createNames.begin(), it);
        
        //push back the column index into a vector
        printColumnsIndexVec.push_back(distIndex);
    }
    
    cin >> whereOrAll;
    
//    if (whereOrAll == "ALL"){
//        if (quietStatus )
//
//
//
//
//        printAll();
//    }
//    else if (whereOrAll == "WHERE"){
//        printWhere();
//    }
//
//
}

void Database::printAll(){
    
}

void Database::printWhere(){
    
}


void Database::generateFunc(){
    
}

void Database::joinFunc(){
    
}


//___________________________________________________________________________________

// Main entry point of the application
int main(int argc, char *argv[]){
    
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    cin >> boolalpha;
    cout << boolalpha;
    
    Database sillyGoose;
    
    sillyGoose.getMode(argc, argv);
    sillyGoose.readIn();
//    gameplayMain.roundBreakdown();
//    gameplayMain.statisticOutput();
    

    return 0;
    
}
