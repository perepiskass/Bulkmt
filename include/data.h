#pragma once
#include <vector>
#include <string>
#include <queue>
#include <condition_variable>
#include "logger.h"

using Time = std::chrono::seconds;
using Bulk = std::pair<std::vector<std::string>,Time>;

class DataIn
{
public:
    DataIn(int count);
    void setData(std::string&& str);
    void notify();
    Bulk getBulk();

    std::queue<Bulk> bulkQ;

private:
    void clearData();
    void checkDilimiter(std::string& str);
    void setQueue();

    std::pair<bool,uint8_t> checkD; ///< переменная для проверки использования знаков динамического разделения блоков "{" и "}" и хранения состояния о их кол-ве
    Bulk bulk;
    const int count;        ///< хранит информацию о размере блока, задаеться при запуске программы (инициализируеться в конструкторе)
    int countTry;           ///< оставшееся ко-во команд для ввода в блок для его формирования
};

class DataToConsole
{
    private:
        std::shared_ptr<DataIn> _data;
    
    public:
        DataToConsole(std::shared_ptr<DataIn> data);
        void update(int id);
};

class DataToFile
{
    private:
        std::shared_ptr<DataIn> _data;

    public:
        DataToFile(std::shared_ptr<DataIn> data);
        void update(int id);
};

