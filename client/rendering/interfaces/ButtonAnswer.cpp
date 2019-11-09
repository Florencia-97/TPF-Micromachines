//
// Created by brian on 11/6/19.
//

#include "ButtonAnswer.h"

#include <utility>
bool ButtonAnswer::get_clicked() {
  return clicked;
}
std::string ButtonAnswer::get_msg() {
  return msg;
}
void ButtonAnswer::set_clicked(bool state) {
  this->clicked = state;
}
void ButtonAnswer::set_msg(std::string nameOfTexture) {
  this->msg = std::move(nameOfTexture);
}
