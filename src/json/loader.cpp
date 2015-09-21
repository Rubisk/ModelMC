#include <fstream>
#include <sstream>

#include "json/loader.h"

using namespace std;

namespace json {

Loader::Loader(const string &path) {
  shared_ptr<ifstream> stream(new ifstream());
  stream->open(path);
  stream_ = stream;
}

Loader::Loader(const char *path) {
  string path_(path);
  shared_ptr<ifstream> stream(new ifstream());
  stream->open(path);
  stream_ = stream;
}

Loader::Loader(InputStream stream) {
  stream_ = stream;
}

Value Loader::Load() {
  char a;
  auto old_pos = stream_->tellg();
  (*stream_) >> std::skipws >> a >> std::noskipws;
  stream_->seekg(old_pos);
  switch (a) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '-':
    return LoadIntValue_();
  case '\"':
    return LoadStringValue_();
  case 't':
  case 'f':
    return LoadBoolValue_();
  case '{':
    return LoadObjectValue_();
  case '[':
    return LoadArrayValue_();
  }
  return Value(); // Return a null value.
}

std::string Loader::LoadString_() {
  char a;
  (*stream_) >> std::skipws >> a >> std::noskipws;
  if (a != '"') {
    std::stringstream ss;
    ss << "Parsing Error: String didn't start with '\"' but with '"
      << a << "'.";
    throw json_exception(ss.str().c_str());
  }

  std::string name = "";
  while ((*stream_) >> a && a != '"') {
    name += a;
    if (name.size() > 1000) {
      throw json_exception("Parsing Error: Name longer then 1000 chars.");
    }
  }

  return name;
}

Value Loader::LoadArrayValue_() {
  Value::Array array_;

  char next_char;
  (*stream_) >> std::skipws >> next_char >> std::noskipws;
  if (next_char != '[') {
    std::stringstream ss;
    ss << "Parsing Error: Expected '[', found '"
      << next_char << "' instead.";
    throw json_exception(ss.str().c_str());
  }

  while (true) {
    Value next_entry = Load();
    array_.push_back(make_shared<Value>(next_entry));

    (*stream_) >> std::skipws >> next_char >> std::noskipws;
    switch (next_char) {
    case (',') :
      continue;
    case (']') :
      return array_;
    default:
      std::stringstream ss;
      ss << "Parsing Error: Expected ']' or ',', found '"
        << next_char << "' instead.";
      throw json_exception(ss.str().c_str());
    }
  }
}

Value Loader::LoadObjectValue_() {
  Value::Object object;

  char next_char;
  (*stream_) >> std::skipws >> next_char >> std::noskipws;
  if (next_char != '{') {
    std::stringstream ss;
    ss << "Parsing Error: Expected '{', found '"
      << next_char << "' instead.";
    throw json_exception(ss.str().c_str());
  }

  while (true) {
    Value next_name = LoadString_();

    (*stream_) >> std::skipws >> next_char >> std::noskipws;
    if (next_char != ':') {
      std::stringstream ss;
      ss << "Parsing Error: Expected ':', found '"
        << next_char << "' instead.";
      throw json_exception(ss.str().c_str());
    }

    Value next_value = Load();
    object[next_name] = std::make_shared<Value>(next_value);

    (*stream_) >> std::skipws >> next_char >> std::noskipws;
    switch (next_char) {
    case (',') :
      continue;
    case ('}') :
      return object;
    default:
      std::stringstream ss;
      ss << "Parsing Error: Expected '}' or ',', found '"
        << next_char << "' instead.";
      throw json_exception(ss.str().c_str());
    }
  }

} // namespace json

Value Loader::LoadIntValue_() {
  int new_value = -1;
  if ((*stream_) >> std::skipws >> new_value >> std::noskipws) {
    return new_value;
  } else {
    throw json_exception("Parsing error: Couldn't read integer from stream.");
  }
}

Value Loader::LoadStringValue_() {
  return LoadString_();
}

Value Loader::LoadBoolValue_() {
  char next_char;
  (*stream_) >> std::skipws >> next_char >> std::noskipws;
  if (next_char == 'f') {
    for (char c : "alse") {
      (*stream_) >> next_char;
      if (next_char != c) {
        std::stringstream ss;
        ss << "Parsing error: Unexpected character while loading bool. Expected: '"
          << c << "', got '" << next_char << "' instead.";
        throw json_exception(ss.str().c_str());
      }
      if (c == 'e') {
        return false;
      }
    }
  } else if (next_char == 't') {
    for (char c : "rue") {
      (*stream_) >> next_char;
      if (next_char != c) {
        std::stringstream ss;
        ss << "Parsing error: Unexpected character while loading bool. Expected: '"
          << c << "', got '" << next_char << "' instead.";
        throw json_exception(ss.str().c_str());
      }
      if (c == 'e') {
        return true;
      }
    }
  }
  std::stringstream ss;
  ss << "Parsing error: Unexpected character while loading bool."
    << "Expected: 'f' or 't', got '" << next_char << "' instead.";
  throw json_exception(ss.str().c_str());
}

} // namespace json
