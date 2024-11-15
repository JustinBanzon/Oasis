//
// Created by banzoj on 10/1/2024.
//

#include "Oasis/Add.hpp"
#include "Oasis/Exponent.hpp"
#include "Oasis/Imaginary.hpp"
#include "Oasis/Integral.hpp"
#include "Oasis/Negate.hpp"
#include "Oasis/Matrix.hpp"
#include "Oasis/Divide.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Pi.hpp"
#include "Oasis/Sine.hpp"
#include "Oasis/Cosine.hpp"

#define EPSILON 10E-6

namespace Oasis {
    Cosine<Expression>::Cosine(const Expression &Operand)
        : UnaryExpression(Operand)
    {
    }

    // std::unique_ptr<Expression> Cosine<Expression>::Integrate(const Expression &integrationVariable) const {
    //     return UnaryExpression<Oasis::Cosine>::Integrate(integrationVariable);
    // }
    //
    // auto Cosine<Expression>::Specialize(const Expression &other) -> std::unique_ptr<Cosine<>> {
    // }
    //
    auto Cosine<Expression>::Simplify() const -> std::unique_ptr<Expression>
    {
        //    std::cout<<"Cosine Simplify"<<std::endl;
        auto simplifiedOperand = op ? op->Simplify() : nullptr;

        if (auto PiCase = Pi::Specialize(*simplifiedOperand); PiCase != nullptr) {
            return std::make_unique<Real>(-1);
        }
        if (auto RealCase = Real::Specialize(*simplifiedOperand); RealCase != nullptr) {
            return std::make_unique<Real>(cos(RealCase->GetValue()));
        }
        if (auto MulPiCase = Multiply<Pi,Real>::Specialize(*simplifiedOperand); MulPiCase != nullptr) {
            const Real& multiple = MulPiCase->GetLeastSigOp();
            return std::make_unique<Real>(cos(Pi::GetValue()*multiple.GetValue()));
        }
        if (auto DivPiCase = Divide<Pi,Real>::Specialize(*simplifiedOperand); DivPiCase != nullptr) {
            const Real& divisor = DivPiCase->GetLeastSigOp();
            return std::make_unique<Real>(cos(Pi::GetValue()/divisor.GetValue()));
        }
        if (auto MulDivPiCase = Divide<Multiply<Pi,Real>,Real>::Specialize(*simplifiedOperand); MulDivPiCase != nullptr) {
            const Real& divisor = MulDivPiCase->GetLeastSigOp();
            const Real& multiple = MulDivPiCase->GetMostSigOp().GetLeastSigOp();
            return std::make_unique<Real>(cos(Pi::GetValue()*multiple.GetValue()/divisor.GetValue()));
        }
        return this->Copy();
    }


    auto Cosine<Expression>::Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression>
    {
        // d/dx(cos(f(x))) = sin(f(x))*d/dx(f(x))
        return Multiply<Expression>{Negate(Sine(this->GetOperand()))/*-sin(x)*/,*this->GetOperand().Differentiate(differentiationVariable)/*d/dx(x)*/}.Generalize();
    }
    auto Cosine<Expression>::Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression>
    {
        // TODO: Implement
        //integral(sin(x) dv)= sin(x)*v-integral(v cos(x) dx)
        //integrate(sin(x) dx) = -cos(x)
        if(auto variable = Variable::Specialize(integrationVariable); variable != nullptr) {
            //integrate(sin(x) dx) = -cos(x) + C
            return Negate<Expression>(Sine<Expression>(this->GetOperand())).Generalize();
        }
        Integral<Expression> integral { *(this->Copy()), *(integrationVariable.Copy()) };

        return integral.Copy();
    }

}