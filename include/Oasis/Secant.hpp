//
// Created by banzoj on 10/1/2024.
//

#ifndef SECANT_HPP
#define SECANT_HPP

#include "BinaryExpression.hpp"
#include "UnaryExpression.hpp"
#include "Real.hpp"

namespace Oasis {
    template <IExpression OperandT>
    class Secant;

    /// @cond
    template <>
    class Secant<Expression> : public UnaryExpression<Secant, Expression> {
    public:
        //    using UnaryExpression::UnaryExpression;

        Secant() = default;
        Secant(const Secant<Expression>& other) = default;

        Secant(const Expression& Operand);

        [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> final;

        [[nodiscard]] auto Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression> final;
        [[nodiscard]] auto Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression> final;

        DECL_SPECIALIZE(Secant)

        EXPRESSION_TYPE(Secant)
        EXPRESSION_CATEGORY(UnExp)
    };
    /// @endcond

    /**
     * The Secant expression calculates the Secant value of the operand.
     *
     * @tparam OperandT The type of the expression to add be added to.
     */
    template <IExpression OperandT = Expression>
    class Secant : public UnaryExpression<Secant, OperandT> {
    public:
        Secant() = default;
        Secant(const Secant<OperandT>& other)
            : UnaryExpression<Oasis::Secant, OperandT>(other)
        {
        }

        explicit Secant(const OperandT& operand)
            : UnaryExpression<Oasis::Secant, OperandT>(operand)
        {
        }

        IMPL_SPECIALIZE_UNARYEXPR(Secant, OperandT)

        auto operator=(const Secant& other) -> Secant& = default;

        EXPRESSION_TYPE(Secant)
        EXPRESSION_CATEGORY(0)
    };}
#endif //SECANT_HPP
