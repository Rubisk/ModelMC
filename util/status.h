#ifndef STATUS_H
#define	STATUS_H

#include <iostream>

enum ErrorState {
  kGood,
  kJsonError,
  kIOException,
};

class Status {
public:
  Status();

  Status(const ErrorState state);

  Status(const ErrorState state, const std::string message);

  bool IsOk();

  ErrorState GetError();

  std::string* GetErrorMessage();

  friend std::ostream& operator<<(std::ostream& os, const Status &s);
private:
  std::string message_;
  ErrorState s_;
};

#endif	// STATUS_H

