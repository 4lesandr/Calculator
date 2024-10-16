#include <cmath>

extern "C" {
    double Execute(double base, double exponent) {
        return pow(base, exponent);
    }
    
    const char* GetFunctionName() {
        return "pow";
    }
}