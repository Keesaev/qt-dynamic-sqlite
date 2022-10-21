#pragma once

#include "window.hpp"

#include <mutex>
#include <vector>

#include <QObject>

class Fetcher : public QObject{
    Q_OBJECT
    std::mutex _taskMutex;
    std::vector<Window> _tasks;
public:
    Fetcher(){}

    void run(){
    }
public slots:
    void push_back(Window w){
    }
signals:
    void fetched(Window w) const;
};
