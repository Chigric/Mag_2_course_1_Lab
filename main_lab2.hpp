#ifndef MAIN_LAB2_HPP
#define MAIN_LAB2_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <valarray>
#include <functional>

#include "lab2.h"

using namespace std;
using namespace std::placeholders;

namespace SundayWork {
// Fredholm integral equation
namespace FIE {

// Output file
const string filenameLab2 = "output2.out";
}
}


int main_lab2()
{
    cout << endl << setw(12) << "START LAB #2" << endl << endl;

    fstream fileLab2(SundayWork::FIE::filenameLab2, fstream::out | fstream::trunc);
    assert(fileLab2.is_open() && "fileLab2 isn't open");


    valarray<valarray<long double> > vecA {
        {1, 2},
        {3, 4}
    };
    valarray<long double> vecY {3, 5};

    /*
    valarray<valarray<long double> > vecA {
        {0, 0, double(1)/4},
        {0, double(2)/8, double(-1)/4},
        {double(-5)/4, 1, 3}
    };
    valarray<long double> vecY {double(-1)/2, 2, 4};
    */
    valarray<long double> vecX = SundayWork::gaussianElimination(vecA, vecY);
    for (auto ptr : vecX)
        cout << ptr << " ";
    cout << endl;

    return 0;
}

#endif // MAIN_LAB2_HPP
