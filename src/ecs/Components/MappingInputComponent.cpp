/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** MappingInput Component methods
*/

#include "MappingInputComponent.hh"

RType::MappingInputComponent::MappingInputComponent()
{
    initInput();
}

void RType::MappingInputComponent::setMappingInput(MappingInput key, sf::Keyboard::Key newKey)
{
    if (newKey != sf::Keyboard::Key::Unknown) {
        // clearInput(newKey);
    }
	_inputs[key] = newKey;
}

sf::Keyboard::Key RType::MappingInputComponent::getMappingInput(MappingInput key) const
{
	return _inputs.at(key);
}

const std::unordered_map<RType::MappingInput, sf::Keyboard::Key>& RType::MappingInputComponent::getMappingInputs() const
{
	return _inputs;
}

void RType::MappingInputComponent::initInput(void)
{
    _inputs.insert(std::make_pair(INPUT_UP, sf::Keyboard::Up));
    _inputs.insert(std::make_pair(INPUT_DOWN, sf::Keyboard::Down));
    _inputs.insert(std::make_pair(INPUT_LEFT, sf::Keyboard::Left));
    _inputs.insert(std::make_pair(INPUT_RIGHT, sf::Keyboard::Right));
    _inputs.insert(std::make_pair(INPUT_SHOOT, sf::Keyboard::Space));
}

void RType::MappingInputComponent::clearInput(sf::Keyboard::Key key)
{
    for (auto it = _inputs.begin(); it != _inputs.end(); ++it)
        if (it->second == key)
            _inputs[it->first] = sf::Keyboard::Key::Unknown;
}

std::string RType::MappingInputComponent::getKeyName(sf::Keyboard::Key key)
{
    switch (key) {
        case sf::Keyboard::A: return "A";
        case sf::Keyboard::B: return "B";
        case sf::Keyboard::C: return "C";
        case sf::Keyboard::D: return "D";
        case sf::Keyboard::E: return "E";
        case sf::Keyboard::F: return "F";
        case sf::Keyboard::G: return "G";
        case sf::Keyboard::H: return "H";
        case sf::Keyboard::I: return "I";
        case sf::Keyboard::J: return "J";
        case sf::Keyboard::K: return "K";
        case sf::Keyboard::L: return "L";
        case sf::Keyboard::M: return "M";
        case sf::Keyboard::N: return "N";
        case sf::Keyboard::O: return "O";
        case sf::Keyboard::P: return "P";
        case sf::Keyboard::Q: return "Q";
        case sf::Keyboard::R: return "R";
        case sf::Keyboard::S: return "S";
        case sf::Keyboard::T: return "T";
        case sf::Keyboard::U: return "U";
        case sf::Keyboard::V: return "V";
        case sf::Keyboard::W: return "W";
        case sf::Keyboard::X: return "X";
        case sf::Keyboard::Y: return "Y";
        case sf::Keyboard::Z: return "Z";
        case sf::Keyboard::Num0: return "0";
        case sf::Keyboard::Num1: return "1";
        case sf::Keyboard::Num2: return "2";
        case sf::Keyboard::Num3: return "3";
        case sf::Keyboard::Num4: return "4";
        case sf::Keyboard::Num5: return "5";
        case sf::Keyboard::Num6: return "6";
        case sf::Keyboard::Num7: return "7";
        case sf::Keyboard::Num8: return "8";
        case sf::Keyboard::Num9: return "9";
        case sf::Keyboard::Escape: return "Escape";
        case sf::Keyboard::LControl: return "Left Control";
        case sf::Keyboard::LShift: return "Left Shift";
        case sf::Keyboard::LAlt: return "Left Alt";
        case sf::Keyboard::LSystem: return "Left System";
        case sf::Keyboard::RControl: return "Right Control";
        case sf::Keyboard::RShift: return "Right Shift";
        case sf::Keyboard::RAlt: return "Right Alt";
        case sf::Keyboard::RSystem: return "Right System";
        case sf::Keyboard::Menu: return "Menu";
        case sf::Keyboard::LBracket: return "[";
        case sf::Keyboard::RBracket: return "]";
        case sf::Keyboard::Semicolon: return ";";
        case sf::Keyboard::Comma: return ",";
        case sf::Keyboard::Period: return ".";
        case sf::Keyboard::Apostrophe: return "'";
        case sf::Keyboard::Slash: return "/";
        case sf::Keyboard::Backslash: return "\\";
        case sf::Keyboard::Grave: return "`";
        case sf::Keyboard::Equal: return "=";
        case sf::Keyboard::Hyphen: return "-";
        case sf::Keyboard::Space: return "Space";
        case sf::Keyboard::Enter: return "Enter";
        case sf::Keyboard::Backspace: return "Backspace";
        case sf::Keyboard::Tab: return "Tab";
        case sf::Keyboard::PageUp: return "Page Up";
        case sf::Keyboard::PageDown: return "Page Down";
        case sf::Keyboard::End: return "End";
        case sf::Keyboard::Home: return "Home";
        case sf::Keyboard::Insert: return "Insert";
        case sf::Keyboard::Delete: return "Delete";
        case sf::Keyboard::Add: return "+";
        case sf::Keyboard::Subtract: return "-";
        case sf::Keyboard::Multiply: return "*";
        case sf::Keyboard::Divide: return "/";
        case sf::Keyboard::Left: return "Left Arrow";
        case sf::Keyboard::Right: return "Right Arrow";
        case sf::Keyboard::Up: return "Up Arrow";
        case sf::Keyboard::Down: return "Down Arrow";
        case sf::Keyboard::Numpad0: return "Numpad 0";
        case sf::Keyboard::Numpad1: return "Numpad 1";
        case sf::Keyboard::Numpad2: return "Numpad 2";
        case sf::Keyboard::Numpad3: return "Numpad 3";
        case sf::Keyboard::Numpad4: return "Numpad 4";
        case sf::Keyboard::Numpad5: return "Numpad 5";
        case sf::Keyboard::Numpad6: return "Numpad 6";
        case sf::Keyboard::Numpad7: return "Numpad 7";
        case sf::Keyboard::Numpad8: return "Numpad 8";
        case sf::Keyboard::Numpad9: return "Numpad 9";
        case sf::Keyboard::F1: return "F1";
        case sf::Keyboard::F2: return "F2";
        case sf::Keyboard::F3: return "F3";
        case sf::Keyboard::F4: return "F4";
        case sf::Keyboard::F5: return "F5";
        case sf::Keyboard::F6: return "F6";
        case sf::Keyboard::F7: return "F7";
        case sf::Keyboard::F8: return "F8";
        case sf::Keyboard::F9: return "F9";
        case sf::Keyboard::F10: return "F10";
        case sf::Keyboard::F11: return "F11";
        case sf::Keyboard::F12: return "F12";
        case sf::Keyboard::F13: return "F13";
        case sf::Keyboard::F14: return "F14";
        case sf::Keyboard::F15: return "F15";
        case sf::Keyboard::Pause: return "Pause";
        default: return "Unknown";
    }
}


std::string RType::MappingInputComponent::getOutput() const
{
    std::string output("Mapping input Component ()");
    return (output);
}

