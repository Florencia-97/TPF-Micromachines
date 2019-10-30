//
// Created by brian on 10/29/19.
//

#include "TEXTURE_ERROR.h"
#include <cerrno>
#include <cstdio>
#include <cstring>

TEXTURE_ERROR::TEXTURE_ERROR(const char *format) {
  int _errno = errno;
  int s = snprintf(msg_error, BUF_LEN, "%s", format);
  strncpy(msg_error + s, strerror(_errno), BUF_LEN - s);
  msg_error[BUF_LEN - 1] = 0;
}
const char *TEXTURE_ERROR::what() const noexcept {
  return this->msg_error;
}
TEXTURE_ERROR::~TEXTURE_ERROR() noexcept = default;
