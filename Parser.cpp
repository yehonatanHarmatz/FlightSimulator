//
// Created by yehonatan on 04/01/2020.
//

#include "Parser.h"
#include "Commands/updateVarCommand.h"
#include "Commands/connectClientCommand.h"
#include "Commands/openDataServer.h"
#include "Commands/ifCommand.h"
#include "Commands/whileCommand.h"
#include "Commands/DefineVarCommand.h"
#include "Commands/PrintCommand.h"
#include "Commands/SleepCommand.h"

/**
 * run the program
 */
void Parser::parse() {
    this->initialize();
    int index = 0;
    while (index < (this->lexer_strings->size())) {
        command * c = this->getCommand(index);
        if (c!= nullptr) {
            index += c->execute(index + 1);
        }
    }
    ///stop the client and server loops
    connectClientCommand* ccc = dynamic_cast<connectClientCommand *>(this->commands.at("connectControlClient"));
    ccc->stopRunning();
    openDataServer* os = dynamic_cast<openDataServer *>(this->commands.at("openDataServer"));
    os->stopRun();
}
/**
 * get command by index
 * @param i index in the lexer vector
 * @return command
 */
command *Parser::getCommand(int i) {
    if (this->commands.find(this->lexer_strings->at(i)) != this->commands.end()) {
        return this->commands.at(this->lexer_strings->at(i));
    } else if (this->st->isVar(this->lexer_strings->at(i))){ ///the 'command' is var, so its mean its ver update value
        this->commands.insert(pair<string, command*>(this->lexer_strings->at(i),
                new updateVarCommand(this->lexer_strings, this->lexer_strings->at(i), this->st)));
        return this->commands.at(this->lexer_strings->at(i));
    }
    return nullptr;
}
/***
 * initialize:
 * create symbol table
 * create the command map
 */
void Parser::initialize() {
    this->st = new SymbolTable();
    openDataServer* os = new openDataServer(lexer_strings, st);
    connectClientCommand* ccc = new connectClientCommand(lexer_strings, st);
    ifCommand* ic = new ifCommand(lexer_strings, st, this);
    whileCommand* wc = new whileCommand(lexer_strings, st, this);
    DefineVarCommand* dvc = new DefineVarCommand(lexer_strings, st);
    PrintCommand* pc = new PrintCommand(lexer_strings, st);
    SleepCommand* sc = new SleepCommand(lexer_strings, st);
    this->commands = map<string, command*>();
    this->commands["openDataServer"] = os;
    this->commands["connectControlClient"] = ccc;
    this->commands["while"] = wc;
    this->commands["if"] = ic;
    this->commands["var"] = dvc;
    this->commands["Print"] = pc;
    this->commands["Sleep"] = sc;


}
