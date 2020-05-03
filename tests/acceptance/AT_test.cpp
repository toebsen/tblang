//
// Created by toebs on 11.04.2020.
//
#include <string>
#include <gtest/gtest.h>

#include "test_fixtures.h"

TEST_F(BaseTest, HelloWorld) {
    std::string code = R"(
    # this is a comment
    def Hello(name) {
        # this is a function
        return "Hello " + name
    }
    # this is a nested function call
    print(Hello("World"));
    )";
    SafeRun(code, "Hello World");
}


TEST_F(BaseTest, ScopingWithFunction) {
    std::string code = R"(
    var x = "global";
    {
        def printVar() {
            print(x);
            return 0;
        }

        printVar();
        var x = "local";
        printVar();
    }
    )";
    SafeRun(code, "global\nglobal");
}

TEST_F(BaseTest, ScopingWithFunction2) {
    std::string code = R"(
    var x = "global";
    {
        def printVar(x) {
            print(x);
            return 0;
        }

        printVar(x);
        var x = "local";
        printVar(x);
    }
    )";
    SafeRun(code, "global\nlocal");
}


TEST_F(BaseTest, SameNameWithInLocalScope) {
    std::string code = R"(
    # redefinition is allowed on a global scope
    var a = "first";
    var a = "second";
    def bad() {
      # but not in a local scope
      var b = "first";
      var b = "second";
    }
    )";
    ExpectRuntimeException(code, "variable `b` already declared in this scope");
}

TEST_F(BaseTest, ReturnTesting) {
    std::string code = R"(
    def somefun()  {
        def inner()  {
            var a = 5;
            return a;
        }

      var x = inner();
      return x;
      return 42;
    }

    var result = somefun();
    print(result);
    )";
    SafeRun(code, "5");
}

TEST_F(BaseTest, TopLevelReturn) {
    std::string code = R"(
    var result = "123";
    return result;
    )";
    ExpectRuntimeException(code, "Can not return from top level code!");
}

TEST_F(BaseTest, Fibonacci) {
    std::string code = R"(
    def fib(n)
    {
        if(n <= 1){ return 1;}
        return fib(n-2) + fib(n-1);
    }
    print(fib(5));
    )";
    SafeRun(code, "8");
}