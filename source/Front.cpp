#include "Front.hpp"
#include <QWidget>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QSpinBox>
#include <QValidator>
#include <QPushButton>
Front::Front()
{
    create();
    input();
}
void Front::create()
{
    setGeometry(0, 0, 810, 625);

    QPushButton *input_window = new QPushButton(this);
    input_window->setGeometry(5, 5, 800, 50);
    input_window->setText("Open input window");
    connect(input_window, SIGNAL(clicked()), this, SLOT(input()));

    table_ = new QTableWidget(this);
    table_->setGeometry(5, 60, 800, 400);

    QPushButton *next_step = new QPushButton(this);
    next_step->setGeometry(5, 465, 800, 50);
    next_step->setText("Next step");
    connect(next_step, &QPushButton ::clicked, this, [=]()
            { data_->nextStep();
            update(); });

    output_ = new QTextEdit(this);
    output_->setGeometry(5, 520, 800, 100);

    show();
}
void Front::input()
{
    QWidget *input_window = new QWidget();
    input_window->setGeometry(0, 0, 265, 115);

    QLineEdit *function = new QLineEdit(input_window);
    function->setGeometry(5, 5, 200, 50);
    function->setAlignment(Qt::AlignCenter);
    function->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]\\d{0,19}"), input_window));

    QSpinBox *variable_count = new QSpinBox(input_window);
    variable_count->setGeometry(210, 5, 50, 50);
    variable_count->setRange(1, 6);

    QPushButton *confirm = new QPushButton(input_window);
    confirm->setGeometry(5, 60, 255, 50);
    confirm->setText("Confirm");
    connect(confirm, &QPushButton ::clicked, input_window, [=]()
            {data_ = new Back(variable_count->value(), function->text().toInt());
            update();
            input_window->close(); });

    input_window->show();
}
void Front::update()
{
    table_->setRowCount(data_->table_.size());
    table_->setColumnCount(data_->table_[0].size());
    for (int i = 0; i < data_->table_.size(); ++i)
    {
        for (int j = 0; j < data_->table_[0].size(); ++j)
        {
            QString sItem = QString::fromStdString(data_->normalize(i, j));
            QVariant oVariant(sItem);
            QTableWidgetItem *poItem = new QTableWidgetItem();
            poItem->setData(Qt::DisplayRole, oVariant);
            poItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            poItem->setTextAlignment(Qt::AlignCenter);
            table_->setItem(i, j, poItem);
            if (data_->color_[i][j] == 0)
            {
                table_->item(i, j)->setBackground(Qt::white);
            }
            else if (data_->color_[i][j] == 1)
            {
                table_->item(i, j)->setBackground(Qt::green);
            }
            else if (data_->color_[i][j] == 2)
            {
                table_->item(i, j)->setBackground(Qt::red);
            }
        }
    }
    output_->setText(QString::fromStdString(data_->imbored()));
}