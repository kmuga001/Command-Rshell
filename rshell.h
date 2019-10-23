#ifndef RSHELL_H
#define RSHELL_H
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Command.h"
#include "CmdArgument.h"
#include "AndConnector.h"
#include "OrConnector.h"
#include "SemicolonConnector.h"
#include "OpenParConnector.h"
#include "CloseParConnector.h"
#include "SingleOutConnector.h"
#include "SingleInputConnector.h"
#include "DoubleOutConnector.h"
#include "PipeConnector.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

class Rshell {
    protected:
        vector<string> vec;
        string cVal;
    public:
        Rshell(string input) : cVal(input) {} /*only need to worry about cVal and we will define vec in buildVector() function*/

        void buildVector() {
            int i = 0;
            int initial = 0;
            //int tempSize = cVal.size(); 
            while(i < cVal.size()){ /*want to go through the entire string and organize into the vec*/
                Command* cAr = new CmdArgument(cVal);
                initial = cAr->parseStr(i); /*this function will return the index where it reaches a connector*/
                /*if(initial < cVal.size()) {
                        if(cVal.at(initial) == ' ') {
                                initial = initial - 1;
                        }
                }*/
                vec.push_back(cAr->getFullString(i, initial)); /*getFullString gives the string before the connector*/
                //need to execute whatever is in this vector element NOW, create the args here! (first word = command, whatever left are the parameters for the command)
                int a = initial;
                if((initial) < cVal.size()){ /* checks if initial is in range*/
                         if(cVal.at(initial) == '&' && cVal.at(initial + 1) == '&'){
                                cVal = cVal.substr(initial - 1);
                                initial = 0; /* need to reset initial every time we use substr()*/
                                Command* andAr = new AndConnector(cVal);
                                a = andAr->parseStr(initial);
                                cVal = cVal.substr(a);
                                a = 0;/* need to reset a because substr() starts index at 0*/
                                string andA = "&&";
                                vec.push_back(andA);
                                i = a;

                         } else if(cVal.at(initial) == '|' && cVal.at(initial + 1) == '|'){
                                cVal = cVal.substr(initial);/* same as && if statement*/
                                initial = 0;
                                Command* orAr = new OrConnector(cVal);
                                a = orAr->parseStr(initial);
                                cVal = cVal.substr(a);
                                a = 0;
                                string orA = "||";
                                vec.push_back(orA);
                                i = a;

                         } else if(cVal.at(initial) == '>' && cVal.at(initial + 1) == '>') {
                                cVal = cVal.substr(initial);
                                initial = 0;
                                Command* doubleOut = new DoubleOutConnector(cVal);
                                a = doubleOut->parseStr(initial);
                                cVal = cVal.substr(a);
                                a = 0;
                                string dOut = ">>";
                                vec.push_back(dOut);
                                i = a;

                         } else if(cVal.at(initial) == '>') {
                                cVal = cVal.substr(initial);
                                initial = 0;
                                Command* singleOut = new SingleOutConnector(cVal);
                                a = singleOut->parseStr(initial);
                                cVal = cVal.substr(a);
                                a = 0;
                                string sOut = ">";
                                vec.push_back(sOut);
                                i = a;
                         } else if(cVal.at(initial) == '<') {
                                cVal = cVal.substr(initial);
                                initial = 0;
                                Command* singleInput = new SingleInputConnector(cVal);
                                a = singleInput->parseStr(initial);
                                cVal = cVal.substr(a);
                                a = 0;
                                string sInp = "<";
                                vec.push_back(sInp);
                                i = a;

                         } else if(cVal.at(initial) == ';') {
                                cVal = cVal.substr(initial);/* same as ; except dont worry about next char*/
                                initial = 0;
                                Command* semAr = new SemicolonConnector(cVal);
                                a = semAr->parseStr(initial);
                                cVal = cVal.substr(a);
                                string semiA = ";";
                                a = 0;
                                vec.push_back(semiA);
                                i = a;
                         } else if(cVal.at(initial) == '#') {
                                cVal = cVal.substr(initial);/*# should basically stop the next commands*/
                                initial = 0;
                                a = initial + 1;
                                //cVal = cVal.substr(a);
                                string hash = "#";
                                a = cVal.size();

                                vec.push_back(hash);
                                break;
                                i = a;
                         } else if(cVal.at(initial) == '|') {
                                cVal = cVal.substr(initial);
                                initial = 0;
                                Command* pipe = new PipeConnector(cVal);
                                a = pipe->parseStr(initial);
                                cVal = cVal.substr(a);
                                a = 0;
                                string pipes = "|";
                                vec.push_back(pipes);
                                i = a;

                         } else if(cVal.at(initial) == '(') {
                                //cout << " there is '(' " << endl;
                                cVal = cVal.substr(initial);
                                initial = 0;
                                Command* openP = new OpenParConnector(cVal);
                                a = openP->parseStr(initial);
                                cVal = cVal.substr(a);
                                string opening = "(";
                                a = 0;
                                vec.push_back(opening);
                                i = a;

                         } else if(cVal.at(initial) == ')') {
                               // cout << " there is ')' " << endl;
                                cVal = cVal.substr(initial);
                                initial = 0;
                                Command* closeP = new CloseParConnector(cVal);
                                a = closeP->parseStr(initial);
                                cVal = cVal.substr(a);
                                string closing = ")";
                                a = 0;
                                vec.push_back(closing);
                                i = a;
                         } else {
                                i = a;
                         }
                }
                i = a;
            }

            //cout << "vec(0) build vec: " << vec.at(0) << endl;
            //vector<int> testingit = createSpaceIndexVec(vec.at(0));
        }


