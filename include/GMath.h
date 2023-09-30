#pragma once
#include <vector>
#include "muParser.h"
#include <unordered_map>
#include <string>


class Equation
{
public:
    mu::Parser parser;
    std::unordered_map<std::string, double*> variables;
    ~Equation(){
        for (const auto& pair : variables) {
            delete variables[pair.first];
        }
    }
};

std::vector<Equation*> equations;
double test_value = 1;