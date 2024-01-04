#pragma once
#include "Back.hpp"
#include <QMainWindow>
#include <QTableWidget>
#include <QTextEdit>
class Front : public QMainWindow
{
    Q_OBJECT

public:
    Front();

private slots:
    void input();

private:
    QTableWidget *table_;
    QTextEdit *output_;
    Back *data_;

    void create();
    void update();
};