#include <iostream>
#include <fstream>
#include <cassert>
#include <valarray>
#include <functional>

#include "lab1.h"

using namespace std;
using namespace std::placeholders;
//using namespace SundayWork;

const string filenameLab1 = "output1.out";


void solveEulerMethod(const string& annotation, fstream& fileLab1,
                      double startX, double startY, double endX,
                      function<long double(double, double)> specFunc,
                      function<void (std::fstream&,
                            double, double, double, double,
                            std::function<long double(double, double)>
                                     )> mathMethod)
{
    auto func = std::bind(mathMethod, std::ref(fileLab1),
                          _1, _2, _3, _4, // startX, startY, endX, step
                          specFunc);
    // step = 0.01 && 0.001
    double steps[] = {0.01L, 0.001L};
    for (auto step : steps) {
        cout << annotation << step << endl;
        fileLab1 << annotation << step << endl;
        func(startX, startY, endX, step);
        // Cool job boy (pretty output && kostil')
        cout        << endl << endl;
        fileLab1    << endl << endl;
        fileLab1.open(filenameLab1, fstream::out);
    }
    cout        << endl;
    fileLab1    << endl;
}

int main()
{
    cout << endl;

    fstream fileLab1(filenameLab1, fstream::out | fstream::trunc);
    assert(fileLab1.is_open() && "fileLab1 isn't open");

    //  // Euler method
    // step = 0.01 && 0.001
    solveEulerMethod("Euler method step=", fileLab1, 1, 1, 2,
                     [](double _x, double _y) -> long double {
        return (1-_x*_x)/(_x*_y);
    },
    SundayWork::eulerMethod);

    /*SundayWork::eulerMethod(fileLab1, 1, 1, 0.01, [](double _x, double _y) -> long double {
        return (1-_x*_x)/(_x*_y);
    });*/

    //  // Modified Euler method
    // step = 0.01
    //fileLab1.open(filenameLab1, fstream::out);
    // step = 0.001
    //fileLab1.open(filenameLab1, fstream::out);

    cout << endl;
    return 0;
}
