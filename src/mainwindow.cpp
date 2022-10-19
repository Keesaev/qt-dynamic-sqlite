#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

#include "db_wrapper.h" // TODO rm

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setModel(&_model);

    db_wrapper wr("/home/keesaev/dev/qt-dynamic-sqlite/test/test.db");
    wr.init();
    auto out = wr.select(999999);

    for(const auto& i : out){
        std::cout << i.id << " " << i.name << " " << i.code << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

