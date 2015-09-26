#ifndef MODELMAKER_UTIL_HELPER_MACROS_H_
#define MODELMAKER_UTIL_HELPER_MACROS_H_

namespace Macros {

// json::Value objects (can) throw on evaluating member access
// operators. Because of that, something like value[key] can't be
// passed to a function to try catch the exception, as it will
// be evaluated before being passed. So we use a Macro instead.
//TODO write all errors to some logger.
#define ASSIGN_OR_DEFAULT(to_assign, assignee, default_) \
  try {                                                  \
    assignee = to_assign;                                \
  } catch (std::runtime_error) {                         \
    assignee = default_;                                 \
  }

#define SET_BETWEEN(min, max, value) \
  if (value < min) value = min;      \
  if (value > max) value = max;

}

#endif // MODELMAKER_UTIL_HELPER_MACROS_H_