#include <cmath>

extern "C" {
    double Execute(double arg) {
        return tan(arg);
    }
    
    const char* GetFunctionName() {
        return "tan";
    }
}