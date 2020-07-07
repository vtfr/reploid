#pragma onc

#include <sys/logger.h>  // Logger

#include <iostream>  // std::cout

namespace sys {

class SystemLogger : public Logger {
 public:
  using Logger::log;

  virtual void log(MessageFactory message) override {
    std::cout << "[Log] ";
    message(std::cout);
    std::cout << std::endl;
  }
};

}  // namespace sys
