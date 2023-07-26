/* Copyright 23.07.2023 Gilberto Addison

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
 *
 * Model class
 *
 */
double Model::take_answer(const std::string &str, bool &error) {
  validator_ = str;

  if (validator_.check_string() == 0) {
    std::string strcp = validator_.get_string();
    parser_.set_string(strcp);
    if (!parser_.parsing_str(calc_)) {
      calc_.full_calculation();
      double result = calc_.get_number();
      parser_.set_unary();
      if (!std::isnan(result))
        return result;
      else
        error = true;
    } else {
      error = true;
    }
  } else {
    error = true;
  }
  return 0;
}
/*
 *
 * Validator class
 *
 */
bool Validator::check_string() const {
  bool error = false;
  int opbr = 0, clbr = 0;
  static char no_repeat[6] = "+-*/^";
  static char operations[6] = "*/^m";
  static char pl_min[3] = "+-";

  for (size_t i = 0; i < str_.length() && error == false; i++) {
    if (str_[i] == '(') opbr++;
    if (str_[i] == ')') clbr++;
    if (str_[0] == 'm') error = true;
    if (str_[i] == 'd' && str_[i + 1] == '0') error = true;
    if (str_[i] == '/' && str_[i + 1] == '0') error = true;

    if (std::strchr(no_repeat, str_[i]) &&
        std::strchr(no_repeat, str_[i + 1]) &&
        std::strchr(no_repeat, str_[i + 2]))
      error = true;

    if (str_[i] == 'm' && std::strchr(operations, str_[i + 3])) error = true;

    if (std::strchr(no_repeat, str_[0]) && std::strchr(no_repeat, str_[1]))
      error = true;

    if (std::strchr(pl_min, str_[i]) && std::strchr(pl_min, str_[i + 1]) &&
        std::strchr(pl_min, str_[i + 2]))
      error = true;

    if (std::strchr(operations, str_[i]) &&
        std::strchr(operations, str_[i + 1]))
      error = true;

    if (!std::isdigit(str_[i]) && str_[i] != ')' && str_[i + 1] == '\0')
      error = true;

    if (!std::isdigit(str_[i]) && str_[i] != ')' && str_[i + 1] == ')')
      error = true;

    if (!std::isdigit(str_[i]) && str_[i] != ')' && str_[i + 1] == ')')
      error = true;

    if (!std::isdigit(str_[i]) && str_[i] != ')' && str_[i + 1] == ')')
      error = true;

    if (str_[i] == '(' && !std::isdigit(str_[i + 1]) && str_[i + 2] == '(')
      error = true;

    if (str_[i] == '(' && (str_[i + 1] == '*' || str_[i + 1] == '/' ||
                           str_[i + 1] == '^' || str_[i + 1] == 'm'))
      error = true;

    if (!std::isdigit(str_[0]) && str_[0] != '(' && str_[0] != '-' &&
        str_[0] != '+' && !std::isalpha(str_[0]))
      error = true;
  }
  if (opbr != clbr) error = true;

  return error;
}

Validator &Validator::operator=(const std::string &str) {
  str_ = str;
  return *this;
}

std::string Validator::get_string() { return str_; }
/*
 *
 * Parser class
 *
 */
void Parser::set_string(std::string &new_str) { infix_str_ = new_str; }

bool Parser::parsing_str(Calculate &calc_) {
  auto iter = infix_str_.begin();
  auto end = infix_str_.end();

  while (iter != end) {
    std::string token = get_token(iter);

    if (token == "") return 1;

    if (std::isdigit(token[0]) || std::isdigit(token[1])) {  // 5 or -5
      size_t st;
      double num = std::stod(token, &st);
      calc_.set_number(num);
    } else if (token == ")") {
      while (calc_.peek_option() != "(" && calc_.get_opt_size() > 0) {
        calc_.one_calculation();
      }
      calc_.get_option();
    } else {
      char_token(calc_, token);
    }
  }

  return 0;
}

