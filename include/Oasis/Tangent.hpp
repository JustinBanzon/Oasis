//
// Created by banzoj on 10/1/2024.
//

#ifndef TANGENT_HPP
#define TANGENT_HPP

#include "BinaryExpression.hpp"
#include "UnaryExpression.hpp"
#include "Real.hpp"

namespace Oasis {
template <typename OperandT>
class Tangent final : public UnaryExpression<Tangent, OperandT> {
public:
    Tangent() = default;
    //cos(x) operand = x
    Tangent(const Tangent& other)
        : UnaryExpression<Tangent, OperandT>(other)
    {
    }

    explicit Tangent(const OperandT& operand)
        : UnaryExpression<Tangent, OperandT>(operand)
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
        return Tangent<Expression> {
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
        return Tangent<Expression> {
            //
            *operandDerivative
        }
        .Simplify();
    }

    IMPL_SPECIALIZE_UNARYEXPR(Tangent, OperandT)

    EXPRESSION_TYPE(Tangent)
    EXPRESSION_CATEGORY(UnExp)
    };
}
#endif //TANGENT_HPP
