#include <functional>
#include <print>
#include <string>
#include <string_view>
#include <vector>
#include <ranges>
#include <algorithm>

using Canvas = std::vector<std::string_view>;
using Command = std::function<void(Canvas *)>;

inline auto addShape(std::string_view shapeName, Canvas *canvas) -> void {
        canvas->push_back(shapeName);
} 

inline auto addTriangle(Canvas *canvas) -> void {
        addShape("triangle", canvas);
} 

inline auto addSquare(Canvas *canvas) -> void {
        addShape("square", canvas);
} 

inline auto clearAll(Canvas *canvas) -> void {
        canvas->clear();
}

class Button {
        Canvas *canvas;
        Command command;
public:
        Button(Command command, Canvas * canvas) : command(command), canvas(canvas) {}
        inline auto click() const -> void {
                command(canvas);
        }
};

inline auto vectorToString(std::vector<std::string_view> sv) -> std::string{
        std::string result{};
        std::ranges::for_each(sv, [&](auto && string) {
                result.append(string);
                result.append(" ");
        });
        return result;
}

auto main() -> int {
        Canvas *canvas = new Canvas;

        Button * addTriangleButton = new Button(addTriangle, canvas);
        Button * addSquareButton = new Button(addSquare, canvas);
        Button * clearAllButton = new Button(clearAll, canvas);

        addTriangleButton->click();
        std::println("Current canvas state: {}", vectorToString(*canvas));
        addSquareButton->click();
        addSquareButton->click();
        addTriangleButton->click();
        std::println("Current canvas state: {}", vectorToString(*canvas));
        clearAllButton->click();
        std::println("Current canvas state: {}", vectorToString(*canvas));

        delete canvas;
        return 0;
}
