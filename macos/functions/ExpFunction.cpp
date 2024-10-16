#include <cmath>

extern "C" {
    double Execute(double arg) {
        return exp(arg);
    }
    
    const char* GetFunctionName() {
        return "exp";
    }
}