#include "DateTime.h"
#include <iostream>
#include <cstring>
#include <iomanip>

int DateTime::count = 0;

// Проверка високосного года
bool DateTime::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); // принимаем год не меняем обьект, высокосный если делиться на 4 но не на 400 или делиться на 100
}

// Количество дней в месяце
int DateTime::daysInMonth(int m, int y) const { // дней в месяце
    if (m == 2) return isLeapYear(y) ? 29 : 28;  // с вопросом, слева если истина справа от точек ложь
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

// Нормализация даты
void DateTime::normalizeDate() {
    // Нормализация секунд
    while (seconds >= 60) {
        seconds -= 60;
        minutes++;
    }
    while (seconds < 0) {
        seconds += 60;
        minutes--;
    }

    // Нормализация минут
    while (minutes >= 60) {
        minutes -= 60;
        hours++;
    }
    while (minutes < 0) {
        minutes += 60;
        hours--;
    }

    // Нормализация часов
    while (hours >= 24) {
        hours -= 24;
        day++;
    }
    while (hours < 0) {
        hours += 24;
        day--;
    }

    // Нормализация дней
    while (day > daysInMonth(month, year)) {
        day -= daysInMonth(month, year);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    while (day < 1) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
        }
        day += daysInMonth(month, year);
    }
}

// Обновление строкового представления
void DateTime::updateDateString() {
    if (dateString != nullptr) { 
        delete[] dateString; // если указатель нулевой освобождаем удаляем память выделенную
    }
    char buffer[50]; // временный массив символов на стеке
    snprintf(buffer, sizeof(buffer), "%02d.%02d.%04d %02d:%02d:%02d", //безопасно форматируем строку
             day, month, year, hours, minutes, seconds);
    dateString = new char[strlen(buffer) + 1]; // выделяем память под строку новую
    strcpy(dateString, buffer); // копируем из буфера
}

// Конструктор по умолчанию
DateTime::DateTime() : day(1), month(1), year(2000), hours(0), minutes(0), seconds(0), dateString(nullptr) { // устанавливаем начальные значения
    updateDateString(); // создаем строковое представление
    count++;
}

// Конструктор с параметрами
DateTime::DateTime(int d, int m, int y, int h, int min, int s) : // собираем все 
    day(d), month(m), year(y), hours(h), minutes(min), seconds(s), dateString(nullptr) {
    normalizeDate(); // убираем то что сделал тот кто сделал грязь
    updateDateString(); // и строку в придачу добавляем, делаем точнее
    count++;
}

// Конструктор копирования
DateTime::DateTime(const DateTime& other) : // через ссылку копируем
    day(other.day), month(other.month), year(other.year), 
    hours(other.hours), minutes(other.minutes), seconds(other.seconds), dateString(nullptr) { // копируем все простые поля
    if (other.dateString != nullptr) {
        dateString = new char[strlen(other.dateString) + 1];
        strcpy(dateString, other.dateString);
    } // ну мы же не дураки, просто так не копируем ссылку, а делаем красиво, создаем новый
    count++;
}

// Деструктор
DateTime::~DateTime() { // чисти чисти, да как я тебе вилкой должен чистить
    if (dateString != nullptr) {
        delete[] dateString;
    }
    count--;
}

// Оператор присваивания
DateTime& DateTime::operator=(const DateTime& other) { // вызываем при копировании
    if (this != &other) { // если мы дураки и решили перекопировать 
        // Освобождаем старую память
        if (dateString != nullptr) {
            delete[] dateString;
            dateString = nullptr;
        }
        
        // Копируем данные
        day = other.day;
        month = other.month;
        year = other.year;
        hours = other.hours;
        minutes = other.minutes;
        seconds = other.seconds;
        
        // Копируем строку
        if (other.dateString != nullptr) { 
            dateString = new char[strlen(other.dateString) + 1];
            strcpy(dateString, other.dateString);
        }
    }
    return *this;
}

// Добавление дней
void DateTime::addDays(int n) {
    day += n;
    normalizeDate();
    updateDateString();
}

// Добавление часов
void DateTime::addHours(int n) {
    hours += n;
    normalizeDate();
    updateDateString();
}

// Добавление минут
void DateTime::addMinutes(int n) {
    minutes += n;
    normalizeDate();
    updateDateString();
}

// Добавление секунд
void DateTime::addSeconds(int n) {
    seconds += n;
    normalizeDate();
    updateDateString();
}

// Вывод даты и времени
void DateTime::print() const {
    std::cout << dateString << std::endl;
}

// Получение количества объектов
int DateTime::getCount() {
    return count;
}