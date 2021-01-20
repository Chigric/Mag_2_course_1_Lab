#ifndef LAB2_H
#define LAB2_H

#include <valarray>
#include <fstream>
#include <functional>

#include "cubatureRules.h"


namespace SundayWork {
// Gauss method for square Matrix (or Gaussian elimination)
Vector gaussianElimination(const DoubleVector& cVecA, const Vector& cVecY);

// Successive approximation method (solve Fredholm integral equation of the second kind)
Vector SuccessiveApproximationMethodFredholm(MaxDouble startIntegral
        , MaxDouble endIntegral
        , SpecFunc2Arg kernelFunc
        , SpecFunc rightFunc
        , ECubatureRules cubatureRule
        , std::size_t amountPoints
        );
}

#endif // LAB2_H

