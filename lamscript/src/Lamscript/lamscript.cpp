#include <Lamscript/lamscript.h>

#include <Lamscript/scanner.h>

namespace lamscript {

/// @brief Run the given source.
void Lamscript::Run(const std::string& source) {
  Scanner* scanner = new Scanner(source);
  std::vector<Token> tokens = scanner->ScanTokens();

  for (Token token: tokens) {}
}

/// @brief Run a given file.
///
/// This functions throws if it cannot successfully open the file.
void Lamscript::RunFile(const std::string& file_path)  {
  std::ifstream source_file(file_path, std::ios::in | std::ios::binary);
  std::string source_as_string;

  if (source_file) {
    source_file.seekg(0, std::ios::end);
    source_as_string.resize(source_file.tellg());
    source_file.seekg(0, std::ios::beg);
    source_file.read(&source_as_string[0], source_as_string.size());
  } else {
    throw "The Input file could not be read";
  }

  Run(source_as_string);
}

/// @brief Runs the prompt for the interpreter.
void Lamscript::RunPrompt() {
  bool running = true;
  std::string source_line;

  while (running) {
    std::cout << "> ";
    std::getline(std::cin, source_line);

    if (!source_line.empty()) {
      Run(source_line);
    }
    source_line.clear();
  }
}

// @brief Report an error
void Lamscript::Error(int line, const std::string& message) {
  Lamscript::Report(line, "", message);
}

// @brief Report function.
void Lamscript::Report(
    int line, const std::string& where, const std::string& message) {
  std::cout << "[line " << "] Error" << where << ":" << message << std::endl; 
}
}  // namespace lamscript
