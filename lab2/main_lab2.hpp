#ifndef MAIN_LAB2_HPP
#define MAIN_LAB2_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <valarray>
#include <functional>
#include <cmath>

#include "lab2.h"
#include "Output.hpp"

# define M_PIl          3.141592653589793238462643383279502884L /* pi */

using namespace std;
using namespace std::placeholders;

namespace SundayWork {
// Fredholm integral equation
namespace FIE_VAR3 {
using MyTypeAccuracy = long double;
// Output file
const string filenameLab2 = "output2.out";
const string filenameLab2ForExcel = "output2ForExcel.out";
// Equation
/// u(x) - /int_startT^endT(kernelFunc(x,t)*u(t)) = rightFunc(x) <=>
/// <=> u(x) = answerFunc(x)
double startT = 0;
double endT = 2*M_PIl;
auto kernelFunc = [](MyTypeAccuracy x, MyTypeAccuracy t) -> MyTypeAccuracy {
    return 1/(4*M_PIl) * 1/(std::sin((x+t)/2)*std::sin((x+t)/2)
                            + 0.25L*std::cos((x+t)/2)*std::cos((x+t)/2));
};
auto rightFunc = [](MyTypeAccuracy x) -> MyTypeAccuracy {
    return 1/(16*M_PIl) * (5 + 3*std::cos(2*x));
};
// answer func (for checking answers)
auto answerFunc = [](MyTypeAccuracy x) -> MyTypeAccuracy {
    return 1/(160*M_PIl) * (25 + 27*std::cos(2*x));
};
}
}

void printVector(SundayWork::Vector&& vecX)
{
    std::cout.precision(5);
    for (auto ptr : vecX)
        cout << ptr << " ";
    cout << endl;
}

void solvingAccuracy(SundayWork::Vector&& numVec, SundayWork::MaxDouble qualStep, std::fstream& file)
{
    using namespace SundayWork::FIE_VAR3;
    SundayWork::MaxDouble stepX = (endT - startT) / qualStep;
    SundayWork::Vector answerVec(qualStep);
    SundayWork::Vector accuracyVec(qualStep);

    int i = 0;
    for (SundayWork::MaxDouble x = startT; x < endT, i < qualStep; x += stepX, i++) {
        answerVec[i] = answerFunc(x);
        accuracyVec[i] = std::abs(answerVec[i] - numVec[i]);
    }
    // print vectors to consol && file
    //printVector(std::move(accuracyVec));
    SundayWork::output2FileOneVec(file, numVec, 5, "X_i");
    file.open(filenameLab2, fstream::in | fstream::app);
    SundayWork::output2FileOneVec(file, answerVec, 5, "answer");
    file.open(filenameLab2, fstream::in | fstream::app);
    SundayWork::output2FileOneVec(file, accuracyVec, 5, "R_i");

    file.open(filenameLab2, fstream::in | fstream::app);
    assert(file.is_open() && "fileLab2 isn't open");
    cout        << "|---------------- END MATH METHOD ----------------|"
                << endl << endl
                << "Max accuracy " << accuracyVec.max()
                << endl << endl;
    file        << "|---------------- END MATH METHOD ----------------|"
                << endl << endl
                << "Max accuracy " << accuracyVec.max()
                << endl << endl;

    // for excel table
    fstream file22222(filenameLab2ForExcel, fstream::in | fstream::app);
    SundayWork::output2ExcelTable(file22222, numVec, 5, "X_i");
}

void printDefaultFuncForExcelTable(SundayWork::MaxDouble qualStep)
{
    using namespace SundayWork::FIE_VAR3;
    SundayWork::MaxDouble stepX = (endT - startT) / qualStep;
    SundayWork::Vector answerVec(qualStep);
    SundayWork::Vector accuracyVec(qualStep);

    int i = 0;
    for (auto x = startT; x < endT, i < qualStep; x += stepX, i++)
        answerVec[i] = answerFunc(x);

    fstream file22222(filenameLab2ForExcel, fstream::in | fstream::app);
    SundayWork::output2ExcelTable(file22222, answerVec, 5, "answer");
}

template <typename Func>
void solveApproximationMethod(Func func, std::fstream& file)
{
    long double steps[] = {10, 100};

    for (auto step : steps) {
        // solve Fredholm integral equation by Trapezoidal rule
        SundayWork::Vector vecXTrapezoidal = func(SundayWork::ECubatureRules::Trapezoidal, step);
        // solve Fredholm integral equation by Simpson rule
        SundayWork::Vector vecXSimpson = func(SundayWork::ECubatureRules::Simpson, step);
        // solve Fredholm integral equation by Simpson 3 by 8 rule
        SundayWork::Vector vecXSimpson_3by8 = func(SundayWork::ECubatureRules::Simpson_3by8, step);

        // For excel table
        printDefaultFuncForExcelTable(step);

        solvingAccuracy(std::move(vecXTrapezoidal), step, file);
        solvingAccuracy(std::move(vecXSimpson), step, file);
        solvingAccuracy(std::move(vecXSimpson_3by8), step, file);
        cout << endl;
    }
}


int main_lab2()
{
    cout << endl << setw(12) << "START LAB #2" << endl << endl;

    fstream fileLab2(SundayWork::FIE_VAR3::filenameLab2, fstream::out | fstream::trunc);
    assert(fileLab2.is_open() && "fileLab2 isn't open");

    // template func for successive solving Fredholm integral equation of the second kind (by approximation method)
    auto approximationMethod = std::bind(SundayWork::SuccessiveApproximationMethodFredholm,
                              SundayWork::FIE_VAR3::startT
                              , SundayWork::FIE_VAR3::endT
                              , SundayWork::FIE_VAR3::kernelFunc
                              , SundayWork::FIE_VAR3::rightFunc
                              , _1  // method
                              , _2); // step
    solveApproximationMethod(approximationMethod, fileLab2);


    return 0;
}

#endif // MAIN_LAB2_HPP
