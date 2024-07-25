#include <print>
#include <string>
#include <string_view>
#include <vector>
#include <ranges>
#include <algorithm>


class Canvas {
        std::vector<std::string_view> shapes;
public:
        auto addShape(const std::string_view newShape) -> void {
                shapes.push_back(newShape);
        }
        auto clearAll() -> void {
                shapes.clear();
        }
        auto getShapes() -> std::vector<std::string_view>& {
                return shapes;
        }
};


class CommandInterface {
public:
        virtual ~CommandInterface() {};
        virtual auto excute() -> void = 0;
}; 


class AddShapeCommand : public CommandInterface {
        std::string_view shapeName{};
        Canvas *canvas;
public:
        AddShapeCommand(std::string_view shapeName, Canvas * canvas) 
                : shapeName{shapeName},  
                canvas{canvas} {}
        auto excute() -> void override {
                canvas->addShape(shapeName);
        }
}; 


class ClearCommand : public CommandInterface {
        Canvas *canvas;
public:
        ClearCommand(Canvas * canvas) 
                : canvas{canvas} {}
        auto excute() -> void override {
                canvas->clearAll();
        }
}; 


class Button {
        CommandInterface *commandInterface;
public:
        Button(CommandInterface *commandInterface) : commandInterface{commandInterface} {}
        auto click() -> void {
                commandInterface->excute();
        }
};

auto vectorToString(std::vector<std::string_view> sv) -> std::string{
        std::string result{};
        std::ranges::for_each(sv, [&](auto && string) {
                result.append(string);
                result.append(" ");
        });
        return result;
}

auto main() -> int {
        Canvas *canvas = new Canvas;

        Button *addTriangleButton = new Button(new AddShapeCommand("triangle", canvas));
        Button *addSquareButton = new Button(new AddShapeCommand("square", canvas));
        Button *clearButton = new Button(new ClearCommand(canvas));

        addTriangleButton->click();
        std::println("Current canvas state: {}", vectorToString(canvas->getShapes()));
        addSquareButton->click();
        addSquareButton->click();
        addTriangleButton->click();
        std::println("Current canvas state: {}", vectorToString(canvas->getShapes()));
        clearButton->click();
        std::println("Current canvas state: {}", vectorToString(canvas->getShapes()));

        delete canvas;
        return 0;
}
