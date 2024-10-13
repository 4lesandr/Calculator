#include <cmath>

extern "C" {
    double Execute(double arg) {
        return cosh(arg);
    }
    
    const char* GetFunctionName() {
        return "cosh";
    }
}