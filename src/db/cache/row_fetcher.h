#pragma once

#include <QObject>

#include <condition_variable>
#include <mutex>

#include "cache_window.hpp"
#include "../db_base_table.hpp"

// TODO CancelTask ?

class FetchTask{
    CacheWindow _window;
    SelectQuery _query;
public:
    FetchTask(CacheWindow w, SelectQuery q)
        : _window(w)
        , _query{q.limit(w.size()).offset(w.left())}
    {
    }
    CacheWindow& window() { return _window; }
    SelectQuery& query() { return _query; }
};

class RowFetcher : public QObject{
    Q_OBJECT
    const DbBaseTable* const _table;
    std::vector<FetchTask> _tasks;

    std::mutex _taskMutex; // protects _tasks and _running
    std::condition_variable _task_cv;
    bool _running;

public:
    RowFetcher(const DbBaseTable* const table);
    ~RowFetcher();

public slots:
    void run();
    void stop();
    void push_back(FetchTask task);

signals:
    void rowsFetched(CacheWindow window, std::vector<TableRow> row);
};

