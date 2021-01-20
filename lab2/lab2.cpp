#include <cassert>
#include <map>

#include "lab2.h"
#include "Output.hpp"

namespace SundayWork {

// Gauss method for square Matrix (or Gaussian elimination)
Vector gaussianElimination(const DoubleVector& cVecA, const Vector& cVecY)
{
    // Matrix isn't square
    assert(cVecA.size() == cVecY.size() && "Matrix isn't square");
    for (auto ptr : cVecA)
        assert(ptr.size() == cVecA.size() && "Matrix isn't square");

    DoubleVector vecA = cVecA;
    Vector vecY = cVecY;
    for (std::size_t i = 0; i < vecA.size(); i++) {
        // swap rows
        if (vecA[i][i] == 0) {
            if (i == vecA.size()-1)
                continue;
            for (std::size_t otherI = i+1; otherI < vecA.size(); otherI++) {
                if (vecA[otherI][i] != 0) {
                    std::swap(vecA[i], vecA[otherI]);
                    std::swap(vecY[i], vecY[otherI]);
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
        for (std::size_t otherI = 0; otherI < vecA.size(); otherI++) {
            if (otherI == i)
                continue;
            const long double base = vecA[otherI][i];
            for (std::size_t j = 0; j < vecA[otherI].size(); j++) {
                vecA[otherI][j] -= vecA[i][j] * base;
            }
            vecY[otherI] -= vecY[i] * base;
        }
    }

    return vecY;
}

// Successive approximation method (solve Fredholm integral equation of the second kind)
Vector SuccessiveApproximationMethodFredholm(
        MaxDouble startIntegral
        , MaxDouble endIntegral
        , SpecFunc2Arg kernelFunc
        , SpecFunc rightFunc
        , ECubatureRules cubatureRule
        , std::size_t amountPoints
        )
{
    // Declaration matrixs (fixed)
    Vector vecX(amountPoints);
    // Declaration matrixs (mutable)
    std::size_t numberPoints = ruleNumberPoints[cubatureRule];
    Vector vecY(numberPoints);
    DoubleVector vecA(numberPoints);
    for (auto& ptr : vecA)
        ptr.resize(numberPoints);
    // some defines
    MaxDouble step = (endIntegral-startIntegral)/(amountPoints-1);
    auto pointI = [&startIntegral, &step](size_t i) -> MaxDouble {
        return startIntegral+step*i;
    };

    // init matrixs
    for (std::size_t k = 0; k < amountPoints; k+=2) {
        for (std::size_t i = k, j = k; i < k+numberPoints; i++) {
            switch (cubatureRule) {
            case ECubatureRules::Trapezoidal:
                vecA[i-k][0] = step * 0.5L * (-1) * kernelFunc(pointI(i), pointI(j));
                vecA[i-k][1] = step * 0.5L * (-1) * kernelFunc(pointI(i), pointI(j+1));
                break;
            case ECubatureRules::Simpson:
                vecA[i-k][0] = step * MaxDouble(1)/6 * (-1) * kernelFunc(pointI(i), pointI(j));
                vecA[i-k][1] = step * MaxDouble(4)/6 * (-1) *
                        kernelFunc(pointI(i), (pointI(j+1)-pointI(j))/2);
                vecA[i-k][2] = step * MaxDouble(1)/6 * (-1) * kernelFunc(pointI(i), pointI(j+1));
                break;
            case ECubatureRules::Simpson_3by8:
                vecA[i-k][0] = step * MaxDouble(3)/8 * (-1) * kernelFunc(pointI(i), pointI(j));
                vecA[i-k][1] = step * MaxDouble(3)/8 * (-1) *
                        3 * kernelFunc(pointI(i), (pointI(j+1)-pointI(j))/3);
                vecA[i-k][2] = step * MaxDouble(3)/8 * (-1) *
                        3 * kernelFunc(pointI(i), ((pointI(j+1)-pointI(j))*2)/3);
                vecA[i-k][3] = step * MaxDouble(3)/8 * (-1) * kernelFunc(pointI(i), pointI(j+1));
                break;
            default:
                assert(false && "I cann't to work with this method");
                break;
            }
            vecY[i-k] = rightFunc(pointI(i));
            vecA[i-k][i-k] += 1;
        }
        Vector tmpVecX = gaussianElimination(vecA, vecY);
        // moving "extreme" points
        vecX[k+0] = tmpVecX[0];
        vecX[k+1] = tmpVecX[numberPoints-1];
    }
    return vecX;
}
}
