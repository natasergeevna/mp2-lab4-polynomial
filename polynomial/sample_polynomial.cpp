#include <iostream>
#include "polynomial.h"
using namespace std;

int main()
{
    int a;
    string s;
    cout << "Введите первый полином, состоящий из мономов: ";
    cin >> s;
    polynom_string str1(s);
    Polynom pol(str1);
    
    cout << "Введите второй полином, состоящий из мономов: ";
    cin >> s;
    polynom_string str2(s);
    Polynom pol1(str2);
    Polynom result;
    
    cout << "Сложение полиномов: ";
    result = pol + pol1;
    result.print();
    cout << endl;
    
    cout << endl << "Вычитание полиномов: ";
    Polynom result1;
    result1 = pol + pol1.MultConst(-1);
    result1.print();
    cout << endl;
        
    cout << endl << "Умножение полиномов: ";
//    cin >> s;
//    polynom_string str3(s);
//    Polynom pol2(str3);
    result = pol * pol1;
    result.print();
    cout << endl;
    
    cout << endl << "Введите точку, для вычисления в ней полинома: ";
    float x, y, z;
    cin >> x >> y >> z;
    cout << pol.ValuePoint(x, y, z) << endl;

  
}
