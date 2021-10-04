#include "Enums.hpp"

#include <map>

Type toType(const std::string& type) {

    static const std::map<std::string, Type> typeMap {
        {"Real", Type::Real},
        {"Integer", Type::Integer},
        {"String", Type::String},
        {"Boolean", Type::Boolean}
    };

    return typeMap.at(type);
}

Causality toCausality(const std::string& causality) {

    static const std::map<std::string, Causality> cMap { 
        {"input", Causality::Input},
        {"output", Causality::Output},
        {"parameter", Causality::Parameter},
        {"calculatedParameter", Causality::CalculatedParameter},
        {"local", Causality::Local},
        {"independent", Causality::Independent} 
    };

    return cMap.at(causality);
}