        bool checkEqualParenth(vector<string> v) {
                int countO = 0;
                int countC = 0;
                for(int i = 0; i < v.size(); i++) {
                        if(v.at(i) == "(") {
                                countO++;
                        }
                        if(v.at(i) == ")") {
                                countC++;
                        }
                }
                if(countO == countC) {
                        return true;
                } else {
                        return false;
                }
        }

        void print() {/* just to check if the vec organized the cVal correctly*/
            for(int i = 0; i < vec.size(); i++){
                cout << "vec.at(i): " << vec.at(i) << endl;
            }

        }


        int miniExecute(string str) {
                     if(str == "exit " || str == " exit" || str == "exit") {
                         exit(0);
                      }
                      int val = 0;
                      int pid = fork();
                      int status;
                      /*vector<char*> charg(aVec.size()+1);
                      for(int i = 0; i < aVec.size(); ++i){
                           charg[i] = &aVec[i][0];
                      }*/
                      if(pid < 0) {
                           perror("error w/ forking");
                           val = -1;
                           exit(1);
                      }
                      else if(pid > 0) {
                           if (waitpid(-1,&status,0) == -1){
                                perror("error w/ waitpid");
                                val = -1;
                           }
                      }
                      else {
                           if((str.at(0) == 't' && str.at(1) == 'e' && str.at(2) == 's' && str.at(3) == 't') || str.at(0) == '['){
                              val = testCommand(str);
                              return val;
                           }

                           //cout << "charg[0]: " << charg[0] << endl;
                           //int exec = execvp(aVec.at(0).c_str(),&charg);
                           //char *argv[] = {"echo", "hello", "world", NULL};
                           const char* strChar = str.c_str();
                  //         cout << "before creating ArgsArray. " << endl;
                           char** argv = createArgsArray(strChar);
                         //  cout << "argv[0]: " << argv[0] << endl;
                           int exec = execvp(argv[0], argv);
                           if(exec == -1) {
                                perror("error w/ execvp");
                                val = 0;
                                return -1;
                                exit(1);

                           }

                      }
                      return val;


        }
        bool zeroParenth() {
                int count = 0;
                for(int i = 0; i < vec.size(); i++) {
                        if((vec.at(i) == "(") || (vec.at(i) == ")")) {
                                return false;
                        }
                }
                return true;
        }

