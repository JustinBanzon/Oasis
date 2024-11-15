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
#include "Oasis/Negate.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/Sine.hpp"
#include "Oasis/Cosine.hpp"
#include "Oasis/Pi.hpp"
#include "Oasis/Variable.hpp"

#include <functional>
#include <iostream>

#define EPSILON 1e-6
//cos(0) -> 0
TEST_CASE("Cosine Zero","[Cos]")
{
    const Oasis::Cosine sineZero {
        Oasis::Real { 0 }
    };
    const auto simplifiedZero = sineZero.Simplify();
    const Oasis::Real expected {1} ;
    REQUIRE(simplifiedZero->Equals(expected));
}
//cos(<pi>/2) -> 1
TEST_CASE("Cosine 1/2 Pi","[Cos]")
{
    const Oasis::Cosine sineHalfPiMul {
        Oasis::Multiply{ Oasis::Real{0.5},Oasis::Pi{}}
    };
    const auto simplified = sineHalfPiMul.Simplify();
    const auto simplified_real = Oasis::Real::Specialize(*simplified);
    const Oasis::Real expected {0} ;
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(expected.GetValue(), EPSILON));
}
//Cosine of a unit fraction of pi tests
TEST_CASE("Cosine Pi/2","[Cos]")
{
    const Oasis::Cosine sineHalfPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{2}}
    };
    const auto simplified = sineHalfPiDiv.Simplify();
    const auto simplified_real = Oasis::Real::Specialize(*simplified);
    const Oasis::Real expected {0} ;
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(expected.GetValue(), EPSILON));
}
TEST_CASE("Cosine Pi/3","[Cos]")
{
    //"Testing cos(Pi/3)"
    const Oasis::Cosine sineQuarterPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{3}}
    };
    const auto simplified = sineQuarterPiDiv.Simplify();
    const auto simplified_real = Oasis::Real::Specialize(*simplified);
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(0.5, EPSILON));
}
TEST_CASE("Cosine Pi/4","[Cos]")
{
    //"Testing cos(Pi/4)"
    const Oasis::Cosine sinThirdPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{4}}
    };
    const auto simplified = sinThirdPiDiv.Simplify();
    const auto simplified_real = Oasis::Real::Specialize(*simplified);
    const Oasis::Real expected {(std::sqrt(2)/2)} ;
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(expected.GetValue(), EPSILON));
}
TEST_CASE("Cosine Pi/6","[Cos]")
{
    //"Testing cos(Pi/6)"
    const Oasis::Cosine sinSixthPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{6}}
    };
    const auto simplified = sinSixthPiDiv.Simplify();
    const auto simplified_real = Oasis::Real::Specialize(*simplified);
    const Oasis::Real expected {(std::sqrt(3)/2)} ;
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(expected.GetValue(), EPSILON));
}
//cos(<pi>) -> 0
TEST_CASE("Cosine Pi","[Cos]")
{
    const Oasis::Cosine sinePi {
        Oasis::Pi{}
    };
    const auto simplified = sinePi.Simplify();
    const Oasis::Real expected {-1} ;
    REQUIRE(simplified->Equals(expected));
}
//cos(3*<pi>/2) -> -1
TEST_CASE("Cosine 3/2 Pi","[Cos]")
{
    const Oasis::Cosine sineThreeHalvesPiMul {
        Oasis::Multiply{ Oasis::Real{1.5},Oasis::Pi{}}
    };
    const auto simplified = sineThreeHalvesPiMul.Simplify();
    const auto simplified_real = Oasis::Real::Specialize(*simplified);
    const Oasis::Real expected {0} ;
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(expected.GetValue(), EPSILON));
}

TEST_CASE("Cosine 3Pi/2","[Cos]")
{
    //Testing cos(3Pi/2) with division
    const Oasis::Cosine sineThreeHalvesPiMulDiv {
         Oasis::Divide{ Oasis::Multiply{ Oasis::Real{3},Oasis::Pi{}},Oasis::Real{2}}
    };
    const auto simplified = sineThreeHalvesPiMulDiv.Simplify();
    const auto simplified_real = Oasis::Real::Specialize(*simplified);
    const Oasis::Real expected {0} ;
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(expected.GetValue(), EPSILON));
}
TEST_CASE("Cosine 3Pi/4","[Cos]")
{
    //Testing cos(3Pi/4)
    const Oasis::Cosine sineThreeHalvesPiMulDiv {
        Oasis::Divide{ Oasis::Multiply{ Oasis::Real{3},Oasis::Pi{}},Oasis::Real{4}}
    };
    const auto simplified = sineThreeHalvesPiMulDiv.Simplify();
    const auto simplified_real = Oasis::Real::Specialize(*simplified);
    const Oasis::Real expected {(-std::sqrt(2)/2)} ;
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(expected.GetValue(), EPSILON));
}
TEST_CASE("Simple Derivative","[Cos]") {
    //Testing derivative of cos(x)
    const Oasis::Cosine func{
        Oasis::Variable{"x"}
    };
    const auto derivative = func.Differentiate(Oasis::Variable{"x"});
    const Oasis::Negate expected {Oasis::Sine{Oasis::Variable{"x"}}};
    REQUIRE(derivative->Simplify()->Equals(*expected.Simplify()));
}
TEST_CASE("Intermediate Derivative","[Cos]") {
    //Testing derivative of cos(x^2)
    const Oasis::Cosine func{
        Oasis::Exponent{Oasis::Variable{"x"},Oasis::Real{2}}
    };
    //d/dx cos(x)
    const auto derivative = func.Differentiate(Oasis::Variable{"x"});
    //should simplify to cos(x)
    const Oasis::Multiply expected {Oasis::Negate{Oasis::Sine{Oasis::Exponent{Oasis::Variable{"x"},Oasis::Real{2}}}},Oasis::Multiply{Oasis::Variable{"x"},Oasis::Real{2}}};
    REQUIRE(derivative->Equals(expected));
}