#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
using namespace std;

class Facultymember // Sign in/ Sign up/ Password changing operations
{
protected:
    char *ID;
    char *Password;

public:
    bool existing(const string &wantedID, const string &wantedPASS, const string &filename) // Before someone sign up to the portal this function ensures that they dont take an existing ID 
    {
        size_t idsize, passsize;

        ifstream stream(filename, ios::binary);
        if (!stream)
        {
            cerr << "Failed to open file." << endl;
            return false;
        }
        while (true)
        {
            cout << "\t\t\t        CHECKING!\n\n";

            stream.read((char *)(&idsize), sizeof(size_t));
            char *newID = new char[idsize + 1]; // +1 for null terminator
            stream.read(newID, idsize);
            newID[idsize] = '\0'; // Add null terminator

            stream.read((char *)(&passsize), sizeof(size_t));
            char *newPassword = new char[passsize + 1]; // +1 for null terminator
            stream.read(newPassword, passsize);
            newPassword[passsize] = '\0'; // Add null terminator

            if (wantedID == newID) // IF ID IS ALREADY TAKEN IT RETURNS 1 WHICH MEANS "YES IT IS EXISTING"
            {
                cout << "\t\t\t        " << wantedID;
                delete[] newID;
                delete[] newPassword;
                stream.close();
                return true;
            }

            delete[] newID;
            delete[] newPassword;
            if (stream.eof())
                break;
        }
        stream.close();
        return false; // IF THERE IS NO MATCHES RETURN 0
    }

