//
// Created by banzoj on 9/27/2024.
//

#ifndef SINE_HPP
#define SINE_HPP
#include "BinaryExpression.hpp"
#include "UnaryExpression.hpp"
#include "Real.hpp"

namespace Oasis {
template <IExpression OperandT>
class Sine;

//To do: get the Add-inspired instance to work
///@cond
template<>
class Sine<
    Expression> : public UnaryExpression<Sine,Expression> {
    public:
    using UnaryExpression::UnaryExpression;

    [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> final;
    auto Simplify(tf::Subflow& subflow) const -> std::unique_ptr<Expression> final;

    [[nodiscard]] auto Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression> final;
    [[nodiscard]] auto Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression> final;

    DECL_SPECIALIZE(Sine)

    EXPRESSION_TYPE(Sine)
    EXPRESSION_CATEGORY(UnExp)
};
///@endcond
template <typename OperandT = Expression>
class Sine final : public UnaryExpression<Sine, OperandT> {
public:
    Sine() = default;
    //sin(x) operand = x
    Sine(const Sine& other)
        : UnaryExpression<Sine, OperandT>(other)
    {
    }

    explicit Sine(const OperandT& operand)
        : UnaryExpression<Sine, OperandT>(operand)
    {
    }

    // In case things break
    // [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> override {
    //     return this->Copy();
    //     //if operand exists, then simplify it otherwise set to null
    //     // auto simplifiedOper = this->HasOperand() ? this->GetOperand().Simplify() : nullptr; ;
    //     // //Create a new Sine instance
    //     // Sine simplifiedSine {*simplifiedOper};
    //     // //for a simplified operand x:
    //     // //If x is a real, calculate sin(x)
    //     // if (auto realCase = Sine<Real>::Specialize(simplifiedSine); realCase != nullptr) {
    //     //     const Real& oper = realCase->GetOperand();
    //     //
    //     //     return std::make_unique<Real>(sin(oper.GetValue()));
    //     // }
    //     // //If x is pi, return 0
    //     // if (auto piCase = Pi::Specialize(*simplifiedOper); piCase != nullptr) {
    //     //     return std::make_unique<Real>(0);
    //     // }
    //     // //If x is a real multiple of pi, return sin(n*pi)
    //     // if (auto piCase = Multiply<Real, Pi>::Specialize(*simplifiedOper); piCase != nullptr) {
    //     //     const Real& oper1 = piCase->GetMostSigOp();
    //     //     const double pi = Pi::GetValue();
    //     //     return std::make_unique<Real>(sin(oper1.GetValue()*pi));
    //     // }
    //     // //If the result is zero, return zero
    //     //
    //     // //default case
    //     // return simplifiedSine.Copy();
    // }
    //
    // // IGNORE
    // auto Simplify(tf::Subflow& subflow) const -> std::unique_ptr<Expression> override
    // {
    //     return this->Copy();
    // }

    [[nodiscard]] auto Differentiate(const Expression& var) const -> std::unique_ptr<Expression> override
    {
        const std::unique_ptr<Expression> operandDerivative = this->GetOperand().Differentiate(var);
        return Sine<Expression> {
            //(d/dx) sin(f(x)) -> cos(f(x))*(d/dx)f(x)
            //(d/dx) sin(x) -> cos(x)
            *operandDerivative
        }
        .Simplify();
    }


    [[nodiscard]] auto Integrate(const Expression& integrationVar) const -> std::unique_ptr<Expression> override
    {
        // TODO: Implement
        const std::unique_ptr<Expression> operandDerivative = this->GetOperand().Integrate(integrationVar);
        return Sine<Expression> {
            //
            *operandDerivative
        }
        .Simplify();
    }

    IMPL_SPECIALIZE_UNARYEXPR(Sine, OperandT)

    EXPRESSION_TYPE(Sine)
    EXPRESSION_CATEGORY(UnExp)
    };
}
#endif //SINE_HPP
