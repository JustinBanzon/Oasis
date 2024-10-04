//
// Created by banzoj on 10/1/2024.
//

#include "Oasis/Add.hpp"
#include "Oasis/Exponent.hpp"
#include "Oasis/Imaginary.hpp"
#include "Oasis/Integral.hpp"
#include "Oasis/Log.hpp"
#include "Oasis/Matrix.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Pi.hpp"
#include "Oasis/Cosine.hpp"

#define EPSILON 10E-6

namespace Oasis {
auto Cosine<Expression>::Simplify() const -> std::unique_ptr<Expression>
{
    //if operand exists, then simplify it otherwise set to null
    auto simplifiedOper = HasOperand() ? this->GetOperand().Simplify() : nullptr; ;
    //Create a new Cosine instance
    Cosine simplifiedCosine {*simplifiedOper};
    //for a simplified operand x:
    //If x is a real, calculate sin(x)
    if (auto realCase = Cosine<Real>::Specialize(simplifiedCosine); realCase != nullptr) {
        const Real& oper = realCase->GetOperand();

        return std::make_unique<Real>(cos(oper.GetValue()));
    }
    //If x is pi, return -1
    if (auto piCase = Pi::Specialize(*simplifiedOper); piCase != nullptr) {
        return std::make_unique<Real>(-1);
    }
    //If x is a real multiple of pi, return cos(n*pi)
    if (auto piCase = Multiply<Real, Pi>::Specialize(*simplifiedOper); piCase != nullptr) {
        const Real& oper1 = piCase->GetMostSigOp();
        const double pi = Pi::GetValue();
        return std::make_unique<Real>(cos(oper1.GetValue()*pi));
    }

    //If the result is zero, return zero

    //default case
    return simplifiedCosine.Copy();
}





}