#pragma once

#include <functional>  // std::function
#include <ostream>     // std::ostream

namespace sys {

class Logger {
 public:
  using MessageFactory = ::std::function<void(::std::ostream&)>;

  virtual void log(const char* message) {
    log([=](::std::ostream& stream) {
      stream << message;
    });
  }

  virtual void log(MessageFactory message) = 0;
};

}  // namespace sys
