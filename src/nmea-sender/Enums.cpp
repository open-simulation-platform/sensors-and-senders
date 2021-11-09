#include "Enums.hpp"

#include <map>

Type to_type(const std::string& type) {

    static const std::map<std::string, Type> type_map {
        {"Real", Type::Real},
        {"Integer", Type::Integer},
        {"String", Type::String},
        {"Boolean", Type::Boolean}
    };

    return type_map.at(type);
}

Causality to_causality(const std::string& causality) {

    static const std::map<std::string, Causality> c_map { 
        {"input", Causality::Input},
        {"output", Causality::Output},
        {"parameter", Causality::Parameter},
        {"calculatedParameter", Causality::CalculatedParameter},
        {"local", Causality::Local},
        {"independent", Causality::Independent} 
    };

    return c_map.at(causality);
}