#include <stdexcept>
#include <sstream>
#include <vector>

#include "json/value.h"
#include "json/iterator.h"
#include "model.h"

using namespace json;

void Model::FromJson(const json::Value &tree) {
  Value::Iterator it = tree["elements"].GetIterator();
  elements.clear();
  while (it.Valid()) {
    Element new_element;
    new_element.FromJson_(it.Get());
    elements.push_back(new_element);
  }
}

void Model::Validate_() {
  for (Element element : elements) {
    element.Validate_();
  }
}
