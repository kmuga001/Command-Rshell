#ifndef ANDCONNECTOR_H
#define ANDCONNECTOR_H

#include "Command.h"
#include <string>

class AndConnector : public Command { /*Connector class does not need to exist*/
    public:
        AndConnector(string input) : Command(input) {}

        int parseStr(int index) {
            /*char str[] = commandVal;
 *             char* arg = strtok(str, " ");
 *                         int i = index; //need to go through the char index in the arg 
 *                                      now we have the index of the && operator*/
            int i;
            for(i = index; i < commandVal.size(); i++){
                if(commandVal.at(i) == '&' && commandVal.at(i+1) == '&' ){
                    return (i+2);
                }

            }

            return i;
        }

        bool isArgType() {
            return false;
        }

        string next(int index) { /*gives the remaining string after parsing*/
            string remaining = "";
            for(int i = index; i < commandVal.size(); i++){
                remaining += commandVal.at(i);
            }
            return remaining;
        }

        string getFullString(int i, int j){
            return "&&";
        }
};
#endif
