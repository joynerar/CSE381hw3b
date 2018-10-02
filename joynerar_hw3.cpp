// Copyright (C) 2018 joynerar@miamiOH.edu

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include "joynerar_hw3.h"

using IntStrMap = std::unordered_map<int, std::string>;
using IntIntMap = std::unordered_map<int, int>;
using namespace pid;
using namespace std;


/** Parses line from input file
*   
*/
void extractLineInfo(std::string& line, int& pid, int& ppid, std::string& cmd) {
    std::istringstream is(line);
    std::string dummy; 
    is >> dummy >> pid >> ppid >> dummy >> dummy >> dummy >> dummy;
    getline(is, cmd);
    cmd = cmd.erase(0, 1);
}

/** Creates map of pids
*
*/
void pidTree::makeMaps(const string& procFile, IntIntMap& pidPPID, IntStrMap& pidCMD) {
    std::string pid, ppid, cmd;
    std::ifstream file(procFile);
    std::string line;
    while (std::getline(file, line)) {
        std::string cmd;
        int pid;
        int ppid;
        extractLineInfo(line, pid, ppid, cmd);
        pidPPID[pid] = ppid;
        pidCMD[pid] = cmd;
    }
}

/** Prints formatted out for traced pid
*
*/
void pidTree::printTree(const int& pid, IntIntMap& pidPPID, IntStrMap& pidCMD) {
    // Starter Text
    cout << "Process tree of PID: " << pid << endl;
    cout << "PID\tPPID\tCMD\n";
    // function Vars
    std::vector<string> out;
    int current = pid; 
    // Builds output string   
    while (current != 0) {
        out.insert(out.begin(), to_string(current) + "\t" + to_string(pidPPID[current]) + "\t" + pidCMD[current] + "\n");
        current = pidPPID[current];
    }
    // Loops through output to display tree
    for (auto i : out) 
        cout << i;
}

int main(int argc, char* argv[]) {
    IntStrMap pidCMD;
    IntIntMap pidPPID;
    pidTree n;
    if (argc == 3) {
        std::string fin = argv[1];
        int pid = stoi(argv[2]);
        n.makeMaps(fin, pidPPID, pidCMD);
        n.printTree(pid, pidPPID, pidCMD);
    } else {
        cerr << "Wrong Number of arguments" << endl;
    }
    return 0;
}

