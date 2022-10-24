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
    DbInstance _db;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void filterChanged(QString const& text, int col);

private:
    Ui::MainWindow *ui;
    DynamicSQLiteModel _model;
};
#endif // MAINWINDOW_H
