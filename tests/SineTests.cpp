//
// Created by banzoj on 9/27/2024.
//
#include "catch2/catch_test_macros.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "Oasis/Add.hpp"
#include "Oasis/Exponent.hpp"
#include "Oasis/Imaginary.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/Sine.hpp"
#include "Oasis/Pi.hpp"
#include "Oasis/Variable.hpp"

#include <functional>

//sin(0) -> 0
TEST_CASE("Sine","[Sin]")
{
    Oasis::Sine sineZero {
        Oasis::Real { 0 }
    };
    const auto simplifiedZero = sineZero.Simplify();
    const Oasis::Real expected {0} ;
    REQUIRE(simplifiedZero->Equals(expected));
}
//sin(<pi>/2) -> 1
TEST_CASE("Sine","[Sin]")
{
    Oasis::Sine sineHalfPiMul {
        Oasis::Multiply{ Oasis::Real{0.5},Oasis::Pi{}}
    };
    const auto simplified = sineHalfPiMul.Simplify();
    const Oasis::Real expected {1} ;
    REQUIRE(simplified->Equals(expected));
}
//sin(<pi>) -> 0
TEST_CASE("Sine","[Sin]")
{
    Oasis::Sine sinePi {
        Oasis::Pi{}
    };
    const auto simplified = sinePi.Simplify();
    const Oasis::Real expected {0} ;
    REQUIRE(simplified->Equals(expected));
}
//sin(3*<pi>/2) -> -1
TEST_CASE("Sine","[Sin]")
{
    Oasis::Sine sineThreeHalvesPiMul {
        Oasis::Multiply{ Oasis::Real{1.5},Oasis::Pi{}}
    };
    const auto simplified = sineThreeHalvesPiMul.Simplify();
    const Oasis::Real expected {-1} ;
    REQUIRE(simplified->Equals(expected));
}