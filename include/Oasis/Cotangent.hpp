//
// Created by banzoj on 10/1/2024.
//

#ifndef COTANGENT_HPP
#define COTANGENT_HPP

#include "BinaryExpression.hpp"
#include "UnaryExpression.hpp"
#include "Real.hpp"

namespace Oasis {
    template <IExpression OperandT>
    class Cotangent;

    /// @cond
    template <>
    class Cotangent<Expression> : public UnaryExpression<Cotangent, Expression> {
    public:
        //    using UnaryExpression::UnaryExpression;

        Cotangent() = default;
        Cotangent(const Cotangent<Expression>& other) = default;

        Cotangent(const Expression& Operand);

        [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> final;

        [[nodiscard]] auto Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression> final;
        [[nodiscard]] auto Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression> final;

        DECL_SPECIALIZE(Cotangent)

        EXPRESSION_TYPE(Cotangent)
        EXPRESSION_CATEGORY(UnExp)
    };
    /// @endcond

    /**
     * The Cotangent expression calculates the Cotangent value of the operand.
     *
     * @tparam OperandT The type of the expression to add be added to.
     */
    template <IExpression OperandT = Expression>
    class Cotangent : public UnaryExpression<Cotangent, OperandT> {
    public:
        Cotangent() = default;
        Cotangent(const Cotangent<OperandT>& other)
            : UnaryExpression<Oasis::Cotangent, OperandT>(other)
        {
        }

        explicit Cotangent(const OperandT& operand)
            : UnaryExpression<Oasis::Cotangent, OperandT>(operand)
        {
        }

        IMPL_SPECIALIZE_UNARYEXPR(Cotangent, OperandT)

        auto operator=(const Cotangent& other) -> Cotangent& = default;

        EXPRESSION_TYPE(Cotangent)
        EXPRESSION_CATEGORY(0)
    };
}
#endif //COTANGENT_HPP
