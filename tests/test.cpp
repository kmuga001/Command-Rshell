#include "../src/Command.h"
#include "../src/AndConnector.h"
#include "../src/ArgumentList.h"
#include "../src/CmdArgument.h"
#include "../src/OrConnector.h"
#include "../src/SemicolonConnector.h"
#include "../src/rshell.h"
#include "../src/CloseParConnector.h"
#include "../src/DoubleOutConnector.h"
#include "../src/OpenParConnector.h"
#include "../src/SingleOutConnector.h"
#include "../src/SingleInputConnector.h"
#include <cstdlib>
#include "gtest/gtest.h"
#include <iostream>

TEST(IndividualCommands, ls) {
    Rshell* rs1 = new Rshell("ls;");
    rs1->buildVector();
    EXPECT_EQ(system("ls"), rs1->mainExecute());
}

TEST(IndividualCommands, lsa) {
    Rshell* rs2 = new Rshell("ls -a");
    rs2->buildVector();
    EXPECT_EQ(system("ls -a"), rs2->mainExecute());
}

TEST(IndividualCommands, echo) {
    Rshell* rs3 = new Rshell("echo hello");
    rs3->buildVector();
    EXPECT_EQ(system("echo hello"), rs3->mainExecute());
}

TEST(OneConnector, semicolon) {
    Rshell* rs5 = new Rshell("ls; echo goodbye");
    rs5->buildVector();
    EXPECT_EQ(system("ls; echo goodbye"), rs5->mainExecute());
}

TEST(OneConnector, andand) {
    Rshell* rs6 = new Rshell("echo foo && ls -a");
    rs6->buildVector();
    EXPECT_EQ(system("echo foo && ls -a"), rs6->mainExecute());
}
TEST(OneConnector, oror) {
    Rshell* rs7 = new Rshell("echo hello || git status");
    rs7->buildVector();
    EXPECT_EQ(system("echo hello || git status"), rs7->mainExecute());
}
TEST(MultiConnectors, two) {
    Rshell* rs8 = new Rshell("ls -a; echo hello; mkdir testitAll1");
    rs8->buildVector();
    EXPECT_EQ(system("ls -a; echo hello; mkdir testitAll3"), rs8->mainExecute());
}

TEST(MultiConnectors, three) {
    Rshell* rs9 = new Rshell("ls -a|| echo hello && echo world; git status");
    rs9->buildVector();
    EXPECT_EQ(system("ls -a || echo hello && echo world; git status"), rs9->mainExecute());
}

TEST(MultiConnectors, four) {
    Rshell* rs10 = new Rshell("ls -a; echo hello && mkdir test || echo world; git status");
    rs10->buildVector();
    EXPECT_EQ(system("ls -a; echo hello && mkdir test || echo world; git status"), rs10->mainExecute());
}

TEST(OnlyConnector, andand) {
    Rshell* rs11 = new Rshell("&&");
    rs11->buildVector();
    EXPECT_EQ(-1, rs11->mainExecute());
}

TEST(Hash, aftercommand) {
    Rshell* rs12 = new Rshell("ls # -lR /");
    rs12->buildVector();
    EXPECT_EQ(system("ls # -lR /,"), rs12->mainExecute());
}

TEST(Hash, onlycommand) {
    Rshell* rs13 = new Rshell("#this should be treated like an empty string");
    rs13->buildVector();
    EXPECT_EQ(-1, rs13->mainExecute());
}

TEST(TestCommand, testkeyword) {
    Rshell* rs14 = new Rshell("test -e src/rshell.h");
    rs14->buildVector();
    EXPECT_EQ(system("test -e src/rshell.h"), rs14->mainExecute());
}
TEST(TestCommand, dashf) {
    Rshell* rs15 = new Rshell("test -f src/rshell.h");
    rs15->buildVector();
    EXPECT_EQ(system("test -f src/rshell.h"), rs15->mainExecute());
}

TEST(TestCommand, dashd) {
    Rshell* rs16 = new Rshell("test -d src");
    rs16->buildVector();
    EXPECT_EQ(system("test -d src"), rs16->mainExecute());
}

TEST(TestCommand, testconnector) {
    Rshell* rs17 = new Rshell("test -e src/rshell.h && echo path exists");
    rs17->buildVector();
    EXPECT_EQ(system("test -e src/rshell.h && echo path exists"), rs17->mainExecute());
}

TEST(TestCommand, testbracket) {
    Rshell* rs18 = new Rshell("[ -e src/rshell.h ]");
    rs18->buildVector();
    EXPECT_EQ(system("[ -e src/rshell.h ]"), rs18->mainExecute());
}

TEST(TestCommand, testdefault) {
    Rshell* rs19 = new Rshell("test src/rshell.h");
    rs19->buildVector();
    EXPECT_EQ(system("test src/rshell.h"), rs19->mainExecute());
}

TEST(Precedence, justparentheses) {
    Rshell* rs20 = new Rshell("(echo hello)");
    rs20->buildVector();
    EXPECT_EQ(system("(echo hello)"), rs20->mainExecute());
}

TEST(Precedence, oneconnector) {
    Rshell* rs21 = new Rshell("echo hello || (echo no)");
    rs21->buildVector();
    EXPECT_EQ(system("echo hello || (echo no)"), rs21->mainExecute());
}

TEST(Precedence, multipleconnectors) {
    Rshell* rs22 = new Rshell("(echo A && echo B) || (echo C && echo D)");
    rs22->buildVector();
    EXPECT_EQ(system("(echo A && echo B) || (echo C && echo D)"), rs22->mainExecute());
}
TEST(Precedence, testcommand) {
    Rshell* rs23 = new Rshell("([ -e src/rshell.h ]) && echo test works");
    rs23->buildVector();
    EXPECT_EQ(system("([ -e src/rshell.h ]) && echo test works"), rs23->mainExecute());
}
TEST(OutputRedirection, mixed) {
    Rshell* rs24 = new Rshell("echo coool >> fileName; echo NOWASAPWHATWHOWHY > fileName");
    rs24->buildVector();
    EXPECT_EQ(system("echo coool >> fileName; echo NOWASAPWHATWHOWHY > fileName"), 0);
}

TEST(OutputRedirection, single) {
    Rshell* rs25 = new Rshell("echo hey > file.txt");
    rs25->buildVector();
    EXPECT_EQ(system("echo hey > file.txt"), 0);
}

TEST(OutputRedirection, doublep) {
    Rshell* rs26 = new Rshell("ls >> file.txt");
    rs26->buildVector();
    EXPECT_EQ(system("ls >> file.txt"), 0);
}

TEST(Piping, pipe) {
    Rshell* rs27 = new Rshell("ls -a | more");
    rs27->buildVector();
    EXPECT_EQ(system("ls -a | more"), rs27->mainExecute());
}

TEST(InputRedirection, testcommand) {
    Rshell* rs28 = new Rshell("cat < fileName");
    rs28->buildVector();
    EXPECT_EQ(system("cat < fileName"), rs28->mainExecute());
}



TEST(Exit, onlycommand) {
    Rshell* rs29 = new Rshell("exit");
    rs29->buildVector();
    EXPECT_EQ(system("exit"), rs29->mainExecute());
}

TEST(Exit, aftercommand) {
    Rshell* rs30 = new Rshell("ls; exit");
    rs30->buildVector();
    EXPECT_EQ(system("ls; exit"), rs30->mainExecute());
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
