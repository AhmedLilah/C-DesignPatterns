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


class ButtonInterface {
public:
        virtual ~ButtonInterface() {};
        virtual auto click() -> void = 0;
};


class AddTriangleButton : public ButtonInterface {
        Canvas *canvas;
public:
        AddTriangleButton(Canvas *canvas) : canvas{canvas} {}
        auto click() -> void override {
                canvas->addShape("triangle");
        }
};


class AddSquareButton : public ButtonInterface {
        Canvas *canvas;
public:
        AddSquareButton(Canvas *canvas) : canvas{canvas} {};
        auto click() -> void override {
                canvas->addShape("square");
        }
};


class ClearButton : public ButtonInterface {
        Canvas *canvas;
public:
        ClearButton(Canvas *canvas) : canvas{canvas} {};
        auto click() -> void override {
                canvas->clearAll();
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

        AddTriangleButton *addTriangleButton = new AddTriangleButton(canvas);
	AddSquareButton *addSquareButton = new AddSquareButton(canvas);
	ClearButton *clearButton = new ClearButton(canvas);

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
