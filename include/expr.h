#pragma once
#include "incl.h"


namespace sirius {


class Expr;
using Parametrs = std::vector<Expr>;
using Function = std::function<Expr(Parametrs)>;


class Expr {
   public:
    enum class Type { Void, Constant, Function };

   private:
    std::variant<std::monostate, ll, Function> data;

   public:
    Expr() = default;
    Expr(const Expr&) = default;
    Expr(Expr&&) noexcept = default;
    ~Expr() noexcept = default;

    Expr& operator=(const Expr&) = default;
    Expr& operator=(Expr&&) noexcept = default;


    Expr(ll value);
    Expr(Function func);


    Type type() const;


    ll value() const;


    Function function() const;


    Expr operator()() const;
    Expr operator()(const Parametrs& params) const;


    Expr operator+(const Expr& other) const&;
    Expr operator-(const Expr& other) const&;
    Expr operator*(const Expr& other) const&;
    Expr operator/(const Expr& other) const&;
    Expr operator%(const Expr& other) const&;

    Expr operator&(const Expr& other) const&;
    Expr operator|(const Expr& other) const&;

    Expr operator==(const Expr& other) const&;
    Expr operator!=(const Expr& other) const&;
    Expr operator<(const Expr& other) const&;
    Expr operator<=(const Expr& other) const&;
    Expr operator>(const Expr& other) const&;
    Expr operator>=(const Expr& other) const&;
};

}  // namespace sirius
