#include "Front.hpp"
#include <QApplication>
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Front w;
  app.exec();
}