#include <fstream>
#include <ios>
#include <iostream>
#include <vector>

#include <Lamscript/AstPrinter.h>
#include <Lamscript/Expression.h>
#include <Lamscript/Lamscript.h>
#include <Lamscript/Token.h>
#include <Lamscript/TokenType.h>

int main(int argc, char** argv) {
  if (argc > 2) {
    std::cout << "Usage: lamscript [script]" << std::endl;
    exit(64);
  } else if (argc == 2) {
    lamscript::Lamscript::RunFile(argv[1]);
    exit(0);
  } else {
    lamscript::Lamscript::RunPrompt();
    exit(0);
  }
}
