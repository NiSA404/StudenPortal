#include <iostream>
#include <string.h>
#include <fstream>
#include "prof.h"
#include "student.h"
#include "Admin.h"
#include "FacultyMember.h"

using namespace std;

void signin();
void signup();
void settings(int v, string &tempID);

int main()
{
    // Main page presentation:
    int choice;
    cout << "\t\t\t____________________________________________________________\n\n";
    cout << "\t\t\t                   *KADİR HAS STUDENT PORTAL*                 \n";
    cout << "\t\t\t____________________________________________________________\n";
    cout << "\t\t\t__________________________¨¨◊ MENU ◊¨¨______________________\n\n\n";
    cout << "\t\t\t◊ press 1 to LOGIN\n";
    cout << "\t\t\t◊ press 2 to REGISTER\n";
    cout << "\t\t\t◊ press 3 to EXIT\n\n";
    cout << "\t\t\tENTER YOUR CHOICE: ";
    cin >> choice;
    cout << endl;
    system("clear");
    // ACCORDING TO USER PREFERENCE FOLLOWING FUNCTIONS WILL BE CALLED
    switch (choice)
    {
    case 1:
        signin();
        break;
    case 2:
        signup();
        break;
    case 3:
        system("clear");
        cout << "\t\t\t______________________◊ You Left the Page ◊__________________\n";
        break;
    default:
        system("clear");
        cout << "\t\t\t🚫INVALID TRY | TRY AGAIN\n";
        main();
    }
}
void signin() // If a member is going to log in, this function ensures information retrieval and accuracy.
{
    system("clear");

    string tempID;
    string tempPASS;
    int type;
    // FIRST THEY CHOOSE THEIR STATUS
    cout << "\t\t\tSIGN IN AS A\n\n";
    cout << "\t\t\t◊ PROFESSOR press 1\n";
    cout << "\t\t\t◊ STUDENT press 2\n";
    cout << "\t\t\t◊ ADMIN press 3\n\n";
    cout << "\t\t\tsign in with: ";
    cin >> type;
    cout << endl;

    if (type == 1 || type == 2 || type == 3)
    {
        system("clear");
        cout << "\t\t\t____________________________________________________________\n\n";
        cout << "\t\t\t        *ENTER YOUR ID: ";
        cin >> tempID; // THIS VARIABLE HOLDS ID
        cout << endl;
        cout << "\t\t\t____________________________________________________________\n\n";
        cout << "\t\t\t        *ENTER YOUR PASSWORD: ";
        cin >> tempPASS; // THIS VARIEBLE HOLDS PASSWORD
        cout << endl;
        cout << "\t\t\t____________________________________________________________\n\n";

        // Then, ChekIn functions takes the control over

        if (type == 1) // professor sign in
        {
            Prof x;
            if (x.CheckIn(tempID, tempPASS, "profUP"))
            {
                cout << " YOUR PAGE IS LOADİNG!\n\n";
            }
            else //IF THERE IS NO MATCH PORTAL GOES BACK TO MAIN
            {
                cout << "\t\t\t        INVALID ID OR PASSWORD\n\n";
                int temp;
                cout << "press 1 to return main page ";
                cin >> temp;
                system("clear");
                main();
            }
        }
        else if (type == 2) // student sign in
        {
            student x;
            if (x.CheckIn(tempID, tempPASS, "stuUP"))
            {

                cout << " YOUR PAGE IS LOADİNG!\n\n";
            }
            else
            {
                cout << "\t\t\t        INVALID ID OR PASSWORD\n\n";
                int temp;
                cout << "press 1 to return main page ";
                cin >> temp;
                system("clear");
                main();
            }
        }
        else if (type == 3) // admin sign in
        {
            ADMIN AD;
            if (AD.CheckIn(tempID, tempPASS, "ADMIN"))
            {
                cout << " YOUR PAGE IS LOADİNG!\n\n";
            }
            else
            {
                cout << "\t\t\t        INVALID ID OR PASSWORD\n\n";
                int temp;
                cout << "press 1 to return main page ";
                cin >> temp;
                system("clear");
                main();
            }
        }

        settings(type, tempID); // this function takes ID and the type of the user as parameters then offers next choices
    }
    else // Something invalid 
    {
        signin();
    }
}
void settings(int v, string &tempID)
{
    system("clear");
    // v is the type of the user
    // I created all possible objects in here because when I tried it in switch-case statements, program gave me some errors
    ADMIN me;
    Facultymember what;
    Prof you;
    student teenager;
    string Change;
    short type1; // this holds the users choice, one of the ones in below
    cout << "\n\n";
    cout << "\t\t\t◊ CHANGE PASSWORD press 0\n"; // everyone can change their password
    if (v != 3)
    {
        cout << "\t\t\t◊ COURSE SETTINGS press 1\n\n"; // Admin already can see all the options so I don't want to offer this choice it is useless
    }
    if (v == 3)
    {                                                           // FOR ADMINS
        cout << "\t\t\t◊ SHOW STUDENT LIST press 2\n";          // SHOWS ALL STUDENTS
        cout << "\t\t\t◊ SHOW PROFESSOR LIST press 3\n";        // SHOWS ALL PROFESSORS
        cout << "\t\t\t◊ SHOW COURSE INFORMATIONS press 4\n\n"; // ALL COURSES' INFOS
    }
    cout << "\t\t\t◊ GO TO MAIN PAGE press 5\n";
    cout << "\t\t\tcountinue to: ";
    cin >> type1;
    switch (type1)
    {
    case 0: // CHANGE PASSWORD
        cout << "\t\t\t____________________________________________________________\n\n";
        cout << "\t\t\t        *ENTER YOUR CURRENT PASSWORD: ";
        cin >> Change;
        what.changePASS(tempID, Change, v); // changePASS is a comman funtion, it takes ID, CURRENT PASSWORD, AND THE TYPE OF THE USER
        signin();
        break;
    case 1:
        if (v == 1) // PROFESSORS' COURSE SETTINGS
        {
            system("clear");
            int sec;
            cout << "\t\t\t◊ OPEN COURSE press 6\n";
            cout << "\t\t\t◊ SHOW MY COURSES LIST press 7\n"; // tempID's giving courses are shown
            cout << "\t\t\tcountinue to: ";
            cin >> sec;
            if (sec == 6)
            {
                you.opencourse(tempID); // CREATES A NEW COURSE
                settings(v, tempID); // then turns to settings
            }
            else if (sec == 7)
            {
                you.seeMYcourses(tempID); // shows professors current courses
                cout << "PREVIOUS PAGE press 5 ";
                cin >> type1;
                settings(v, tempID);
            }
            else
            {
                system("clear");
                cout << "INVALID TRY\n";
                settings(v, tempID);
            }
        }
        if (v == 2) // students' course settings
        {
            system("clear");
            int sec;
            cout << "\t\t\t◊ ENROLL A COURSE press 6\n";
            cout << "\t\t\t◊ SHOW MY COURSES LIST press 7\n"; //
            cout << "\t\t\tcountinue to: ";
            cin >> sec;
            system("clear");
            if (sec == 6)
            {
                teenager.enroll(tempID); // shows available courses and makes able to chose one
                cout << "PREVIOUS PAGE press 5 ";
                cin >> type1;
                settings(v, tempID);
            }
            else if (sec == 7)
            {
                cout << "\t\t\t◊ " << tempID << "'s courses:\n";
                teenager.enrolledCourses(tempID); //shows your courses
                cout << "PREVIOUS PAGE press 5 ";
                cin >> type1;
                settings(v, tempID);
            }
        }
        break;
    case 2:
        if (v != 3) // someone except admin can still choose 2 but they should not so that I  am returning them back
        {
            system("clear");
            settings(v, tempID);
        }
        me.seeMEMBERS("stuUP"); // shows student list
        cout << "PREVIOUS PAGE press 5 ";
        cin >> type1;
        settings(v, tempID);
        break;
    case 3:
        if (v != 3)
        {
            system("clear");
            settings(v, tempID);
        }
        me.seeMEMBERS("profUP");  // shows professor list
        cout << "GO BACK PAGE press 5 ";
        cin >> type1;
        settings(v, tempID);
        break;
    case 4:
        if (v != 3)
        {
            system("clear");
            settings(v, tempID);
        }
        me.seeCOURSES();
        cout << "GO BACK PAGE press 5 ";  // shows courses list
        cin >> type1;
        settings(v, tempID);
        break;
    case 5:
        system("clear");
        main();
    default:
        system("clear");
        main();
    }
}
void signup()
{
    string tempID;
    string tempPASS;
    int type;
    // printing the choices for sign up
    cout << "\t\t\tCREATE ACCOUNT AS A\n\n";
    cout << "\t\t\t◊ PROFESSOR press 1\n";
    cout << "\t\t\t◊ STUDENT press 2\n";
    cout << "\t\t\t◊ ADMIN press 3\n\n";
    cout << "\t\t\tsign up with: ";
    cin >> type;
    cout << endl;
    // only three choices are valid
    if (type == 1 || type == 2 || type == 3)
    {
        // before creating files, user creates its ID and pASSWORD
        system("clear");
        cout << "\t\t\t____________________________________________________________\n\n";
        cout << "\t\t\t        *CREATE AN ID     : ";
        cin >> tempID;
        cout << endl;
        cout << "\t\t\t____________________________________________________________\n\n";
        cout << "\t\t\t        *CREATE A PASSWORD: ";
        cin >> tempPASS;
        cout << endl;
        cout << "\t\t\t____________________________________________________________\n\n";
        // If user is a professor "profUP" file will be opened
        //  signup method is a boolean function in parent class so it checks if the ID is already in use or file is open succesfully
        if (type == 1)
        {
            Prof A;
            if (A.signup(tempID, tempPASS, tempID.size(), tempPASS.size(), "profUP"))
            {
                system("clear");
                cout << endl
                     << "\t\t\t         Account succesfully created\n\n";
                main();
            }
            else
            {
                system("clear");
                cout << "\t\t\t        EXISTING OR INVALID ID!\n\n";
                signup();
            }
        }
        else if (type == 2) // Appearently type 2 is a student class
        {
            student B;

            if (B.signup(tempID, tempPASS, sizeof(tempID), sizeof(tempPASS), "stuUP"))
            {
                system("clear");
                cout << endl
                     << "\t\t\t         Account succesfully created\n\n";
                main();
            }
            else
            {
                system("clear");
                cout << "\t\t\t        EXISTING OR INVALID ID!\n\n";
                signup();
            }
        }
        else if (type == 3) // admin class, creates a different file for admins
        {
            ADMIN ad;
            int k;
            cout << "\t\t\t        ENTER THE ADMIN CODE: "; // I defined a code, and only ones who know the code can create an admin account
            cin >> k;
            if (ad.ADMINISTRATION(k)) // this function checks the code
            {
                if (ad.signup(tempID, tempPASS, sizeof(tempID), sizeof(tempPASS), "ADMIN")) // signup funtion is a parent method which is defined in FacultyMember class and it does the same thing
                {                                                                           // with in the previous types
                    system("clear");
                    cout << endl
                         << "\t\t\t         Account succesfully created\n\n";
                    main();
                }
                else
                {
                    system("clear");
                    cout << "\t\t\t        EXISTING OR INVALID ID!\n\n";
                    signup();
                }
            }
            else // ıf admın code does not true then it will never check ID and create account
                cout << "\t\t\t      !!ACCESS DENIED!!\n\n";
        }
        main();
    }
    else // in case of invalid type choice, system turns to the sign up page
    {
        system("clear");
        cout << "\t\t\t      INVALID CHOICE\n\n";
        return signup();
    }
}
