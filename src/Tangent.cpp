//
// Created by banzoj on 10/1/2024.
//

#include "Oasis/Add.hpp"
#include "Oasis/Exponent.hpp"
#include "Oasis/Imaginary.hpp"
#include "Oasis/Integral.hpp"
#include "Oasis/Log.hpp"
#include "Oasis/Undefined.hpp"
#include "Oasis/Divide.hpp"
#include "Oasis/Matrix.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Pi.hpp"
#include "Oasis/Secant.hpp"
#include "Oasis/Tangent.hpp"

#define EPSILON 10E-6

namespace Oasis {
    Tangent<Expression>::Tangent(const Expression& operand)
    : UnaryExpression(operand)
    {
    }

    auto Tangent<Expression>::Simplify() const -> std::unique_ptr<Expression>
    {
        //    std::cout<<"Cosine Simplify"<<std::endl;
        auto simplifiedOperand = op ? op->Simplify() : nullptr;

        if (auto PiCase = Pi::Specialize(*simplifiedOperand); PiCase != nullptr) {
            return std::make_unique<Real>(0);
        }
        if (auto RealCase = Real::Specialize(*simplifiedOperand); RealCase != nullptr) {
            auto result = tan(RealCase->GetValue());
            try {
                return std::make_unique<Real>(result);
            } catch (...) {
                return std::make_unique<Undefined>(Undefined());
            }
        }
        if (auto MulPiCase = Multiply<Pi,Real>::Specialize(*simplifiedOperand); MulPiCase != nullptr) {
            const Real& multiple = MulPiCase->GetLeastSigOp();
            if(multiple.GetValue()-floor(multiple.GetValue())==0.5 || multiple.GetValue()-floor(multiple.GetValue())==-0.5) {
                return std::make_unique<Undefined>(Undefined());
            }
            return std::make_unique<Real>(tan(Pi::GetValue()*multiple.GetValue()));

        }
        if (auto DivPiCase = Divide<Pi,Real>::Specialize(*simplifiedOperand); DivPiCase != nullptr) {
            const Real& divisor = DivPiCase->GetLeastSigOp();
            if(divisor.GetValue()==2) {
                return std::make_unique<Undefined>(Undefined());
            }
            return std::make_unique<Real>(tan(Pi::GetValue()/divisor.GetValue()));
        }
        if (auto MulDivPiCase = Divide<Multiply<Pi,Real>,Real>::Specialize(*simplifiedOperand); MulDivPiCase != nullptr) {
            const Real& divisor = MulDivPiCase->GetLeastSigOp();
            const Real& multiple = MulDivPiCase->GetMostSigOp().GetLeastSigOp();
            return std::make_unique<Real>(tan(Pi::GetValue()*multiple.GetValue()/divisor.GetValue()));
        }
        return std::make_unique<Real>(-128);

    }

    auto Tangent<Expression>::Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression>
    {
        // TODO: Implement Secant
        // d/dx(tan(f(x))) = sec^2(f(x))*d/dx(f(x))
        return Multiply<Expression>{Add{Exponent(Tangent(this->GetOperand()),Real(2))/*-sin(x)*/,Real(1)},*this->GetOperand().Differentiate(differentiationVariable)/*d/dx(x)*/}.Generalize();
    }
    //tan(x) = sin(x)/cos(x), d/dx(tan(f(x))) = cos^2(f(x))+sin^2(f(x))/cos^2(f(x))*d/dx(f(x)) = sec^2(f(x))*d/dx(f(x))
    auto Tangent<Expression>::Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression>
    {
        // TODO: Implement
        //integral(sin(x) dv)= sin(x)*v-integral(v cos(x) dx)
        //integrate(sin(x) dx) = -cos(x)
        if(auto variable = Variable::Specialize(integrationVariable); variable != nullptr) {
            //integrate(sin(x) dx) = -cos(x) + C
            return Exponent<Expression>(Secant<Expression>(this->GetOperand()),Real(2)).Generalize();
        }
        Integral<Expression> integral { *(this->Copy()), *(integrationVariable.Copy()) };

        return integral.Copy();
    }

}
