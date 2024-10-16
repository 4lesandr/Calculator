#include <cmath>
#include <stdexcept>

extern "C" {
    double Execute(double arg) {
        if (arg <= 0) {
            throw std::domain_error("Logarithm of a non-positive number.");
        }
        return log(arg);
    }
    
    const char* GetFunctionName() {
        return "log";
    }
}