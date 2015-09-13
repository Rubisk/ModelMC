#include "status.h"

namespace { // anonymous namespace

const char* ErrorStrings[] = {
  "",
  "Json Exception: ",
  "IOException: "
};

} // anonymous namespace

Status::Status() {
  s_ = kGood;
}

Status::Status(const ErrorState state) {
  s_ = state;
}

Status::Status(const ErrorState state, const std::string message) {
  s_ = state;
  message_ = message;
}

bool Status::IsOk() {
  return s_ == kGood;
}

ErrorState Status::GetError() {
  return s_;
}

std::string* Status::GetErrorMessage() {
  return &message_;
}

std::ostream& operator<<(std::ostream& os, const Status &s) {
  os << ErrorStrings[s.s_] << s.message_;
  return os;
}
