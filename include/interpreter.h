#pragma once
#include <iostream>
#include <map>

#include "expr.h"


namespace sirius {


class Interpreter {
   public:
    static void global_init();

   private:
    std::map<std::string, Expr> mem;
    std::vector<Expr> stack;


    Expr dfs(const Json& json);


   public:
    Interpreter() = default;
    Interpreter(const Interpreter&) = default;
    Interpreter(Interpreter&&) noexcept = default;
    ~Interpreter() noexcept = default;

    Interpreter& operator=(const Interpreter&) = default;
    Interpreter& operator=(Interpreter&&) noexcept = default;


    void clear(bool all = false);


    void run(const Json& json);


   private:
    Expr for_constant(const Json& json);
    Expr for_variable(const Json& json);
    Expr for_binary_operator(const Json& json);

    Expr for_skip(const Json& json);

    Expr for_read(const Json& json);
    Expr for_write(const Json& json);

    Expr for_sequence(const Json& json);

    Expr for_if_else(const Json& json);

    Expr for_init_function(const Json& json);
    Expr for_call_function(const Json& json);

    Expr for_let(const Json& json);


    Expr wrap_for_function(const Parametrs& args, const Json& json);
};


}  // namespace sirius
