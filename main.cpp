#include <iostream>
using namespace std;

#include "interpreter.h"
using namespace sirius;

int main() {
    Interpreter::global_init();
    Interpreter interpreter;
    Json json;

    cin >> json;

    interpreter.run(json);
}
