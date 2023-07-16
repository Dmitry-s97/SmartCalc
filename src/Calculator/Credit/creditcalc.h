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

#ifndef CPP3_SMARTCALC_V2_CALCULATOR_CREDITCALC_H
#define CPP3_SMARTCALC_V2_CALCULATOR_CREDITCALC_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QDialog {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

 private:
  Ui::CreditCalc *ui_;

 private slots:
  void error_f();
  void annuity_calc();
  void differential_calculator();
  void calculation();
};

#endif  // CPP3_SMARTCALC_V2_CALCULATOR_CREDITCALC_H
