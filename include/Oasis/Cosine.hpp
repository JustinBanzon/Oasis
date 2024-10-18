//
// Created by banzoj on 10/1/2024.
//

#ifndef COSINE_HPP
#define COSINE_HPP

#include "BinaryExpression.hpp"
#include "UnaryExpression.hpp"
#include "Real.hpp"

namespace Oasis {
    template <IExpression OperandT>
    class Cosine;

    /// @cond
    template <>
    class Cosine<Expression> : public UnaryExpression<Cosine, Expression> {
    public:
        //    using UnaryExpression::UnaryExpression;

        Cosine() = default;
        Cosine(const Cosine<Expression>& other) = default;

        Cosine(const Expression& Operand);

        [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> final;

        [[nodiscard]] auto Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression> final;
        [[nodiscard]] auto Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression> final;

        DECL_SPECIALIZE(Cosine)

        EXPRESSION_TYPE(Cosine)
        EXPRESSION_CATEGORY(UnExp)
    };
    /// @endcond

    /**
     * The Cosine expression calculates the Cosine value of the operand.
     *
     * @tparam OperandT The type of the expression to add be added to.
     */
    template <IExpression OperandT = Expression>
    class Cosine : public UnaryExpression<Cosine, OperandT> {
    public:
        Cosine() = default;
        Cosine(const Cosine<OperandT>& other)
            : UnaryExpression<Oasis::Cosine, OperandT>(other)
        {
        }

        explicit Cosine(const OperandT& operand)
            : UnaryExpression<Oasis::Cosine, OperandT>(operand)
        {
        }

        IMPL_SPECIALIZE_UNARYEXPR(Cosine, OperandT)

        auto operator=(const Cosine& other) -> Cosine& = default;

        EXPRESSION_TYPE(Cosine)
        EXPRESSION_CATEGORY(0)
    };}
#endif //COSINE_HPP
