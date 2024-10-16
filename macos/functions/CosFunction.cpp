#include <cmath>

extern "C" {
    double Execute(double arg) {
        return cos(arg);
    }
    
    const char* GetFunctionName() {
        return "cos";
    }
}