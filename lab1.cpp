#include "lab1.h"
#include "Output.hpp"

using namespace std;

namespace SundayWork {
void eulerMethod(fstream& fileLab1, double startX, double startY, double endX, double step,
                 std::function<long double(double, double)> func) {
    size_t maxSize = ((endX - startX) / step) + 1;
    std::valarray<double> arrX(maxSize);
    std::valarray<double> arrY(maxSize);

    // init array for X_n
    for (size_t i = 0; i < arrX.size(); i++)
        arrX[i] = startX + step*i;

    // init array for Y_n
    arrY[0] = startY;
    auto iterY = begin(arrY), iterX = begin(arrX);
    while (++iterY != end(arrY)) {
        auto prevY = std::prev(iterY);
        (*iterY) = (*prevY) + step * func((*iterX++), *prevY);
    }

    // Output to console && file
    output2File(fileLab1, arrX, arrY);
}
}
