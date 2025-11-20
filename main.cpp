#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ComplaintSystem
{
private:
    string emails[10000];
    string texts[10000];
    string categories[10000];
    string status[10000];
    int ids[10000];
    int count;
    int nextId;

public:
    ComplaintSystem();
    void loadFromFile();
    void saveToFile();
    void addComplaint();
    void viewByEmail();
    void viewByID();
    void editComplaint();
    void deleteComplaint();
};

ComplaintSystem::ComplaintSystem()
{
    count = 0;
    nextId = 1;
    loadFromFile();
}

void ComplaintSystem::loadFromFile()
{
    ifstream file("complaints.txt");
    if (!file)
        return;

    count = 0;

    while (true)
    {
        int id;
        string email, category, text, stat;

        if (!(file >> id))   // if reading ID fails -> stop
            break;

        file.ignore();       // remove leftover newline
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

    nextId = (count == 0) ? 1 : ids[count - 1] + 1;
}


void ComplaintSystem::saveToFile()
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


void ComplaintSystem::addComplaint()
{
    if (count >= 10000)
    {
        cout << "Storage full.\n";
        return;
    }

    cout << "Enter your email: ";
    cin >> emails[count];

    cin.ignore();
    cout << "Enter complaint category (Hostel/Mess/Transport/Academics/Others): ";
    getline(cin, categories[count]);

    cout << "Enter your complaint: ";
    getline(cin, texts[count]);

    status[count] = "Pending";

    ids[count] = nextId;

    cout << "Complaint added! Your ID = " << nextId << "\n";

    count++;
    nextId++;

    saveToFile();
}

void ComplaintSystem::viewByEmail()
{
    string email;
    cout << "Enter your email: ";
    cin >> email;

    bool found = false;

    for (int i = 0; i < count; i++)
    {
        if (emails[i] == email)
        {
            found = true;
            cout << "\nComplaint ID: " << ids[i]
                 << "\nCategory: " << categories[i]
                 << "\nComplaint: " << texts[i]
                 << "\nStatus: " << status[i]
                 << "\n";
        }
    }

    if (!found)
        cout << "No complaints found.\n";
}

void ComplaintSystem::viewByID()
{
    int id;
    cout << "Enter complaint ID: ";
    cin >> id;

    for (int i = 0; i < count; i++)
    {
        if (ids[i] == id)
        {
            cout << "\nEmail: " << emails[i]
                 << "\nCategory: " << categories[i]
                 << "\nComplaint: " << texts[i]
                 << "\nStatus: " << status[i]
                 << "\n";
            return;
        }
    }

    cout << "Complaint not found.\n";
}

void ComplaintSystem::editComplaint()
{
    int id;
    cout << "Enter ID to edit: ";
    cin >> id;
    cin.ignore();

    for (int i = 0; i < count; i++)
    {
        if (ids[i] == id)
        {
            cout << "Current category: " << categories[i] << "\n";
            cout << "Enter new category: ";
            getline(cin, categories[i]);

            cout << "Current complaint: " << texts[i] << "\n";
            cout << "Enter new complaint: ";
            getline(cin, texts[i]);

            cout << "Complaint updated.\n";
            saveToFile();
            return;
        }
    }

    cout << "Complaint not found.\n";
}

void ComplaintSystem::deleteComplaint()
{
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    for (int i = 0; i < count; i++)
    {
        if (ids[i] == id)
        {
            for (int j = i; j < count - 1; j++)
            {
                ids[j] = ids[j + 1];
                emails[j] = emails[j + 1];
                categories[j] = categories[j + 1];
                texts[j] = texts[j + 1];
                status[j] = status[j + 1];
            }

            count--;
            cout << "Complaint deleted.\n";
            saveToFile();
            return;
        }
    }

    cout << "Complaint not found.\n";
}

int main()
{
    ComplaintSystem cs;
    int choice;
    int cont = 1;

    while (cont == 1)
    {
        cout << "1. Add Complaint\n";
        cout << "2. View by Email\n";
        cout << "3. View by ID\n";
        cout << "4. Edit Complaint\n";
        cout << "5. Delete Complaint\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cs.addComplaint();
            break;
        case 2:
            cs.viewByEmail();
            break;
        case 3:
            cs.viewByID();
            break;
        case 4:
            cs.editComplaint();
            break;
        case 5:
            cs.deleteComplaint();
            break;
        case 0:
            cout << "Thank You!\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
        }

        cout << "\nDo you want to continue? (1 yes / 0 no): ";
        cin >> cont;

        if (cont == 0)
        {
            cout << "Thank You!\n";
            break;
        }
    }

    return 0;
}
