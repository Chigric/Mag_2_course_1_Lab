#ifndef MAIN_LAB3_HPP
#define MAIN_LAB3_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <valarray>
#include <functional>
#include <cmath>

#include "lab3.h"
#include "Output.hpp"

# define M_PIl          3.141592653589793238462643383279502884L /* pi */

using namespace std;
using namespace std::placeholders;

namespace SundayWork {
// Volterra integral equation
namespace VIE_VAR3 {
using MyTypeAccuracy = long double;
// Output file
const string filenameLab3 = "output3.out";
const string filenameLab3ForExcel = "output3ForExcel.out";
// Equation
/// u(x) - /int_startT^endT(kernelFunc(x,t)*u(t)) = rightFunc(x) <=>
/// <=> u(x) = answerFunc(x)
double startT = 0;
double endT = 1;
auto kernelFunc = [](MyTypeAccuracy x, MyTypeAccuracy t) -> MyTypeAccuracy {
    return std::exp(-(x - t));
};
auto rightFunc = [](MyTypeAccuracy x) -> MyTypeAccuracy {
    return std::exp(-x);
};
// answer func (for checking answers)
auto answerFunc = [](MyTypeAccuracy x) -> MyTypeAccuracy {
    return 1;
};
}
}


void solvingAccuracy3(SundayWork::Vector&& numVec, SundayWork::MaxDouble qualStep, std::fstream& file)
{
    using namespace SundayWork;
    using namespace SundayWork::VIE_VAR3;
    MaxDouble stepX = (endT - startT) / (qualStep-1);
    Vector answerVec(qualStep);
    Vector accuracyVec(qualStep);

    int i = 0;
    for (MaxDouble x = startT; x <= endT; x += stepX, i++) {
        answerVec[i] = answerFunc(x);
        accuracyVec[i] = std::abs(answerVec[i] - numVec[i]);
    }
    // print vectors to consol && file
    SundayWork::output2FileOneVec(file, numVec, 5, "X_i");
    file.open(filenameLab3, fstream::in | fstream::app);
    SundayWork::output2FileOneVec(file, answerVec, 5, "answer");
    file.open(filenameLab3, fstream::in | fstream::app);
    SundayWork::output2FileOneVec(file, accuracyVec, 5, "R_i");

    file.open(filenameLab3, fstream::in | fstream::app);
    assert(file.is_open() && "fileLab2 isn't open");
    cout        << "|---------------- END MATH METHOD ----------------|"
                << std::endl << std::endl
                << "Max accuracy " << accuracyVec.max()
                << std::endl << std::endl;
    file        << "|---------------- END MATH METHOD ----------------|"
                << std::endl << std::endl
                << "Max accuracy " << accuracyVec.max()
                << std::endl << std::endl;

    // for excel table
    fstream file33333(filenameLab3ForExcel, fstream::in | fstream::app);
    SundayWork::output2ExcelTable(file33333, numVec, 5, "X_i");
}

void printDefaultFuncForExcelTable3(SundayWork::MaxDouble qualStep)
{
    using namespace SundayWork::VIE_VAR3;
    SundayWork::MaxDouble stepX = (endT - startT) / qualStep;
    SundayWork::Vector answerVec(qualStep+1);

    int i = 0;
    for (auto x = startT; x < endT; x += stepX, i++)
        answerVec[i] = answerFunc(x);

    fstream file33333(filenameLab3ForExcel, fstream::in | fstream::app);
    SundayWork::output2ExcelTable(file33333, answerVec, 5, "answer");
}

template <typename Func>
void solveApproximationMethod3(Func func, std::fstream& file)
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
        printDefaultFuncForExcelTable3(step);

        solvingAccuracy3(std::move(vecXTrapezoidal), step, file);
        solvingAccuracy3(std::move(vecXSimpson), step, file);
        solvingAccuracy3(std::move(vecXSimpson_3by8), step, file);
        cout << endl;
    }
}

int main_lab3()
{
    cout << endl << setw(12) << "START LAB #3" << endl << endl;

    fstream fileLab3(SundayWork::VIE_VAR3::filenameLab3, fstream::out | fstream::trunc);
    assert(fileLab3.is_open() && "fileLab3 isn't open");

    // template func for successive solving Fredholm integral equation of the second kind (by approximation method)
    auto approximationMethod = std::bind(SundayWork::successiveApproximationMethodVolterra,
                              SundayWork::VIE_VAR3::startT
                              , SundayWork::VIE_VAR3::endT
                              , SundayWork::VIE_VAR3::kernelFunc
                              , SundayWork::VIE_VAR3::rightFunc
                              , _1  // method
                              , _2); // step
    solveApproximationMethod3(approximationMethod, fileLab3);

    return 0;
}

#endif // MAIN_LAB3_HPP
