#pragma once

#include "Common.h"

#include <variant>
#include <string>

namespace NGame {

class TVariable {
public:
    TVariable() = default;

    template<typename T>
    TVariable(const T& value)
        : Data_(value) {
    }

    void SetDouble(double value);
    void SetString(const std::string& value);
    void SetInt(int value);
    void SetBool(bool value);

    double Double() const;
    std::string String() const;
    int Int() const;
    bool Bool() const;

private:
    std::variant<double, std::string, int, bool> Data_;
};

} // namespace NGame