void Parser::char_token(Calculate &calc_, std::string &token) {
  static char operations[8] = "+-*/^m(";
  if (std::strchr(operations, token[0])) {
    unary_ = true;
    if (token[0] == '(') {
      calc_.set_option(token);
      return;
    }
  }
  if (check_priority(token) > check_priority(calc_.peek_option())) {
    calc_.set_option(token);
  } else if (token == "^" &&
             calc_.peek_option() == "^") {  // Right associativity
    calc_.set_option(token);
  } else if (check_priority(token) <= check_priority(calc_.peek_option()) &&
             calc_.peek_option() != "(") {
    calc_.one_calculation();
    char_token(calc_, token);
  }
}
void Parser::set_unary() { unary_ = true; }

std::string Parser::get_token(std::string::iterator &iter) {
  static const std::string tokens[] = {
      "+",    "-",    "*",    "/",   "^",  "mod",  "tan", "sin", "cos",
      "atan", "asin", "acos", "log", "ln", "sqrt", "(",   ")"};

  if (isdigit(*iter) || (unary_ && (*iter == '-' || *iter == '+'))) {
    std::string number;
    unary_ = false;
    if (*iter == '-')
      number.push_back(*iter++);
    else if (*iter == '+')
      *iter++;
    while (std::isdigit(*iter) || *iter == '.') number.push_back(*iter++);
    return number;
  }

  for (auto &tk : tokens) {
    std::string token(iter, iter + tk.size());
    if (std::strncmp(token.c_str(), tk.c_str(), tk.size()) == 0) {
      iter += tk.size();
      return token;
    }
  }

  return "";
}

int Parser::check_priority(std::string option) const {
  int priority = 0;
  if (option == "+" || option == "-") {
    priority = 1;
  } else if (option == "*" || option == "/" || option == "m") {
    priority = 2;
  } else if (option == "^") {
    priority = 3;
  } else if (std::isalpha(option[1])) {
    priority = 4;
  }
  return priority;
}
/*
 *
 * Calculate class
 *
 */
void Calculate::set_number(double &value) { poland_numbers_.push(value); }

void Calculate::set_option(std::string &value) { poland_options_.push(value); }

double Calculate::get_number() {
  double res = poland_numbers_.top();
  poland_numbers_.pop();
  return res;
}

size_t Calculate::get_opt_size() const { return poland_options_.size(); }

std::string Calculate::get_option() {
  std::string res = poland_options_.top();
  poland_options_.pop();
  return res;
}

std::string Calculate::peek_option() {
  if (poland_options_.size() > 0) return poland_options_.top();
  return "0";
}

void Calculate::one_calculation() {
  std::string opt = get_option();
  if (opt == "*" || opt == "/" || opt == "+" || opt == "-" || opt == "^" ||
      opt == "pow" || opt == "mod") {
    binary(opt);
  } else {
    unary(opt);
  }
}

void Calculate::full_calculation() {
  while (get_opt_size() > 0) {
    one_calculation();
  }
}

void Calculate::binary(std::string &option) {
  double result = 0;
  double a = get_number();
  double b = get_number();

  if (option == "*")
    result = b * a;
  else if (option == "/")
    result = b / a;
  else if (option == "-")
    result = b - a;
  else if (option == "+")
    result = b + a;
  else if (option == "^")
    result = pow(b, a);
  else if (option == "mod")
    result = fmod(b, a);

  set_number(result);
}

void Calculate::unary(std::string &option) {
  double result = 0;
  double a = get_number();

  if (option == "sin")
    result = sin(a);
  else if (option == "cos")
    result = cos(a);
  else if (option == "tan")
    result = tan(a);
  else if (option == "atan")
    result = atan(a);
  else if (option == "acos")
    result = acos(a);
  else if (option == "asin")
    result = asin(a);
  else if (option == "ln")
    result = log(a);
  else if (option == "log")
    result = log10(a);
  else if (option == "sqrt")
    result = sqrt(a);

  set_number(result);
}
}  // namespace s21
