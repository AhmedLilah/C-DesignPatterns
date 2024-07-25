#include <print>
#include <string>
#include <vector>
#include <functional>

// using Validator = std::function<bool(const std::string &)>;

auto lengthValidator(const std::string &str) -> bool {
        uint8_t stringMinLength = 20;
        return str.length() > stringMinLength;
};

auto someOtherValidator(const std::string &str) -> bool {
        uint8_t stringMinLength = 10;
        return str.length() > stringMinLength;
};

// auto chainValidators(std::vector<Validator> validators, const std::string &str) -> bool {
auto chainValidators(std::vector<bool(*)(const std::string &)> validators, const std::string &str) -> bool {
        for (auto validator : validators) {
                if (not validator(str)) {
                        return false;
                }
        }
        return true;
};

int main() {
        std::vector<std::string> strings = {"Ahmed Sabry Ali Ali Lilah", "Ahmed S. Lilah"};
        // std::vector<Validator> validators = {lengthValidator, someOtherValidator};
        std::vector<bool(*)(const std::string &)> validators = {lengthValidator, someOtherValidator};

        for (const auto& str : strings) {
                std::println("{}", chainValidators(validators, str));
        }

        return 0;
}
