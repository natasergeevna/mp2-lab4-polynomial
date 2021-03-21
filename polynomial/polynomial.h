#pragma once
#include <string>
#include <iostream>

using namespace std;

class polynom_string
{
    string str;
    bool isCorrect();
public:
    polynom_string(string s)
    {
        for (int i = 0; i < s.length(); i++)
            if (s[i] != ' ')
                str += s[i];
        if (!isCorrect())
            throw logic_error("Wrong polynom");
    }
    string getstr() const
    {
        return str;
    }
};

struct Link
{
    Link* pNext;
    double coefficient;
    int degree;
};

class Polynom
{
    Link* pFirst;
    void Insert(double c, int d);
    void reduct();
public:
    Polynom()
    {
        Link* p = new Link;
        p->coefficient = 0;
        p->degree = -1;
        p->pNext = nullptr;
        pFirst = p;
    }
    Polynom(polynom_string _s);
    Polynom(const Polynom& l);
    Polynom& operator=(const Polynom& l);
    bool operator==(const Polynom& l);
    bool operator!=(const Polynom& l);
    Polynom& operator+=(const Polynom& l);
    Polynom operator+(const Polynom& l);
    Polynom operator*(const Polynom& l);
    Polynom MultConst(double c);
    double ValuePoint(double x, double y, double z);
    void print();
    ~Polynom()
    {
        while (pFirst != nullptr)
        {
            Link* p = pFirst;
            pFirst = p->pNext;
            delete p;
        }
    }
};

