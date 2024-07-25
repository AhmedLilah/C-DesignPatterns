#include <print>
#include <format>
#include <vector>
#include <ranges>
#include <algorithm>
#include <execution>

class ChatMember;

using ChatMessage = std::string;
using ChatGroup = std::vector<std::shared_ptr<ChatMember>>;

class ChatMember {
        std::string name;
public:
        ChatMember(std::string name) : name(std::move(name)) {}
        inline auto notify(ChatMessage msg, ChatGroup const & grp, std::string const & grpName) const {
                std::println("{} got a message from {} saying: {}", this->name, grpName, msg);
        }
};

inline auto publish(ChatMessage const & msg, ChatGroup &grp, std::string const & grpName) {
        std::ranges::for_each(grp, [msg, grp, grpName](std::shared_ptr<ChatMember> const &member){
                member->notify(msg, grp, grpName);
        });
}

inline auto subscribe(ChatGroup &grp, std::shared_ptr<ChatMember> member) {
        grp.push_back(member);
}

inline auto unsubscribe(ChatGroup &grp, std::shared_ptr<ChatMember> member) {
        if (auto pos = std::find(grp.begin(), grp.end(), member); pos != grp.end()) {
                grp.erase(pos);
        }
}

auto main() -> int {
        ChatGroup g1;
        ChatGroup g2;

        auto m1 {std::make_shared<ChatMember>("M1")};
        auto m2 {std::make_shared<ChatMember>("M2")};
        auto m3 {std::make_shared<ChatMember>("M3")};

        subscribe(g1, m1);
        subscribe(g1, m2);
        subscribe(g2, m2);
        subscribe(g2, m3);


        publish({"Welcome everyone."}, g1, {"G1"});
        publish({"Hi everbody."}, g2, {"G2"});


        return 0;
}
