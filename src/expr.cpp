#include <stdexcept>

#include "expr.h"


namespace sirius {


Expr::Expr(sirius::ll value) : data(value) {}


Expr::Expr(sirius::Function func) : data(func) {}


Expr::Type Expr::type() const {
    return static_cast<Type>(data.index());
}


ll Expr::value() const {
    return std::get<ll>(data);
}


Function Expr::function() const {
    return std::get<Function>(data);
}


Expr Expr::operator()() const {
    return std::get<Function>(data)(Parametrs());
}

Expr Expr::operator()(const sirius::Parametrs& params) const {
    return std::get<Function>(data)(params);
}


Expr Expr::operator+(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t add for non-constant");
    return std::get<ll>(data) + std::get<ll>(other.data);
}


Expr Expr::operator-(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t sub for non-constant");
    return std::get<ll>(data) - std::get<ll>(other.data);
}


Expr Expr::operator*(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t mul for non-constant");
    return std::get<ll>(data) * std::get<ll>(other.data);
}


Expr Expr::operator/(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t div for non-constant");
    return std::get<ll>(data) / std::get<ll>(other.data);
}


Expr Expr::operator%(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t mod for non-constant");
    return std::get<ll>(data) % std::get<ll>(other.data);
}


Expr Expr::operator&(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t and for non-constant");
    return std::get<ll>(data) && std::get<ll>(other.data);
}


Expr Expr::operator|(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t or for non-constant");
    return std::get<ll>(data) || std::get<ll>(other.data);
}


Expr Expr::operator==(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t equal for non-constant");
    return std::get<ll>(data) == std::get<ll>(other.data);
}


Expr Expr::operator!=(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t not equal for non-constant");
    return std::get<ll>(data) != std::get<ll>(other.data);
}


Expr Expr::operator<(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t less for non-constant");
    return std::get<ll>(data) < std::get<ll>(other.data);
}


Expr Expr::operator>(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t greater for non-constant");
    return std::get<ll>(data) > std::get<ll>(other.data);
}


Expr Expr::operator<=(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t less or equal for non-constant");
    return std::get<ll>(data) <= std::get<ll>(other.data);
}


Expr Expr::operator>=(const sirius::Expr& other) const {
    if (this->type() != Type::Constant || other.type() != Type::Constant)
        throw std::logic_error("can`t greater or equal for non-constant");
    return std::get<ll>(data) >= std::get<ll>(other.data);
}


}  // namespace sirius
