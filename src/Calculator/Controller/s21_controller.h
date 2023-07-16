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

#ifndef CPP3_SMARTCALC_V2_CALCULATOR_S21_CONTROLLER_H
#define CPP3_SMARTCALC_V2_CALCULATOR_S21_CONTROLLER_H

#include <cctype>
#include <string>

#include "../Model/s21_model.h"

namespace s21 {

class controller {
 public:
  /*
   * Constructors && Destructor
   */
  controller(std::string str) : expression_(str){};
  controller(controller&& m) noexcept : expression_(std::move(m.expression_)){};
  controller(const controller& m) : expression_(m.expression_){};
  controller& operator=(const controller& c);
  controller& operator=(controller&& c);
  ~controller(){};
  /*
   * Check method
   */
  double controller_string(int* error);
  int controller_string_letters();

 private:
  void check_one();
  void check_two();

 private:
  std::string expression_{};
  int error_{};
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_CALCULATOR_S21_CONTROLLER_H
