#pragma once

#include <gtest/gtest.h>

#include <libiscorrect/iscorrect.h>

class IsCorrectTest : public ::testing::Test {
protected:
    IsCorrectTest() = default;
    virtual ~IsCorrectTest() = default;
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(IsCorrectTest, IsolatedIntegralConstantIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("1234"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("0"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("001"), result_correct);
}

TEST_F(IsCorrectTest, IsolatedFunctionIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("abs(10)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("log(10)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("xyz(10)"), result_correct);
}

TEST_F(IsCorrectTest, FunctionNameMayBeSeparatedFromBracesWithSpaces) {
    EXPECT_EQ(IsExpressionCorrect("abs (10)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("log (10)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("xyz (10)"), result_correct);
}

TEST_F(IsCorrectTest, IsolatedBracedExpressionIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("(10)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(100)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(0)"), result_correct);
}

TEST_F(IsCorrectTest, UnaryOperatorWithOperandIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("+2"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("-10"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("-0"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("-abs(2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("-(2)"), result_correct);
}

TEST_F(IsCorrectTest, BinaryOperatorWithBothOperandsIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("1 + 2"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("1 - 2"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("1 * 2"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("1 / 2"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("1 / abs(2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("1 / (2)"), result_correct);
}

TEST_F(IsCorrectTest, BinaryAndUnaryOperatorCompositionIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("1 + -2"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("1 - +2"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("1 + +-2"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("1 - -+2"), result_correct);
}

TEST_F(IsCorrectTest, BracedUnaryOperatorWithOperandIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("(+2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(-10)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(-0)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(-abs(2))"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(-(2))"), result_correct);
}

TEST_F(IsCorrectTest, BracedBinaryOperatorWithOperandIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("(1 + 2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(1 - 2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(1 * 2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(1 / 2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(1 / abs(2))"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(1 / (2))"), result_correct);
}

TEST_F(IsCorrectTest, FunctionWrappedUnaryOperatorWithOperandIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("abs(+2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs(-10)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs(-0)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs(-abs(2))"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs(-(2))"), result_correct);
}

TEST_F(IsCorrectTest, FunctionWrappedBracedBinaryOperatorWithOperandIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("abs(1 + 2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs(1 - 2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs(1 * 2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs(1 / 2)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs(1 / abs(2))"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs(1 / (2))"), result_correct);
}

TEST_F(IsCorrectTest, MultipleBinaryOperatorsWithOperandsIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("1 + 2 + 3"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("1 - 2 / 3"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("1 * 2 - 3"), result_correct);
}

TEST_F(IsCorrectTest, ExpressionWithNestedBracesIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("((1))"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("(1 + (1))"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("((1) + (1))"), result_correct);
}

TEST_F(IsCorrectTest, ExpressionWithNestedBracesOfFunctionsAndFunctionsThemselfIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("abs((1) + (1))"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs(abs(1) + abs(1))"), result_correct);
}

TEST_F(IsCorrectTest, ExpressionCombiningMultipleBraceTypesIsCorrect) {
    EXPECT_EQ(IsExpressionCorrect("([{1}])"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("{[(1)]}"), result_correct);
}

TEST_F(IsCorrectTest, FunctionsWithDifferentBraceTypesAreCorrect) {
    EXPECT_EQ(IsExpressionCorrect("abs(1)"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs[1]"), result_correct);
    EXPECT_EQ(IsExpressionCorrect("abs{1}"), result_correct);
}

TEST_F(IsCorrectTest, BinaryOperatorWithoutFirstOperandIsIncorrect) {
    EXPECT_EQ(IsExpressionCorrect("* 1"), result_unexpected_token);
    EXPECT_EQ(IsExpressionCorrect("/ 1"), result_unexpected_token);
}

TEST_F(IsCorrectTest, BinaryOperatorWithoutSecondOperandIsIncorrect) {
    EXPECT_EQ(IsExpressionCorrect("1 *"), result_unexpected_token);
    EXPECT_EQ(IsExpressionCorrect("1 /"), result_unexpected_token);
    EXPECT_EQ(IsExpressionCorrect("1 +"), result_unexpected_token);
    EXPECT_EQ(IsExpressionCorrect("1 -"), result_unexpected_token);
}

TEST_F(IsCorrectTest, IsolatedOperatorIsIncorrect) {
    EXPECT_EQ(IsExpressionCorrect("*"), result_unexpected_token);
    EXPECT_EQ(IsExpressionCorrect("/"), result_unexpected_token);
    EXPECT_EQ(IsExpressionCorrect("+"), result_unexpected_token);
    EXPECT_EQ(IsExpressionCorrect("-"), result_unexpected_token);
}

TEST_F(IsCorrectTest, SequenceOfBinaryOperatorsIsIncorrect) {
    EXPECT_EQ(IsExpressionCorrect("1 ** 1"), result_unexpected_token);
    EXPECT_EQ(IsExpressionCorrect("1 /* 1"), result_unexpected_token);
    EXPECT_EQ(IsExpressionCorrect("1 +/ 1"), result_unexpected_token);
    EXPECT_EQ(IsExpressionCorrect("1 -* 1"), result_unexpected_token);
}

TEST_F(IsCorrectTest, FunctionNameWithoutBracesIsIncorrect) {
    EXPECT_EQ(IsExpressionCorrect("abs"), result_unexpected_token);
}

TEST_F(IsCorrectTest, FunctionWithNoArgumentsIsIncorrect) {
    EXPECT_EQ(IsExpressionCorrect("abs()"), result_unexpected_token);
}

TEST_F(IsCorrectTest, EmptyBracesIsIncorrect) {
    EXPECT_EQ(IsExpressionCorrect("()"), result_unexpected_token);
}

TEST_F(IsCorrectTest, UnbalancedBracesIsIncorrect) {
    EXPECT_EQ(IsExpressionCorrect("("), result_unbalanced_braces);
    EXPECT_EQ(IsExpressionCorrect("((1)"), result_unbalanced_braces);
    EXPECT_EQ(IsExpressionCorrect("(1))"), result_unbalanced_braces);
    EXPECT_EQ(IsExpressionCorrect(")"), result_unbalanced_braces);
    EXPECT_EQ(IsExpressionCorrect("([1]"), result_unbalanced_braces);
    EXPECT_EQ(IsExpressionCorrect("([{1}]"), result_unbalanced_braces);
}

TEST_F(IsCorrectTest, UnmatchedBracesIsIncorrect) {
    EXPECT_EQ(IsExpressionCorrect("(1]"), result_unmatched_braces);
    EXPECT_EQ(IsExpressionCorrect("{1]"), result_unmatched_braces);
    EXPECT_EQ(IsExpressionCorrect("({1)}"), result_unmatched_braces);
    EXPECT_EQ(IsExpressionCorrect("([{1)]}"), result_unmatched_braces);
}

TEST_F(IsCorrectTest, UnbalancedBracesInFunctionIsIncorrect) {
    EXPECT_EQ(IsExpressionCorrect("abs("), result_unbalanced_braces);
    EXPECT_EQ(IsExpressionCorrect("abs((1)"), result_unbalanced_braces);
    EXPECT_EQ(IsExpressionCorrect("abs([1]"), result_unbalanced_braces);
    EXPECT_EQ(IsExpressionCorrect("abs([{1}]"), result_unbalanced_braces);
}

TEST_F(IsCorrectTest, UnmatchedBracesInFunctionIsIncorrect) {
    EXPECT_EQ(IsExpressionCorrect("abs(1]"), result_unmatched_braces);
    EXPECT_EQ(IsExpressionCorrect("abs{1]"), result_unmatched_braces);
    EXPECT_EQ(IsExpressionCorrect("abs({1)}"), result_unmatched_braces);
    EXPECT_EQ(IsExpressionCorrect("abs([{1)]}"), result_unmatched_braces);
}

TEST_F(IsCorrectTest, RandomVariousComplexCorrectExpresions) {
    EXPECT_EQ(IsExpressionCorrect("-(-1 + 5) / ln[(1 - abs(-1)) / (1 - exp{4 / 5})]"), result_correct);
}
