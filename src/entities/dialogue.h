#pragma once
#include <string>
#include <memory>
class Dialogue {
public:
    explicit Dialogue(const std::string& text) : text_(text) {}
    const std::string& getText() const { return text_; }
private:
    std::string text_;
};