#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// Function to save the integer database to a file
/*
* This function takes a filename and a vector of integers as input.
* the function opens the specified file for writing and writes each integer from the vector to the file, one per line.
*/
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

void listDatabase(const std::filesystem::path& filepath) {
    try {
        if (fs::exists(filepath)) {
            std::cout << "Database contents:\n";
            for (const auto& entry : fs::directory_iterator(filepath)) {
                if (fs::is_regular_file(entry)) {
                    std::cout << "- " << entry.path().filename() << "\n";
                }
            }
        }
        else {
            std::cout << "Database directory does not exist.\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error occurred while listing database: " << e.what() << "\n";
    }
}


void deleteDatabase(const std::string& filename) {
	if (std::remove(filename.c_str()) == 0) {
		std::cout << "Database file deleted successfully.\n";
	}
	else {
		std::cerr << "Error deleting database file.\n";
	}
}

void createDatabase(const std::filesystem::path& filepath) {
    try {
        if (!fs::exists(filepath)) {
            std::ofstream outfile(filepath);
            std::cout << "Database file created successfully.\n";
        }
        else {
            std::cout << "Database file already exists.\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error occurred while creating database file: " << e.what() << "\n";
    }
}

int main() {
    std::vector<int> database;
    fs::path dbPath = "./database_list";
    fs::path activeDatabaseFile;
    bool hasOpenDatabase = false;

    if (!fs::exists(dbPath)) {
        fs::create_directory(dbPath);
    }
    
    
    // database manager

    int mainmenu_choice = 0;
    while (mainmenu_choice != 5) {
        std::cout << "\n--- Integer Database Menu ---\n"
            << "1. List Database\n"
            << "2. Create Database\n"
            << "3. Open Database\n"
            << "4. Delete Database\n"
            << "5. Exit\n"  
            << "Enter your choice (1-5): ";

        if (!(std::cin >> mainmenu_choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (mainmenu_choice) {
        case 1:
            listDatabase(dbPath);
            break;
        case 2: {
            std::string name;
            std::cout << "Enter new database name: ";
            std::cin >> name;

            fs::path newDatabaseFile = dbPath / name;

            createDatabase(newDatabaseFile);

            database.clear();
            activeDatabaseFile = newDatabaseFile;
            hasOpenDatabase = true;

            break;
        }
        case 3: {
            std::string name;
            std::cout << "Enter database name to open: ";
            std::cin >> name;

            fs::path fileToOpen = dbPath / name;

            if (fs::exists(fileToOpen)) {
                loadDatabase(fileToOpen.string(), database);
                activeDatabaseFile = fileToOpen;
                hasOpenDatabase = true;
            }
            else {
                std::cout << "Database does not exist.\n";
            }

            break;
        }
        case 4:
            database.clear();
            std::cout << "Database cleared from memory.\n";
            break;
        case 5:
            std::cout << "Exiting program. Goodbye!\n";
            break; 

    //int choice = 0;
    //while (choice != 5) {
    //    std::cout << "\n--- Integer Database Menu ---\n"
    //        << "1. Show Database\n"
    //        << "2. Add Integer\n"
    //        << "3. Save Database\n"
    //        << "4. Clear Database\n"
    //        << "5. Exit\n"
    //        << "Enter your choice (1-5): ";

    //    if (!(std::cin >> choice)) {
    //        std::cout << "Invalid input. Please enter a number.\n";
    //        std::cin.clear();
    //        std::cin.ignore(1000, '\n');
    //        continue;
    //    }

    //    switch (choice) {
    //    case 1:
    //        showDatabase(database);
    //        break;
    //    case 2: {
    //        int inputNum;
    //        std::cout << "Enter an integer to add: ";
    //        if (std::cin >> inputNum) {
    //            database.push_back(inputNum);
    //            std::cout << "Integer added.\n";
    //        }
    //        break;
    //    }
    //    case 3:
    //        saveDatabase(dbFile, database);
    //        break;
    //    case 4:
    //        database.clear();
    //        std::cout << "Database cleared from memory.\n";
    //        break;
    //    case 5:
    //        std::cout << "Exiting program. Goodbye!\n";
    //        break;
        default:
            std::cout << "Invalid choice. Please pick between 1 and 5.\n";
        }
    }

    return 0;
}
