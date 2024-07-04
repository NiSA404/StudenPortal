#include <iostream>
#include <string>
#include <fstream>
#include "FacultyMember.h"
#include "courses.h"
using namespace std;

// Admin class and its methods gives lots of opportunities to admins
class ADMIN : public Facultymember
{
    int hidden;

public:
    ADMIN()
    {
        hidden = 2021;
    }
    void seeCOURSES() // Treates an object form "ders" class. Then, calls the overloaded constructure, shows the courses
    {
        system("clear");
        int number; // number is not necessary in this case
        ders oku(number);
        // cout << "∆ " << number << " courses are listed\n";
    }
    void seeMEMBERS(string filename) // Shows faculty members, the first administrator needs to select their status. Then the relevant file will be read
    {
        size_t idsize, passsize;
        system("clear");
        ifstream stream(filename, ios::binary);
        if (!stream)
        {
            cerr << "Failed to open file." << endl;
        }
        while (stream.read((char *)(&idsize), sizeof(size_t)))
        {
            char *newID = new char[idsize + 1]; // +1 for null terminator
            stream.read(newID, idsize);
            newID[idsize] = '\0'; // Add null terminator

            stream.read((char *)(&passsize), sizeof(size_t));
            char *newPassword = new char[passsize + 1]; // +1 for null terminator
            stream.read(newPassword, passsize);
            newPassword[passsize] = '\0'; // Add null terminator

            cout << "\t\t\t      " << newID << endl;

            delete[] newID;
            delete[] newPassword;
        }
        stream.close();
    }
    bool ADMINISTRATION(int k) // For admin administration, a specific code is needed
    {
        if (k == hidden)
        {
            return 1;
        }
        system("clear");
        cout << "\t\t\t        INVALID CODE!!\n";
        return 0;
    }
};