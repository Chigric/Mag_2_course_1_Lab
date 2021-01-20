#ifndef LAB2_H
#define LAB2_H

#include <valarray>
#include <fstream>
#include <functional>


namespace SundayWork {
// Some types definition
using MaxDouble = long double;
using Vector = std::valarray<MaxDouble>;
using DoubleVector = std::valarray<std::valarray<MaxDouble> >;

using SpecFunc = std::function<MaxDouble(MaxDouble)>;
using SpecFunc2Arg = std::function<MaxDouble(MaxDouble, MaxDouble)>;

// Gauss method for square Matrix (or Gaussian elimination)
Vector gaussianElimination(const DoubleVector& cVecA, const Vector& cVecY);

namespace CubatureRules {
    // Type of cubature rule
    using TCubatureRule = std::function<MaxDouble(MaxDouble, MaxDouble, SpecFunc)>;

    MaxDouble Trapezoidal(MaxDouble a, MaxDouble b, SpecFunc func);
    MaxDouble Simpson(MaxDouble a, MaxDouble b, SpecFunc func);
    MaxDouble Simpson_3by8(MaxDouble a, MaxDouble b, SpecFunc func); // Simpson's 3/8
}

enum class ECubatureRules : short int
{
    Trapezoidal
    , Simpson
    , Simpson_3by8
};

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

