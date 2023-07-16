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

#include "creditcalc.h"

#include "../Controller/s21_controller.h"
#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QDialog(parent), ui_(new Ui::CreditCalc) {
  ui_->setupUi(this);
  connect(ui_->pushButton_eq, SIGNAL(clicked()), this, SLOT(calculation()));
}

CreditCalc::~CreditCalc() { delete ui_; }

void CreditCalc::calculation() {
  if (ui_->radioButton_an->isChecked()) {
    annuity_calc();
  } else if (ui_->radioButton_dif->isChecked()) {
    differential_calculator();
  } else {
    QMessageBox::information(this, "Attention!", "Select calculation type");
  }
}

void CreditCalc::annuity_calc() {
  int error = 0;
  QString str_time = ui_->lineEdit_time->text();
  QString str_loan_amount = ui_->lineEdit_full->text();
  double procent = ui_->lineEdit_procent->text().toDouble();

  if (str_loan_amount != "" && str_time != "" && procent > 0 && procent < 100) {
    QString annui_ty = "K*((1+P)^(M-1))";  // constant formula
    QString str_procent =
        QString::number(procent / 12 / 100);  // changed percent to string
    annui_ty.replace(QString("K"), str_loan_amount);
    annui_ty.replace(QString("P"), str_procent);
    annui_ty.replace(QString("M"), str_time);

    s21::controller control(annui_ty.toUtf8().constData());
    control.controller_string_letters();

    if (error == 0) {
      double all = control.controller_string(&error);
      if (error == 0 && all != INFINITY && all != NAN) {
        int month = all / str_time.toDouble();
        QString str_monthly_pay = QString::number(month, 'f', 0);
        ui_->lineEdit_res_month->setText(str_monthly_pay);

        double more = all - str_loan_amount.toDouble();
        QString str_overpay = QString::number(more, 'f', 0);
        ui_->lineEdit_more->setText(str_overpay);

        QString str_total = QString::number(all, 'f', 0);
        ui_->lineEdit_all->setText(str_total);
      } else {
        error_f();
      }
    } else {
      error_f();
    }
  } else {
    QMessageBox::information(this, "Attention!", "Enter data for calculation");
  }
}

void CreditCalc::differential_calculator() {
  QString str_time = ui_->lineEdit_time->text(),
          str_loan_amount = ui_->lineEdit_full->text(),
          str_percent = ui_->lineEdit_procent->text();
  QString check_str = str_time + str_loan_amount + str_percent;
  s21::controller control(check_str.toUtf8().constData());
  int error = control.controller_string_letters();

  if (error == 0) {
    double procent = str_percent.toDouble();

    if (str_time != "" && str_loan_amount != "" && procent > 0 &&
        procent < 100) {
      int month = ui_->lineEdit_time->text().toInt(),
          i = ui_->calendarWidget->monthShown();
      double first = 0, last = 0,
             tmp_sum = ui_->lineEdit_full->text().toDouble(), sum = tmp_sum,
             tmp_cd = 0, tmp_cp = 0, procent_more = 0;
      procent = procent / 100;

      for (int j = 1; j <= month; i++, j++) {
        tmp_cd = sum / month;
        if (i == 13) {
          i = 1;
        }
        if (i == 2) {
          tmp_cp = (tmp_sum * procent * 28) / 365;
        } else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 ||
                   i == 12) {
          tmp_cp = (tmp_sum * procent * 31) / 365;
        } else if (i == 4 || i == 6 || i == 9 || i == 11) {
          tmp_cp = (tmp_sum * procent * 30) / 365;
        }
        tmp_sum = tmp_sum - tmp_cd;
        procent_more += tmp_cp;
        if (j == 1) {
          first = tmp_cd + tmp_cp;
        }
        if (j == month) {
          last = tmp_cd + tmp_cp;
        }
      }

      QString first_str = QString::number(first, 'f', 0),
              last_str = QString::number(last, 'f', 0);
      ui_->lineEdit_res_month->setText(first_str + "..." + last_str);

      QString procent_more_str = QString::number(procent_more, 'f', 0);
      ui_->lineEdit_more->setText(procent_more_str);

      sum += procent_more;
      QString sum_str = QString::number(sum, 'f', 0);
      ui_->lineEdit_all->setText(sum_str);
    } else {
      error_f();
    }
  } else {
    QMessageBox::information(this, "Attention", "Enter data for calculation");
  }
}

void CreditCalc::error_f() { QMessageBox::critical(this, "ERROR", "ERROR"); }
