//
// Created by brian on 11/6/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_ANSWER_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_ANSWER_H_

#include <string>
#include <utility>
class ButtonAnswer {
  bool clicked;
  std::string car_color;
 public:
  ButtonAnswer(bool cliecked, std::string color) : clicked(cliecked), car_color(std::move(color)) {}
  bool get_state();
  std::string get_color();
  void set_state(bool state);
  void set_color(std::string nameOfTexture);
};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_ANSWER_H_