    bool signup(string &id, string &pass, size_t sID, size_t sPass, string filename)
    {
        // Allocate memory for ID and Password
        ID = new char[sID + 1];
        Password = new char[sPass + 1];

        // Copy strings to char arrays
        strncpy(ID, id.c_str(), sID);
        ID[sID] = '\0'; // Null-terminate
        strncpy(Password, pass.c_str(), sPass);
        Password[sPass] = '\0'; // Null-terminate

        ofstream stream(filename, ios::binary | ios::app); // OPENING REQUIRED FILE

        // CHECKING ALL CASES WITH EXISTING FUNCTION
        if (existing(id, pass, "profUP") || existing(id, pass, "stuUP") || existing(id, pass, "ADMIN")) 
        {
            // IF ANY MATCHES OCCUR RETURN 0
            delete[] ID;
            delete[] Password;
            stream.close();
            return false;
        }

        //IF FUNCTION COUNTINUES, WRITE INTO FILE
        if (stream.is_open())
        {
            stream.write(reinterpret_cast<char *>(&sID), sizeof(size_t));
            stream.write(ID, sID);
            stream.write(reinterpret_cast<char *>(&sPass), sizeof(size_t));
            stream.write(Password, sPass);
            stream.close();

            delete[] ID;
            delete[] Password;
            return true;
        }
        else
        {
            delete[] ID;
            delete[] Password;
            return false;
        }
    }
    //THIS ONE ACTUALLY SIGN IN FUNCTION
    //COMPARES ID AND PASSWORD WITH THE ONES IN THE FILE
    bool CheckIn(const string &wantedID, const string &wantedPASS, const string &filename) 
    {
        size_t idsize, passsize;

        ifstream stream(filename, ios::binary);
        if (!stream)
        {
            cerr << "Failed to open file." << endl;
            return false;
        }

        while (true)
        {
            if (stream.eof())
                break;
            cout << "\t\t\t        CHECKING!\n\n";

            stream.read((char *)(&idsize), sizeof(size_t));
            char *newID = new char[idsize + 1]; // +1 for null terminator
            stream.read(newID, idsize);
            newID[idsize] = '\0'; // Add null terminator

            stream.read((char *)(&passsize), sizeof(size_t));
            char *newPassword = new char[passsize + 1]; // +1 for null terminator
            stream.read(newPassword, passsize);
            newPassword[passsize] = '\0'; // Add null terminator

            if (wantedID == newID && wantedPASS == newPassword) // IF IT MATCHES RETURN TRUE
            {
                system("clear");
                cout << "\t\t\t       " << wantedID;
                delete[] newID;
                delete[] newPassword;
                return true;
            }

            delete[] newID;
            delete[] newPassword;
            if (stream.eof())
                break;
        }
        return false; // NO MATCHING
    }
    bool changePASS(string &wantedID, string &changeP, int &v) // v : 1 = proUP, 2 = stuUP, 3 = ADMIN
    {
        system("clear");
        string filename;
        size_t idsize, passize;
        bool che = false; //this is the FLAG that checks if the password succesfully changed or not
        //ACCORDING TO MEMMBER TYPE, FILE WILL BE OPENED
        switch (v)
        {
        case 1:
            filename = "profUP";
            break;
        case 2:
            filename = "stuUP";
            break;
        case 3:
            filename = "ADMIN";
            break;
        }
        ifstream stream(filename, ios::binary | ios::beg);
        ofstream temp("tempfile", ios::binary | ios::app); //this file will keep the passwords except "chageP" because it will be replaced with a new one
        if (!(stream && temp))
        {
            cerr << "Failed to open file!" << endl;
            return 0;
        }
        while (stream.read((char *)&idsize, sizeof(size_t)))
        {
            // reading ID
            ID = new char[idsize + 1];
            stream.read(ID, idsize);
            ID[idsize] = '\0';

            stream.read((char *)&passize, sizeof(size_t));
            // READİNG PASSWORD
            Password = new char[passize + 1];
            stream.read(Password, passize);
            Password[passize] = '\0';

            if (wantedID == ID && Password == changeP)
            {
                if (Password == changeP) 
                {
                    delete[] Password;
                    string del;
                    cout << "\t\t\t        ENTER YOUR NEW PASSWORD\n\n";
                    cin >> del;
                    system("clear");
                    size_t delsize = del.size();
                    Password = new char[delsize + 1];
                    strncpy(Password, del.c_str(), delsize);
                    Password[delsize] = '\0';
                    temp.write((char *)&idsize, sizeof(size_t));
                    temp.write(ID, idsize);
                    temp.write((char *)&delsize, sizeof(size_t));
                    temp.write(Password, delsize);
                    che = true;  
                }
                else
                {
                    system("clear");
                    cout << "\t\t\t        current password does not match!";
                    delete[] ID;
                    delete[] Password;
                    stream.close();
                    temp.close();
                    remove("tempfile");

                    return false;
                }
            }
            else if (wantedID != ID) //ID ALREADY DOES NOT MATCH SO TRANSFER ALL TO THE TEMP FILE
            {
                temp.write((char *)&idsize, sizeof(size_t));
                temp.write(ID, idsize);
                temp.write((char *)&passize, sizeof(size_t));
                temp.write(Password, passize);
            }
            delete[] Password;
            delete[] ID;
        }//END OF THE FILE
        stream.close();
        temp.close();

        if (che) // FLAG IS TRUE WHICH MEANS PASSWORD IS CHANGED
        {
            //THEN WE CAN REMOVE THE OLD FILE AND RENAME THE TEMP FILE
            if (remove(filename.c_str()) != 0 || rename("tempfile", filename.c_str()) != 0)
            {
                cerr << "\t\t\t        Error updating file" << endl;
                return false;
            }
            cout << "\t\t\t        Password successfully changed!" << endl;
            return true;
        }
        else //IF FLAG IS 0 EVERYTHING REMAINS SAME IN THE ORIGINAL FILE 
        {
            remove("tempfile");
            cout << "\t\t\t        ID is not found or password is not changed" << endl;
            return false;
        }
    } 
    /*~Facultymember()
    {

        if(ID  != nullptr)
            delete[] ID;
        if(Password != nullptr)
            delete[] Password;
    }*/
};
