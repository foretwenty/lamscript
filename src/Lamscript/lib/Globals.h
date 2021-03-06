#ifndef SRC_LAMSCRIPT_LIB_GLOBALS_H_
#define SRC_LAMSCRIPT_LIB_GLOBALS_H_

#include <any>
#include <chrono>
#include <vector>

#include <Lamscript/parsed/LamscriptCallable.h>
#include <Lamscript/runtime/Interpreter.h>

namespace lamscript {
namespace lib {

class Clock : public parsed::LamscriptCallable {
 public:
  int Arity() const override { return 0; }
  std::any Call(
      runtime::Interpreter* interpreter,
      std::vector<std::any> arguments) override {
    return static_cast<double>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count());
  }

  std::string ToString() const override { return "<native fn>"; }
};

}  // namespace lib
}  // namespace lamscript

#endif  // SRC_LAMSCRIPT_LIB_GLOBALS_H_
