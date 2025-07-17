#include "Variable.h"

namespace NGame {

void TVariable::SetDouble(double value) {
    Data_ = value;
}

void TVariable::SetString(const std::string& value) {
    Data_ = value;
}

void TVariable::SetInt(int value) {
    Data_ = value;
}

void TVariable::SetBool(bool value) {
    Data_ = value;
}

double TVariable::Double() const {  
    const auto asDouble = TOverload {
        [](int value) { return double(value); },
        [](double value) { return value; },
        [](const std::string value) { 
            try {
                return std::stod(value);
            } catch (...) {
                return 0.0;
            }
        },
        [](bool value) { return double(value); }
    };

    return std::visit(asDouble, Data_);
}

std::string TVariable::String() const {
    const auto asString = TOverload {
        [](int value) { return std::to_string(value); },
        [](double value) { return std::to_string(value); },
        [](const std::string value) { return value; },
        [](bool value) { return std::to_string(value); }
    };

    return std::visit(asString, Data_);
}

int TVariable::Int() const {
    const auto asInt = TOverload {
        [](int value) { return value; },
        [](double value) { return int(value); },
        [](const std::string value) { 
            try {
                return std::stoi(value); 
            } catch (...) {
                return 0;
            }
        },
        [](bool value) { return int(value); }
    };

    return std::visit(asInt, Data_);
}

bool TVariable::Bool() const {
    const auto asBool = TOverload {
        [](int value) { return value != 0; },
        [](double value) { return value != 0; },
        [](const std::string value) { 
            std::string caseFolded = ToUpper(Trim(value));
            if (caseFolded == "TRUE") {
                return true;
            }
            return false;
        },
        [](bool value) { return value; }
    };

    return std::visit(asBool, Data_);
}

} // namespace NGame
