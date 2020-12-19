#ifndef LAB2_H
#define LAB2_H

#include <valarray>
#include <fstream>
#include <functional>


namespace SundayWork {

using MaxDouble = long double;
using Vector = std::valarray<MaxDouble>;
using DoubleVector = std::valarray<std::valarray<MaxDouble> >;

using SpecFunc = std::function<MaxDouble(MaxDouble)>;

// Gauss method for square Matrix (or Gaussian elimination)
//template <typename Vector, typename doubleVector>


Vector gaussianElimination(const DoubleVector& cVecA, const Vector& cVecY);
//std::valarray<long double>&& gaussianElimination(const std::valarray<std::valarray<long double> >& cVecA, const std::valarray<long double>& cVecY);

namespace CubatureRules {
    MaxDouble Trapezoidal(MaxDouble a, MaxDouble b, SpecFunc func);
    MaxDouble Simpson(MaxDouble a, MaxDouble b, SpecFunc func);
    MaxDouble Simpson_3by8(MaxDouble a, MaxDouble b, SpecFunc func); // Simpson's 3/8
}
}

#endif // LAB2_H
