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
#include "Oasis/Sine.hpp"
#include "Oasis/Cosine.hpp"
#include "Oasis/Pi.hpp"
#include "Oasis/Variable.hpp"

#include <functional>
#include <iostream>

#define EPSILON 1e-6
//sin(0) -> 0
TEST_CASE("Sine Zero","[Sin]")
{
    const Oasis::Sine sineZero {
        Oasis::Real { 0 }
    };
    const auto simplifiedZero = sineZero.Simplify();
    const Oasis::Real expected {0} ;
    REQUIRE(simplifiedZero->Equals(expected));
}
//sin(<pi>/2) -> 1
TEST_CASE("Sine 1/2 Pi","[Sin]")
{
    const Oasis::Sine sineHalfPiMul {
        Oasis::Multiply{ Oasis::Real{0.5},Oasis::Pi{}}
    };
    const auto simplified = sineHalfPiMul.Simplify();
    const Oasis::Real expected {1} ;
    REQUIRE(simplified->Equals(expected));
}
//Sine of a unit fraction of pi tests
TEST_CASE("Sine Pi/2","[Sin]")
{
    const Oasis::Sine sineHalfPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{2}}
    };
    const auto simplified = sineHalfPiDiv.Simplify();
    const Oasis::Real expected {1} ;
    REQUIRE(simplified->Equals(expected));
}
TEST_CASE("Sine Pi/3","[Sin]")
{
    std::cout<<"Testing sin(Pi/3)"<<std::endl;
    const Oasis::Sine sineQuarterPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{3}}
    };
    const auto simplified = sineQuarterPiDiv.Simplify();
    const Oasis::Real expected {(std::sqrt(3)/2)} ;
    REQUIRE(simplified->Equals(expected));
}
TEST_CASE("Sine Pi/4","[Sin]")
{
    std::cout<<"Testing sin(Pi/4)"<<std::endl;
    const Oasis::Sine sinThirdPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{4}}
    };
    const auto simplified = sinThirdPiDiv.Simplify();
    const Oasis::Real expected {(std::sqrt(2)/2)} ;
    REQUIRE(simplified->Equals(expected));
}
TEST_CASE("Sine Pi/6","[Sin]")
{
    std::cout<<"Testing sin(Pi/6)"<<std::endl;
    const Oasis::Sine sinSixthPiDiv {
        Oasis::Divide{ Oasis::Pi{},Oasis::Real{6}}
    };
    const auto simplified = sinSixthPiDiv.Simplify();
    auto simplified_real = Oasis::Real::Specialize(*simplified);
    std::cout <<"sine returned value "<< simplified_real->GetValue() <<std::endl;
    REQUIRE_THAT(simplified_real->GetValue(), Catch::Matchers::WithinAbs(0.5, EPSILON));
}
//sin(<pi>) -> 0
TEST_CASE("Sine Pi","[Sin]")
{
    const Oasis::Sine sinePi {
        Oasis::Pi{}
    };
    const auto simplified = sinePi.Simplify();
    const Oasis::Real expected {0} ;
    REQUIRE(simplified->Equals(expected));
}
//sin(3*<pi>/2) -> -1
TEST_CASE("Sine 3/2 Pi","[Sin]")
{
    const Oasis::Sine sineThreeHalvesPiMul {
        Oasis::Multiply{ Oasis::Real{1.5},Oasis::Pi{}}
    };
    const auto simplified = sineThreeHalvesPiMul.Simplify();
    const Oasis::Real expected {-1} ;
    REQUIRE(simplified->Equals(expected));
}

TEST_CASE("Sine 3Pi/2","[Sin]")
{
    //Testing sin(3Pi/2) with division
    const Oasis::Sine sineThreeHalvesPiMulDiv {
         Oasis::Divide{ Oasis::Multiply{ Oasis::Real{3},Oasis::Pi{}},Oasis::Real{2}}
    };
    const auto simplified = sineThreeHalvesPiMulDiv.Simplify();
    const Oasis::Real expected {-1} ;
    REQUIRE(simplified->Equals(expected));
}
TEST_CASE("Sine 3Pi/4","[Sin]")
{
    //Testing sin(3Pi/4)
    const Oasis::Sine sineThreeHalvesPiMulDiv {
        Oasis::Divide{ Oasis::Multiply{ Oasis::Real{3},Oasis::Pi{}},Oasis::Real{4}}
    };
    const auto simplified = sineThreeHalvesPiMulDiv.Simplify();
    const Oasis::Real expected {(std::sqrt(2)/2)} ;
    REQUIRE(simplified->Equals(expected));
}
TEST_CASE("Simple Derivative","[Sin]") {
    //Testing derivative of sin(x)
    const Oasis::Sine func{
        Oasis::Variable{"x"}
    };
    const auto derivative = func.Differentiate(Oasis::Variable{"x"});
    const Oasis::Cosine expected {Oasis::Variable{"x"}};
    REQUIRE(derivative->Equals(expected));
}
TEST_CASE("Intermediate Derivative","[Sin]") {
    //Testing derivative of sin(x^2)
    const Oasis::Sine func{
        Oasis::Exponent{Oasis::Variable{"x"},Oasis::Real{2}}
    };
    //d/dx sin(x)
    const auto derivative = func.Differentiate(Oasis::Variable{"x"});
    //should simplify to cos(x)
    const Oasis::Multiply expected {Oasis::Cosine{Oasis::Exponent{Oasis::Variable{"x"},Oasis::Real{2}}},Oasis::Multiply{Oasis::Variable{"x"},Oasis::Real{2}}};
    REQUIRE(derivative->Equals(expected));
}