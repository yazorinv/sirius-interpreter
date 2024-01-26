#include <chrono>
#include <iostream>
using namespace std;
using namespace chrono;

#include "interpreter.h"
using namespace sirius;

int main() {
    Interpreter::global_init();
    Interpreter interpreter;
    Json json;

    cin >> json;


    auto start = high_resolution_clock::now();
    interpreter.run(json);
    auto end = high_resolution_clock::now();
    cout << (end - start) / 1.0ms << '\n';
}
