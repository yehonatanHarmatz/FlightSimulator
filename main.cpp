#include <iostream>
#include "lexer.h"
#include "SymbolTable.h"
#include "Expression/Interpreter.h"
#include "Expression/Div.h"
#include "Expression/Value.h"
#include "Parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    lexer l = lexer();
    vector<string> v = l.laxe(argv[1]);
    Parser p = Parser(&v);
    p.parse();
    return 0;
}
