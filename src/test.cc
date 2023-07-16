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

#include <gtest/gtest.h>

#include <string>

#include "./Calculator/Controller/s21_controller.h"

TEST(Back, a) {
  std::string str = "sin(30)+2*3-(5-1)";
  long double origin = 1.011968375907;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, origin, 0.0000001);
}

TEST(Back, b) {
  std::string str = "2+2.2*54/3+4";
  long double origin = 45.6;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, origin, 0.0000001);
}

TEST(Backend, test01) {
  std::string str = "sin(cos(2^3))";
  long double origin = -0.1449871;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, origin, 0.0000001);
}

TEST(Backend, test02) {
  std::string str = "sin(cos(2^3)";
  int error = 0;
  s21::controller control(str);
  control.controller_string(&error);
  ASSERT_EQ(error, 1);
}

TEST(Backend, test03) {
  std::string str = "sqrt(4.12)+asin(0)";
  long double origin = 2.029778313;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, origin, 0.0000001);
}

TEST(Backend, test04) {
  std::string str = "55+3/2";
  long double origin = 56.5;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, origin, 0.0000001);
}

TEST(Backend, test05) {
  std::string str = "atan(0.5422/23.12)+tan(0.256)+log(2.21)";
  long double origin = 0.6295825;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, origin, 0.0000001);
}

TEST(Backend, test06) {
  std::string str = "12+(cos(23.12+sin(12.12-cos(2.21/12))))";
  long double origin = 11.00962042178;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, origin, 0.00001);
}

TEST(Backend, test07) {
  std::string str = "tan(3.14159/2)";
  long double origin = 753695.995140;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  EXPECT_NEAR(res, origin, 0.00001);
}

TEST(Backend, test08) {
  std::string str = "-3-(-4)";
  long double origin = 1;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  ASSERT_EQ(res, origin);
}

TEST(Backend, test09) {
  std::string str = ".";
  int error = 0;
  s21::controller control(str);
  control.controller_string(&error);
  ASSERT_EQ(error, 1);
}

TEST(Backend, test10) {
  std::string str = "acos()";
  int error = 0;
  s21::controller control(str);
  control.controller_string(&error);
  ASSERT_EQ(error, 1);
}

TEST(Backend, test11) {
  std::string str = "sin(3.14159/2)*2.231^3-acos(0.123)";
  long double origin = 9.65700833938;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, origin, 0.00001);
}

TEST(Backend, test12) {
  std::string str = "5^2+25/5*6";
  long double origin = 55;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  ASSERT_EQ(res, origin);
}

TEST(Backend, test13) {
  std::string str = "10mod5";
  long double origin = 0;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, origin, 0.0000001);
}

TEST(Backend, test14) {
  std::string str = "sqrt(15)";
  long double origin = 3.8729833;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, origin, 0.0000001);
}

TEST(Backend, test15) {
  std::string str = "ln(2.718281828459045)";
  double origin = 0.99999999;
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, origin, 0.0000001);
}

TEST(Backend, test16) {
  std::string str = "0*3+sin(-55)";
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, 0.9997551, 0.0000001);
}

TEST(Backend, test17) {
  std::string str = "0*3+cos(-55)";
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, 0.022126756262, 0.0000001);
}

TEST(Backend, test18) {
  std::string str = "acos(-1)+53542/4555+(22+1.511)";
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, 38.407148087, 0.0001);
}

TEST(Backend, test19) {
  std::string str = "asin(-1)+53542/4555+(22+1.511)";
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, 33.6947591, 0.0000001);
}

TEST(Backend, test22) {
  std::string str = "sin(22)/cos(22)+5";
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, 5.0088516, 0.0000001);
}

TEST(Backend, test23) {
  std::string str = "log(10)+ln(5)/sqrt(5)";
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, 1.7197625, 0.0000001);
}

TEST(Backend, test24) {
  std::string str = "75/atan(-5)*7*3*3*2*2*2*2*2";
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, -110091.681640989, 0.0000001);
}

TEST(Backend, test25) {
  std::string str = "3*2*2*2*2*2*";
  int error = 0;
  s21::controller control(str);
  control.controller_string(&error);
  ASSERT_EQ(error, 1);
}

TEST(Backend, test26) {
  std::string str = "+7.5";
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  ASSERT_EQ(res, 7.5);
}

TEST(Backend, test27) {
  std::string str = "7.5.5.5";
  int error = 0;
  s21::controller control(str);
  control.controller_string(&error);
  ASSERT_EQ(error, 1);
}

TEST(Backend, test28) {
  std::string str = "7.5";
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  ASSERT_EQ(res, 7.5);
}

TEST(Backend, test28a) {
  std::string str = "2^cos(2)";
  int error = 0;
  s21::controller control(str);
  double res = control.controller_string(&error);
  ASSERT_EQ(error, 0);
  EXPECT_NEAR(res, 0.74942352, 0.0000001);
}

TEST(Backend, test30) {
  std::string str = "mod";
  int error = 0;
  s21::controller control(str);
  control.controller_string(&error);
  ASSERT_EQ(error, 1);
}

TEST(Backend, test31) {
  std::string str = "5mod0";
  int error = 0;
  s21::controller control(str);
  control.controller_string(&error);
  ASSERT_EQ(error, 1);
}

TEST(Backend, test32) {
  std::string str = "5/0";
  int error = 0;
  s21::controller control(str);
  control.controller_string(&error);
  ASSERT_EQ(error, 1);
}

TEST(Backend, test33) {
  std::string str = "-";
  int error = 0;
  s21::controller control(str);
  control.controller_string(&error);
  ASSERT_EQ(error, 1);
}

TEST(Backend, test34) {
  std::string str = "cos(.)";
  int error = 0;
  s21::controller control(str);
  control.controller_string(&error);
  ASSERT_EQ(error, 1);
}

TEST(Backend, test35) {
  int error = 0;
  std::string str = "5^";
  s21::controller control(str);
  control.controller_string(&error);
  ASSERT_EQ(error, 1);
}

TEST(Backend, test36) {
  s21::model A("1+1");
  s21::model B = A;
}

TEST(Backend, test37) {
  s21::model A("1+1");
  s21::model B = std::move(A);
}

TEST(Backend, test38) {
  s21::model A("1+1");
  s21::model B("2+2");
  B = A;
}

TEST(Backend, test39) {
  s21::model A("1+1");
  s21::model B("2+2");
  B = std::move(A);
}

TEST(Backend, test40) {
  s21::controller A("1+1");
  s21::controller B = A;
}

TEST(Backend, test41) {
  s21::controller A("1+1");
  s21::controller B = std::move(A);
}

TEST(Backend, test42) {
  s21::controller A("1+1");
  s21::controller B("2+2");
  B = A;
}

TEST(Backend, test43) {
  s21::controller A("1+1");
  s21::controller B("2+2");
  B = std::move(A);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
