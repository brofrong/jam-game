#include "State.h"

#include <stdexcept>

namespace NGame {

TVariable& TState::Variable(const std::string_view& name) {
    auto stringName = std::string(name);
    auto iterator = Variables_.find(stringName);

    if (iterator != Variables_.end()) {
        return iterator->second;
    } else {
        return SetVariable(name, 0);
    }
}

const TVariable& TState::Variable(const std::string_view& name) const {
    auto stringName = std::string(name);
    auto iterator = Variables_.find(stringName);

    if (iterator != Variables_.end()) {
        return iterator->second;
    }
    
    throw std::runtime_error("Attempting to access non-existing variable");
}

bool TState::ContainsVariable(const std::string_view& name) const {
    auto stringName = std::string(name);
    auto iterator = Variables_.find(stringName);

    if (iterator != Variables_.end()) {
        return true;
    }
    return false;
}

} // namespace NGame
