#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void generateSampleLogs(const string& fileName) {
    ofstream outFile(fileName);
    if (!outFile) {
        cout << "Error creating sample log file.\n";
        return;
    }

    outFile << "2026-11-11 09:15:02 INFO Server boot sequence completed\n";
    outFile << "2026-11-11 09:22:18 INFO User session initialized for ID_402\n";
    outFile << "2026-11-11 09:40:55 WARNING CPU temperature reached 78C\n";
    outFile << "2026-11-11 10:05:11 ERROR Database connection timeout on port 5432\n";
    outFile << "2026-11-11 10:12:49 INFO Daily backup job started\n";
    outFile << "2026-11-11 10:19:30 WARNING High RAM usage detected (84%)\n";
    outFile << "2026-11-11 10:27:04 ERROR Authentication service failed to respond\n";
    outFile << "2026-11-11 10:33:19 ERROR Database connection timeout on port 5432\n";
    outFile << "2026-11-11 10:45:00 INFO Health check ping OK\n";

    outFile.close();
}

bool loadLogs(const string& fileName, unordered_map<string, int>& counts, vector<string>& allLogs, vector<string>& errorLogs) {
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        return false;
    }

    counts.clear();
    allLogs.clear();
    errorLogs.clear();

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        
        allLogs.push_back(line);

        if (line.find("INFO") != string::npos) {
            counts["INFO"]++;
        } else if (line.find("WARNING") != string::npos) {
            counts["WARNING"]++;
        } else if (line.find("ERROR") != string::npos) {
            counts["ERROR"]++;
            errorLogs.push_back(line);
        }
    }

    inFile.close();
    return true;
}

void showHealthReport(unordered_map<string, int>& counts, int totalLines) {
    cout << "\n========================================\n";
    cout << "        SERVER HEALTH SUMMARY           \n";
    cout << "========================================\n";
    cout << "Total Logs Scanned : " << totalLines << "\n";
    cout << "INFO Messages      : " << counts["INFO"] << "\n";
    cout << "WARNING Messages   : " << counts["WARNING"] << "\n";
    cout << "ERROR Messages     : " << counts["ERROR"] << "\n";
    cout << "----------------------------------------\n";

    if (counts["ERROR"] >= 3) {
        cout << "[CRITICAL ALERT] P1 Incident Triggered!\n";
        cout << "Action Required: Escalate to L2 Support.\n";
    } else {
        cout << "[STATUS] Server operating within normal limits.\n";
    }
    cout << "========================================\n";
}

void searchByKeyword(const vector<string>& allLogs) {
    string keyword;
    cout << "\nEnter keyword to search (e.g., Database, WARNING, 10:): ";
    cin >> keyword;

    cout << "\n--- Search Results for '" << keyword << "' ---\n";
    bool found = false;
    for (const string& entry : allLogs) {
        if (entry.find(keyword) != string::npos) {
            cout << entry << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No matching log entries found.\n";
    }
}

void exportIncidentReport(unordered_map<string, int>& counts, const vector<string>& errorLogs) {
    ofstream reportFile("incident_report.txt");
    if (!reportFile) {
        cout << "Failed to create report file.\n";
        return;
    }

    reportFile << "=== AUTOMATED INCIDENT REPORT ===\n";
    reportFile << "Total Errors Found: " << counts["ERROR"] << "\n\n";
    reportFile << "Critical Error Logs:\n";
    for (const string& err : errorLogs) {
        reportFile << "- " << err << "\n";
    }

    reportFile.close();
    cout << "\nReport successfully saved to 'incident_report.txt'!\n";
}

int main() {
    string logFileName = "server_logs.txt";
    
    generateSampleLogs(logFileName);

    unordered_map<string, int> logCounts;
    vector<string> allLogs;
    vector<string> errorLogs;

    if (!loadLogs(logFileName, logCounts, allLogs, errorLogs)) {
        cout << "Error: Could not open " << logFileName << "\n";
        return 1;
    }

    int choice = 0;
    while (true) {
        cout << "\n--- IT Operations Log Monitor ---\n";
        cout << "1. View Server Health Summary\n";
        cout << "2. View All Critical Errors\n";
        cout << "3. Search Logs by Keyword\n";
        cout << "4. Export Incident Report to File\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";

        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        if (choice == 1) {
            showHealthReport(logCounts, allLogs.size());
        } else if (choice == 2) {
            cout << "\n--- Critical Error Logs ---\n";
            for (const string& err : errorLogs) {
                cout << err << "\n";
            }
        } else if (choice == 3) {
            searchByKeyword(allLogs);
        } else if (choice == 4) {
            exportIncidentReport(logCounts, errorLogs);
        } else if (choice == 5) {
            cout << "Exiting Log Monitor. Goodbye!\n";
            break;
        } else {
            cout << "Please choose a valid option (1-5).\n";
        }
    }

    return 0;
}

