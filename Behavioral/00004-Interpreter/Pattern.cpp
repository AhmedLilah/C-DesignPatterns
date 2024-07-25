#include <print>
#include <string>
#include <limits>

class ExpressionInterface {
public:
        virtual ~ExpressionInterface() = default;
        virtual auto evaluate() -> double = 0;
};

class NumberExpression : public ExpressionInterface {
private: 
        double number;
public:
        NumberExpression(std::string const & str)
                : number(std::stod(str)) {}

        auto evaluate() -> double override {
                return number;
        }
};

enum class Operator {
        PLUS, MINUS, MULTIPLY, DIVIDE
};

class BinaryOperatorExpression : public ExpressionInterface {
private: 
        Operator op;
        ExpressionInterface * lhs;
        ExpressionInterface * rhs;
public:
        BinaryOperatorExpression(Operator op, ExpressionInterface *lhs, ExpressionInterface *rhs)
                : op(op)
                , lhs(lhs)
                , rhs(rhs) {}

        auto evaluate() -> double override {
                switch (op) {
                        case Operator::PLUS:
                                return lhs->evaluate() + rhs->evaluate();
                                break;
                        default: 
                                return std::numeric_limits<double>::quiet_NaN();
                                break;
                }
                return std::numeric_limits<double>::quiet_NaN();
        }
};

auto main() -> int {
        ExpressionInterface *lhs{new NumberExpression("5.0")};
        ExpressionInterface *rhs{new NumberExpression("6.0")};
        ExpressionInterface *pls{new BinaryOperatorExpression(Operator::PLUS, lhs, rhs)};

        std::println("5 + 6 = {}", pls->evaluate());
        return 0;
}
