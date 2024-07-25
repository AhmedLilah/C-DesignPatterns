#include <print>
#include <memory>
#include <array>

struct UIState {
        bool nameTextboxVisibility{true};
        bool isMarriedCheckboxVisibility{true};
        bool spousesNameTextBoxVisibility{false};
        bool submitButtonVisibility{false};
};

void mediate(const std::string & event, UIState *state);

class InterfaceElement {
protected:
        std::string name;
        bool &isVisible;
        UIState *state;
public:
        InterfaceElement(const std::string & name, bool &isVisible, UIState *state) 
                : name(name), isVisible(isVisible), state(state) {};
        void setVisibility(bool isVisible) { this->isVisible = isVisible; };
        std::string getDescription() {
                return isVisible
                ? name + " is visible"
                : name + " is NOT visible";
        }
};

class ButtonElement : public InterfaceElement {
public:
        ButtonElement(const std::string & name, bool &isVisible, UIState *state) 
                : InterfaceElement(name, isVisible, state) {};
        virtual ~ButtonElement() {};
        virtual void click() {
                mediate(name + " clicked", state);
        };
};

class TextBox : public InterfaceElement {
        std::string textValue = "";
public:
        TextBox(const std::string & name, bool &isVisible, UIState *state) 
                : InterfaceElement(name, isVisible, state) {};
        virtual ~TextBox() {};
        virtual void changeText(const std::string & newValue) {
                textValue = newValue;
                if (newValue.empty()) {
                        mediate(name + " empty", state);
                } else {
                        mediate(name + " not empty", state);
                }
        };
};

class CheckBox : public InterfaceElement {
        bool isChecked = false;
public:
        CheckBox(const std::string & name, bool &isVisible, UIState *state) 
                : InterfaceElement(name, isVisible, state) {};
        virtual ~CheckBox() {};
        virtual void setIsChecked(bool isChecked) {
                this->isChecked = isChecked;

                if (isChecked) {
                        mediate(name + " is checked", state);
                } else {
                        mediate(name + " is unchecked", state);
                }
        };
};

int main(int argc, const char * argv[]) {
        auto state {new UIState};

        auto nameTextBox{new TextBox("Name textbox", state->nameTextboxVisibility, state)};
        auto isMarriedCheckbox{new CheckBox("Is married checkbox", state->isMarriedCheckboxVisibility, state)};
        auto spousesNameTextBox{new TextBox("Spouse's name textbox", state->spousesNameTextBoxVisibility, state)};
        auto submitButton{new ButtonElement("Submit button", state->submitButtonVisibility, state)};
        std::array<InterfaceElement *, 4> elements {nameTextBox, isMarriedCheckbox, spousesNameTextBox, submitButton};
        for (auto element : elements) {
                std::println("{}", element->getDescription());
        }

        isMarriedCheckbox->setIsChecked(true);

        for (auto element : elements) {
                std::println("{}", element->getDescription());
        }

        delete state;
        return 0;
}

void mediate(const std::string & event, UIState *state) {
        std::println("Mediating event: {}...", event);
        if (event == "Name textbox is empty") {
                state->submitButtonVisibility = false;
        } else if (event == "Name textbox is not empty") {
                state->submitButtonVisibility = true;
        } else if (event == "Is married checkbox is checked") {
                state->spousesNameTextBoxVisibility = true;
        } else if (event == "Is married checkbox is unchecked") {
                state->spousesNameTextBoxVisibility = false;
                std::println("Submitted!");
        } else {
                std::println("Unrecognized event!");
        }
}
