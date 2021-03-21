#include "polynomial.h"
static const size_t npos = -1;

bool polynom_string::isCorrect()
{
    int length = str.length();
    if (length == 0)
        return false;
    int k[3] = {0,0,0};
    int flag = 0;
    int point = 0;
    int simbol = 0;
    str = str + "+";
    string can = "xyz-+0123456789.";
    if (str[0] == '.')
        return false;
    for (int i = 0; i < length; i++)
    {
        if (can.find(str[i]) == npos)
            return false;
        for (int j = 0; j < 3; j++)
        {
            if ((str[i] == can[j]) && (flag == 0))
            {
                if (k[j] == 1)
                    return false;
                k[j]++;
                flag = 1;
                point = 0;
                simbol = 0;
                break;
            }
            if (flag == 1)
            {
                if ((str[i] < '0') || (str[i] > '9'))
                    return false;
                else
                {
                    string temp = "xyz+-";
                    if (temp.find(str[i + 1]) != npos)
                        flag = 0;
                    else
                        return false;
                }
            }
        }
        if ((str[i] == '-') || (str[i] == '+'))
        {
            if (simbol > 0)
                return false;
            else
            {
                k[0] = k[1] = k[2] = 0;
                simbol++;
            }
        }
        if ((str[i] >= '0') && (str[i] <= '9'))
            simbol = 0;
        if (str[i] == '.')
        {
            if (point > 0)
                return false;
            else
            {
                if ((str[i - 1] < '0') || (str[i - 1] > '9'))
                    return false;
                else
                    point++;
            }
        }
    }
    if ((str[length - 1] == '-') || (str[length - 1] == '+'))
        return false;
    str.erase(length);
    return true;
}

Polynom::Polynom(polynom_string _s)
{
    Link* p = new Link;
    p->coefficient = 0;
    p->degree = -1;
    p->pNext = nullptr;
    pFirst = p;
    string s = _s.getstr() + "+";
    if ((s[0] != '-') && (s[0] != '+'))
        s = "+" + s;
    int length = s.length();
    int i = 0;
    while (i != (length - 1))
    {
        double c;
        if ((s[i + 1] == 'x') || (s[i + 1] == 'y') || (s[i + 1] == 'z'))
        {
            if (s[i] == '+')
                c = 1;
            else
                c = -1;
            i++;
        }
        else
        {
            string temp;
            int j = s.find_first_of("-+xyz", i + 1);
            while (i < j)
            {
                temp = temp + s[i];
                i++;
            }
            c = stof(temp);
        }
        int x = 0, y = 0, z = 0;
        for (int j = 0; j < 3; j++)
        {
            switch (s[i])
            {
            case 'x':
                x = s[i + 1] - '0';
                i += 2;
                break;
            case 'y':
                y = s[i + 1] - '0';
                i += 2;
                break;
            case 'z':
                z = s[i + 1] - '0';
                i += 2;
                break;
            }
        }
        int d = x * 10000 + y * 100 + z;
        Insert(c, d);
    }
    reduct();
}

Polynom::Polynom(const Polynom& l)
{
    Link* p = new Link;
    pFirst = p;
    p->coefficient = 0;
    p->degree = -1;
    p->pNext = nullptr;
    Link* pp = l.pFirst->pNext;
    while (pp != nullptr)
    {
        p->pNext = new Link;
        p = p->pNext;
        p->coefficient = pp->coefficient;
        p->degree = pp->degree;
        p->pNext = nullptr;
        pp = pp->pNext;
    }
}

Polynom& Polynom::operator=(const Polynom& l)
{
    if (this != &l)
    {
        Link* p = pFirst;
        p = p->pNext;
        pFirst->pNext = nullptr;
        while (p != nullptr)
        {
            Link* pp = p;
            p = pp->pNext;
            delete pp;
        }
        p = pFirst;
        Link* pp = l.pFirst->pNext;
        while (pp != nullptr)
        {
            p->pNext = new Link;
            p = p->pNext;
            p->coefficient = pp->coefficient;
            p->degree = pp->degree;
            p->pNext = nullptr;
            pp = pp->pNext;
        }
    }
    return *this;
}

