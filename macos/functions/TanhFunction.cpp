#include <cmath>

extern "C" {
    double Execute(double arg) {
        return tanh(arg);
    }
    
    const char* GetFunctionName() {
        return "tanh";
    }
}