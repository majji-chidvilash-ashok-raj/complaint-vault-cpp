#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class EmployeeSystem
{
private:
    string emails[1000];
    string texts[1000];
    string categories[1000];
    string status[1000];
    int ids[1000];
    int count;

public:
    EmployeeSystem();
    void loadFromFile();
    void saveToFile();
    void showNextPending();
    void searchByID();     // NEW FEATURE
};

EmployeeSystem::EmployeeSystem()
{
    count = 0;
    loadFromFile();
}

void EmployeeSystem::loadFromFile()
{
    ifstream file("complaints.txt");
    if (!file)
        return;

    count = 0;

    while (true)
    {
        int id;
        string email, category, text, stat;

        if (!(file >> id))  // if reading ID fails -> stop
            break;

        file.ignore();      // remove leftover newline
        getline(file, email);
        getline(file, category);
        getline(file, text);
        getline(file, stat);

        ids[count] = id;
        emails[count] = email;
        categories[count] = category;
        texts[count] = text;
        status[count] = stat;

        count++;
    }
}


void EmployeeSystem::saveToFile()
{
    ofstream file("complaints.txt");
    if (!file)
    {
        cout << "Error saving file!\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        file << ids[i] << "\n";
        file << emails[i] << "\n";
        file << categories[i] << "\n";
        file << texts[i] << "\n";
        file << status[i] << "\n";
    }
}


void EmployeeSystem::showNextPending()
{
    for (int i = 0; i < count; i++)
    {
        if (status[i] == "Pending" || status[i] == "pending")
        {
            cout << "\n===== PENDING COMPLAINT =====\n";
            cout << "ID: " << ids[i] << "\n";
            cout << "Email: " << emails[i] << "\n";
            cout << "Category: " << categories[i] << "\n";
            cout << "Complaint: " << texts[i] << "\n";
            cout << "Status: " << status[i] << "\n";
            cout << "=============================\n";

            cout << "\nEnter new status (Resolved / Pending): ";
            cin.ignore();
            getline(cin, status[i]);

            cout << "Status updated!\n";
            saveToFile();
            return;
        }
    }

    cout << "\nNo more pending complaints left!\n";
}

void EmployeeSystem::searchByID()
{
    int cid;
    cout << "\nEnter Complaint ID to search: ";
    cin >> cid;

    for (int i = 0; i < count; i++)
    {
        if (ids[i] == cid)
        {
            cout << "\n===== COMPLAINT DETAILS =====\n";
            cout << "ID: " << ids[i] << "\n";
            cout << "Email: " << emails[i] << "\n";
            cout << "Category: " << categories[i] << "\n";
            cout << "Complaint: " << texts[i] << "\n";
            cout << "Status: " << status[i] << "\n";
            cout << "==============================\n";

            char ch;
            cout << "\nDo you want to update status? (y/n): ";
            cin >> ch;

            if (ch == 'y' || ch == 'Y')
            {
                cout << "Enter new status (Resolved / Pending): ";
                cin.ignore();
                getline(cin, status[i]);

                saveToFile();
                cout << "Status updated!\n";
            }

            return;
        }
    }

    cout << "\nNo complaint found with ID " << cid << "\n";
}

int main()
{
    EmployeeSystem es;
    int choice;

    while (true)
    {
        cout << "\n===== EMPLOYEE PANEL =====\n";
        cout << "1. View & Update Next Pending Complaint\n";
        cout << "2. Search Complaint by ID\n";   // NEW OPTION
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            es.showNextPending();
            break;

        case 2:
            es.searchByID();
            break;

        case 0:
            cout << "Goodbye!\n";
            return 0;

        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
