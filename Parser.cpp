//
// Created by yehonatan on 04/01/2020.
//

#include "Parser.h"
#include "Commands/updateVarCommand.h"
#include "Commands/connectClientCommand.h"
#include "Commands/openDataServer.h"
#include "Commands/ifCommand.h"
#include "Commands/whileCommand.h"

void Parser::parse() {
    this->initialize();
    int index = 0;
    while (index < (this->lexer_strings->size())) {
        command * c = this->getCommand(index);
        if (c!= nullptr) {
            index += c->execute(index + 1);
        }
    }
    connectClientCommand* ccc = dynamic_cast<connectClientCommand *>(this->commands.at("connectControlClient"));
    ccc->stopRunning();
    openDataServer* os = dynamic_cast<openDataServer *>(this->commands.at("openDataServer"));
    os->stopRun();
}

command *Parser::getCommand(int i) {
    if (this->commands.find(this->lexer_strings->at(i)) != this->commands.end()) {
        return this->commands.at(this->lexer_strings->at(i));
    } else if (this->st->isVar(this->lexer_strings->at(i))){
        this->commands.insert(pair<string, command*>(this->lexer_strings->at(i),
                new updateVarCommand(this->lexer_strings, this->lexer_strings->at(i), this->st)));
        return this->commands.at(this->lexer_strings->at(i));
    }
    return nullptr;
}

void Parser::initialize() {
    this->st = new SymbolTable();
    openDataServer* os = new openDataServer(lexer_strings, st);
    connectClientCommand* ccc = new connectClientCommand(lexer_strings, st);
    ifCommand* ic = new ifCommand(lexer_strings, st, this);
    whileCommand* wc = new whileCommand(lexer_strings, st, this);
    this->commands = map<string, command*>();
    this->commands["openDataServer"] = os;
    this->commands["connectControlClient"] = ccc;
    this->commands["while"] = wc;
    this->commands["if"] = ic;

}
