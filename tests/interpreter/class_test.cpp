//
// Created by toebs on 17.05.2020.
//

#include <string>

#include <gtest/gtest.h>

#include "test_fixtures.h"

TEST_F(ClassTest, DefaultConstructor) {
    DeclareEmptyClass("MyClass");
    auto call = std::make_shared<FunctionCall>(last_class_, kNoArgs);
    context_.interpreter->visit(call);
    ASSERT_EQ(GetResultType()->IsInstance(), true);
    ASSERT_EQ(GetResultType()->AsInstance()->Stringify(),
              "Instance of class(MyClass)");
}

TEST_F(ClassTest, ClassMethods) {
    DeclareSingleFunctionClass("MyClass", "myMethod", 42);

    expression_t call = std::make_shared<FunctionCall>(last_class_, kNoArgs);
    call = std::make_shared<Get>(call, "myMethod");
    call = std::make_shared<FunctionCall>(call, kNoArgs);

    context_.interpreter->visit(std::make_shared<ExpressionStatement>(call));

    ASSERT_EQ(GetResultType()->IsInteger(), true);
    ASSERT_EQ(GetResultType()->AsInteger(), 42);
}

TEST_F(ClassTest, BoundMethod) {
    DeclareClassWithMethodReturningSelf("MyClass", "bound");
    auto call = std::make_shared<FunctionCall>(last_class_, kNoArgs);
    auto assignment = std::make_shared<Declaration>("x", call);
    context_.interpreter->visit(assignment);

    auto getter = std::make_shared<Get>(
        std::make_shared<IdentifierLiteral>("x"), "bound");
    auto bound_call = std::make_shared<FunctionCall>(getter, kNoArgs);
    context_.interpreter->visit(bound_call);

    ASSERT_EQ(GetResultType()->IsInstance(), true);
    ASSERT_EQ(GetResultType()->AsInstance()->Stringify(),
              "Instance of class(MyClass)");
}

TEST_F(ClassTest, GetSetExpression) {
    DeclareEmptyClass("MyClass");
    auto call = std::make_shared<FunctionCall>(last_class_, kNoArgs);
    auto assignment = std::make_shared<Declaration>("x", call);
    context_.interpreter->visit(assignment);

    auto setter =
        std::make_shared<Set>(std::make_shared<IdentifierLiteral>("x"), "y",
                              std::make_shared<IntLiteral>(123));
    context_.interpreter->visit(setter);

    auto getter =
        std::make_shared<Get>(std::make_shared<IdentifierLiteral>("x"), "y");

    context_.interpreter->visit(getter);

    ASSERT_EQ(GetResultType()->IsInteger(), true);
    ASSERT_EQ(GetResultType()->AsInteger(), 123);
}

TEST_F(ClassTest, ErronousGetExpression) {
    auto assignment =
        std::make_shared<Declaration>("x", std::make_shared<IntLiteral>(123));
    context_.interpreter->visit(assignment);

    auto getter =
        std::make_shared<Get>(std::make_shared<IdentifierLiteral>("x"), "y");

    EXPECT_THROW(context_.interpreter->visit(getter), RuntimeError);
}

TEST_F(ClassTest, ErronousSetExpression) {
    auto assignment =
        std::make_shared<Declaration>("x", std::make_shared<IntLiteral>(123));
    context_.interpreter->visit(assignment);

    auto setter =
        std::make_shared<Set>(std::make_shared<IdentifierLiteral>("x"), "y",
                              std::make_shared<IntLiteral>(123));

    EXPECT_THROW(context_.interpreter->visit(setter), RuntimeError);
}

TEST_F(ClassTest, ErronousClassMethods) {
    DeclareSingleFunctionClass("MyClass", "myMethod", 42);

    expression_t call = std::make_shared<FunctionCall>(last_class_, kNoArgs);
    call = std::make_shared<Get>(call, "myMethod123");
    call = std::make_shared<FunctionCall>(call, kNoArgs);

    EXPECT_THROW(context_.interpreter->visit(
                     std::make_shared<ExpressionStatement>(call)),
                 RuntimeError);
}

TEST_F(ClassTest, ErronousSelf) {
    EXPECT_THROW(context_.interpreter->visit(std::make_shared<Self>()),
                 RuntimeError);
}