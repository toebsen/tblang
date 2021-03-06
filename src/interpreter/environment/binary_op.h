//
// Created by toebs on 05.04.2020.
//

#ifndef ANGREAL_SRC_INTERPRETER_ENVIRONMENT_BINARY_OP_H_
#define ANGREAL_SRC_INTERPRETER_ENVIRONMENT_BINARY_OP_H_

#include "../parser/ast.h"
#include "common.h"
#include "type.h"

using angreal::parser::AST::BinaryOperation;

namespace angreal::interpreter::environment {

class BinaryOp : private NonCopyable {
   public:
    BinaryOp(BinaryOperation::OpType op_type, type_t lhs, type_t rhs);

    type_t Call();

   private:
    type_t Add();

    type_t Sub();

    type_t Mul();

    type_t Divide();

    type_t Or();

    type_t And();

    type_t Equals();

    type_t NotEquals();

    type_t Greater();

    type_t GreaterEqual();

    type_t Less();

    type_t LessEqual();

    BinaryOperation::OpType op_type_;
    type_t lhs_;
    type_t rhs_;
};

}  // namespace angreal::interpreter::environment

#endif  // ANGREAL_SRC_INTERPRETER_ENVIRONMENT_BINARY_OP_H_
