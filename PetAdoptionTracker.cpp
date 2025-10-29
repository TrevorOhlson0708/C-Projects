// Author: Trevor Ohlson
// Improvements to ChatGPT
// Homework 3, Deliverable 2
#include <iostream>
#include <string>
#include <cassert>
#include <iomanip>
using namespace std;

// Stores the owners info such as name and number
struct OwnerInfo {
    string ownerName;
    string phoneNumber;

    bool isValid() const {
        return !ownerName.empty() && phoneNumber.size() >= 7;
    }
};

// Stores the pets info such as its name, type, and its age :)
class Pet {
private:
    string name;
    int age;
    string type;

public:
    Pet() : name(""), age(0), type("") {}
    Pet(string n, int a, string t) : name(n), age(a), type(t) {}
    
    // Get the information from the user of the pet and validated that info
    friend istream& operator>>(istream& in, Pet& p) {
        cout << "Enter pet name: ";
        getline(in, p.name);
        while (p.name.empty()) {
            cout << "Name cannot be empty. Enter again: ";
            getline(in, p.name);
        }

        cout << "Enter pet age (0–30): ";
        in >> p.age;
        while (in.fail() || p.age < 0 || p.age > 30) {
            in.clear();
            in.ignore(1000, '\n');
            cout << "Invalid age. Enter a number between 0 and 30: ";
            in >> p.age;
        }
        in.ignore();

        cout << "Enter pet type (e.g., Dog, Cat): ";
        getline(in, p.type);
        while (p.type.empty()) {
            cout << "Type cannot be empty. Enter again: ";
            getline(in, p.type);
        }
        return in;
    }
    
    // This prints the pets information in a format 
    friend ostream& operator<<(ostream& out, const Pet& p) {
        out << left << setw(10) << p.name
            << setw(6) << p.age
            << setw(10) << p.type;
        return out;
    }

    string getName() const { return name; }
    int getAge() const { return age; }
    string getType() const { return type; }
};

class AdoptionRecord {
private:
    Pet pet;
    OwnerInfo owner;

public:
    AdoptionRecord() {}
    AdoptionRecord(Pet p, OwnerInfo o) : pet(p), owner(o) {}

    // Prompts the user for the pet and owners info and validated it
    friend istream& operator>>(istream& in, AdoptionRecord& ar) {
        in >> ar.pet;
        cout << "Enter owner's name: ";
        getline(in, ar.owner.ownerName);
        cout << "Enter owner's phone number: ";
        getline(in, ar.owner.phoneNumber);

        while (!ar.owner.isValid()) {
            cout << "Invalid input. Owner name or phone too short.\n";
            cout << "Re-enter owner's name: ";
            getline(in, ar.owner.ownerName);
            cout << "Re-enter phone number: ";
            getline(in, ar.owner.phoneNumber);
        }
        return in;
    }

    // Prints formated pet and owner information into a format
    friend ostream& operator<<(ostream& out, const AdoptionRecord& ar) {
        out << left << setw(10) << ar.pet.getName()
            << setw(6) << ar.pet.getAge()
            << setw(10) << ar.pet.getType()
            << setw(15) << ar.owner.ownerName
            << setw(12) << ar.owner.phoneNumber;
        return out;
    }
};

class Shelter {
private:
    AdoptionRecord* records;
    int capacity;
    int count;

    // Expands the arrays size if more space is needed
    void resizeArray(int newSize) {
        assert(newSize > 0);
        AdoptionRecord* newArr = new AdoptionRecord[newSize];
        for (int i = 0; i < count && i < newSize; ++i)
            newArr[i] = records[i];
        delete[] records;
        records = newArr;
        capacity = newSize;
    }

public:
    Shelter(int size = 2) : capacity(size), count(0) {
        records = new AdoptionRecord[capacity];
    }

    ~Shelter() {
        delete[] records;
    }

    // Adds an adoption record and calls resize if more space is needed
    void addRecord(const AdoptionRecord& ar) {
        if (count >= capacity)
            resizeArray(capacity * 2);
        records[count++] = ar;
    }

    // Displays all info in a formated table
    void showSummary() const {
        if (count == 0) {
            cout << "\nNo adoption records yet.\n";
            return;
        }

        cout << "\n-------------------------------------------------------------\n";
        cout << "                      ADOPTION SUMMARY                       \n";
        cout << "-------------------------------------------------------------\n";
        cout << left << setw(10) << "Name"
             << setw(6) << "Age"
             << setw(10) << "Type"
             << setw(15) << "Owner"
             << setw(12) << "Phone" << endl;
        cout << "-------------------------------------------------------------\n";

        for (int i = 0; i < count; ++i)
            cout << records[i] << endl;

        cout << "-------------------------------------------------------------\n";
        cout << "Total Records: " << count << endl;
        cout << "Array Capacity: " << capacity << endl;
        cout << "-------------------------------------------------------------\n";
    }
};

// MAIN !!!! The goated function which calls everything and handles user inputs :)
int main() {
    cout << "===========================================\n";
    cout << "   Pet Adoption Registration System (v2.0)  \n";
    cout << "   Created by: Trevor Ohlson                  \n";
    cout << "===========================================\n\n";

    Shelter myShelter;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Register a new pet adoption\n";
        cout << "2. View adoption summary\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        while (cin.fail() || choice < 0 || choice > 2) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter 0, 1, or 2: ";
            cin >> choice;
        }
        cin.ignore();

        if (choice == 1) {
            AdoptionRecord record;
            cin >> record;
            myShelter.addRecord(record);
            cout << "\n✅ Adoption registered successfully!\n";
        } else if (choice == 2) {
            myShelter.showSummary();
        }

    } while (choice != 0);

    cout << "\nThank you for using the Pet Adoption Registration System!\n";
    return 0;
}