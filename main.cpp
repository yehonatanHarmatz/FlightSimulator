#include <iostream>
#include "laxer.h"
#include "SymbolTable.h"
#include "Expression/Interpreter.h"
#include "Expression/Div.h"
#include "Expression/Value.h"
#include "Parser.h"

using namespace std;

int main() {
    laxer l = laxer();
    vector<string> v = l.laxe("fly.txt");
    Parser p = Parser(&v);
    p.parse();
    return 0;
}
