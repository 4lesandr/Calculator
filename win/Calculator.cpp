#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "ExpressionParser.h"

typedef double (*MathFunction)(double);

void loadAllPlugins(const std::string& pluginsDir, ExpressionParser& parser) {
    std::vector<std::string> pluginNames = { "funcsin.dll", "funcdeg.dll" }; // Пример имен библиотек; добавьте остальные

    for (const auto& pluginName : pluginNames) {
        std::string pluginPath = pluginsDir + "\\" + pluginName;
        HMODULE hLib = LoadLibrary(pluginPath.c_str());

        if (hLib != nullptr) {
            auto executeFunc = reinterpret_cast<MathFunction>(GetProcAddress(hLib, "Execute"));
            auto getNameFunc = reinterpret_cast<const char* (*)()>(GetProcAddress(hLib, "GetFunctionName"));

            if (executeFunc != nullptr && getNameFunc != nullptr) {
                const char* functionName = getNameFunc();
                parser.registerFunction(functionName, executeFunc);
                std::cout << "Successfully registered function: " << functionName << std::endl;
            } else {
                std::cerr << "Failed to find necessary functions in " << pluginName << std::endl;
                FreeLibrary(hLib);
            }
        } else {
            std::cerr << "Could not load plugin: " << pluginName << std::endl;
        }
    }
}

int main() {
    ExpressionParser parser;
    loadAllPlugins(".\\plugins", parser);

    std::string expression;
    std::cout << "Enter an expression (e.g., sin(45) + cos(30)): ";
    std::getline(std::cin, expression);

    try {
        double result = parser.evaluate(expression);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::domain_error& e) {
        std::cerr << "Math error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error while evaluating expression: " << e.what() << std::endl;
    }

    return 0;
}