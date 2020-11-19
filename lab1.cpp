#include "lab1.h"
#include "Output.hpp"

using namespace std;

namespace SundayWork {

namespace  {
// init array for X_n
template<typename TArray, typename Type>
void initArrX(TArray& arrX, const Type startX, const Type step)
{
    for (size_t i = 0; i < arrX.size(); i++)
        arrX[i] = startX + step*i;
}
}

void eulerMethod(fstream& fileLab1,
                 double startX, double startY, double endX, double step,
                 std::function<long double(long double, long double)> func) {
    size_t maxSize = ((endX - startX) / step) + 1;
    std::valarray<long double> arrX(maxSize);
    std::valarray<long double> arrY(maxSize);

    // init array for X_n
    initArrX(arrX, startX, step);

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

void modifiedEulerMethod(fstream& fileLab1,
                         double startX, double startY, double endX, double step,
                         std::function<long double(long double, long double)> func) {
    size_t maxSize = ((endX - startX) / step) + 1;
    std::valarray<long double> arrX(maxSize);
    std::valarray<long double> arrY(maxSize);

    // init array for X_n
    initArrX(arrX, startX, step);

    // init array for Y_n
    arrY[0] = startY;
    auto iterY = begin(arrY), iterX = begin(arrX);
    while (++iterY != end(arrY) && ++iterX) {
        auto prevY = std::prev(iterY);
        auto prevX = std::prev(iterX);
        long double pseudoY = (*prevY) + step * func((*prevX), *prevY);
        (*iterY) = (*prevY) + (step/2) *
                ( func((*prevX), *prevY) + func((*iterX), pseudoY) );
    }

    // Output to console && file
    output2File(fileLab1, arrX, arrY);
}

void RK4Method(std::fstream& fileLab1,
               double startX, double startY, double endX, double step,
               std::function<long double(long double, long double)> func)
{
    size_t maxSize = ((endX - startX) / step) + 1;
    std::valarray<long double> arrX(maxSize);
    std::valarray<long double> arrY(maxSize);

    // init array for X_n
    initArrX(arrX, startX, step);

    // init array for Y_n
    arrY[0] = startY;
    auto iterY = begin(arrY), iterX = begin(arrX);
    while (++iterY != end(arrY) && ++iterX) {
        auto prevY = std::prev(iterY);
        auto prevX = std::prev(iterX);
        long double k_1 = func((*prevX), (*prevY));
        long double k_2 = func( (*prevX) + step/2,
                                (*prevY)  + (step * k_1 / 2) );
        long double k_3 = func( (*prevX) + step/2,
                                (*prevY)  + (step * k_2 / 2) );
        long double k_4 = func( (*prevX) + step,
                                (*prevY)  + (step * k_3) );
        (*iterY) = (*prevY) + (step/6) * ( k_1 + 2*k_2 + 2*k_3 + k_4 );
    }

    // Output to console && file
    output2File(fileLab1, arrX, arrY);
}
}