void Polynom::Insert(double c, int d)
{
    Link* p = new Link;
    p->coefficient = c;
    p->degree = d;
    Link* pp = pFirst;
    while (pp->pNext != nullptr)
    {
        Link* ppp = pp->pNext;
        if (d <= ppp->degree)
        {
            p->pNext = pp->pNext;
            pp->pNext = p;
            break;
        }
        pp = pp->pNext;
    }
    if (pp->pNext == nullptr)
    {
        pp->pNext = p;
        p->pNext = nullptr;
    }
}

void Polynom::reduct()
{
    Link* p = pFirst;
    Link* pp = p->pNext;
    if (pp != nullptr)
    {
        while (pp->pNext != nullptr)
        {
            if (pp->degree == pp->pNext->degree)
            {
                Link* temp = pp->pNext;
                pp->coefficient += temp->coefficient;
                pp->pNext = temp->pNext;
                delete temp;
            }
            else
            {
                if (pp->coefficient != 0)
                {
                    p = pp;
                    pp = pp->pNext;
                }
                else
                {
                    Link* temp = pp;
                    p->pNext = temp->pNext;
                    pp = pp->pNext;
                    delete temp;
                }
            }
        }
        if (pp->coefficient == 0)
        {
            p->pNext = nullptr;
            delete pp;
        }
    }
}

void Polynom::print()
{
    Link* p = pFirst;
    p = p->pNext;
    string s;
    while (p != nullptr)
    {
        int x = p->degree / 10000;
        int y = (p->degree % 10000) / 100;
        int z = p->degree % 100;
        if (p->coefficient > 0)
            s = s + "+";
        if ((x + y + z) != 0)
        {
            if ((p->coefficient != -1) && (p->coefficient != 1))
                s += to_string(p->coefficient);
            else
                if (p->coefficient == -1)
                    s = s + "-";
        }
        else
            s += to_string(p->coefficient);
        if (x != 0)
        {
            s += "x";
            s += to_string(x);
        }
        if (y != 0)
        {
            s += "y";
            s += to_string(y);
        }
        if (z != 0)
        {
            s += "z";
            s += to_string(z);
        }
        p = p->pNext;
    }
    if (s.length() == 0)
        s = "0";
    if (s[0] == '+')
        s.erase(0, 1);
    cout << s;
}

Polynom& Polynom::operator+=(const Polynom& l)
{
    Link* p = l.pFirst->pNext;
    while (p != nullptr)
    {
        Insert(p->coefficient, p->degree);
        p = p->pNext;
    }
    reduct();
    return *this;
}

Polynom Polynom::operator+(const Polynom& l)
{
    Polynom temp(*this);
    temp += l;
    return temp;
}

Polynom Polynom::operator*(const Polynom& l)
{
    Polynom temp;
    Link* p = pFirst->pNext;
    while (p != nullptr)
    {
        Link* pp = l.pFirst->pNext;
        while (pp != nullptr)
        {
            temp.Insert(p->coefficient * pp->coefficient, p->degree + pp->degree);
            pp = pp->pNext;
        }
        temp.reduct();
        p = p->pNext;
    }
    return temp;
}

Polynom Polynom::MultConst(double c)
{
    Polynom temp(*this);
    Link* p = temp.pFirst->pNext;
    while (p != nullptr)
    {
        p->coefficient *= c;
        p = p->pNext;
    }
    temp.reduct();
    return temp;
}

double Polynom::ValuePoint(double x, double y, double z)
{
    double result = 0;
    Link* p = pFirst->pNext;
    while (p != nullptr)
    {
        int sx = p->degree / 10000;
        int sy = (p->degree % 10000) / 100;
        int sz = p->degree % 100;
        double temp = pow(x, sx) * pow(y, sy) * pow(z, sz);
        result += temp * p->coefficient;
        p = p->pNext;
    }
    return result;
}

bool Polynom::operator==(const Polynom& l)
{
    Link* p = l.pFirst->pNext;
    Link* pp = pFirst->pNext;
    while ((p != nullptr) && (pp != nullptr))
    {
        if (p->degree != pp->degree)
            return false;
        else
        {
            if (p->coefficient != pp->coefficient)
                return false;
        }
        p = p->pNext;
        pp = pp->pNext;
    }
    if (((p != nullptr) && (pp == nullptr)) || ((pp != nullptr) && (p == nullptr)))
        return false;
    return true;
}

bool Polynom::operator!=(const Polynom& l)
{
    if (*this == l)
        return false;
    return true;
}


