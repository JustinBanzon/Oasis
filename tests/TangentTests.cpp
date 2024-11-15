//
// Created by banzoj on 9/27/2024.
//
#include "catch2/catch_test_macros.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "Oasis/Add.hpp"
#include "Oasis/Exponent.hpp"
#include "Oasis/Imaginary.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Divide.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/Undefined.hpp"
#include "Oasis/Tangent.hpp"
#include "Oasis/Secant.hpp"
#include "Oasis/Cosine.hpp"
#include "Oasis/Pi.hpp"
#include "Oasis/Variable.hpp"

#include <functional>
#include <iostream>

#define EPSILON 1e-6
//tan(0) -> 0
TEST_CASE("Tangent Zero","[Tan]")
{
    const Oasis::Tangent tangentZero {
        Oasis::Real { 0 }
    };
    const auto simplifiedZero = tangentZero.Simplify();
    const Oasis::Real expected {0} ;
    REQUIRE(simplifiedZero->Equals(expected));
}
//tan(<pi>/2) -> 1
TEST_CASE("Tangent 1/2 Pi","[Tan]")
{
    const Oasis::Tangent tangentHalfPiMul {
        Oasis::Multiply{ Oasis::Real{0.5},Oasis::Pi{}}
    };
    const auto simplified = tangentHalfPiMul.Simplify();
    const Oasis::Undefined expected;
    REQUIRE(simplified->Equals(expected));
}
//Tangent of a unit fraction of pi tests
TEST_CASE("Tangent Pi/2","[Tan]")
{
    const Oasis::Tangent tangentHalfPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{2}}
    };
    const auto simplified = tangentHalfPiDiv.Simplify();
    const Oasis::Real expected {1} ;
    REQUIRE(simplified->Equals(expected));
}
TEST_CASE("Tangent Pi/3","[Tan]")
{
    //Testing tan(Pi/3)
    const Oasis::Tangent tanThirdPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{3}}
    };
    const auto simplified = tanThirdPiDiv.Simplify();
    const auto simplified_real = Oasis::Real::Specialize(*simplified);
    const Oasis::Real expected {std::sqrt(3)} ;
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(expected.GetValue(), EPSILON));
}
TEST_CASE("Tangent Pi/4","[Tan]")
{
    //Testing tan(Pi/4)
    const Oasis::Tangent tanQuarterPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{4}}
    };
    const auto simplified = tanQuarterPiDiv.Simplify();
    const auto simplified_real = Oasis::Real::Specialize(*simplified);
    const Oasis::Real expected {1} ;
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(expected.GetValue(), EPSILON));
}
TEST_CASE("Tangent Pi/6","[Tan]")
{
    //Testing tan(Pi/6)
    const Oasis::Tangent tanSixthPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{6}}
    };
    const auto simplified = tanSixthPiDiv.Simplify();
    const auto simplified_real = Oasis::Real::Specialize(*simplified);
    const Oasis::Real expected {std::sqrt(3)/3} ;
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(expected.GetValue(), EPSILON));
}
//tan(<pi>) -> 0
TEST_CASE("Tangent Pi","[Tan]")
{
    const Oasis::Tangent tangentPi {
        Oasis::Pi{}
    };
    const auto simplified = tangentPi.Simplify();
    const Oasis::Real expected {0} ;
    REQUIRE(simplified->Equals(expected));
}
//tan(3*<pi>/2) -> -1
TEST_CASE("Tangent 3/2 Pi","[Tan]")
{
    const Oasis::Tangent tangentThreeHalvesPiMul {
        Oasis::Multiply{ Oasis::Real{1.5},Oasis::Pi{}}
    };
    const auto simplified = tangentThreeHalvesPiMul.Simplify();
    const Oasis::Undefined expected ;
    REQUIRE(simplified->Equals(expected));
}

TEST_CASE("Tangent 3Pi/2","[Tan]")
{
    //Testing tan(3Pi/2) with division
    const Oasis::Tangent tangentThreeHalvesPiMulDiv {
         Oasis::Divide{ Oasis::Multiply{ Oasis::Real{3},Oasis::Pi{}},Oasis::Real{2}}
    };
    const auto simplified = tangentThreeHalvesPiMulDiv.Simplify();
    const Oasis::Undefined expected ;
    REQUIRE(simplified->Equals(expected));
}
TEST_CASE("Tangent 3Pi/4","[Tan]")
{
    //Testing tan(3Pi/4)
    const Oasis::Tangent tangentThreeHalvesPiMulDiv {
        Oasis::Divide{ Oasis::Multiply{ Oasis::Real{3},Oasis::Pi{}},Oasis::Real{4}}
    };
    const auto simplified = tangentThreeHalvesPiMulDiv.Simplify();
    const Oasis::Real expected {-1} ;
    REQUIRE(simplified->Equals(expected));
}
TEST_CASE("Simple Derivative","[Tan]") {
    //Testing derivative of tan(x)
    const Oasis::Tangent func{
        Oasis::Variable{"x"}
    };
    const auto derivative = func.Differentiate(Oasis::Variable{"x"});
    const Oasis::Exponent<> expected {Oasis::Secant{Oasis::Variable{"x"}},Oasis::Real{2}};
    REQUIRE(derivative->Simplify()->Equals(*expected.Simplify()));
}
TEST_CASE("Intermediate Derivative","[Tan]") {
    //Testing derivative of tan(x^2)
    const Oasis::Tangent func{
        Oasis::Exponent{Oasis::Variable{"x"},Oasis::Real{2}}
    };
    //d/dx tan(x)
    const auto derivative = func.Differentiate(Oasis::Variable{"x"});
    //should simplify to sec^2(x^2)d/dx(x^2)
    const Oasis::Multiply expected {Oasis::Exponent{Oasis::Secant{Oasis::Exponent{Oasis::Variable{"x"},Oasis::Real{2}}},Oasis::Real{2}},Oasis::Multiply{Oasis::Variable{"x"},Oasis::Real{2}}};
    REQUIRE(derivative->Equals(expected));
}