#include <print>
#include <vector>
#include <ranges>
#include <algorithm>


class Subscriber {
public:
        virtual auto notify(const std::string & publisherName, const std::string & message) -> void = 0;
        virtual auto getName() -> std::string =0;
};

class Publisher {
public: 
        virtual auto subscribe(Subscriber * subscriber) -> void = 0;
        virtual auto unsubscribe(Subscriber * subscriber) -> void = 0;
        virtual auto publish(std::string) -> void = 0;
};

class ChatGroup : public Publisher {
        std::string name;
        std::vector<Subscriber *> subscribers;
public:
        ChatGroup(std::string name) : name(std::move(name)) {}
        virtual auto subscribe(Subscriber * subscriber) -> void override {
                subscribers.push_back(subscriber);
        }
        virtual auto unsubscribe(Subscriber * subscriber) -> void override {
                if (auto pos {std::find(this->subscribers.begin(), this->subscribers.end(), subscriber)}; pos != this->subscribers.end()) {
                        std::println("Erasing: {}", (*pos)->getName());
                        subscribers.erase(pos);
                }
        }
        virtual auto publish(std::string message) -> void override {
                std::ranges::for_each(this->subscribers, [message, this](auto const sub){ sub->notify(this->name, message); });
        }
};

class ChatMember : public Subscriber {
        std::string name;
public:
        ChatMember(std::string name) : name(std::move(name)) {}
        virtual auto notify(const std::string & publisher, const std::string & message) -> void override {
                std::println("{:<15} got a message from {:<10}: {}", this->name, publisher, message);
        }
        virtual auto getName() -> std::string override {
                return this->name;
        }
};

auto main() -> int {
        auto Cpp {std::make_shared<ChatGroup>("C++")};
        auto C {std::make_shared<ChatGroup>("C")};

        auto CCppM {std::make_shared<ChatMember>("Ahmed")};
        auto CppM {std::make_shared<ChatMember>("Khaled")};
        auto CM {std::make_shared<ChatMember>("Ibrahim")};

        Cpp->subscribe(CCppM.get());
        Cpp->subscribe(CppM.get());

        C->subscribe(CCppM.get());
        C->subscribe(CM.get());

        Cpp->publish("C++23 standard isn't fully implmented by the compiler yet.");
        std::println("");
        C->publish("C23 standard have alot of new ideas including ones form C++.");

        return 0;
}
