#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>

using namespace std;

struct Variable {
    string n;  // Name of the variable
    int v;     // Value of the variable
};

class StkCstm {
public:
    list<Variable> LISTs;  // The list to store the stack of variables

    void push(const Variable& var) {
        LISTs.push_back(var);
    }

    void pop() {
        if (!LISTs.empty()) {
            LISTs.pop_back();
        }
    }

    bool isEmpty() const {
        return LISTs.empty();
    }

    void display() const {
        if (LISTs.empty()) {
            cout << "Stack is empty!" << endl;
            return;
        }
        for (const auto& var : LISTs) {
            cout << "Name: " << var.n << " Value: " << (var.v == -1 ? "None" : to_string(var.v)) << endl;
        }
    }
};

void disS(const StkCstm& VARs) {
    cout << "Stack content:" << endl;
    VARs.display();
}

void PL(StkCstm& VARs, const string& line) {
    stringstream ss(line);
    string word;
    ss >> word;

    if (word == "int") {
        string varName;
        ss >> varName;

        if (varName == "main()") {
            return;
        }

        Variable var;
        var.n = varName;
        var.v = -1;  // Initialize the variable with no value (None)

        string nextWord;
        ss >> nextWord;
        if (nextWord == "=") {
            int value;
            ss >> value;
            var.v = value;
        }

        VARs.push(var);
    } 
    else if (word == "return") {
        string temp;
        ss >> temp;

        if (temp == "0;") {
            disS(VARs);
        }
    } 
    else {
        string varName;
        ss >> varName;

        for (auto& var : VARs.LISTs) {
            if (var.n == varName) {
                int value;
                ss >> value;
                var.v = value;
                break;
            }
        }
    }
}

void PF(StkCstm& VARs) {
    ifstream file("code.txt");
    string line;
    int lineCount = 1;

    while (getline(file, line)) {
        cout << "Line " << lineCount << ":" << endl;
        PL(VARs, line);
        lineCount++;
    }

    file.close();
}

int main() {
    StkCstm VARs;
    PF(VARs);
    return 0;
}
