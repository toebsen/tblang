//
// Created by toebs on 24.05.2020.
//

#ifndef ANGREAL_TESTS_ERROR_REPORTER_MOCKS_H_
#define ANGREAL_TESTS_ERROR_REPORTER_MOCKS_H_

#include "error_handler.h"

namespace angreal::mock {
class ErrorReporter : public IErrorHandler {
   public:
    bool HasError() override { return error_occurred; };

    void ParserError(const string_t& error) override {
        error_occurred = true;
        last_error = error;
    };

    void AnalysisError(const string_t& error) override {
        error_occurred = true;
        last_error = error;
    };

    void RuntimeError(const string_t& error) override {
        error_occurred = true;
        last_error = error;
        throw angreal::RuntimeError(error);
    };

    void HandleCrucialError(const string_t& error) override {
        last_error = error;
    };

    bool error_occurred {false};
    string_t last_error {""};
};
}  // namespace angreal::mock
#endif  // ANGREAL_TESTS_ERROR_REPORTER_MOCKS_H_
