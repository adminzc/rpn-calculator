// rpn_calculator.h
#ifndef RPN_CALCULATOR_H
#define RPN_CALCULATOR_H

#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <iostream>

class RPNCalculator {
private:
    std::vector<double> stack;
    
public:
    RPNCalculator() = default;
    
    // 清空栈
    void clear() {
        stack.clear();
    }
    
    // 显示当前栈内容
    void displayStack() const {
        if (stack.empty()) {
            std::cout << "Stack is empty" << std::endl;
            return;
        }
        
        std::cout << "Stack (top to bottom): ";
        for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    
    // 压入数字到栈中
    void push(double value) {
        stack.push_back(value);
    }
    
    // 从栈中弹出数字
    double pop() {
        if (stack.empty()) {
            throw std::runtime_error("Error: Stack is empty");
        }
        double value = stack.back();
        stack.pop_back();
        return value;
    }
    
    // 执行加法运算
    void add() {
        if (stack.size() < 2) {
            throw std::runtime_error("Error: Not enough operands for addition");
        }
        double b = pop();
        double a = pop();
        push(a + b);
    }
    
    // 执行减法运算
    void subtract() {
        if (stack.size() < 2) {
            throw std::runtime_error("Error: Not enough operands for subtraction");
        }
        double b = pop();
        double a = pop();
        push(a - b);
    }
    
    // 执行乘法运算
    void multiply() {
        if (stack.size() < 2) {
            throw std::runtime_error("Error: Not enough operands for multiplication");
        }
        double b = pop();
        double a = pop();
        push(a * b);
    }
    
    // 执行除法运算
    void divide() {
        if (stack.size() < 2) {
            throw std::runtime_error("Error: Not enough operands for division");
        }
        double b = pop();
        if (b == 0.0) {
            throw std::runtime_error("Error: Division by zero");
        }
        double a = pop();
        push(a / b);
    }
    
    // 执行平方根运算
    void squareRoot() {
        if (stack.empty()) {
            throw std::runtime_error("Error: Not enough operands for square root");
        }
        double a = pop();
        if (a < 0) {
            throw std::runtime_error("Error: Square root of negative number");
        }
        push(std::sqrt(a));
    }
    
    // 执行幂运算
    void power() {
        if (stack.size() < 2) {
            throw std::runtime_error("Error: Not enough operands for power operation");
        }
        double exponent = pop();
        double base = pop();
        push(std::pow(base, exponent));
    }
    
    // 执行正弦运算（弧度）
    void sine() {
        if (stack.empty()) {
            throw std::runtime_error("Error: Not enough operands for sine");
        }
        double a = pop();
        push(std::sin(a));
    }
    
    // 执行余弦运算（弧度）
    void cosine() {
        if (stack.empty()) {
            throw std::runtime_error("Error: Not enough operands for cosine");
        }
        double a = pop();
        push(std::cos(a));
    }
    
    // 执行正切运算（弧度）
    void tangent() {
        if (stack.empty()) {
            throw std::runtime_error("Error: Not enough operands for tangent");
        }
        double a = pop();
        push(std::tan(a));
    }
    
    // 获取栈顶元素（不弹出）
    double peek() const {
        if (stack.empty()) {
            throw std::runtime_error("Error: Stack is empty");
        }
        return stack.back();
    }
    
    // 获取栈的大小
    size_t size() const {
        return stack.size();
    }
    
    // 判断栈是否为空
    bool empty() const {
        return stack.empty();
    }
    
    // 处理单个RPN表达式
    double evaluateExpression(const std::string& expression) {
        std::istringstream iss(expression);
        std::string token;
        
        while (iss >> token) {
            if (token == "+") {
                add();
            } else if (token == "-") {
                subtract();
            } else if (token == "*") {
                multiply();
            } else if (token == "/") {
                divide();
            } else if (token == "sqrt") {
                squareRoot();
            } else if (token == "pow") {
                power();
            } else if (token == "sin") {
                sine();
            } else if (token == "cos") {
                cosine();
            } else if (token == "tan") {
                tangent();
            } else if (token == "clear") {
                clear();
            } else if (token == "display") {
                displayStack();
            } else {
                // 尝试解析为数字
                try {
                    double value = std::stod(token);
                    push(value);
                } catch (const std::invalid_argument&) {
                    throw std::runtime_error("Error: Invalid token '" + token + "'");
                } catch (const std::out_of_range&) {
                    throw std::runtime_error("Error: Number out of range '" + token + "'");
                }
            }
        }
        
        if (stack.size() != 1) {
            throw std::runtime_error("Error: Invalid expression - stack has " + 
                                   std::to_string(stack.size()) + " elements instead of 1");
        }
        
        return pop();
    }
};

#endif
// main.cpp
#include "rpn_calculator.h"
#include <iostream>
#include <string>

void printHelp() {
    std::cout << "=== RPN Calculator ===" << std::endl;
    std::cout << "Supported operations:" << std::endl;
    std::cout << "  +, -, *, /        : Basic arithmetic" << std::endl;
    std::cout << "  sqrt              : Square root" << std::endl;
    std::cout << "  pow               : Power (x^y)" << std::endl;
    std::cout << "  sin, cos, tan     : Trigonometric functions (radians)" << std::endl;
    std::cout << "  clear             : Clear the stack" << std::endl;
    std::cout << "  display           : Display current stack" << std::endl;
    std::cout << "  help              : Show this help" << std::endl;
    std::cout << "  quit/exit         : Exit calculator" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  '3 4 +'           : 3 + 4 = 7" << std::endl;
    std::cout << "  '5 1 2 + 4 * + 3 -' : Equivalent to 5 + ((1 + 2) * 4) - 3 = 14" << std::endl;
    std::cout << "  '9 sqrt'          : Square root of 9 = 3" << std::endl;
    std::cout << "  '2 3 pow'         : 2^3 = 8" << std::endl;
    std::cout << std::endl;
}

int main() {
    RPNCalculator calculator;
    std::string input;
    
    std::cout << "RPN Calculator started. Type 'help' for instructions." << std::endl;
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if (input == "quit" || input == "exit") {
            break;
        } else if (input == "help") {
            printHelp();
            continue;
        } else if (input.empty()) {
            continue;
        }
        
        try {
            double result = calculator.evaluateExpression(input);
            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    
    std::cout << "Goodbye!" << std::endl;
    return 0;
}
