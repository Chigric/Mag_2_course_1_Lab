#include <cassert>
#include <map>
#include <functional>
#include <numeric>

#include "lab3.h"
#include "Output.hpp"

namespace SundayWork {

// Solving coefficients for solution Volterra integral equation
Vector coefsForVolterraIntegralEquation(ECubatureRules cubatureRule, std::size_t amountPoints)
{
    Vector coefs(0.L, amountPoints);
    switch (cubatureRule) {
    case ECubatureRules::Trapezoidal:
        for (std::size_t i = 0; i < amountPoints-1; i++) {
            coefs[i+0] += 0.5L;
            coefs[i+1] += 0.5L;
        }
        break;
    case ECubatureRules::Simpson:
        for (std::size_t i = 0; i < amountPoints-2; i++) {
            coefs[i+0] += 1.L/6;
            coefs[i+1] += 4.L/6;
            coefs[i+2] += 1.L/6;
        }
        break;
    case ECubatureRules::Simpson_3by8:
        for (std::size_t i = 0; i < amountPoints-3; i++) {
            coefs[i+0] += 3.L/8;
            coefs[i+1] += 9.L/8;
            coefs[i+2] += 9.L/8;
            coefs[i+3] += 3.L/8;
        }
        break;
    default:
        assert(false && "I cann't to work with this method");
        break;
    }

    return std::move(coefs);
}

// Successive approximation method (solve Volterra integral equation of the second kind)
Vector successiveApproximationMethodVolterra(MaxDouble startIntegral
        , MaxDouble endIntegral
        , SpecFunc2Arg kernelFunc
        , SpecFunc rightFunc
        , ECubatureRules cubatureRule
        , std::size_t amountPoints
        )
{
    using namespace std;

    Vector nodes(amountPoints);
    MaxDouble step = (endIntegral - startIntegral) / (amountPoints-1);
    auto nodeI = [&startIntegral, &step](size_t i) -> MaxDouble {
        return startIntegral+step*i;
    };
    Vector coefs = SundayWork::coefsForVolterraIntegralEquation(cubatureRule, amountPoints);

    nodes[0] = rightFunc(startIntegral);
    for (size_t i = 1; i < amountPoints; i++) {
        MaxDouble curNode = nodeI(i);
        MaxDouble sunEquation = 0.L;
        for (size_t j = 0; j < i; j++) {
            MaxDouble curSubNode = nodeI(j);
            sunEquation += coefs[j] * kernelFunc(curNode, curSubNode) * nodes[j];
        }
        nodes[i] += 1/(1 - step*coefs[0]*kernelFunc(curNode, curNode))
                * (rightFunc(curNode) + step*sunEquation);
    }

    return nodes;
}

};
