#pragma once
#include <stdexcept>
#include <string>
class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& msg) : std::runtime_error(msg) {}
};
class FileException : public GameException {
public:
    explicit FileException(const std::string& msg) : GameException("File error: " + msg) {}
};
class InventoryException : public GameException {
public:
    explicit InventoryException(const std::string& msg) : GameException("Inventory error: " + msg) {}
};