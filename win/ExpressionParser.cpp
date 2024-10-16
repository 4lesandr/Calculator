#include "ExpressionParser.h"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <iostream>

ExpressionParser::ExpressionParser() {
    operators["+"] = [](double a, double b) { return a + b; };
    operators["-"] = [](double a, double b) { return a - b; };
    operators["*"] = [](double a, double b) { return a * b; };
    operators["/"] = [](double a, double b) { 
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b; 
    };
}

void ExpressionParser::registerFunction(const std::string& name, PluginFunction func) {
    functions[name] = func;
}

double ExpressionParser::evaluate(const std::string& expression) {
    auto tokens = tokenize(expression);
    auto rpn = toRPN(tokens);

    std::stack<double> evalStack;
    for (const auto& token : rpn) {
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-' && isdigit(token[1]))) {
            evalStack.push(std::stod(token));
        } else if (isOperator(token)) {
            if (evalStack.size() < 2) {
                throw std::runtime_error("Error: insufficient values in expression");
            }
            double b = evalStack.top(); evalStack.pop();
            double a = evalStack.top(); evalStack.pop();
            evalStack.push(operators[token](a, b));
        } else if (isFunction(token)) {
            if (evalStack.empty()) {
                throw std::runtime_error("Error: insufficient values for function");
            }
            double a = evalStack.top(); evalStack.pop();
            evalStack.push(functions[token](a));
        } else {
            throw std::runtime_error("Error: unknown token in expression");
        }
    }

    if (evalStack.size() != 1) {
        throw std::runtime_error("Error: improper expression evaluation");
    }

    return evalStack.top();
}

int ExpressionParser::getPrecedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

bool ExpressionParser::isOperator(const std::string& token) {
    return operators.find(token) != operators.end();
}

bool ExpressionParser::isFunction(const std::string& token) {
    return functions.find(token) != functions.end();
}

std::vector<std::string> ExpressionParser::tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::string token;
    bool expectNumber = true;

    for (size_t i = 0; i < expression.length(); ++i) {
        char current = expression[i];

        if (isspace(current)) {
            continue;
        }

        if (isdigit(current) || current == '.') {
            token += current;
            expectNumber = false;
        } else if (isalpha(current)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            while (i < expression.length() && isalpha(expression[i])) {
                token += expression[i++];
            }
            --i;
            tokens.push_back(token);
            token.clear();
            expectNumber = false;
        } else if (current == '-' && expectNumber) {
            token += current;
        } else {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, current));
            expectNumber = (current == '(' || isOperator(std::string(1, current)));
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> ExpressionParser::toRPN(const std::vector<std::string>& tokens) {
    std::vector<std::string> outputQueue;
    std::stack<std::string> operatorStack;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string& token = tokens[i];
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-' && isdigit(token[1]))) {
            outputQueue.push_back(token);
        } else if (isFunction(token)) {
            operatorStack.push(token);
        } else if (isOperator(token)) {
            while (!operatorStack.empty() && isOperator(operatorStack.top()) &&
                   getPrecedence(operatorStack.top()) >= getPrecedence(token)) {
                outputQueue.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
        } else if (token == "(") {
            operatorStack.push(token);
        } else if (token == ")") {
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                outputQueue.push_back(operatorStack.top());
                operatorStack.pop();
            }
            if (!operatorStack.empty()) {
                operatorStack.pop(); 
            }
        }
    }

    while (!operatorStack.empty()) {
        outputQueue.push_back(operatorStack.top());
        operatorStack.pop();
    }

    for (const auto& rpnToken : outputQueue) {
        std::cout << "RPN Token: " << rpnToken << std::endl;
    }

    return outputQueue;
}