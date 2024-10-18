//
// Created by banzoj on 10/1/2024.
//

#ifndef TANGENT_HPP
#define TANGENT_HPP

#include "BinaryExpression.hpp"
#include "UnaryExpression.hpp"
#include "Real.hpp"

namespace Oasis {
    template <IExpression OperandT>
    class Tangent;

    /// @cond
    template <>
    class Tangent<Expression> : public UnaryExpression<Tangent, Expression> {
    public:
        //    using UnaryExpression::UnaryExpression;

        Tangent() = default;
        Tangent(const Tangent<Expression>& other) = default;

        Tangent(const Expression& Operand);

        [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> final;

        [[nodiscard]] auto Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression> final;
        [[nodiscard]] auto Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression> final;

        DECL_SPECIALIZE(Tangent)

        EXPRESSION_TYPE(Tangent)
        EXPRESSION_CATEGORY(UnExp)
    };
    /// @endcond

    /**
     * The Tangent expression calculates the Tangent value of the operand.
     *
     * @tparam OperandT The type of the expression to add be added to.
     */
    template <IExpression OperandT = Expression>
    class Tangent : public UnaryExpression<Tangent, OperandT> {
    public:
        Tangent() = default;
        Tangent(const Tangent<OperandT>& other)
            : UnaryExpression<Oasis::Tangent, OperandT>(other)
        {
        }

        explicit Tangent(const OperandT& operand)
            : UnaryExpression<Oasis::Tangent, OperandT>(operand)
        {
        }

        IMPL_SPECIALIZE_UNARYEXPR(Tangent, OperandT)

        auto operator=(const Tangent& other) -> Tangent& = default;

        EXPRESSION_TYPE(Tangent)
        EXPRESSION_CATEGORY(0)
    };
}
#endif //TANGENT_HPP
