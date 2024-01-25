#include "interpreter.h"


namespace sirius {


std::map<std::string, std::function<Expr(Interpreter&, const Json&)>> funcs;
std::map<std::string, std::function<Expr(const Expr&, const Expr&)>> bin_ops;


void Interpreter::global_init() {
    funcs["Skip"] = &Interpreter::for_skip;
    funcs["Read"] = &Interpreter::for_read;
    funcs["Write"] = &Interpreter::for_write;
    funcs["If"] = &Interpreter::for_if_else;
    funcs["Let"] = &Interpreter::for_let;
    funcs["Fun"] = &Interpreter::for_init_function;
    funcs["Call"] = &Interpreter::for_call_function;
    funcs["Const"] = &Interpreter::for_constant;
    funcs["Var"] = &Interpreter::for_variable;
    funcs["Op"] = &Interpreter::for_binary_operator;
    funcs["Seq"] = &Interpreter::for_sequence;

    bin_ops["+"] = [](const Expr& a, const Expr& b) { return a + b; };
    bin_ops["-"] = [](const Expr& a, const Expr& b) { return a - b; };
    bin_ops["*"] = [](const Expr& a, const Expr& b) { return a * b; };
    bin_ops["/"] = [](const Expr& a, const Expr& b) { return a / b; };
    bin_ops["%"] = [](const Expr& a, const Expr& b) { return a % b; };

    bin_ops["&"] = [](const Expr& a, const Expr& b) { return a & b; };
    bin_ops["|"] = [](const Expr& a, const Expr& b) { return a | b; };

    bin_ops["<"] = [](const Expr& a, const Expr& b) { return a < b; };
    bin_ops["<="] = [](const Expr& a, const Expr& b) { return a <= b; };
    bin_ops[">"] = [](const Expr& a, const Expr& b) { return a > b; };
    bin_ops[">="] = [](const Expr& a, const Expr& b) { return a >= b; };
    bin_ops["=="] = [](const Expr& a, const Expr& b) { return a == b; };
    bin_ops["!="] = [](const Expr& a, const Expr& b) { return a != b; };
}


Expr Interpreter::dfs(const sirius::Json& json) {
    if (json.contains("kind")) {
        auto fnd = funcs.find(json["kind"]);
        if (fnd == funcs.end())
            throw std::logic_error("Unknown \"kind\"");

        return fnd->second(*this, json);
    }

    auto fnd = funcs.find(std::string(json));
    if (fnd == funcs.end())
        throw std::logic_error("Unknown literal");
    return fnd->second(*this, json);
}


void Interpreter::clear(bool all) {
    if (all)
        funcs.clear();
    mem.clear();
    stack.clear();
}


void Interpreter::run(const sirius::Json& json) {
    dfs(json);
}


Expr Interpreter::for_skip(const sirius::Json& json) {
    if (json.empty())
        throw std::logic_error("Expected \"skip\"");
    return Expr();
}


Expr Interpreter::for_read(const sirius::Json& json) {
    if (json.empty())
        throw std::logic_error("Expected \"Read\"");
    ll val;
    std::cin >> val;
    return Expr(val);
}


Expr Interpreter::for_write(const sirius::Json& json) {
    auto val = dfs(json["value"]);
    std::cout << val.value() << std::endl;
    return Expr();
}


Expr Interpreter::for_constant(const sirius::Json& json) {
    return Expr(ll(json["value"]));
}


Expr Interpreter::for_variable(const sirius::Json& json) {
    std::string name = json["name"];
    return mem[name];
}


Expr Interpreter::for_sequence(const sirius::Json& json) {
    dfs(json["left"]);
    return dfs(json["right"]);
}


Expr Interpreter::for_if_else(const sirius::Json& json) {
    auto cond = dfs(json["cond"]);
    if (cond.value() == 1)
        return dfs(json["then"]);
    else
        return dfs(json["else"]);
}


Expr Interpreter::for_let(const sirius::Json& json) {
    std::string name = json["name"];
    stack.emplace_back(std::move(mem[name]));
    mem[name] = dfs(json["rhs"]);
    auto res = dfs(json["body"]);
    mem[name] = std::move(stack.back());
    return res;
}


Expr Interpreter::for_binary_operator(const sirius::Json& json) {
    std::string name = json["name"];
    auto a = dfs(json["left"]);
    auto b = dfs(json["right"]);
    return bin_ops[name](a, b);
}


Expr Interpreter::for_call_function(const sirius::Json& json) {
    auto func = dfs(json["func"]);
    Parametrs args;
    for (auto& arg : json["args"])
        args.emplace_back(dfs(arg));
    return func(args);
}


Expr Interpreter::wrap_for_function(const sirius::Parametrs& args, const sirius::Json& json) {
    size_t index = 0;
    for (auto& t : json["params"]) {
        stack.emplace_back(std::move(mem[t]));
        mem[t] = args[index++];
    }

    auto res = dfs(json["body"]);

    for (auto it = json["params"].rbegin(); it != json["params"].rend(); it++) {
        mem[*it] = std::move(stack.back());
        stack.pop_back();
    }

    return res;
}


Expr Interpreter::for_init_function(const sirius::Json& json) {
    auto val = *this;
    auto buf = [val, &json](const Parametrs& args) mutable -> Expr { return val.wrap_for_function(args, json); };
    // "Топорная" реализация
    return Expr(buf);
}


}  // namespace sirius
