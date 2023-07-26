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

#ifndef CPP3_SMARTCALC_V2_CALCULATOR_S21_MODEL_H
#define CPP3_SMARTCALC_V2_CALCULATOR_S21_MODEL_H

#include <cctype>
#include <cmath>
#include <cstring>
#include <stack>
#include <string>

// Pattern Facade + SOLID(Single responsibility)

namespace s21 {
class Validator {
 public:
  Validator() = default;
  ~Validator() = default;

  Validator(Validator&& validator) = delete;
  Validator(const Validator& validator) = delete;
  Validator& operator=(Validator&& validator) = delete;
  Validator& operator=(const Validator& validator) = delete;

  Validator& operator=(const std::string& str);

  std::string get_string();
  bool check_string() const;

 private:
  std::string str_{};
};

class Calculate {
 public:
  Calculate() = default;
  ~Calculate() = default;

  Calculate(Calculate&& calculate) = delete;
  Calculate(const Calculate& calculate) = delete;
  Calculate& operator=(Calculate&& calculate) = delete;
  Calculate& operator=(const Calculate& calculate) = delete;

  // setters
  void set_number(double& value);
  void set_option(std::string& value);
  // getters
  double get_number();
  size_t get_opt_size() const;
  std::string get_option();
  // other
  std::string peek_option();
  void binary(std::string& option);
  void unary(std::string& option);
  void one_calculation();
  void full_calculation();

 private:
  std::stack<double> poland_numbers_{};
  std::stack<std::string> poland_options_{};
};

class Parser {
 public:
  Parser() = default;
  ~Parser() = default;

  Parser(Parser&& parser) = delete;
  Parser(const Parser& parser) = delete;
  Parser& operator=(Parser&& parser) = delete;
  Parser& operator=(const Parser& parser) = delete;

  // setters
  void set_string(std::string& new_str);
  void set_unary();
  // other
  bool parsing_str(Calculate& calc_);
  void char_token(Calculate& calc_, std::string& token);

 private:
  std::string get_token(std::string::iterator& iter);
  int check_priority(std::string option) const;

 private:
  std::string infix_str_{};
  bool unary_ = true;
};

class Model {
 public:
  Model() = default;
  ~Model() = default;

  Model(Model&& model) = delete;
  Model(const Model& model) = delete;
  Model& operator=(Model&& model) = delete;
  Model& operator=(const Model& model) = delete;

  double take_answer(const std::string& str, bool& error);

 private:
  Validator validator_{};
  Parser parser_{};
  Calculate calc_{};
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_CALCULATOR_S21_MODEL_H
