#include <iostream>
#include <filesystem>
#include <vector>
#include <dlfcn.h>
#include "ExpressionParser.h"

typedef double (*MathFunction)(double);

struct Plugin {
    void* handle;
    MathFunction func;
};

void loadAllPlugins(const std::string& pluginsDir, ExpressionParser& parser) {
    bool pluginLoaded = false;

    for (const auto& entry : std::filesystem::directory_iterator(pluginsDir)) {
        if (entry.path().extension() == ".dylib") {
            void* handle = dlopen(entry.path().c_str(), RTLD_LAZY);
            if (handle) {
                try {
                    auto executeFunc = (MathFunction)dlsym(handle, "Execute");
                    char* errorMsg = dlerror();
                    if (errorMsg) throw std::runtime_error(errorMsg);

                    auto getNameFunc = (const char* (*)())dlsym(handle, "GetFunctionName");
                    errorMsg = dlerror();
                    if (errorMsg) throw std::runtime_error(errorMsg);

                    if (executeFunc && getNameFunc) {
                        const char* actualName = getNameFunc();
                        parser.registerFunction(actualName, executeFunc);
                        std::cout << "Successfully registered function: " << actualName << std::endl;
                        pluginLoaded = true;
                    } else {
                        throw std::runtime_error("Failed to load required functions.");
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error loading plugin " << entry.path() << ": " << e.what() << std::endl;
                    dlclose(handle);
                }
            } else {
                std::cerr << "Could not load plugin from " << entry.path() << ": " << dlerror() << std::endl;
            }
        }
    }

    if (!pluginLoaded) {
        std::cerr << "No plugins loaded. Please check the plugins directory and the plugins themselves." << std::endl;
    }
}

int main() {
    ExpressionParser parser;

    //регистрация всех плагинов из ./plugins
    loadAllPlugins("./plugins", parser);

    std::string expression;
    std::cout << "Enter an expression (e.g., sin(45) + cos(30)): ";
    std::getline(std::cin, expression);

    try {
        double result = parser.evaluate(expression);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::domain_error& e) {
        std::cerr << "Mathematical error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error while evaluating expression: " << e.what() << std::endl;
    }

    return 0;
}