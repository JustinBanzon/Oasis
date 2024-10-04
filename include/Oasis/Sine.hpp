//
// Created by banzoj on 9/27/2024.
//

#ifndef SINE_HPP
#define SINE_HPP
#include "BinaryExpression.hpp"
#include "UnaryExpression.hpp"
#include "Real.hpp"

namespace Oasis {
template <typename OperandT>
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


    [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> override;

    auto Simplify(tf::Subflow& subflow) const -> std::unique_ptr<Expression> override
    {
        return Multiply {
            Real { -1.0 },
            this->GetOperand()
        }
        .Simplify(subflow);
    }

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
