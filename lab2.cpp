#include <cassert>

#include "lab2.h"
#include "Output.hpp"

using namespace std;

namespace SundayWork {

// Gauss method for square Matrix (or Gaussian elimination)
//template <typename Vector, typename doubleVector>
Vector gaussianElimination(const doubleVector& cVecA, const Vector& cVecY)
//std::valarray<long double>&& gaussianElimination(const std::valarray<std::valarray<long double> >& cVecA, const std::valarray<long double>& cVecY)
{
    // Matrix isn't square
    assert(cVecA.size() == cVecY.size() && "Matrix isn't square");
    for (auto ptr : cVecA)
        assert(ptr.size() == cVecA.size() && "Matrix isn't square");

    doubleVector vecA = cVecA;
    Vector vecY = cVecY;
    for (size_t i = 0; i < vecA.size(); i++) {
        // swap rows
        if (vecA[i][i] == 0) {
            if (i == vecA.size()-1)
                continue;
            for (size_t otherI = i+1; otherI < vecA.size(); otherI++) {
                if (vecA[otherI][i] != 0) {
                    swap(vecA[i], vecA[otherI]);
                    swap(vecY[i], vecY[otherI]);
                    break;
                }
            }
        }
        // diagonal elements = 1
        if (vecA[i][i] != 1) {
            const long double alignmentBase = vecA[i][i];
            for (auto& ptr : vecA[i])
                ptr /= alignmentBase;
            vecY[i] /= alignmentBase;
        }
        // reset other all elements in column to 0
        for (size_t otherI = 0; otherI < vecA.size(); otherI++) {
            if (otherI == i)
                continue;
            const long double base = vecA[otherI][i];
            for (size_t j = 0; j < vecA[otherI].size(); j++) {
                vecA[otherI][j] -= vecA[i][j] * base;
            }
            vecY[otherI] -= vecY[i] * base;
        }
    }

    return vecY;
}

}
