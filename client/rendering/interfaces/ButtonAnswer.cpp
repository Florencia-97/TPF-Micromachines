//
// Created by brian on 11/6/19.
//

#include "ButtonAnswer.h"

#include <utility>
bool ButtonAnswer::get_state() {
  return clicked;
}
std::string ButtonAnswer::get_color() {
  return car_color;
}
void ButtonAnswer::set_state(bool state) {
  this->clicked = state;
}
void ButtonAnswer::set_color(std::string name) {
  this->car_color = std::move(name);
}
