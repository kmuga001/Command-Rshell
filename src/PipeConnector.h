#ifndef PIPECONNECTOR_H
#define PIPECONNECTOR_H

#include "Command.h"
#include <string>

class PipeConnector : public Command {
    public:
    PipeConnector(string input) : Command(input){}

    int parseStr(int index){
        int i; /* returns the index value of the char value after ;*/
        for(i = index; i < commandVal.size(); ++i){
            if(commandVal.at(i) == '|'){
                return i + 1;
            }
        }
        return i;

    }

    bool isArgType() {
        return false;
    }

    string next(int index) { /*gives the remaining string after parsing*/
        string remaining = "";
        return commandVal.substr(index);
    }


     string getFullString(int i, int j){
         return "|";
     }

};

#endif
