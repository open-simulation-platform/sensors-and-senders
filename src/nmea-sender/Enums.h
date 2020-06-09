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


enum class Variability {
    Constant,
    Fixed,
    Tunable,
    Discrete,
    Continuous
};

enum class Type {
    Real,
    Integer,
    Boolean,
    String,
    Invalid
};

Type toType(const std::string& type);
Causality toCausality(const std::string& causality);