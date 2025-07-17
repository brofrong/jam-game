#pragma once

#include "Common.h"

#include "Variable.h"

#include <memory>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace NGame {

class TState {
public:
    TVariable& Variable(const std::string_view& name);
    const TVariable& Variable(const std::string_view& name) const;
    bool ContainsVariable(const std::string_view& name) const;
    
    template<typename T>
    TVariable& SetVariable(const std::string_view& name, const T& value) {
        auto stringName = std::string(name);
        auto result = Variables_.emplace(std::make_pair(stringName, value));
        if (result.second) {
            return result.first->second;
        }

        throw std::runtime_error("Failed to set variable");
    }

private:
    std::unordered_map<std::string, TVariable> Variables_;
};

} // namespace NGame