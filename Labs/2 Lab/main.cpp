#include "DateTime.h"
#include <iostream>

int main() {
    std::cout << "=== Testing DateTime class ===" << std::endl;
    
    // Тестирование конструкторов
    DateTime dt1;
    std::cout << "Default constructor: ";
    dt1.print();

    DateTime dt2(15, 7, 2024, 14, 30, 45);
    std::cout << "Parameter constructor: ";
    dt2.print();

    DateTime dt3 = dt2;
    std::cout << "Copy constructor: ";
    dt3.print();

    std::cout << "Objects count: " << DateTime::getCount() << std::endl;

    // Тестирование методов
    std::cout << "\n=== Testing methods ===" << std::endl;
    
    dt2.addDays(10);
    std::cout << "After adding 10 days: ";
    dt2.print();

    dt2.addHours(5);
    std::cout << "After adding 5 hours: ";
    dt2.print();

    dt2.addMinutes(90);
    std::cout << "After adding 90 minutes: ";
    dt2.print();

    dt2.addSeconds(120);
    std::cout << "After adding 120 seconds: ";
    dt2.print();

    // Тестирование счетчика объектов
    std::cout << "\n=== Testing object counter ===" << std::endl;
    {
        DateTime temp(1, 1, 2025, 0, 0, 0);
        std::cout << "Temp object created. Count: " << DateTime::getCount() << std::endl;
    }
    std::cout << "After temp destruction. Count: " << DateTime::getCount() << std::endl;

    return 0;
}