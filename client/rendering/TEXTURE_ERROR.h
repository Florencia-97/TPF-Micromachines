//
// Created by brian on 10/29/19.
//

#ifndef MICROMACHINES_CLIENT_TEXTURE_ERROR_H_
#define MICROMACHINES_CLIENT_TEXTURE_ERROR_H_
#include <typeinfo>
#define BUF_LEN 256
class TEXTURE_ERROR : public std::exception {
 private:
  char msg_error[BUF_LEN]{};
 public:

  /*Builder of the exception*/
  explicit TEXTURE_ERROR(const char *format);

  /*Override of the what method of the std::exception*/
  const char *what() const noexcept override;

  /*Destroyer of the class*/
  ~TEXTURE_ERROR() noexcept override;
};

#endif //MICROMACHINES_CLIENT_TEXTURE_ERROR_H_
