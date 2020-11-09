#ifndef LAB1_H
#define LAB1_H

#include <valarray>
#include <fstream>
#include <functional>


namespace SundayWork {
void eulerMethod(std::fstream& fileLab1,
                 double startX, double startY, double endX, double step,
                 std::function<long double(double, double)> func);

void modifiedEulerMethod(std::fstream& fileLab1,
                         double startX, double startY, double endX, double step,
                         std::function<long double(double, double)> func);
}

#endif // LAB1_H
