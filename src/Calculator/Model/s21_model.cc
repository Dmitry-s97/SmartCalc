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

#include "s21_model.h"

namespace s21 {
/*
 * Operators
 */
model& model::operator=(const model& m) {
  this->infix_str_ = m.infix_str_;
  return *this;
}

model& model::operator=(model&& m) {
  this->infix_str_ = std::move(m.infix_str_);
  return *this;
}
/*
 *   Calculation methods
 */
double model::return_values() {
  double number = poland_numbers_.front();
  poland_numbers_.pop_front();
  return number;
}

double model::func_sum() {
  double a = return_values();
  double b = return_values();
  return (a + b);
}

double model::func_sub() {
  double a = return_values();
  double b = return_values();
  return (b - a);
}

double model::func_mul() {
  double a = return_values();
  double b = return_values();
  return (b * a);
}

double model::func_del() {
  double a = return_values();
  double b = return_values();
  return (b / a);
}

double model::func_ln() {
  double a = return_values();
  return (log(a));
}

double model::func_log() {
  double a = return_values();
  return (log10(a));
}

double model::func_sin() {
  double a = return_values();
  return (sin(a));
}

double model::func_cos() {
  double a = return_values();
  return (cos(a));
}

double model::func_tan() {
  double a = return_values();
  return (tan(a));
}

double model::func_mod() {
  int a = static_cast<int>(return_values());
  int b = static_cast<int>(return_values());
  return (b % a);
}

double model::func_asin() {
  double a = return_values();
  return (asin(a));
}

double model::func_acos() {
  double a = return_values();
  return (acos(a));
}

double model::func_atan() {
  double a = return_values();
  return (atan(a));
}

double model::func_sqrt() {
  double a = return_values();
  return (sqrt(a));
}

double model::func_exp() {
  double a = return_values();
  double b = return_values();
  return (pow(b, a));
}

void model::to_calculate() {
  char opt = poland_options_.front().option_;
  poland_options_.pop_front();
  poland_numbers_.push_front(calculate(opt));
}

double model::calculate(char opt) {
  double result = 0;
  switch (opt) {
    case '*':
      result = func_mul();
      break;
    case '/':
      result = func_del();
      break;
    case '+':
      result = func_sum();
      break;
    case '-':
      result = func_sub();
      break;
    case '^':
      result = func_exp();
      break;
    case 'o':
      result = func_cos();
      break;
    case 't':
      result = func_sin();
      break;
    case 'h':
      result = func_tan();
      break;
    case 'f':
      result = func_acos();
      break;
    case 'i':
      result = func_asin();
      break;
    case 'x':
      result = func_atan();
      break;
    case 's':
      result = func_sqrt();
      break;
    case 'e':
      result = func_ln();
      break;
    case 'n':
      result = func_log();
      break;
    case 'm':
      result = func_mod();
      break;
  }
  return result;
}
/*
 * Parsing methods
 */
double model::parsing_str() {
  for (auto iter = infix_str_.begin(); iter != infix_str_.end(); iter++) {
    check_number(&iter);
    check_options(&iter);
    check_letter(&iter);
    check_bracket(&iter);
  }

  while (poland_options_.size() > 0) {
    to_calculate();
  }
  return poland_numbers_.front();
}

int model::check_priority(char opt) {
  int priority = 0;
  char massive[10] = "othfixsen";  // array of possible trigonometric matches

  if (opt == '+' || opt == '-') {
    priority = 1;
  } else if (opt == '*' || opt == '/' || opt == 'm') {
    priority = 2;
  } else if (opt == '^') {
    priority = 3;
  } else if (std::strchr(massive, opt) != nullptr) {
    priority = 4;
  }

  return priority;
}

void model::check_options(std::string::iterator* iter) {
  if (**iter == '-' || **iter == '+' || **iter == '*' || **iter == '/' ||
      **iter == '^') {
    int priority = check_priority(**iter);
    if (priority > poland_options_.front().priority_ ||
        poland_options_.size() == 0) {
      poland_options_.push_front({**iter, priority});
    } else if (priority <= poland_options_.front().priority_) {
      to_calculate();
      check_options(iter);  // write next operand
    }
  }
}

void model::check_bracket(std::string::iterator* iter) {
  if (**iter == '(') {
    poland_options_.push_front({**iter, 0});
  } else if (**iter == ')') {
    while (poland_options_.front().option_ != '(' &&
           poland_options_.size() > 0) {
      to_calculate();
    }
    poland_options_.pop_front();
  }
}

void model::check_number(std::string::iterator* iter) {
  if (isdigit(**iter) ||
      ((**iter == '-' || **iter == '+') &&
       (*iter == infix_str_.begin() || *(*iter - 1) == '('))) {
    char tmp_num[255] = {0};
    int j = 0;
    if (**iter == '-') {
      tmp_num[j++] = **iter;
      (*iter)++;
    }
    do {
      tmp_num[j++] = **iter;
      (*iter)++;
    } while (isdigit(**iter) || **iter == '.');
    (*iter)--;
    double number = atof(tmp_num);
    poland_numbers_.push_front(number);
  }
}

void model::check_letter(std::string::iterator* iter) {
  if (**iter == 'c' || **iter == 's' || **iter == 't' || **iter == 'a' ||
      **iter == 'l' || **iter == 'm') {  // compare the symbol with the symbols
                                         // of trigonometric functions
    char func_example[5] = {0};
    if (**iter != 'm') {  // if not mod
      for (int i = 0; **iter != '('; i++, (*iter)++) {
        func_example[i] = **iter;
      }
    } else if (**iter == 'm') {  // if mod
      for (int i = 0; isalpha(**iter); i++, (*iter)++) {
        func_example[i] = **iter;
      }
    }
    (*iter)--;
    check_trigonometric(func_example);
  }
}

void model::check_trigonometric(char* func_example) {
  char functions[11][5] = {"cos",  "sin",  "tan", "acos", "asin",
                           "atan", "sqrt", "ln",  "log",  "mod"};
  int error = 1;
  char example = 0;

  // compare the resulting string with an array of functions.
  // 'example' will equate to some letters of the numbers
  for (int i = 0; i < 11 && error == 1; i++) {
    if (std::strcmp(func_example, functions[i]) == 0) {
      if (i == 0) {  // i = 0 - cos
        example = 'o';
      } else if (i == 1) {  // i = 1 - sin
        example = 't';
      } else if (i == 2) {  // i = 2 - tan
        example = 'h';
      } else if (i == 3) {  // i = 3 - acos
        example = 'f';
      } else if (i == 4) {  // i = 4 - asin
        example = 'i';
      } else if (i == 5) {  // i = 5 - atan
        example = 'x';
      } else if (i == 6) {  // i = 6 - sqrt
        example = 's';
      } else if (i == 7) {  // i = 7 - ln
        example = 'e';
      } else if (i == 8) {  // i = 8 - log
        example = 'n';
      } else if (i == 9) {  // i = 9 - mod
        example = 'm';
      }

      poland_options_.push_front({example, 4});
      error = 0;
    }
  }
}
}  // namespace s21
