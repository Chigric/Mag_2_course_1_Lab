#ifndef CUBATURE_RULES_H
#define CUBATURE_RULES_H

#include <valarray>
#include <functional>
#include <map>

namespace SundayWork {

// Some types definition
using MaxDouble = long double;
using Vector = std::valarray<MaxDouble>;
using DoubleVector = std::valarray<std::valarray<MaxDouble> >;

using SpecFunc = std::function<MaxDouble(MaxDouble)>;
using SpecFunc2Arg = std::function<MaxDouble(MaxDouble, MaxDouble)>;


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

static std::map<ECubatureRules, int> ruleNumberPoints = {
    {ECubatureRules::Trapezoidal, 2}
    , {ECubatureRules::Simpson, 3}
    , {ECubatureRules::Simpson_3by8, 4}
};


}

#endif // CUBATURE_RULES_H
