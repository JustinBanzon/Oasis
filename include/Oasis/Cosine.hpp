//
// Created by banzoj on 10/1/2024.
//

#ifndef COSINE_HPP
#define COSINE_HPP

#include "BinaryExpression.hpp"
#include "UnaryExpression.hpp"
#include "Real.hpp"

namespace Oasis {
template <typename OperandT>
class Cosine final : public UnaryExpression<Cosine, OperandT> {
public:
    Cosine() = default;
    //cos(x) operand = x
    Cosine(const Cosine& other)
        : UnaryExpression<Cosine, OperandT>(other)
    {
    }

    explicit Cosine(const OperandT& operand)
        : UnaryExpression<Cosine, OperandT>(operand)
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
        return Cosine<Expression> {
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
        return Cosine<Expression> {
            //
            *operandDerivative
        }
        .Simplify();
    }

    IMPL_SPECIALIZE_UNARYEXPR(Cosine, OperandT)

    EXPRESSION_TYPE(Cosine)
    EXPRESSION_CATEGORY(UnExp)
    };
}
#endif //COSINE_HPP
