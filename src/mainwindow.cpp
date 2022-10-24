#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _db("../test/test.db")
    , _model(_db, "TEST_TABLE")
{
    ui->setupUi(this);

    ui->tableView->setModel(&_model);

    connect(ui->lineEdit1, &QLineEdit::editingFinished, &_model, [this](){
        _model.changeFilter(ui->lineEdit1->text(), 0);
    });
    connect(ui->lineEdit2, &QLineEdit::editingFinished, &_model, [this](){
        _model.changeFilter(ui->lineEdit2->text(), 1);
    });
    connect(ui->lineEdit3, &QLineEdit::editingFinished, &_model, [this](){
        _model.changeFilter(ui->lineEdit3->text(), 2);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
