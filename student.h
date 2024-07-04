#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <fstream>
#include "FacultyMember.h"
#include "prof.h"
#include "courses.h"
using namespace std;

class student : public Facultymember
{
    string *CodesARR;
    int size;

public:
    void enroll(string sID) // If a a student wants to enroll an existing course this function runs.
    {
        int choice;
        size_t length;
        size_t tıd, tis;
        char *tempıd;
        char *tempsifre;

        // Creating an object of class "ders".
        // overloaded constructor shows the list of courses also count how many courses are there.
        ders teen(this->size); // size variable of this class is sent by reference and it counts the number of courses, also prints each of them.

        // allocating array according to new value of "size"
        this->CodesARR = new string[this->size]; // this array will hold the codes of each courses
        this->CodesARR = teen.array(this->size); // that's why, array method of the object teen is called here, it will return an array of strings and assign it to this->array

        cout << "Choose the number of the course you want to enroll: ";
        cin >> choice; // (choice - 1) will be the choice
        cout << endl;

        length = CodesARR[choice - 1].size(); // size of the course's code

        // "enroll.bin" file keep the record of the students and their courses codes

        ifstream check("enroll.bin", ios::binary);
        if (check) // Before student taking course, this loop checks if student is already in the course
        {
            while (check.read((char *)&tıd, sizeof(size_t)))
            {
                // read the student ID
                tempıd = new char[tıd + 1];
                check.read(tempıd, tıd);
                tempıd[tıd] = '\0';

                // READ THE COURSE CODE
                check.read((char *)&tis, sizeof(size_t));
                tempsifre = new char[tis + 1];
                check.read(tempsifre, tis);
                tempsifre[tis] = '\0';

                if (sID == tempıd && tempsifre == CodesARR[choice - 1]) // ıf these are same, student cannot enroll to course
                {
                    cout << endl
                         << "\t\t\t        You are already enrolled to this course!\n";
                    delete[] tempıd;
                    delete[] tempsifre;
                    check.close();
                    return;
                }
                // dealllocating char pointers to read next stu and course
                delete[] tempıd;
                delete[] tempsifre;
            }
            // if it does not match any of the records then student can enroll
            check.close();
        }

        ofstream kayıt("enroll.bin", ios::binary | ios::app);
        if (!kayıt)
        {
            cerr << "FILE OPENING ERROR/STUDENT>enroll\n";
            return;
        }

        // in this part!!!!!!!!!!

        // student ID is copied to char array
        size_t stu = sID.size();
        ID = new char[stu + 1];
        strncpy(ID, (char *)sID.c_str(), stu);
        ID[stu] = '\0';

        // size of the student's ID is written to binary file
        kayıt.write((char *)&stu, sizeof(size_t));
        // Then itself
        kayıt.write(ID, stu);

        // size of the course code
        kayıt.write((char *)&length, sizeof(size_t));
        // then itself
        kayıt.write((char *)&CodesARR[choice - 1], length);

        // system("clear");
        cout << "ENLROLLED to " << CodesARR[choice - 1];
        cout << endl;
        kayıt.close();
        // deallocating char pointer and dynamic array
        delete[] ID;
        delete[] CodesARR;
    }
    void enrolledCourses(string card) // this method ables students to see their registered courses
    {
        size_t x, y;
        ifstream pas("enroll.bin", ios::binary);
        if (pas)
        {
            // reading the file and checking for matches
            while (pas.read((char *)&x, sizeof(size_t)))
            {
                ID = new char[x + 1];
                pas.read(ID, x);
                ID[x] = '\0';

                pas.read((char *)&y, sizeof(size_t));
                Password = new char[y + 1];
                pas.read(Password, y);
                Password[y] = '\0';

                if (ID == card)
                {
                    cout << "____________________________________________________________\n\n";
                    cout << "Course Code  | " << Password << endl;
                    cout << "____________________________________________________________\n\n";
                }
                delete[] ID;
                delete[] Password;
            }
        }
        else
            cout << "\t\t\t        File Opening Error!\n\n";
        pas.close();
    }
    /*~student()
    {
        if(CodesARR != nullptr)
        {
            delete[] CodesARR;
        }
    } */
};
#endif // STUDENT_H