#ifndef PROF_H
#define PROF_H
#include <iostream>
#include <string>
#include <fstream>
#include "FacultyMember.h"
#include "courses.h"
#include "date.h"
using namespace std;

class Prof : public Facultymember
{
public:
    void opencourse(string &pID) // this method asks from a prof object, its course code and the other necessary information, creates an object of ders, then with them
    {                            // calls overloaded constructure of the class ders
        string code;
        string final;
        int capacity, x, y, z;
        cout << "\t\t\t____________________________________________________________\n\n";
        cout << "\t\t\t        *ENTER COURSE CODE : ";
        cin >> code;
        cout << endl;
        cout << "\t\t\t        *ENTER COURSE CAPACITY : ";
        cin >> capacity;
        cout << endl;
        cout << "\t\t\t        *ENTER FINAL DATE(day-month-year): ";
        cin >> x;
        cin >> y;
        cin >> z;
        Date date(x, y, z);
        date.getstring(final);
        cout << endl;
        cout << "\t\t\t____________________________________________________________\n\n";

        ders yeni(code, code.size(), final, final.size(), pID, pID.size(), capacity); // This method is from "courses" header and "ders" class.
    }
    void seeMYcourses(string &ıd) // This method ables proffesor to see her/his own courses
    {
        ders my(ıd); // it creates an obcejt of "ders" then overloads the method with Id;
    }
};

#endif // PROF_H