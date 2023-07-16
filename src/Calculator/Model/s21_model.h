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

#ifndef CPP3_SMARTCALC_V2_CALCULATOR_S21_MODEL_H
#define CPP3_SMARTCALC_V2_CALCULATOR_S21_MODEL_H

#include <cctype>
#include <cmath>
#include <cstring>
#include <list>
#include <string>

namespace s21 {
struct opt {
  char option_;
  int priority_;
};

class model {
 public:
  model(model &&m) noexcept : infix_str_(std::move(m.infix_str_)){};
  model(const model &m) : infix_str_(m.infix_str_){};
  model(std::string a) { infix_str_ = a; };
  model &operator=(const model &m);
  model &operator=(model &&m);
  ~model(){};

  double parsing_str();

 private:
  /*
   * Parsing methods
   */
  void check_bracket(std::string::iterator *iter);
  void check_letter(std::string::iterator *iter);
  void check_number(std::string::iterator *iter);
  void check_options(std::string::iterator *opt);
  void check_trigonometric(char *opt);
  int check_priority(char opt);
  /*
   * Calculation methods
   */
  double calculate(char opt);
  double return_values();
  void to_calculate();
  double func_sqrt();
  double func_asin();
  double func_acos();
  double func_atan();
  double func_sum();
  double func_sub();
  double func_mul();
  double func_del();
  double func_exp();
  double func_sin();
  double func_cos();
  double func_tan();
  double func_mod();
  double func_log();
  double func_ln();

 private:
  std::list<double> poland_numbers_;
  std::list<opt> poland_options_;
  std::string infix_str_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_CALCULATOR_S21_MODEL_H
