#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dynamic_sqlite_model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DynamicSQLiteModel _model;
};
#endif // MAINWINDOW_H
