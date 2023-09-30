#include "yyext/pch.h"
#include "yyext/Extension_Interface.h"
#include "yyext/YYRValue.h"
#include <iostream>
#include <string>
#include <vector>
#include "gmbuiltins.h"
#include "muParser.h"
#include "GMath.h"
#include <algorithm>

YYRunnerInterface gs_runnerInterface;
YYRunnerInterface* g_pYYRunnerInterface;
using std::string;
/* usage:
YYEXPORT void Example(RValue& Result, CInstance* selfinst, CInstance* otherinst, int argc, RValue* arg)
{
    double inc = YYGetReal(arg, 0);

	Result.kind = VALUE_REAL;
	Result.val = inc;
}
*/

bool _equation_exists(int id)
{
    if(equations.size() == 0) return false;
    if(equations.size() -1 < id) return false;
    if(equations.at(id) == nullptr) return false;
    return true;
}

YYEXPORT void YYExtensionInitialise(const struct YYRunnerInterface* _pFunctions, size_t _functions_size)
{
	 //copy out all the functions 
	memcpy(&gs_runnerInterface, _pFunctions, sizeof(YYRunnerInterface));
	g_pYYRunnerInterface = &gs_runnerInterface;
	if (_functions_size < sizeof(YYRunnerInterface)) {
		DebugConsoleOutput("ERROR : runner interface mismatch in extension DLL\n ");
	} // end if
	DebugConsoleOutput("YYExtensionInitialise CONFIGURED \n ");
}

double* create_equation_variable(const char* name, void* eq)
{
    if(isBuiltin(string(name)))
    {
        YYError((string("Math Parser Error: Equation variable names cannot match built in variables. Current invalid name is \"") + string(name) + string("\"")).c_str());
        return 0;
    }
    Equation* equation = (Equation*)eq;
    double* value = new double;
    *value = test_value;
    equation->variables[string(name)] = value;
    return value;
}

YYEXPORT void create_equation(RValue& Result, CInstance* selfinst, CInstance* otherinst, int argc, RValue* arg)
{
    string equationString = string(YYGetString(arg, 0));
    Equation* equation = new Equation;
    equation->parser = mu::Parser();
    std::replace( equationString.begin(), equationString.end(), '\n', ',');
    try
    {
        equation->parser.SetExpr(equationString);
        equation->parser.SetVarFactory(create_equation_variable, equation);
        equation->parser.Eval();

    }
    catch(mu::Parser::exception_type &e)
    {
        YYError((string("Math Parser Error: ")+e.GetMsg()).c_str());
    }
    equations.push_back(equation);
    Result.kind = VALUE_REAL;
    Result.val = equations.size() - 1;
}

YYEXPORT void eval_equation(RValue& Result, CInstance* selfinst, CInstance* otherinst, int argc, RValue* arg)
{
    int equationId = YYGetReal(arg, 0);
    // Check if the equation exists
    if(!_equation_exists(equationId))
    {
        YYError(("Math Parser Error: Equation with id " + std::to_string(equationId) + " does not exist.").c_str());
        return;
    }
    RValue* varStruct = YYGetStruct(arg, 1);
    const char* thing;
    int count;
    int num_keys = YYStructGetKeys(varStruct, NULL, NULL);
    std::vector<const char*> structKeys(num_keys);
    YYStructGetKeys(varStruct, structKeys.data(), &num_keys);
    Equation* equation = equations.at(equationId);
    for (const auto& pair : equation->variables) {
        if(std::find(structKeys.begin(), structKeys.end(), pair.first) == structKeys.end())
        {
//            YYError(("Math Parser Error: Variable " + string(pair.first) + " needed in equation but not passed in struct.").c_str());
            *(equation->variables[pair.first]) = NAN;
            continue;
        }
        RValue *member = YYStructGetMember(varStruct, pair.first.c_str());
        *(equation->variables[pair.first]) = member->val;
    }
    double result;
    try
    {
        result = equation->parser.Eval();
    }
    catch(mu::Parser::exception_type &e)
    {
        YYError((string("Math Parser Error: ")+e.GetMsg()).c_str());
        return;
    }
    if(isnan(result))
    {
        YYError("Math parser returned NAN! Check that you input all function variables.\nIf this is intended, please wrap the call in try/catch.");
        return;
    }
    Result.kind = VALUE_REAL;
    Result.val = result;
    
}

YYEXPORT void delete_equation(RValue& Result, CInstance* selfinst, CInstance* otherinst, int argc, RValue* arg)
{
    int equation = YYGetReal(arg, 0);
    if(!_equation_exists(equation)) return;
    equations.at(equation) = nullptr;
}

YYEXPORT void equation_exists(RValue& Result, CInstance* selfinst, CInstance* otherinst, int argc, RValue* arg)
{
    int equation = YYGetReal(arg, 0);
    Result.val = _equation_exists(equation);
    Result.kind = VALUE_BOOL;
}