#include <cmath>

extern "C" {
    double Execute(double arg) {
        return sinh(arg);
    }
    
    const char* GetFunctionName() {
        return "sinh";
    }
}