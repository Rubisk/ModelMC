#ifndef OBJECT_VALUE_H
#define	OBJECT_VALUE_H

#include <map>

#include "src/json/json.h"

namespace json {

typedef std::map<std::string, Value*> ValueMap;

class ObjectValue : public Value {
public:
  ObjectValue();

  ObjectValue(ValueMap* values);

  Status GetChild(const std::string &key, Value** &valueptr);

  void SaveValue(std::ostream* output);

  Status LoadValue(std::istream &stream);

  ~ObjectValue();
private:
  ValueMap* values_;

  Status LoadAndSaveValue_(std::istream &stream);
};

} // namespace json

#endif	// OBJECT_VALUE_H

