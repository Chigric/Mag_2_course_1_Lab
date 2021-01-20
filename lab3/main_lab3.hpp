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
double endT = M_PIl/3;
auto kernelFunc = [](MyTypeAccuracy x, MyTypeAccuracy t) -> MyTypeAccuracy {
    return 2*std::exp(x - t);
};
auto rightFunc = [](MyTypeAccuracy x) -> MyTypeAccuracy {
    return std::sin(x);
};
// answer func (for checking answers)
auto answerFunc = [](MyTypeAccuracy x) -> MyTypeAccuracy {
    return 0.2L*std::exp(3*x) - 0.2L*std::cos(x) + 0.4L*std::sin(x);
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

    for (int i = 0; i < qualStep; i++) {
        answerVec[i] = answerFunc(startT + (stepX*i));
        accuracyVec[i] = std::abs(answerVec[i] - numVec[i]);
    }
    // print vectors to consol && file
    SundayWork::output2FileOneVec(file, numVec, 5, "X_i");
    file.open(filenameLab3, fstream::in | fstream::app);
    SundayWork::output2FileOneVec(file, answerVec, 5, "answer");
    file.open(filenameLab3, fstream::in | fstream::app);
    SundayWork::output2FileOneVec(file, accuracyVec, 5, "R_i");

    file.open(filenameLab3, fstream::in | fstream::app);
    assert(file.is_open() && "fileLab3 isn't open");
    cout        << "|---------------- END MATH METHOD ----------------|"
                << std::endl << std::endl
                << "Max accuracy " << accuracyVec.max()
                << std::endl << std::endl;
    file        << "|---------------- END MATH METHOD ----------------|"
                << std::endl << std::endl
                << "Max accuracy " << accuracyVec.max()
                << std::endl << std::endl;
}

void printDefaultFuncForExcelTable3(SundayWork::MaxDouble qualStep
                                    , SundayWork::Vector& trap
                                    , SundayWork::Vector& simpson
                                    , SundayWork::Vector& simpson_3by8)
{
    using namespace SundayWork::VIE_VAR3;
    SundayWork::MaxDouble stepX = (endT - startT) / (qualStep-1);
    SundayWork::Vector answerVec(qualStep);

    // generation answer array
    for (int i = 0; i < qualStep; i++)
        answerVec[i] = answerFunc(startT + (stepX*i));
    // opening file
    fstream fileExcel(filenameLab3ForExcel, fstream::in | fstream::app);
    //SundayWork::output2ExcelTable(fileExcel, answerVec, 5, "answer");
    SundayWork::DoubleOutput out(fileExcel, 5);

    // out array to excel table
    out << "i" << "\tx"
        << "\tАналитическое решение"
        << "\tМетод трапеций"
        << "\tМетод Симпсона"
        << "\tМетод трех восьмых"
        << SundayWork::endl;
    for (int i = 0; i < qualStep; i++) {
        out << i
            << "\t" << (startT + stepX*i)
            << "\t" << answerVec[i]
            << "\t" << trap[i]
            << "\t" << simpson[i]
            << "\t" << simpson_3by8[i];
        out << SundayWork::endl;
    }
    out << SundayWork::endl;
}

template <typename Func>
void solveApproximationMethod3(Func func, std::fstream& file)
{
    long double steps[] = {10, 100};

    for (auto step : steps) {
        // solve Volterra integral equation by Trapezoidal rule
        SundayWork::Vector vecXTrapezoidal = func(SundayWork::ECubatureRules::Trapezoidal, step);
        // solve Volterra integral equation by Simpson rule
        SundayWork::Vector vecXSimpson = func(SundayWork::ECubatureRules::Simpson, step);
        // solve Volterra integral equation by Simpson 3 by 8 rule
        SundayWork::Vector vecXSimpson_3by8 = func(SundayWork::ECubatureRules::Simpson_3by8, step);

        // For excel table
        printDefaultFuncForExcelTable3(step, vecXTrapezoidal, vecXSimpson, vecXSimpson_3by8);

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

    fstream filenameLab3ForExcel(SundayWork::VIE_VAR3::filenameLab3ForExcel, fstream::out | fstream::trunc);
    assert(filenameLab3ForExcel.is_open() && "filenameLab3ForExcel isn't open");

    // template func for successive solving Volterra integral equation of the second kind (by approximation method)
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
