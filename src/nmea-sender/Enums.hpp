#pragma once

#include <string>

enum class Causality {
    Parameter,
    CalculatedParameter,
    Input,
    Output,
    Local,
    Independent,
};

enum class Type {
    Real,
    Integer,
    Boolean,
    String,
    Invalid
};

Type to_type(const std::string& type);
Causality to_causality(const std::string& causality);