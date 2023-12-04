#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Calculator/CalculatorController.h"
#include <sstream>

bool IsEqual(double a, double b)
{
	if (std::isinf(a) && std::isinf(b))
	{
		return true;
	}
	if (std::isnan(a) && std::isnan(b))
	{
		return true;
	}
	return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

SCENARIO("Test calculator")
{
	// добавить тестов в математических операциях
	WHEN("Test create variable")
	{
		Calculator calculator;
		REQUIRE(calculator.CreateVariable("x"));
		REQUIRE(IsEqual(calculator.GetValueOfVariable("x"), NAN));
		REQUIRE(calculator.SetVariableToValue("x", "10"));
		REQUIRE(IsEqual(calculator.GetValueOfVariable("x"), 10.0));
		REQUIRE(!calculator.CreateVariable("1x"));
		REQUIRE(calculator.SetVariableToValue("z", "10"));
		REQUIRE(IsEqual(calculator.GetValueOfVariable("z"), 10));
		WHEN("Test get variables")
		{
			Calculator::Variables vars{
				{ "x", 10 },
				{ "z", 10 }
			};
			REQUIRE(calculator.GetVariables() == vars);
		}
	}

	WHEN("Test calclulator addition")
	{
		Calculator calculator;
		double addition = calculator.CalculateResultOfFunction({ "0.1", "0.2", Operations::Operation::ADDITION });
		REQUIRE(IsEqual(addition, 0.3));
		addition = calculator.CalculateResultOfFunction({ "0.000001", "0.0000002", Operations::Operation::ADDITION });
		REQUIRE(IsEqual(addition, 0.0000012));
		addition = calculator.CalculateResultOfFunction({ "12", "22", Operations::Operation::ADDITION });
		REQUIRE(IsEqual(addition, 34.0));
		addition = calculator.CalculateResultOfFunction({ "1.7976931348623158e+308", "1.7976931348623158e+308", Operations::Operation::ADDITION });
		REQUIRE(IsEqual(addition, NAN));
		addition = calculator.CalculateResultOfFunction({ "10", "-10", Operations::Operation::ADDITION });
		REQUIRE(IsEqual(addition, 0));
	}

	WHEN("Test calclulator substraction")
	{
		Calculator calculator;
		double substraction = calculator.CalculateResultOfFunction({ "0.1", "0.2", Operations::Operation::SUBSTRACTION });
		REQUIRE(IsEqual(substraction, -0.1));
		substraction = calculator.CalculateResultOfFunction({ "0.5", "0.2", Operations::Operation::SUBSTRACTION });
		REQUIRE(IsEqual(substraction, 0.3));
		substraction = calculator.CalculateResultOfFunction({ "5", "-2", Operations::Operation::SUBSTRACTION });
		REQUIRE(IsEqual(substraction, 7));
		substraction = calculator.CalculateResultOfFunction({ "1.7976931348623158e+308", "-1.7976931348623158e+308", Operations::Operation::SUBSTRACTION });
		REQUIRE(IsEqual(substraction, NAN));
		substraction = calculator.CalculateResultOfFunction({ "1.7976931348623158e+308", "1.7976931348623158e+308", Operations::Operation::SUBSTRACTION });
		REQUIRE(IsEqual(substraction, 0));
	}

	WHEN("Test calclulator divison")
	{
		Calculator calculator;
		double divison = calculator.CalculateResultOfFunction({ "20", "20", Operations::Operation::DIVISION });
		REQUIRE(IsEqual(divison, 1));
		divison = calculator.CalculateResultOfFunction({ "20", "-0", Operations::Operation::DIVISION });
		REQUIRE(IsEqual(divison, NAN));
		divison = calculator.CalculateResultOfFunction({ "0.5", "2", Operations::Operation::DIVISION });
		REQUIRE(IsEqual(divison, 0.25));
		divison = calculator.CalculateResultOfFunction({ "-0.5", "0.125", Operations::Operation::DIVISION });
		REQUIRE(IsEqual(divison, -4));
		divison = calculator.CalculateResultOfFunction({ "5", "-125", Operations::Operation::DIVISION });
		REQUIRE(IsEqual(divison, -0.04));
		divison = calculator.CalculateResultOfFunction({ "5", "1", Operations::Operation::DIVISION });
		REQUIRE(IsEqual(divison, 5));
		divison = calculator.CalculateResultOfFunction({ "-1.7976931348623158e+308", "-1.7976931348623158e+308", Operations::Operation::DIVISION });
		REQUIRE(IsEqual(divison, 1));
		// делить на безумно меелкое число
	}

	WHEN("Test calclulator multiplication")
	{
		Calculator calculator;
		double multiplication = calculator.CalculateResultOfFunction({ "5", "5", Operations::Operation::MULTIPLICATION });
		REQUIRE(IsEqual(multiplication, 25));
		multiplication = calculator.CalculateResultOfFunction({ "-0.5", "5", Operations::Operation::MULTIPLICATION });
		REQUIRE(IsEqual(multiplication, -2.5));
		multiplication = calculator.CalculateResultOfFunction({ "0.2", "5", Operations::Operation::MULTIPLICATION });
		REQUIRE(IsEqual(multiplication, 1));
		multiplication = calculator.CalculateResultOfFunction({ "20", "5", Operations::Operation::MULTIPLICATION });
		REQUIRE(IsEqual(multiplication, 100));
		multiplication = calculator.CalculateResultOfFunction({ "1.7976931348623158e+308", "1.7976931348623158e+308", Operations::Operation::MULTIPLICATION });
		REQUIRE(IsEqual(multiplication, std::numeric_limits<double>::infinity()));
	}

	WHEN("Test calculator get result of functioon")
	{
		Calculator calculator;
		REQUIRE(calculator.CreateVariable("x"));
		REQUIRE(calculator.SetVariableToValue("x", "10"));
		REQUIRE(calculator.SetVariableToValue("y", "5"));
		REQUIRE(calculator.CreateFunction("fn1", { "x", "y", Operations::Operation::ADDITION }));
		REQUIRE(calculator.CreateFunction("fn2", { "fn1", "20", Operations::Operation::SUBSTRACTION }));
		REQUIRE(calculator.CreateFunction("fn3", { "fn1", "fn2", Operations::Operation::SUBSTRACTION }));
		REQUIRE(!calculator.CreateFunction("fn3", { "fn1", "fn2", Operations::Operation::DIVISION }));
		REQUIRE(calculator.CreateFunction("fn4", { "1.7976931348623158e+308", "1.7976931348623158e+308", Operations::Operation::ADDITION }));
		REQUIRE(IsEqual(calculator.CalculateResultOfFunction({ "fn3", "y", Operations::Operation::SUBSTRACTION }), 15));
		REQUIRE(IsEqual(calculator.CalculateResultOfFunction({ "fn1", "y", Operations::Operation::SUBSTRACTION }), 10));
		REQUIRE(IsEqual(calculator.CalculateResultOfFunction({ "fn3", "fn1", Operations::Operation::ADDITION }), 35));
		REQUIRE(calculator.SetVariableToValue("z", "20"));
		REQUIRE(calculator.SetVariableToValue("a", "0"));
		REQUIRE(calculator.SetVariableToValue("b", "1"));
		REQUIRE(IsEqual(calculator.CalculateResultOfFunction({ "fn3", "z", Operations::Operation::DIVISION }), 1));
		REQUIRE(IsEqual(calculator.CalculateResultOfFunction({ "fn4", "a", Operations::Operation::DIVISION }), NAN));
		REQUIRE(IsEqual(calculator.CalculateResultOfFunction({ "fn4", "b", Operations::Operation::MULTIPLICATION }), NAN));
	}
}
