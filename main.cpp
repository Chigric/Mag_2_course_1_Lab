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
double startY = 1;
double endX = 2;
auto func = [](double _x, double _y) -> long double {
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
    double steps[] = {0.01L, 0.001L};
    for (auto step : steps) {
        cout << annotation << step << endl;
        fileLab1 << annotation << step << endl;
        mathMethod(step);
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
    auto eulerMethodVar3 = std::bind(SundayWork::eulerMethod,
                                     std::ref(fileLab1),
                                     SundayWork::Var3::startX,
                                     SundayWork::Var3::startY,
                                     SundayWork::Var3::endX,
                                     _1,    // step
                                     SundayWork::Var3::func);
    // step = 0.01 && 0.001
    solveEulerMethod("Euler method step=", fileLab1, eulerMethodVar3);

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
