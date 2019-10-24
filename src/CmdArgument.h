#ifndef CMDARGUMENT_H
#define CMDARGUMENT_H
#include "Command.h"

#include <string>
/*This function is used to help us figure out how to organize the command arguments and return the proper string value*/
class CmdArgument : public Command {
    public:
        CmdArgument(string input) : Command(input) {}

        int parseStr(int index) { /*returns the index where there is a connector after parsing
            char str[] = commandVal;
            char* arg = strtok(str, " ");
            char fullArg[] = "";
            while((arg != NULL) && ((arg != "&&") || (arg != "||") || (arg != ";"))){
                go through arg and check to see if there is a semicolon, if there is STOP
                
            }*/
            int i;
            for(i = index; i < commandVal.size(); i++){
                if(commandVal.at(i) == '<' || commandVal.at(i) == '>' || commandVal.at(i) == '(' || commandVal.at(i) == ')' || commandVal.at(i) == '#' || commandVal.at(i) == '&' || commandVal.at(i) == '|' || commandVal.at(i) == ';'){
                        return i;
                }

            }
            return i;

        }


        bool isArgType(){
            return true;
        }

        string getFullString(int i, int j){
            string fullStr = "";
            for(int val = i; val < j; val++) {
                fullStr += commandVal.at(val);
            }
            return fullStr;
        }

        string next(int index) { /*gives the remaining string after parsing*/
            string remaining = "";
            for(int i = index; i < commandVal.size(); i++){
                remaining += commandVal.at(i);
            }
            return remaining;
        }


};
#endif
