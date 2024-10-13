#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

using OperatorFunction = std::function<double(double, double)>;
using PluginFunction = std::function<double(double)>;

class ExpressionParser {
public:
    ExpressionParser();
    double evaluate(const std::string& expression);

    void registerFunction(const std::string& name, PluginFunction func);

private:
    std::unordered_map<std::string, OperatorFunction> operators;
    std::unordered_map<std::string, PluginFunction> functions;

    int getPrecedence(const std::string& op);
    bool isOperator(const std::string& token);
    bool isFunction(const std::string& token);
    std::vector<std::string> tokenize(const std::string& expression);
    std::vector<std::string> toRPN(const std::vector<std::string>& tokens);
};