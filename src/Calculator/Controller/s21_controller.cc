/* Copyright 29.06.2023 Gilberto Addison

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "s21_controller.h"

namespace s21 {
/*
 * Operators
 */
controller &controller::operator=(const controller &c) {
  this->expression_ = c.expression_;
  return *this;
}

controller &controller::operator=(controller &&c) {
  this->expression_ = std::move(c.expression_);
  return *this;
}
/*
 * Check string
 */
double controller::controller_string(int *error) {
  check_one();
  double result = 0;

  if (error_ == 0) {
    model model_string(expression_);
    result = model_string.parsing_str();
  } else {
    *error = error_;
  }
  return result;
}
/*
 * Extra methods
 */
void controller::check_one() {
  int close_ = 0, open_ = 0;
  // it's a big function but because of it performs one task (checks the string)
  // I won't split a function
  for (size_t i = 0; i < expression_.size() && error_ == 0; i++) {
    // Branches
    if (expression_[i] == '(') {
      open_++;
    } else if (expression_[i] == ')') {
      close_++;
    }
    if (expression_[i] == '(' && expression_[i + 1] == '.' &&
        expression_[i + 2] == ')') {
      error_ = 1;
    }
    if (expression_[i] == '(' && expression_[i + 1] == '^' &&
        expression_[i + 2] == ')') {
      error_ = 1;
    }
    if (expression_[i] == '(' && expression_[i + 1] == '/' &&
        expression_[i + 2] == ')') {
      error_ = 1;
    }
    if (expression_[i] == '(' && expression_[i + 1] == '*' &&
        expression_[i + 2] == ')') {
      error_ = 1;
    }
    if (expression_[i] == '(' && expression_[i + 1] == '+' &&
        expression_[i + 2] == ')') {
      error_ = 1;
    }
    if (expression_[i] == '(' && expression_[i + 1] == '-' &&
        expression_[i + 2] == ')') {
      error_ = 1;
    }
    if (expression_[i] == '(' && expression_[i + 1] == ')') {
      error_ = 1;
    }
    if (expression_[i] == '(' && expression_[i + 1] == '\0') {
      error_ = 1;
    }
    // Mod
    if (expression_[i] == 'd' && expression_[i + 1] == '\0') {
      error_ = 1;
    }
    if (expression_[0] == 'm') {
      error_ = 1;
    }
    // Delete on zero
    if (expression_[i] == '0' &&
        (expression_[i - 1] == 'd' || expression_[i - 1] == '/')) {
      error_ = 1;
    }
    // Dots
    if (expression_[i] == '.' && isdigit(expression_[i + 1]) &&
        expression_[i + 2] == '.') {
      error_ = 1;
    }
    if (expression_[0] == '.' && expression_[1] == '\0') {
      error_ = 1;
    }
    // Pow
    if (expression_[i] == '^' &&
        ((!isdigit(expression_[i + 1]) && expression_[i + 1] != '(') &&
         !isalpha(expression_[i + 1]))) {
      error_ = 1;
    }
    if (expression_[i] == '^' && i == 0) {
      error_ = 1;
    }
    if (expression_[i] == '^' &&
        ((!isdigit(expression_[i - 1]) && expression_[i - 1] != ')'))) {
      error_ = 1;
    }
  }

  if (open_ != close_) {
    error_ = 1;
  }

  if (error_ == 0) {
    check_two();
  }
}

void controller::check_two() {
  char str_check_opr[6][2] = {"+", "-", "/", "*", "."};
  char str_check_all[9][2] = {"+", "-", "/", "*", "(", ")", "^", "."};
  // check on repeat operations (example: 3++5, 9//3, 7--8, 10++6) minus works
  // only so: 7-(-8)
  for (size_t i = 0; i < expression_.size(); i++) {
    for (int j = 0; j < 6 && error_ == 0; j++) {
      if (std::strchr(str_check_opr[j], expression_[i]) != nullptr &&
          std::strchr(str_check_opr[j], expression_[i + 1]) != nullptr) {
        error_ = 1;
      }
    }
    // check that operations sre not first element
    for (int j = 0; j < 9 && error_ == 0; j++) {
      if (std::strchr(str_check_opr[j], expression_[0]) != nullptr &&
          expression_[0] != '-' && expression_[0] != '+' &&
          expression_[0] != '(') {
        error_ = 1;
      }
    }
    // check that operations are not the last element of the string (example:
    // 3+, 6/, 9*, 7^)
    for (int j = 0; j < 9 && error_ == 0; j++) {
      if (std::strchr(str_check_all[j], expression_[i]) != nullptr &&
          expression_[i + 1] == '\0' && expression_[i] != ')') {
        error_ = 1;
      }
    }
  }
}

int controller::controller_string_letters() {
  for (size_t i = 0; i < expression_.length(); i++) {
    if (std::isalpha(expression_[i])) {
      error_ = 1;
    }
  }
  return error_;
}

}  // namespace s21
