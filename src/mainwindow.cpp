#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setModel(&_model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
