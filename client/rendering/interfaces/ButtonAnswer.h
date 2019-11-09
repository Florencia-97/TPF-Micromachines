//
// Created by brian on 11/6/19.
//

#ifndef MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_ANSWER_H_
#define MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_ANSWER_H_

#include <string>
#include <utility>
class ButtonAnswer {

  bool clicked;

  std::string msg;

 public:

  ButtonAnswer(bool clicked, std::string color) : clicked(clicked), msg(std::move(color)) {};

  bool get_clicked();

  std::string get_msg();

  void set_clicked(bool state);

  void set_msg(std::string nameOfTexture);

};

#endif //MICROMACHINES_CLIENT_RENDERING_INTERFACES_BUTTON_ANSWER_H_
