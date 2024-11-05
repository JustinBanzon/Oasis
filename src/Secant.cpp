//
// Created by banzoj on 10/1/2024.
//

#include "Oasis/Add.hpp"
#include "Oasis/Cosine.hpp"
#include "Oasis/Exponent.hpp"
#include "Oasis/Imaginary.hpp"
#include "Oasis/Integral.hpp"
#include "Oasis/Negate.hpp"
#include "Oasis/Matrix.hpp"
#include "Oasis/Divide.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Pi.hpp"
#include "Oasis/Sine.hpp"
#include "Oasis/Secant.hpp"
#include "Oasis/Undefined.hpp"

#define EPSILON 10E-6

namespace Oasis {
    auto Secant<Expression>::Simplify() const -> std::unique_ptr<Expression>
    {
        //    std::cout<<"Cosine Simplify"<<std::endl;
        auto simplifiedOperand = op ? op->Simplify() : nullptr;

        if (auto PiCase = Pi::Specialize(*simplifiedOperand); PiCase != nullptr) {
            return std::make_unique<Real>(1);
        }
        if (auto RealCase = Real::Specialize(*simplifiedOperand); RealCase != nullptr) {
            auto val = cos(RealCase->GetValue());
            if (abs(val) < EPSILON) {
             return std::make_unique<Undefined>(Undefined());
            }
            return std::make_unique<Real>(1/val);
        }
        if (auto MulPiCase = Multiply<Pi,Real>::Specialize(*simplifiedOperand); MulPiCase != nullptr) {
            const Real& multiple = MulPiCase->GetLeastSigOp();
            auto val = cos(Pi::GetValue()*multiple.GetValue());
            if (abs(val) < EPSILON) {}
            return std::make_unique<Real>(1/val);
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
        return std::make_unique<Real>(-128);
    }


    auto Secant<Expression>::Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression>
    {
        // ToDo: implement Secant derivative
        // d/dx(cos(f(x))) = sin(f(x))*d/dx(f(x))
        return Multiply<Expression>{Divide{Sine(this->GetOperand()),Exponent(Cosine(this->GetOperand()),Real(2))}/*-sin(x)*/,*this->GetOperand().Differentiate(differentiationVariable)/*d/dx(x)*/}.Generalize();
    }


}