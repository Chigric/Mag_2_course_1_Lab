#ifndef LAB2_H
#define LAB2_H

#include <valarray>
#include <fstream>
#include <functional>


namespace SundayWork {
// Gauss method for square Matrix (or Gaussian elimination)
//template <typename Vector, typename doubleVector>
using Vector = std::valarray<long double>;
using doubleVector = std::valarray<std::valarray<long double> >;
Vector gaussianElimination(const doubleVector& cVecA, const Vector& cVecY);
//std::valarray<long double>&& gaussianElimination(const std::valarray<std::valarray<long double> >& cVecA, const std::valarray<long double>& cVecY);


}

#endif // LAB2_H
