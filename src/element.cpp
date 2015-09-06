#include <stdexcept>
#include <csignal>

#include "src/json/json.h"
#include "element.h"

void handleSegFaults(int signum) {
  std::cout << "Caught segfault";
  throw new json::json_exception("Value not found");
}

Element* loadElement(json::Value* element) {
  Element* to_return = new Element();
  return loadElement(element, to_return);
}

Element* loadElement(json::Value* element, Element* target) {
  void (*prev_handler)(int);
  prev_handler = signal(SIGSEGV, handleSegFaults);

  //TODO every catch block should write to a future logger as well.
  try {
    json::Value* from = (*element)["from"];
    for (int i = 0; i < N_AXI; ++i) target->from[i] = (*from)[i]->as_int();
  } catch (json::json_exception) {
    for (int i = 0; i < N_AXI; ++i) target->from[i] = 0;
  }

  try {
    json::Value* to = (*element)["to"];
    for (int i = 0; i < N_AXI; ++i) target->to[i] = (*to)[i]->as_int();
  } catch (json::json_exception) {
    std::cout << "test";
    for (int i = 0; i < N_AXI; ++i) target->to[i] = 0;
  }

  try {
    json::Value* rotation = (*element)["rotation"];
    try {
      json::Value* origin = (*rotation)["origin"];
      for (int i = 0; i < N_AXI; ++i)
        target->rotation_origin[i] = (*origin)[i]->as_int();
    } catch (json::json_exception) {
      for (int i = 0; i < N_AXI; ++i) target->rotation_origin[i] = 0;
    }

    try {
      target->rotation_axis = (*rotation)["axis"]->as_int();
    } catch (json::json_exception) {
      target->rotation_axis = AXIS_X;
    }

    try {
      target->rotation_rescale = (*rotation)["rescale"]->as_bool();
    } catch (json::json_exception) {
      target->rotation_rescale = false;
    }

    try {
      target->rotation_angle = (*rotation)["angle"]->as_int();
    } catch (json::json_exception) {
      target->rotation_angle = 0;
    }
  } catch (json::json_exception) {
    for (int i = 0; i < N_AXI; ++i) target->rotation_origin[i] = 0;
    target->rotation_axis = AXIS_X;
    target->rotation_rescale = false;
    target->rotation_angle = 0;
  }

  signal(SIGSEGV, prev_handler);
  return target;
}

json::Value* saveElement(Element* element) {

}

json::Value* saveElement(Element* element, json::Value* target) {

}

