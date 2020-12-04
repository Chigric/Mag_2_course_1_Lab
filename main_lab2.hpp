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



    return 0;
}

#endif // MAIN_LAB2_HPP
