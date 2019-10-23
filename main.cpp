#include "rshell.h"
#include <iostream>
//#include "gtest/gtest.h"
int main(){
    string argumentlist = "";
    cout << "$ ";
    getline(cin, argumentlist);
    while(argumentlist != "exit"){
        if(argumentlist != ""){
           // cout << "did" << endl;
            Rshell* rs = new Rshell(argumentlist);
           // cout << "you2345678" <<  endl;
            rs->buildVector();
            //rs->print();
           // cout << "work56789" << endl;
            int x = rs->mainExecute();
           // cout << "yet234567890" << endl;
            cout << "$ ";
            getline(cin, argumentlist);
        }
        else {
             cout << "error: nothing entered." << endl;
             cout << "$ ";
             getline(cin, argumentlist);
        }
       /* Rshell* rs = new Rshell(argumentlist);
        rs->buildVector();
        rs->print();
        rs->printArgs();
        rs->execute();*/
        int testing = 0;
        /*if(argumentlist == "echo hello" || argumentlist == "echo hello;") {
                testing = rs->execute();
                if(testing != -1) {
                        cout << "Echo test passed. " << endl;
                } else {
                        cout << "Echo test failed. " << endl;
                }
        } else {
                testing = rs->execute();
        }*/
        /*int x = rs->execute();
        cout << "yet234567890" << endl;
        cout << "$ ";
        getline(cin, argumentlist);*/
    }
    return 0;
}
