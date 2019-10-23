#ifndef COMMAND_H
#define COMMAND_H
#include <string>
using namespace std;
class Command{
    protected:
        string commandVal;

    public:
        Command(string input) : commandVal(input) {}
        virtual int parseStr(int index) = 0;
        virtual bool isArgType() = 0;
        virtual string next(int index) = 0;
        virtual string getFullString(int i, int j) = 0;
};
#endif
