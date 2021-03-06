#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-special-member-functions"
//
// Created by bichlmaier on 10.02.2020.
//

#ifndef ANGREAL_AST_INTERFACES_H
#define ANGREAL_AST_INTERFACES_H

#include <memory>
#include <optional>
#include <vector>

#include "common.h"
#include "visitor.h"

namespace angreal::parser::AST {

class Node : private NonCopyable {
   public:
    ~Node() override = default;

    virtual void accept(const visitor_t& visitor) = 0;

    void SetLine(uint32_t line) { line_no = line; };
    std::optional<uint32_t> GetLine() { return line_no; };

   protected:
    std::optional<uint32_t> line_no;
};

class Statement : public Node {
   public:
    void accept(const visitor_t& visitor) override = 0;

    ~Statement() override = default;
};

class Expression : public Node {
   public:
    void accept(const visitor_t& visitor) override = 0;

    ~Expression() override = default;
};

}  // namespace angreal::parser::AST
#endif  // ANGREAL_AST_INTERFACES_H

#pragma clang diagnostic pop