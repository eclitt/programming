#pragma once // предотвращает многократное включение одного и того же заголовочного файла
#include <cstring> // для си подобных строк, по заданию динамическое выделение

class DateTime { // ваще не класс((
private: // приваточка, только для методов
    int day, month, year;
    int hours, minutes, seconds;
    char* dateString; // Динамическая строка, по заданию, ссылочки там
    static int count; // Статический счётчик, единственный для всего класса
    // Приватные функции ждя класса
    void updateDateString(); // Обновление строки даты
    bool isLeapYear(int y) const; // высокосный ли
    int daysInMonth(int m, int y) const; // дней в месяце
    void normalizeDate(); // Нормализация даты
// интерфейс класса
public:
    // Конструкторы и деструктор
    DateTime(); // создаем с начальными параметрами
    DateTime(int d, int m, int y, int h, int min, int s); //с указанными параметрами
    DateTime(const DateTime& other); // копируем
    ~DateTime(); // удаляем и освобождаем дин память

    // Оператор присваивания
    DateTime& operator=(const DateTime& other); // без произойдет поверх копирование указателей

    // Методы изменения даты и времени
    void addDays(int n);
    void addHours(int n);
    void addMinutes(int n);
    void addSeconds(int n);

    // Методы вывода
    void print() const; // коснт указывает что не меняем обьект

    // Статический метод
    static int getCount(); // колво созданных обьектов, работает на уровне класса
};