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

#ifndef CPP3_SMARTCALC_V2_CALCULATOR_MAINWINDOW_H
#define CPP3_SMARTCALC_V2_CALCULATOR_MAINWINDOW_H

#include <QFile>
#include <QMainWindow>
#include <QMessageBox>
#include <QVector>
#include <iostream>

#include "../Controller/s21_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void input();
  void Quit_triggered();
  void on_pushButton_c_clicked();
  void on_pushButton_eq_clicked();
  void on_pushButton_ac_clicked();
  void on_pushButton_done_clicked();
  void on_pushButton_graph_clicked();
  void input_triginometric_operation();

 private:
  void show_error();
  void graph_theme();
  void to_color_graph();

 private:
  Ui::MainWindow *ui_;
  s21::Controller *controller_;
};
#endif  // CPP3_SMARTCALC_V2_CALCULATOR_MAINWINDOW_H
