//
// Created by banzoj on 10/1/2024.
//

#ifndef COSECANT_HPP
#define COSECANT_HPP

#include "BinaryExpression.hpp"
#include "UnaryExpression.hpp"
#include "Real.hpp"

namespace Oasis {
    template <IExpression OperandT>
    class Cosecant;

    /// @cond
    template <>
    class Cosecant<Expression> : public UnaryExpression<Cosecant, Expression> {
    public:
        //    using UnaryExpression::UnaryExpression;

        Cosecant() = default;
        Cosecant(const Cosecant<Expression>& other) = default;

        Cosecant(const Expression& Operand);

        [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> final;

        [[nodiscard]] auto Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression> final;
        [[nodiscard]] auto Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression> final;

        DECL_SPECIALIZE(Cosecant)

        EXPRESSION_TYPE(Cosecant)
        EXPRESSION_CATEGORY(UnExp)
    };
    /// @endcond

    /**
     * The Cosecant expression calculates the Cosecant value of the operand.
     *
     * @tparam OperandT The type of the expression to add be added to.
     */
    template <IExpression OperandT = Expression>
    class Cosecant : public UnaryExpression<Cosecant, OperandT> {
    public:
        Cosecant() = default;
        Cosecant(const Cosecant<OperandT>& other)
            : UnaryExpression<Oasis::Cosecant, OperandT>(other)
        {
        }

        explicit Cosecant(const OperandT& operand)
            : UnaryExpression<Oasis::Cosecant, OperandT>(operand)
        {
        }

        IMPL_SPECIALIZE_UNARYEXPR(Cosecant, OperandT)

        auto operator=(const Cosecant& other) -> Cosecant& = default;

        EXPRESSION_TYPE(Cosecant)
        EXPRESSION_CATEGORY(0)
    };}
#endif //SECANT_HPP
