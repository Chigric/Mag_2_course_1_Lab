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
namespace FIE_VAR17 {
using MyTypeAccuracy = long double;
// Output file
const string filenameLab2 = "output2.out";
// Equation
/// u(x) - /int_0^1(x*t^2*u(t)dt) = 1
/// u(x) - /int_startT^endT(kernelFunc(x,t)*u(t)) = rightFunc(x) <=>
/// <=> u(x) = answerFunc(x)
double startT = 0;
double endT = 1;
auto kernelFunc = [](MyTypeAccuracy x, MyTypeAccuracy t) -> MyTypeAccuracy {
    return x * (t*t);
};
auto rightFunc = [](MyTypeAccuracy x) -> MyTypeAccuracy {
    return 1;
};
// answer func (for checking answers)
auto answerFunc = [](MyTypeAccuracy x) -> MyTypeAccuracy {
    return 1 + (4/9)*x;
};
}
}


int main_lab2()
{
    cout << endl << setw(12) << "START LAB #2" << endl << endl;

    fstream fileLab2(SundayWork::FIE_VAR17::filenameLab2, fstream::out | fstream::trunc);
    assert(fileLab2.is_open() && "fileLab2 isn't open");

    // solve Fredholm integral equation by Trapezoidal rule
    SundayWork::Vector vecX = SundayWork::SuccessiveApproximationMethodFredholm(
                SundayWork::FIE_VAR17::startT
                , SundayWork::FIE_VAR17::endT
                , SundayWork::FIE_VAR17::kernelFunc
                , SundayWork::FIE_VAR17::rightFunc
                , SundayWork::ECubatureRules::Trapezoidal
                , 6);
    for (auto ptr : vecX)
        cout << ptr << " ";
    cout << endl;

    return 0;
}

#endif // MAIN_LAB2_HPP
