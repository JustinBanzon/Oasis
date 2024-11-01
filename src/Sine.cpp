//
// Created by Andrew Nazareth on 10/8/24.
//

#include "Oasis/Sine.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Cosine.hpp"
#include "Oasis/Divide.hpp"
#include "Oasis/Pi.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/Integral.hpp"
#include "Oasis/Variable.hpp"
#include "Oasis/Negate.hpp"

namespace Oasis {
Sine<Expression>::Sine(const Expression& operand)
    : UnaryExpression(operand)
{
}

auto Sine<Expression>::Simplify() const -> std::unique_ptr<Expression>
{
    //    std::cout<<"Sine Simplify"<<std::endl;
    auto simplifiedOperand = op ? op->Simplify() : nullptr;

    if (auto PiCase = Pi::Specialize(*simplifiedOperand); PiCase != nullptr) {
        return std::make_unique<Real>(0);
    }
    if (auto RealCase = Real::Specialize(*simplifiedOperand); RealCase != nullptr) {
        return std::make_unique<Real>(sin(RealCase->GetValue()));
    }
    if (auto MulPiCase = Multiply<Pi,Real>::Specialize(*simplifiedOperand); MulPiCase != nullptr) {
        const Real& multiple = MulPiCase->GetLeastSigOp();
        return std::make_unique<Real>(sin(Pi::GetValue()*multiple.GetValue()));
    }
    if (auto DivPiCase = Divide<Pi,Real>::Specialize(*simplifiedOperand); DivPiCase != nullptr) {
        const Real& divisor = DivPiCase->GetLeastSigOp();
        return std::make_unique<Real>(sin(Pi::GetValue()/divisor.GetValue()));
    }
    if (auto MulDivPiCase = Divide<Multiply<Pi,Real>,Real>::Specialize(*simplifiedOperand); MulDivPiCase != nullptr) {
        const Real& divisor = MulDivPiCase->GetLeastSigOp();
        const Real& multiple = MulDivPiCase->GetMostSigOp().GetLeastSigOp();
        return std::make_unique<Real>(sin(Pi::GetValue()*multiple.GetValue()/divisor.GetValue()));
    }
    return std::make_unique<Real>(-128);
}

auto Sine<Expression>::Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression>
{
    // TODO: Implement
    //integral(sin(x) dv)= sin(x)*v-integral(v cos(x) dx)
    //integrate(sin(x) dx) = -cos(x)
    if(auto variable = Variable::Specialize(integrationVariable); variable != nullptr) {
        //integrate(sin(x) dx) = -cos(x) + C
        return Negate(Cosine(integrationVariable)).Specialize(*variable);
    }
    Integral<Expression> integral { *(this->Copy()), *(integrationVariable.Copy()) };

    return integral.Copy();
}

auto Sine<Expression>::Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression>
{
    // TODO: Implement
    // d/dx sin(f(x)) = cos(f(x))*d/dxf(x)
    return Multiply<Expression>{Cosine(this->GetOperand())/*cos(x)*/,*this->GetOperand().Differentiate(differentiationVariable)/*d/dx(x)*/}.Generalize();
}

}