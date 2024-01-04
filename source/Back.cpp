#include "Back.hpp"
#include <iostream>
#include <algorithm>
int utility::count1(int x)
{
  return bool(x & 1) + bool(x & 2) + bool(x & 4) + bool(x & 8) + bool(x & 16) + bool(x & 32);
}
int utility::countlen(std::set<std::string> s)
{
  int result = 0;
  for (auto it = s.begin(); it != s.end(); ++it)
  {
    for (char c : (*it))
    {
      if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f')
      {
        ++result;
      }
    }
  }
  return result;
}
Back::Back(int length, unsigned long long function)
{
  resize(length);
  fillHead();
  fillFunction(function);
  fillBody();
}
void Back::resize(int length)
{
  size_ = length;
  table_.resize((1 << length) + 1);
  color_.resize((1 << length) + 1);
  for (int i = 0; i < table_.size(); ++i)
  {
    table_[i].resize(1 << length);
    color_[i].resize(1 << length);
  }
}
void Back::fillHead()
{
  for (int i = 1; i < table_[0].size(); ++i)
  {
    table_[0][i] = i;
  }
  std::sort(table_[0].begin() + 1, table_[0].end(), [](int a, int b)
            {int a_cnt = bool(a & 1) + bool(a & 2) + bool(a & 4) + bool(a & 8) + bool(a & 16) + bool(a & 32),
            b_cnt = bool(b & 1) + bool(b & 2) + bool(b & 4) + bool(b & 8) + bool(b & 16) + bool(b & 32);
            return a_cnt < b_cnt || a_cnt == b_cnt && a > b; });
}
void Back::fillFunction(unsigned long long function)
{
  for (int i = 1; i < table_.size(); ++i)
  {
    table_[i][0] = bool(function & ((unsigned long long)1 << (table_.size() - (i + 1))));
  }
}
void Back::fillBody()
{
  for (int i = 1; i < table_.size(); ++i)
  {
    for (int j = 1; j < table_[0].size(); ++j)
    {
      table_[i][j] = i - 1 & table_[0][j];
    }
  }
}
void Back::recolorOld()
{
  for (int i = 0; i < table_.size(); ++i)
  {
    for (int j = 0; j < table_[0].size(); ++j)
    {
      if (color_[i][j] == 1)
      {
        color_[i][j] = 2;
      }
    }
  }
}
void Back::nextStep()
{
  recolorOld();
  if (step_ == 0)
  {
    step1();
  }
  else if (step_ == 1)
  {
    step2();
  }
  else if (step_ == 2)
  {
    step3();
  }
  else
  {
    step4();
  }
  ++step_;
}
void Back::step1()
{
  for (int i = 1; i < table_.size(); ++i)
  {
    if (!table_[i][0])
      for (int j = 0; j < table_[0].size(); ++j)
      {
        color_[i][j] = 1;
      }
  }
}
void Back::step2()
{
  for (int i = 1; i < table_.size(); ++i)
  {
    for (int j = 0; j < table_[i].size(); ++j)
    {
      if (color_[i][j])
      {
        recolorInColumn(j, table_[i][j]);
      }
    }
  }
}
void Back::step3()
{
  for (int i = 1; i < table_.size(); ++i)
  {
    for (int j = 1; j < table_[0].size(); ++j)
    {
      if (!color_[i][j])
      {
        recolorLargerInRow(i, j);
      }
    }
  }
}
void Back::step4()
{
  ans_.clear();
  for (int i = 1; i < table_.size(); ++i)
  {
    if (color_[i][0])
    {
      continue;
    }
    int tmp = findOnlyOneInRow(i);
    if (tmp == 0)
    {
      continue;
    }
    for (int j = 1; j < table_.size(); ++j)
    {
      if (color_[j][0])
      {
        continue;
      }
      if (table_[j][tmp] == table_[i][tmp])
      {
        color_[j][0] = 1;
      }
    }
    std::cout << 1;
    ans_base_.insert(getstring(i, tmp));
  }
  pereborhahaha(1, ans_base_);
  eraselishnee();
}
void Back::eraselishnee()
{
  int m = 99999;
  for (auto it = ans_.begin(); it != ans_.end(); ++it)
  {
    m = std::min(m, utility::countlen(*it));
  }
  for (auto it = ans_.begin(); it != ans_.end();)
  {
    if (utility::countlen(*it) > m)
    {
      it = ans_.erase(it);
    }
    else
    {
      ++it;
    }
  }
}
void Back::pereborhahaha(int begin, std::set<std::string> current)
{
  if (begin == table_.size())
  {
    ans_.insert(current);
    return;
  }
  if (color_[begin][0])
  {
    pereborhahaha(begin + 1, current);
    return;
  }
  for (int i = 1; i < table_[0].size(); ++i)
  {
    if (!color_[begin][i])
    {
      std::string thisoneisfrom7am = getstring(begin, i);
      if (current.find(thisoneisfrom7am) == current.end())
      {
        current.insert(thisoneisfrom7am);
        pereborhahaha(begin + 1, current);
        current.erase(thisoneisfrom7am);
      }
      else
      {
        pereborhahaha(begin + 1, current);
      }
    }
  }
}
std::string Back::imbored()
{
  std::string result;
  for (auto it = ans_.begin(); it != ans_.end(); ++it)
  {
    for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2)
    {
      result += *it2 + " + ";
    }
    result = result.substr(0, result.size() - 3);
    result += '\n';
  }
  if (!result.empty())
  {
    result.pop_back();
  }
  return result;
}
std::string Back::getstring(int x, int y)
{
  std::string result;
  if (table_[0][y] & 32)
  {
    if (!(table_[x][y] & 32))
    {
      result += '!';
    }
    result += 'a' - 6 + size_;
  }
  if (table_[0][y] & 16)
  {
    if (!(table_[x][y] & 16))
    {
      result += '!';
    }
    result += 'b' - 6 + size_;
  }
  if (table_[0][y] & 8)
  {
    if (!(table_[x][y] & 8))
    {
      result += '!';
    }
    result += 'c' - 6 + size_;
  }
  if (table_[0][y] & 4)
  {
    if (!(table_[x][y] & 4))
    {
      result += '!';
    }
    result += 'd' - 6 + size_;
  }
  if (table_[0][y] & 2)
  {
    if (!(table_[x][y] & 2))
    {
      result += '!';
    }
    result += 'e' - 6 + size_;
  }
  if (table_[0][y] & 1)
  {
    if (!(table_[x][y] & 1))
    {
      result += '!';
    }
    result += 'f' - 6 + size_;
  }
  return result;
}
int Back::findOnlyOneInRow(int row)
{
  int result = -1;
  for (int i = 1; i < table_[0].size(); ++i)
  {
    if (!color_[row][i])
    {
      if (result != -1)
      {
        return 0;
      }
      result = i;
    }
  }
  return result;
}
void Back::recolorColumn(int i)
{
  for (int k = 0; k < table_.size(); ++k)
  {
    if (!color_[k][i])
    {
      color_[k][i] = 1;
      color_[k][0] = 1;
    }
  }
}
void Back::recolorInColumn(int j, int elem)
{
  for (int i = 1; i < table_.size(); ++i)
  {
    if (table_[i][j] == elem && !color_[i][j])
    {
      color_[i][j] = 1;
    }
  }
}
void Back::recolorLargerInRow(int row, int j)
{
  for (int i = 0; i < table_[0].size(); ++i)
  {
    if (!color_[row][i] && (table_[0][j] & table_[0][i]) == table_[0][j] && table_[0][i] != table_[0][j])
    {
      color_[row][i] = 1;
    }
  }
}
std::string Back::normalize(int x, int y)
{
  if (x == 0 && y == 0)
  {
    return "F";
  }
  if (x == 0)
  {
    std::string result;
    if (table_[0][y] & 32)
    {
      result += 'a' - 6 + size_;
    }
    if (table_[0][y] & 16)
    {
      result += 'b' - 6 + size_;
    }
    if (table_[0][y] & 8)
    {
      result += 'c' - 6 + size_;
    }
    if (table_[0][y] & 4)
    {
      result += 'd' - 6 + size_;
    }
    if (table_[0][y] & 2)
    {
      result += 'e' - 6 + size_;
    }
    if (table_[0][y] & 1)
    {
      result += 'f' - 6 + size_;
    }
    return result;
  }
  if (y == 0)
  {
    return std::string(1, '0' + table_[x][0]);
  }
  std::string result;
  if (table_[0][y] & 32)
  {
    result += '0' + bool(table_[x][y] & 32);
  }
  if (table_[0][y] & 16)
  {
    result += '0' + bool(table_[x][y] & 16);
  }
  if (table_[0][y] & 8)
  {
    result += '0' + bool(table_[x][y] & 8);
  }
  if (table_[0][y] & 4)
  {
    result += '0' + bool(table_[x][y] & 4);
  }
  if (table_[0][y] & 2)
  {
    result += '0' + bool(table_[x][y] & 2);
  }
  if (table_[0][y] & 1)
  {
    result += '0' + bool(table_[x][y] & 1);
  }
  return result;
}