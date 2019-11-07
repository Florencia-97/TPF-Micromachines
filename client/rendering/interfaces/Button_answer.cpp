//
// Created by brian on 11/6/19.
//

#include "Button_answer.h"

#include <utility>
bool Button_answer::get_state() {
  return clicked;
}
std::string Button_answer::get_color() {
  return car_color;
}
void Button_answer::set_state(bool state) {
  this->clicked = state;
}
void Button_answer::set_color(std::string name) {
  this->car_color = std::move(name);
}
