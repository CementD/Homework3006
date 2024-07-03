#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
using namespace std;

class DirectoryEntry {
public:
    string companyName;
    string owner;
    string phone;
    string address;
    string activity;

    DirectoryEntry() {}
    DirectoryEntry(string cName, string own, string ph, string addr, string act)
        : companyName(cName), owner(own), phone(ph), address(addr), activity(act) {}
};

class Directory {
private:
    vector<DirectoryEntry> entries;
    const string fileName = "directory.txt";

    void loadFromFile() {
        ifstream file(fileName);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string companyName, owner, phone, address, activity;
            getline(ss, companyName, ',');
            getline(ss, owner, ',');
            getline(ss, phone, ',');
            getline(ss, address, ',');
            getline(ss, activity, ',');
            entries.push_back(DirectoryEntry(companyName, owner, phone, address, activity));
        }
    }

    void saveToFile() {
        ofstream file(fileName);
        for (const auto& entry : entries) {
            file << entry.companyName << "," << entry.owner << "," << entry.phone << ","
                << entry.address << "," << entry.activity << "\n";
        }
        file.close();
    }

public:
    Directory() {
        loadFromFile();
    }

    ~Directory() {
        saveToFile();
    }

    void addEntry(const DirectoryEntry& entry) {
        entries.push_back(entry);
    }

    unique_ptr<DirectoryEntry> searchByCompanyName(string name) const {
        for (const auto& entry : entries) {
            if (entry.companyName == name) {
                return make_unique<DirectoryEntry>(entry);
            }
        }
        return nullptr;
    }

    void searchByOwner(string owner) const {
        for (const auto& entry : entries) {
            if (entry.owner == owner) {
                printEntry(entry);
            }
        }
    }

    void searchByPhone(string phone) const {
        for (const auto& entry : entries) {
            if (entry.phone == phone) {
                printEntry(entry);
            }
        }
    }

    void searchByActivity(string activity) const {
        for (const auto& entry : entries) {
            if (entry.activity == activity) {
                printEntry(entry);
            }
        }
    }

    void printAllEntries() const {
        for (const auto& entry : entries) {
            printEntry(entry);
        }
    }

    void printEntry(const DirectoryEntry& entry) const {
        cout << "Company Name: " << entry.companyName << "\n"
            << "Owner: " << entry.owner << "\n"
            << "Phone: " << entry.phone << "\n"
            << "Address: " << entry.address << "\n"
            << "Activity: " << entry.activity << "\n"
            << "-------------------------\n";
    }
};

int main() {
    Directory directory;

    directory.addEntry(DirectoryEntry("Company A", "Name A", "123456789", "Street A", "Activity A"));
    directory.addEntry(DirectoryEntry("Company B", "Name B", "987654321", "Street B", "Activity B"));

    cout << "Search by company name 'Company A':\n";
    unique_ptr<DirectoryEntry> entry = directory.searchByCompanyName("Company A");
    if (entry) {
        directory.printEntry(*entry);
    }
    else {
        cout << "Company not found.\n";
    }

    cout << "\nSearch by owner 'Name B':\n";
    directory.searchByOwner("Name B");

    cout << "\nSearch by phone '123456789':\n";
    directory.searchByPhone("123456789");

    cout << "\nSearch by activity 'Activity B':\n";
    directory.searchByActivity("Activity B");

    cout << "\nAll entries:\n";
    directory.printAllEntries();

    return 0;
}
