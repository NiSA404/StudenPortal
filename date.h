#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
using namespace std;

class Date
{
    int day;
    int month;
    int year;

public:
    Date(int x, int y, int z)
    {
        year = z;
        month = setmonth(y);
        day = setday(x);
    }
    void getstring(string &final)
    {
        final = "";
        final += to_string(day);
        final += convertmonth();
        final += to_string(year);
    }
    bool isLeapYear()
    {
        if (((this->year % 4 == 0) && (this->year % 100 != 0)) || (this->year % 400 == 0))
            return true;
        return false;
    }
    int setmonth(int x)
    {
        while (x < 1 || x > 12)
        {
            cout << "enter a valid month: ";
            cin >> x;
        }
        return x;
    }
    int setday(int x)
    {

        if (x < 32 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
        {
            return x;
        }
        if (x < 31 && (month == 4 || month == 6 || month == 9 || month == 11))
        {
            return x;
        }
        if (month == 2 && isLeapYear() && x < 30)
        {
            return x;
        }
        if (month == 2 && !isLeapYear() && x < 29)
        {
            return x;
        }
        else
        {
            int a;
            cout << "enter a valid day: ";
            cin >> a;
            return setday(a);
        }
    }
    string convertmonth()
    {
        string y;
        switch (month)
        {
        case 1:
            y = " JANUARY ";
            break;
        case 2:
            y = " February ";
            break;
        case 3:
            y = " March ";
            break;
        case 4:
            y = " April ";
            break;
        case 5:
            y = " May ";
            break;
        case 6:
            y = " June ";
            break;
        case 7:
            y = " July ";
            break;
        case 8:
            y = " August ";
            break;
        case 9:
            y = " Semptember ";
            break;
        case 10:
            y = " October ";
            break;
        case 11:
            y = " November ";
            break;
        case 12:
            y = " December ";
            break;
        default:
            y = " 0 ";
        }
        return y;
    }
};