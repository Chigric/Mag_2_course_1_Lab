#include <iostream>
#include <fstream>
#include <cassert>
#include <valarray>
#include <functional>

#include "lab1.h"

using namespace std;
using namespace std::placeholders;

namespace SundayWork {
namespace Var3 {

double startX = 1;
double startY = 2;
double endX = 2;
auto func = [](long double _x, long double _y) -> long double {
    //assert(_y == 0 && "arg y is division by 0");
    if (_y == 0.L) throw std::invalid_argument("arg y is division by 0");
    return (1-_x*_x)/(_x*_y);
};

}
}

const string filenameLab1 = "output1.out";


template<typename Func>
void solveEulerMethod(const string& annotation, fstream& fileLab1,
                      Func& mathMethod)
{
    // step = 0.01 && 0.001
    long double steps[] = {0.01L, 0.001L};
    for (auto step : steps) {
        cout << annotation << step << endl;
        fileLab1 << annotation << step << endl;
        mathMethod(step);
        // Cool job boy (pretty output && kostil')
        fileLab1.open(filenameLab1, fstream::in | fstream::app);
        cout        << endl << endl;
        fileLab1    << endl << endl;
    }

    cout        << "|---------------- END MATH METHOD ----------------|"
                << endl << endl;
    fileLab1    << "|---------------- END MATH METHOD ----------------|"
                << endl << endl;
}

int main(int argc, char** argv)
{
    cout << endl;

    fstream fileLab1(filenameLab1, fstream::out | fstream::trunc);
    assert(fileLab1.is_open() && "fileLab1 isn't open");

    //  // Euler method
    auto eulerMethod_Var3 = std::bind(SundayWork::eulerMethod,
                                     std::ref(fileLab1),
                                     SundayWork::Var3::startX,
                                     SundayWork::Var3::startY,
                                     SundayWork::Var3::endX,
                                     _1,    // step
                                     SundayWork::Var3::func);
    // step = 0.01 && 0.001
    solveEulerMethod("Euler method step=", fileLab1, eulerMethod_Var3);

    //  // Modified Euler method
    auto modifiedEulerMethod_Var3 = std::bind(SundayWork::modifiedEulerMethod,
                                     std::ref(fileLab1),
                                     SundayWork::Var3::startX,
                                     SundayWork::Var3::startY,
                                     SundayWork::Var3::endX,
                                     _1,    // step
                                     SundayWork::Var3::func);

    // step = 0.01 && 0.001
    solveEulerMethod("Modified euler method step=", fileLab1, modifiedEulerMethod_Var3);

    //  // Runge-Kutta fourth-order method (RK4)
    auto RK4Method_Var3 = std::bind(SundayWork::RK4Method,
                                     std::ref(fileLab1),
                                     SundayWork::Var3::startX,
                                     SundayWork::Var3::startY,
                                     SundayWork::Var3::endX,
                                     _1,    // step
                                     SundayWork::Var3::func);

    // step = 0.01 && 0.001
    solveEulerMethod("Runge-Kutta fourth-order method step=", fileLab1, RK4Method_Var3);

    cout << endl;
    return 0;
}
