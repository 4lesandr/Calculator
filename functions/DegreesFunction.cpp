#include <cmath>

extern "C" {
    double Execute(double radians) {
        return radians * (180.0 / M_PI);
    }
    
    const char* GetFunctionName() {
        return "degrees";
    }
}