        int mainExecute() {
                int execMin = 0;
                //cout << "vec at 0: " << vec.at(0) << endl;
                //print();
                /*if(vec.at(0) == "") {
                        return -1;
                } */
                if(vec.at(0) == "&&" || vec.at(0) == "||" || vec.at(0) == ";" || vec.at(0) == "#") {
                        //perror("no commands entered");
                        return -1;
                }
                //cout << vec.at(0) << endl;
                vector<string> executeVec;
                bool pCheck = checkEqualParenth(vec);
                if(pCheck == false) {
                        perror("uneven parentheses");
                        return -1;
                } else {
                        stack<string> stack;
                        int i = 0;
                        //int execMin = 0;
                        if(zeroParenth() == true) {
                                //executeVec.push_back(stack.top());
                                execMin = execute(vec);
                                return execMin;
                        }
                           //cout << "not zero" << endl;
                           while((i < vec.size()) && (execMin != -1)) {
                                if((i - 1) >= 0) {
                                        if((vec.at(i) == "||") && (vec.at(i - 1) == " ")) {
                                                if(execMin != -1) {
                                                        i++;
                                                        int orVal = i;
                                                        while(orVal < vec.size()){
                                                                if(vec.at(orVal) == ")"){
                                                                        i++;
                                                                        break;
                                                                }
                                                                i++;
                                                                orVal = i;
                                                        }
                                                        continue;
                                                }
                                        }

                                }
                                stack.push(vec.at(i));
                                //cout << "stack top: " << stack.top() << endl;
                                //cout << "inside mainExecute while: " << stack.top() << endl;
                                //cout << "zeroParen: " << zeroParenth() << endl;
                                if(zeroParenth() == true) {
                                        //cout << "zero parentheses" << endl;
                                        executeVec.push_back(stack.top());
                                        execMin = execute(executeVec);
                                        //break;
                                } else if(stack.top() == ")") {
                                        //cout << "closed stack top: " << stack.top() << endl;
                                        //i++;
                                        stack.pop();
                                        //cout << "there is a closed parenthesis" << endl;
                                        //cout << "stack top before != " << stack.top();
                                        while(stack.top() != "("){
                                                executeVec.push_back(stack.top());
                                                stack.pop();
                                        }
                                        if(stack.top() == "(") {
                                                stack.pop();
                                        }
                                        reverse(executeVec.begin(), executeVec.end());
                                        execMin = execute(executeVec);
                                        executeVec.clear();
                                }
                                i++;

                           }


                }
                return execMin;
        }


