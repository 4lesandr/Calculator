#include <cmath>
#include <stdexcept>

extern "C" {
    double Execute(double arg) {
        if (arg <= 0) {
            throw std::domain_error("Natural logarithm of a non-positive number is undefined.");
        }
        return log(arg);
    }
    
    const char* GetFunctionName() {
        return "ln";
    }
}