#pragma once
#include <iostream>
#include <map>

#include "expr.h"


namespace sirius {


class Interpreter {
   private:
    std::map<std::string, std::function<Expr(Interpreter&, const Json&)>> funcs;
    std::map<std::string, Expr> mem;
    std::vector<Expr> stack;


    Expr dfs(const Json& json);

   public:
    Interpreter();
    Interpreter(const Interpreter&) = default;
    Interpreter(Interpreter&&) noexcept = default;
    ~Interpreter() noexcept = default;

    Interpreter& operator=(const Interpreter&) = default;
    Interpreter& operator=(Interpreter&&) noexcept = default;


    void clear();


    void run(const Json& json, std::istream& cin = std::cin, std::ostream& cout = std::cout);
};


}  // namespace sirius
