#include <cmath>

extern "C" {
    double Execute(double arg) {
        return sin(arg);
    }
    
    const char* GetFunctionName() {
        return "sin";
    }
}