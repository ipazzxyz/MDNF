#pragma once
#include <vector>
#include <string>
#include <set>
namespace utility
{
  int count1(int);
  int countlen(std::set<std::string>);
} // namespace utility
struct Back
{
  int step_ = 0;
  std::vector<std::vector<int>> table_;
  std::vector<std::vector<int>> color_;
  std::set<std::string> ans_base_;
  std::set<std::set<std::string>> ans_;

  Back(int, unsigned long long);

  void resize(int);
  void fillHead();
  void fillFunction(unsigned long long);
  void fillBody();
  void nextStep();
  std::string normalize(int, int);

  int findOnlyOneInRow(int);

  std::string getstring(int, int);
  void pereborhahaha(int, std::set<std::string>);
  void eraselishnee();
  std::string imbored();
  void step1();
  void step2();
  void step3();
  void step4();
  void recolorOld();
  void recolorColumn(int);
  void recolorInColumn(int, int);
  void recolorLargerInRow(int, int);

  int size_;
};
