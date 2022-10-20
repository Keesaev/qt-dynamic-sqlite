#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

#include "db/db_test_table.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setModel(&_model);

    db_instance inst("./../test/test.db");
    db_test_table test(inst, "TEST_TABLE");

    auto select = test.select(select_query(test.table_name(), test.row_count()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
