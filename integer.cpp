#include <iostream>
#include <vector>
#include <fstream>

// Function to save the integer database to a file
void saveDatabase(const std::string& filename, const std::vector<int>& db) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int num : db) {
            outFile << num << "\n";
        }
        std::cout << "Database saved successfully!\n";
    }
    else {
        std::cerr << "Error opening file for writing.\n";
    }
}


// Function to load the integer database from a file
void loadDatabase(const std::string& filename, std::vector<int>& db) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        db.clear();
        int num;
        while (inFile >> num) {
            db.push_back(num);
        }
        std::cout << "Database loaded successfully!\n";
    }
    else {
        std::cout << "No existing database found. Starting fresh.\n";
    }
}

// Function to display the database
void showDatabase(const std::vector<int>& db) {
    if (db.empty()) {
        std::cout << "The database is currently empty.\n";
    }
    else {
        std::cout << "Database contents: ";
        for (int num : db) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    std::vector<int> database;
    std::string dbFile = "int_database.txt";

    // Load existing data on startup
    loadDatabase(dbFile, database);

    int choice = 0;
    while (choice != 5) {
        std::cout << "\n--- Integer Database Menu ---\n"
            << "1. Show Database\n"
            << "2. Add Integer\n"
            << "3. Save Database\n"
            << "4. Clear Database\n"
            << "5. Exit\n"
            << "Enter your choice (1-5): ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            showDatabase(database);
            break;
        case 2: {
            int inputNum;
            std::cout << "Enter an integer to add: ";
            if (std::cin >> inputNum) {
                database.push_back(inputNum);
                std::cout << "Integer added.\n";
            }
            break;
        }
        case 3:
            saveDatabase(dbFile, database);
            break;
        case 4:
            database.clear();
            std::cout << "Database cleared from memory.\n";
            break;
        case 5:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please pick between 1 and 5.\n";
        }
    }

    return 0;
}