        int execute(vector<string> ve){ /*the function to actually execute the commands*/
          // int pid = fork(); 
           /*exit command; exits when prompted*/
           // if (vec.at(0) == "exit"){
           //     exit(0);
           // }
            if (ve.at(0) == ""){
               // perror("nothing entered");
                return -1;

            }
            /* exits if the only string is a connector*/
            if (ve.at(0) == "&&" || ve.at(0) == "||" || ve.at(0) == ";"){
                perror("no commands entered");
                return -1;
            }
            int x = 0;
           // if(pid == 0){
            for(int i = 0; i < ve.size(); i++) {
               /* if(vec.at(i) == " "){
                     if(vec.at(i+1) == "&" && vec.at(i+2) == "&"){
                        i = i + 4;
                        x = miniExecute(vec.at(i));
                     }
                }*/
               // if (vec.at(i) == "exit"){
               //     exit(0);
               // }
                if(ve.at(i) != "|" && ve.at(i) != "#" && ve.at(i) != "<" && ve.at(i) != ">>" && ve.at(i) != "&&" && ve.at(i) != "||" && ve.at(i) != ";" && ve.at(i) != ">") {
                     //cout << "inside the EXECUTE" << endl;
                     if((i + 2) < ve.size()) {
                        //cout << "VEC size: " << ve.size() << endl;
                        if(ve.at(i + 1) == "<") {
                                /*command before < will process the file and result is displayed*/
                                x = miniExecuteOut(ve.at(i), ve.at(i+2));
                                i = i+3;
                                continue;
                        } else if(ve.at(i+1) == "|") {
                                x = miniExecutePipe(ve.at(i), ve.at(i+2));
                                i = i+3;
                                continue;
                        } else if(ve.at(i + 1) == ">") {
                                /*command is executed and the results are written to the file, is overwritten!!*/
                                //cout << "it is in >" << endl;
                                x = miniExecuteIn(ve.at(i), ve.at(i+2));
                               // cout << "after mini execute "<< endl;
                                 i = i + 3;
                                //cout << "i valueeeeeee: " << i << endl;
                                continue;
                        } else if(ve.at(i + 1) == ">>") {                                                                                                                  /*command is executed and the results are APPENDED to file, file is created if doesn't exist */
                                x = miniExecuteDoubleIn(ve.at(i), ve.at(i+2));
                                i = i+3;
                                continue;
                        } else {
                                x = miniExecute(ve.at(i));
                                continue;
                        }
                    } else {
                     //cout << "we are in normal" << endl;
                     x = miniExecute(ve.at(i));
                     continue;
                    }
                } else {
                        x = 0;
                        continue;
                }
                if((i+1) != ve.size()){
                        if(ve.at(i+1) == "&&") {
                                if(x != -1) {
                                        if((i+2) != ve.size()) {
                                                continue; /* can execute upcoming command */
                                        }
                                } else {

                                        if((i+2) != ve.size()) {
                                                i = i + 3;
                                                continue;
                                        }

                                }
                        } else if(ve.at(i+1) == "||") {
                                if(x == -1) {
                                        if((i+2) != ve.size()) {
                                                continue; /* can execute upcoming command */
                                        }
                                } else {
                                        if((i+2) != ve.size()) {
                                                i = i + 3;
                                                continue;
                                        }
                                }

                        } else if(ve.at(i+1) == ";") {
                                continue;
                        }
                } else {
                        continue;
                }

                /*if(ve.at(i) != "<" && ve.at(i) != ">>" && ve.at(i) != ">") {
                        x = miniExecute(ve.at(i));
                } else {
                        x = 0;
                        continue;
                }*/
               /*       if((i + 2) != ve.size()) {
                        if(ve.at(i + 1) == "<") {
                                //command before < will process the file and result is displayed
                                
                        } else if(ve.at(i + 1) == ">") {
                                //command is executed and the results are written to the file, is overwritten!!
                                //cout << "it is in >" << endl;
                                x = miniExecuteIn(ve.at(i), ve.at(i+2));
                                i = i + 3;
                        } else if(ve.at(i + 1) == ">>") {
                                //command is executed and the results are APPENDED to file, file is created if doesn't exist 
                        }
                }*/
            }
           // }
            return x;
        }
        int miniExecuteIn(string str, string fileName) {
                int val = 0;
                string actualFile = fileName;
                while(actualFile[0] == ' '){
                    actualFile = actualFile.substr(1);
                }
                int pid = fork();
                int pipe(int pipefd[2]);
                if(pid ==0 ){
                int out = open(actualFile.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                if (out < 0){
                    perror("open");
                    exit(1);
                }
                int d = dup2(out, 1);
                if (d < 0){
                    perror("dup2");
                    exit(1);
                }
                close(out);
                const char* strChar = str.c_str();
                char** argv = createArgsArray(strChar);
                execvp(argv[0], argv);
               perror("execvp");
               }
                return -1;
        }

        int miniExecutePipe(string str, string str2) {
                int pipefd[2];
                int pid;
                int val = 0;
                pipe(pipefd);
                pid = fork();
                if(pid == 0) {
                        dup2(pipefd[0], 0);
                        close(pipefd[1]);
                        const char* strChar = str.c_str();
                        char** argv = createArgsArray(strChar);
                        int ex = execvp(argv[0], argv);
                        //cout << "WHAAAAAT" << endl;
                        if(ex == -1) {
                                perror("execvp error");
                                return -1;
                                exit(1);
                        }

                } else {
                        //cout << "WHAT PIPINGGGG" << endl;
                        dup2(pipefd[1], 1);
                        //cout << "DID DUP2 HAPPEN?" << endl;
                        close(pipefd[1]);
                        //cout << "STRCCCCCCCC: " << str2 << endl;
                        const char* strC = str2.c_str();
                        char** argV = createArgsArray(strC);
                        int e = execvp(argV[0], argV);
                        if(e == -1) {
                                perror("execvp error");
                                return -1;
                                exit(1);
                        }
                }
                return val;
        }

        int miniExecuteDoubleIn(string str, string fileName) {
                int val = 0;
                string actualFile = fileName;
                while(actualFile[0] == ' '){
                    actualFile = actualFile.substr(1);
                }
                int pid = fork();
                int pipe(int pipefd[2]);
                if(pid ==0 ){
                int out = open(actualFile.c_str(), O_WRONLY | O_CREAT | O_APPEND);
                if (out < 0){
                    perror("open");
                    exit(1);
                }
                int d = dup2(out, 1);
                if (d < 0){
                    perror("dup2");
                    exit(1);
                }
                close(out);
                const char* strChar = str.c_str();
                char** argv = createArgsArray(strChar);
                execvp(argv[0], argv);
                perror("execvp");
               }
                return -1;
        }


        int miniExecuteOut(string str, string fileName) {
                int val = 0;
                string actualFile = fileName;
                while(actualFile[0] == ' '){
                    actualFile = actualFile.substr(1);
                }
               // int pid = fork();
                int pipe(int pipefd[2]);
                //if(pid ==0 ){
                //int out = open("newOutputFile2", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                int in = open(actualFile.c_str(), O_RDONLY);
                if (in < 0){
                    perror("open");
                    exit(1);
                }
                int d = dup2(in, 0);
                if (d < 0){
                    perror("dup2");
                    exit(1);
                }
                close(in);
                const char* strChar = str.c_str();
                char** argv = createArgsArray(strChar);
                execvp(argv[0], argv);
                perror("execvp");
               // }
                return -1;
        }

        vector<int> createSpaceIndexVec(string sample) {
                /*vector<int> spaceVector;
                for(int i = 0; i < sample.size(); i++) {
                        if(sample.at(i) == ' ') {
                                spaceVector.push_back(i);
                        } else {
                                continue;
                        }
                
                }*/
                /*for(int i = 0; i < spaceVector.size(); i++) {
                        cout << spaceVector.at(i);
                }
                cout << endl;*/
                vector<int> spaceVector;
                string search = " ";
                int position = sample.find(search);
                while(position != -1) {
                        spaceVector.push_back(position);

                        position = sample.find(search, position + search.size());
                }
                return spaceVector;
        }
        char** createArgsArray(const char* str) {
                //char** comArgs = malloc(sizeof(char*)*9);
                char** comArgs = new char*[3];
                for(int i = 0; i < 3; i++) {
                        comArgs[i] = new char;
                }
                char* strCh = strdup(str);
                string space = " ";
                const char* spaceChar = space.c_str();
                int ind = 0;
                char* args = strtok(strCh, spaceChar);
                while(args != NULL) {
                        comArgs[ind] = args;
                        ind += 1;
                        args = strtok(NULL, spaceChar);
                }
                comArgs[ind] = NULL;
                //free(strCh);
                return comArgs;
        }
        
        int testCommand(string c){
            vector<string> micro(c.size());
            int wordcount = 1;
            int j = 0;
            int s = 0;
            for(int i = 0; i < c.size(); ++i){
                if(c.at(i) == ' '){
                    ++wordcount;
                    micro.at(j) = c.substr(s, i-s);
                    s = i+1;
                    ++j;
                    if(c.substr(s).find(' ') == string::npos){
                        micro.at(j) = c.substr(s);
                        break;
                     }
                  }
              }
              char **vchar = new char*[wordcount+1];
              for(int i = 0; i < wordcount; ++i){
                  vchar[i] = new char[micro.at(i).size() + 1];
                  std::strcpy(vchar[i], micro.at(i).c_str());
              }
               vchar[wordcount] = '\0';
               struct stat sb;
               if(micro.at(1) == "-e"){
                   if(stat(vchar[2], &sb) == -1){
                      // perror("error w/ stat");
                       cout << "(False)" << endl;
                       return -1;
                    }
                    else{
                        cout << "(True)" << endl;
                    }
                 }
               else if ((micro.at(1) != "-f" && micro.at(1) != "-d")){
                        if(stat(vchar[1], &sb) == -1){
                            // perror("error w/ stat");
                             cout << "(False)" << endl;
                             return -1;
                          }
                          else{
                             cout << "(True)" << endl;
                             exit(1);
                          }
                   }
               else if(micro.at(1) == "-d"){
                      if(stat(vchar[2], &sb) == -1){
                        // perror("error w/ stat");
                         cout << "(False)" << endl;
                         return -1;
                     }
                     else{
                         if(S_ISDIR(sb.st_mode)){
                             cout << "(True)" << endl;
                         }
                         else{
                             cout << "(False)" << endl;
                             return -1;
                         }
                     }
                     exit(1);
                   }
                else{
                    if(stat(vchar[2], &sb) == -1){
                        // perror("error w/ stat");
                         cout << "(False)" << endl;
                         return -1;
                     }
                     else{
                         if(S_ISREG(sb.st_mode)){
                             cout << "(True)" << endl;
                         }
                         else{
                             cout << "(False)" << endl;
                             return -1;
                         }
                     }
                     exit(1);
                   }

                  return 0;
              }


};
#endif
