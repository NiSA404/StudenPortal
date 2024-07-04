#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "FacultyMember.h"
using namespace std;

// The file kurslar.bin holds the courses in the instutition
// ders class has three overloaded constructures and A function which returns a array of strings.
class ders
{
    char *profID;
    char *kod;
    char *sınav;
    int kontenjan;

public:
    // OPENING A NEW COURSE
    ders(string kod, size_t kodsize, string sınav, size_t sınavsize, string profID, size_t kimliksize, int cap); // kod represents the name of the course, sınav is the final date, cap is the capacity of the course.
    // MONITORING EXISTING COURSES
    ders(int &number);
    ders(string &id);
    string *array(int size);
};
inline ders::ders(string kod, size_t kodsize, string sınav, size_t sınavsize, string profID, size_t kimliksize, int cap)
{
    ofstream openkurs("kurslar.bin", ios::binary | ios::app);
    if (!openkurs)
    {
        cerr << "FILE OPENING ERROR!?\n";
        return;
    }
    // to write strings into a binary file ,I am putting every charachter of them into a char array
    this->kod = new char[kodsize + 1];     // size of the arrays is one more than size of the the string
    this->sınav = new char[sınavsize + 1]; // beacuse I will add a null terminator at the end, manually.
    this->profID = new char[kimliksize + 1];
    this->kontenjan = cap;
    strncpy(this->kod, kod.c_str(), kodsize); // I learned thet strcpy() handles null terminator, so no need to di it manually but I already did it.
    this->kod[kodsize] = '\0';
    strncpy(this->sınav, sınav.c_str(), sınavsize);
    this->sınav[sınavsize] = '\0';
    strncpy(this->profID, profID.c_str(), kimliksize);
    this->profID[kimliksize] = '\0';
    // write into binary file operations:
    openkurs.write((char *)&kimliksize, sizeof(size_t));
    openkurs.write(this->profID, kimliksize);
    openkurs.write((char *)&kodsize, sizeof(size_t));
    openkurs.write(this->kod, kodsize);
    openkurs.write((char *)&sınavsize, sizeof(size_t));
    openkurs.write(this->sınav, sınavsize);
    openkurs.write((char *)&kontenjan, sizeof(int));
    openkurs.close();
    cout << "COURSE IS OPEN NOW\n";
    // end of the writing operation class informations are visible now.
    delete[] this->kod;
    delete[] this->sınav;
    delete[] this->profID;
    
}
inline ders::ders(int &number) // MONITORING COURSE INFORMATIONS
{
    // Number is passed by reference because in some parts of the code I wanted to use number to see course numbers.
    // However, for some parts I HAVE NOT USE NUMBER AT ALL

    // Opening the file which contains courses informations
    ifstream bilgigör("kurslar.bin", ios::binary);
    if (!bilgigör)
    {
        cerr << "FILE OPENING ERROR!\n";
        return;
    }
    size_t one, two, three;                             // assign the size of ıd;kod;final date into these variables
    number = 0;                                         // this is a counter, counts courses numbers
    while (bilgigör.read((char *)&one, sizeof(size_t))) // According to the structure of the binary file, first read the professors' ID size until end of the file.
    {
        number++; // everytime this while loop works, counter will be increased one.

        // profID, kod, sınav and kontenjan are the variables of the class which are char pointers. So that, while reaading them from file,first their sizes
        // are readed

        profID = new char[one + 1];
        bilgigör.read(profID, one);
        profID[one] = '\0';

        cout << "____" << number << "_____|\n";
        cout << "PROFESSOR | " << profID << endl;

        bilgigör.read((char *)&two, sizeof(size_t));
        kod = new char[two + 1];
        bilgigör.read(kod, two);
        kod[two] = '\0';

        cout << "CODE      | " << kod << endl;

        bilgigör.read((char *)&three, sizeof(size_t));
        sınav = new char[three + 1];
        bilgigör.read(sınav, three);
        sınav[three] = '\0';

        cout << "FINAL DATE| " << sınav << endl;

        bilgigör.read((char *)&kontenjan, sizeof(int));

        cout << "CAPACITY  | " << kontenjan << endl;
        cout << "____________________________________________________________\n\n";

        delete[] kod;
        delete[] sınav;
        delete[] profID;
    }
    bilgigör.close();
}

inline string *ders::array(int size) // this function also monitors the course ınformatıons but, for students. ıts purpose, returning array courses codes
{                                    // so that, student can choose a course
    string *arr = new string[size];
    ifstream bilgigör("kurslar.bin", ios::binary);
    if (!bilgigör)
    {
        cerr << "FILE OPENING ERROR!\n";
        return nullptr;
    }
    size_t one, two, three; // size of ıd;kod;final date
    int s = 0;              // first index of the array
    while (bilgigör.read((char *)&one, sizeof(size_t)))
    {

        profID = new char[one + 1];
        bilgigör.read(profID, one);
        profID[one] = '\0';

        bilgigör.read((char *)&two, sizeof(size_t));
        kod = new char[two + 1];
        bilgigör.read(kod, two);
        kod[two] = '\0';

        arr[s] = kod; // code is assigned to the array
        s++;

        bilgigör.read((char *)&three, sizeof(size_t));
        sınav = new char[three + 1];
        bilgigör.read(sınav, three);
        sınav[three] = '\0';

        bilgigör.read((char *)&kontenjan, sizeof(int));

        delete[] kod;
        delete[] sınav;
        delete[] profID;
    }
    bilgigör.close();
    return arr;
}

inline ders::ders(string &id) // for professors to see their courses
{
    system("clear");
    ifstream myc("kurslar.bin", ios::binary);
    if (!myc)
    {
        cerr << "FILE OPENING ERROR!?\n";
        return;
    }
    size_t one, two, three;
    int u = 0;
    while (myc.read((char *)&one, sizeof(size_t)))
    {
        profID = new char[one + 1];
        myc.read(profID, one);
        profID[one] = '\0';

        myc.read((char *)&two, sizeof(size_t));
        kod = new char[two + 1];
        myc.read(kod, two);
        kod[two] = '\0';

        myc.read((char *)&three, sizeof(size_t));
        sınav = new char[three + 1];
        myc.read(sınav, three);
        sınav[three] = '\0';

        myc.read((char *)&kontenjan, sizeof(int));

        if (profID == id)
        {
            u++;
            cout << profID << "     | COURSE " << u << " :\n";
            cout << "___________________\n\n";
            cout << "CODE      | " << kod << endl;
            cout << "FINAL DATE| " << sınav << endl;
            cout << "CAPACITY  | " << kontenjan << endl
                 << endl;
            cout << "____________________________________________________________\n\n";
        }

        delete[] kod;
        delete[] sınav;
        delete[] profID;
    }
    myc.close();
}
