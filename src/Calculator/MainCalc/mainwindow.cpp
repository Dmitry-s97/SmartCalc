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

#include "mainwindow.h"

#include "../Credit/creditcalc.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);

  ui_->pushButton_done->hide();
  ui_->line_res_x->hide();

  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_div, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_mul, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_pow, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_open, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_plus, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_close, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_minus, SIGNAL(clicked()), this, SLOT(input()));

  connect(ui_->pushButton_x, SIGNAL(clicked()), this, SLOT(input()));
  connect(ui_->pushButton_done, SIGNAL(clicked()), this, SLOT(input()));

  connect(ui_->actionQuit, SIGNAL(triggered()), this, SLOT(Quit_triggered()));

  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(tr_operations()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(tr_operations()));
  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(tr_operations()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(tr_operations()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(tr_operations()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this, SLOT(tr_operations()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this, SLOT(tr_operations()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this, SLOT(tr_operations()));
  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(tr_operations()));
}

MainWindow::~MainWindow() { delete ui_; }
/*
 * Input methods
 */
void MainWindow::input() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  if (ui_->line_res->isEnabled() && button->text() != "done") {
    if ((button->text() != ".") &&
        ui_->line_res->text() == "0") {  // rewrite zero if it's not a dot
      new_label = button->text();
    } else {
      new_label = ui_->line_res->text() + button->text();
    }
    ui_->line_res->setText(new_label);
    if (button->text() == 'x') {  // change a button for entering a value of X
      ui_->line_res->setDisabled(true);
      ui_->line_res_x->setEnabled(true);
      ui_->pushButton_x->hide();
      ui_->pushButton_done->show();
      ui_->line_res_x->show();
    }
  } else {
    if (button->text() != "done") {
      new_label = ui_->line_res_x->text() + button->text();
      ui_->line_res_x->setText(new_label);
    } else {  // after entering 'X'
      on_pushButton_done_clicked();
    }
  }
}

void MainWindow::tr_operations() {
  input();
  ui_->line_res->setText(ui_->line_res->text() + "(");
}
/*
 * Clear methods
 */
void MainWindow::on_pushButton_ac_clicked() {
  ui_->line_res->setText("");
  ui_->line_res_x->setText("");
}

void MainWindow::on_pushButton_c_clicked() {
  if (ui_->line_res_x->isEnabled()) {
    QString str_copy = ui_->line_res_x->text();
    str_copy.resize(str_copy.size() - 1);
    ui_->line_res_x->setText(str_copy);
  } else {
    QString str_copy = ui_->line_res->text();
    str_copy.resize(str_copy.size() - 1);
    ui_->line_res->setText(str_copy);
  }
}

void MainWindow::on_pushButton_done_clicked() {
  ui_->line_res_x->setDisabled(true);
  ui_->line_res->setEnabled(true);
  ui_->pushButton_x->show();
  ui_->pushButton_done->hide();
  ui_->line_res_x->hide();
}

void MainWindow::error_f() {
  on_pushButton_ac_clicked();
  on_pushButton_done_clicked();
  QMessageBox::critical(this, "ERROR", "ERROR");
}
/*
 * Calculation method
 */
void MainWindow::on_pushButton_eq_clicked() {
  QString str_origin = ui_->line_res->text();

  if (str_origin != "") {
    if (ui_->line_res->text().contains('x')) {
      str_origin.replace("x", ui_->line_res_x->text());
    }

    int error = 0;
    s21::controller control(str_origin.toUtf8().constData());
    double res = control.controller_string(&error);

    if (error == 0 && res != NAN && res != INFINITY) {
      QString new_label;
      new_label = QString::number(res, 'g', 8);
      ui_->line_res->setText(new_label);
    } else {
      error_f();
    }

    on_pushButton_done_clicked();  // return to initial layout
    ui_->line_res_x->clear();

  } else {
    error_f();
  }
}
/*
 * Graphics methods
 */
void MainWindow::beautiful_graph() {
  QPen pen;
  pen.setColor(QColor(220, 220, 220));  // color
  pen.setWidth(3);                      // width
  ui_->widget->graph(0)->setPen(pen);
}

void MainWindow::on_pushButton_graph_clicked() {
  QString str = ui_->line_res->text();  // extra string for helping

  if (str != "") {
    x_.clear();
    y_.clear();

    X_ = xBegin_ = ui_->line_res_x->text().toDouble();

    if (X_ > 0) {
      X_ = xBegin_ = -X_;
    }

    h_ = abs(xBegin_) / 10000;  // step
    ui_->widget->xAxis->setRange(-xBegin_, xBegin_);
    ui_->widget->yAxis->setRange(-xBegin_, xBegin_);

    ui_->widget->addGraph();

    for (; X_ < abs(xBegin_); X_ += h_) {
      if (X_ >= 0.002 || X_ <= -0.001) {  // because of some calculations with
                                          // small values ​​skip data X

        QString str_tmp(str);  // Calculate from this string
        str_tmp.insert(str_tmp.indexOf("0123456789", 0) + 1,
                       "(");  // I's just need, don't touch it
        str_tmp.append(")");

        str_tmp.replace("x", QString::number(X_));

        int err = 0;
        s21::controller control(str_tmp.toUtf8().constData());
        double res = control.controller_string(&err);

        if (res < abs(xBegin_) && res > xBegin_) {
          if (err == 0) {
            x_.push_back(X_);
            y_.push_back(res);
          } else {
            error_f();
            break;
          }
        }
      }
    }

    beautiful_graph();
    ui_->widget->graph(0)->setData(x_, y_);
    ui_->widget->replot();

    ui_->widget->setInteraction(QCP::iRangeZoom, true);
    ui_->widget->setInteraction(QCP::iRangeDrag, true);
  } else {
    error_f();
  }
}

void MainWindow::graph_theme() {
  QLinearGradient B;
  B.setColorAt(1, 1);
  ui_->widget->setBackground(B);

  ui_->widget->xAxis->setTickLabelColor(Qt::white);  // for numbers
  ui_->widget->yAxis->setTickLabelColor(Qt::white);
  ui_->widget->xAxis->setBasePen(QPen(Qt::white, 1));  // for line
  ui_->widget->yAxis->setBasePen(QPen(Qt::white, 1));
}

void MainWindow::on_pushButton_wide_clicked() {
  if (isMaximized()) {
    showNormal();
  } else {
    graph_theme();
    showMaximized();
  }
}
/*
 * Methods from menu
 */
void MainWindow::on_actionCredit_Calculator_triggered() {
  CreditCalc window;
  window.setWindowTitle("CreditCalc");
  window.setModal(true);
  window.exec();
}

void MainWindow::Quit_triggered() { QApplication::quit(); }
