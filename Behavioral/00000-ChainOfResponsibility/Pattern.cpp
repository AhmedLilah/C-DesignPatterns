#include <print>
#include <string>
#include <iostream>

class Validator {
public:
        virtual ~Validator() = 0;
        virtual auto setValidator(Validator *nextValidator) -> Validator* = 0;
        virtual auto validate(std::string const & str) -> bool = 0;
};

Validator::~Validator() {}

class BaseValidator : public Validator { 
public:
        virtual ~BaseValidator() { delete next; } 
        virtual auto setValidator(Validator *nextValidator) -> Validator* override {
                return next = nextValidator;
        }
        virtual auto validate(std::string const & str) -> bool override {
                if (next) {
                        return next->validate(str);
                }
                return true;
        }
protected:
        Validator * next{};
};


class LengthValidator : public BaseValidator { 
public:
        virtual auto validate(std::string const & str) -> bool override {
                if (str.length() > stringMinLength){
                        if (next) {
                                return next->validate(str);
                        }
                        return true;
                }
                return false;
        }
private:
        uint8_t stringMinLength = 20;
};


auto main() -> int {
        BaseValidator validator;

        validator.setValidator(new LengthValidator)
                ->setValidator(new LengthValidator)
                ->setValidator(new LengthValidator)
                ->setValidator(new LengthValidator)
                ->setValidator(new LengthValidator);

        std::println("{}", validator.validate("Ahmed sabry Ali Ali Lilah"));
        std::println("{}", validator.validate("Ahmed S. Lilah"));
        return 0;
}
