#ifndef LAB3_H
#define LAB3_H

#include "lab2.h"

namespace SundayWork {

// Solving coefficients for solution Volterra integral equation
Vector coefsForVolterraIntegralEquation(ECubatureRules rule, std::size_t amountPoints);

// Successive approximation method (solve Volterra integral equation of the second kind)
Vector successiveApproximationMethodVolterra(MaxDouble startIntegral
        , MaxDouble endIntegral
        , SpecFunc2Arg kernelFunc
        , SpecFunc rightFunc
        , ECubatureRules cubatureRule
        , std::size_t amountPoints
        );

}

#endif // LAB3_H
