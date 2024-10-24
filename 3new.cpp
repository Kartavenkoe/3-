#include <iostream>          // Подключение библиотеки для ввода/вывода
#include <vector>           // Подключение библиотеки для работы с векторами
#include <string>           // Подключение библиотеки для работы со строками
#include <limits>           // Подключение библиотеки для работы с границами типов данных
#include <cctype>           // Подключение библиотеки для работы с символами
#include <stdexcept>        // Подключение библиотеки для обработки исключений

class Point {              // Определение класса Point для представления точки на плоскости
private:
    int x, y;             // Закрытые переменные для хранения координат точки
public:
    Point(int x, int y) : x(x), y(y) {}   // Конструктор класса, инициализирующий координаты точки
    std::string print() const {             // Метод для получения строки с представлением точки
        return "{" + std::to_string(x) + ";" + std::to_string(y) + "}"; // Форматирование строки
    }
};

// Определение класса Line для представления линии
class Line {
private:
    Point start, end;      // Переменные для хранения начальной и конечной точек линии
public:
    Line(Point start, Point end) : start(start), end(end) {}  // Конструктор класса, инициализирующий начальную и конечную точки
    Point getStart() const { return start; } // Метод для получения начальной точки линии
    Point getEnd() const { return end; }     // Метод для получения конечной точки линии
    void setStart(Point newStart) { start = newStart; } // Метод для установки новой начальной точки
    void setEnd(Point newEnd) { end = newEnd; } // Метод для установки новой конечной точки
    std::string print() const {          // Метод для получения строки с представлением линии
        return "Линия от " + start.print() + " до " + end.print(); // Форматирование строки
    }
};

// Класс для представления студента
class Student {
private:
    std::string name;                          // Имя студента
    std::vector<int> grades;                   // Вектор для хранения оценок студента
public:
    Student(const std::string& name, const std::vector<int>& grades = {}) : name(name), grades(grades) {} // Конструктор класса
    std::string print() const {               // Метод для получения строки с представлением студента
        std::string result = "Имя: " + name + " ["; // Начало строки с именем и оценками
        for (size_t i = 0; i < grades.size(); i++) { // Цикл по всем оценкам
            result += std::to_string(grades[i]); // Добавление оценки к строке
            if (i < grades.size() - 1)         // Если это не последняя оценка
                result += ", ";                 // Добавление запятой
        }
        result += "]";                          // Закрывающая скобка
        return result;                          // Возврат итоговой строки
    }
    float averageGrade() const {               // Метод для расчета среднего балла
        if (grades.empty()) return 0;          // Если оценок нет, вернуть 0
        float sum = 0;                         // Переменная для суммы оценок
        for (int grade : grades) {             // Цикл по всем оценкам
            sum += grade;                      // Суммирование оценок
        }
        return sum / grades.size();            // Возврат среднего балла
    }
    bool isExcellent() const {                  // Метод для проверки, является ли студент отличником
        if (grades.empty()) return false;      // Если нет оценок, вернуть false
        for (int grade : grades) {             // Цикл по всем оценкам
            if (grade != 5) return false;      // Если хотя бы одна оценка не 5, вернуть false
        }
        return true;                           // Если все оценки 5, вернуть true
    }
    void setGrade(size_t index, int value) {   // Метод для установки оценки по индексу
        if (index < grades.size()) {           // Проверка на выход за пределы
            grades[index] = value;             // Установка новой оценки
        } else {
            std::cerr << "Индекс выхода за пределы! Попробуйте снова.\n"; // Сообщение об ошибке
        }
    }
    const std::vector<int>& getGrades() const { // Метод для получения оценок
        return grades;                         // Возврат вектора оценок
    }
    void setGrades(const std::vector<int>& newGrades) { // Метод для установки новых оценок
        grades = newGrades;                  // Установка новых оценок
    }
};

// Утилитарные функции для валидации ввода
template<typename T> // Шаблонная функция для получения значения с валидацией
T getValue(const std::string& prompt) {
    T value; // Переменная для хранения введенного значения
    while (true) { // Бесконечный цикл для повторного запроса в случае ошибки
        std::cout << prompt; // Вывод сообщения запроса
        std::cin >> value;   // Ввод значения
        if (std::cin.fail()) { // Если произошла ошибка считывания
            std::cin.clear(); // Очистка состояния потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование некорректного ввода
            std::cout << "Ошибка ввода! Пожалуйста, введите корректное значение.\n"; // Сообщение об ошибке
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка остатка строки
            return value; // Возврат корректного значения
        }
    }
}

// Функция проверки имени на наличие чисел
bool isNameValid(const std::string& name) {
    for (char c : name) { // Цикл по всем символам в имени
        if (std::isdigit(c)) { // Если символ является цифрой
            return false; // Возврат false, имя недействительно
        }
    }
    return true; // Если все символы валидные, возвращаем true
}

// Функция для получения имени студента с проверкой
std::string getStudentName(const std::string& prompt) {
    std::string name; // Переменная для хранения имени
    while (true) { // Бесконечный цикл для повторного запроса в случае ошибки
        std::cout << prompt; // Вывод сообщения запроса
        std::getline(std::cin, name); // Чтение строки с именем
        if (isNameValid(name)) { // Проверка имени на валидность
            return name; // Возврат валидного имени
        } else {
            std::cout << "Ошибка! Имя не должно содержать цифр. Попробуйте снова.\n"; // Сообщение об ошибке
        }
    }
}

// Функция для получения оценки с проверкой
int getValidGrade() {
    int grade; // Переменная для хранения оценки
    while (true) { // Бесконечный цикл для повторного запроса в случае ошибки
        grade = getValue<int>("Введите оценку (от 1 до 5): "); // Запрос оценки
        if (grade >= 1 && grade <= 5) { // Проверка валидности оценки
            return grade; // Возврат валидной оценки
        } else {
            std::cout << "Ошибка! Оценка должна быть от 1 до 5. Попробуйте снова.\n"; // Сообщение об ошибке
        }
    }
}

void task1() { 
    std::cout << "Задача 1:\n"; 
    int x, y; // Переменные для хранения координат
    std::cout << "Введите координаты точки 1 (x y): "; // Запрос координат первой точки
    std::cin >> x >> y; // Ввод координат первой точки
    if (std::cin.fail()) { // Проверка на ошибки
        std::cin.clear(); // Очистка состояния потока
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование некорректного ввода
        std::cout << "Ошибка! Ввод должен быть числом. Попробуйте снова.\n"; // Сообщение об ошибке
        return; // Завершение задачи 1
    }
    Point p1(x, y); // Создание первой точки
    
    std::cout << "Введите координаты точки 2 (x y): "; // Запрос координат второй точки
    std::cin >> x >> y; // Ввод координат второй точки
    if (std::cin.fail()) { // Проверка на ошибки
        std::cin.clear(); // Очистка состояния потока
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование некорректного ввода
        std::cout << "Ошибка! Ввод должен быть числом. Попробуйте снова.\n"; // Сообщение об ошибке
        return; // Завершение задачи 1
    }
    Point p2(x, y); // Создание второй точки
    
    std::cout << "Введите координаты точки 3 (x y): "; // Запрос координат третьей точки
    std::cin >> x >> y; // Ввод координат третьей точки
    if (std::cin.fail()) { // Проверка на ошибки
        std::cin.clear(); // Очистка состояния потока
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование некорректного ввода
        std::cout << "Ошибка! Ввод должен быть числом. Попробуйте снова.\n"; // Сообщение об ошибке
        return;   
    }
    Point p3(x, y); // Создание третьей точки
    
    std::cout << "Точки:\n"; 
    std::cout << p1.print() << "\n"; 
    std::cout << p2.print() << "\n"; 
    std::cout << p3.print() << "\n"; 
}

void task2() { // Функция для задачи 2
    std::cout << "Задача 2:\n"; // Вывод заголовка задачи
    Point start1(1, 3); // Создание первой стартовой точки
    Point end1(23, 8); // Создание первой конечной точки
    Line line1(start1, end1); // Создание линии 1
    std::cout << "Линия 1: " << line1.print() << "\n"; // Вывод линии 1
    int height = 10; // Высота для линии 2
    Point start2(5, height); // Создание стартовой точки для линии 2
    Point end2(25, height); // Создание конечной точки для линии 2
    Line line2(start2, end2); // Создание линии 2
    std::cout << "Линия 2: " << line2.print() << "\n"; // Вывод линии 2
    Line line3(start1, end2); // Создание линии 3
    std::cout << "Линия 3 (зависит от линий 1 и 2): " << line3.print() << "\n"; // Вывод линии 3

    // Обновление координат для линии 1
    int newX1Start = 2, newY1Start = 4, newX1End = 24, newY1End = 9; // Новые координаты для линии 1
    line1.setStart(Point(newX1Start, newY1Start)); // Установка новой начальной точки для линии 1
    line1.setEnd(Point(newX1End, newY1End)); // Установка новой конечной точки для линии 1
    std::cout << "После изменения линии 1:\n"; // Сообщение о результате
    std::cout << line1.print() << "\n"; // Вывод измененной линии 1
    line3.setStart(Point(newX1Start, newY1Start)); // Установка новой начальной точки для линии 3
    line3.setEnd(end2); // Установка конца линии 3
    std::cout << "Линия 3 после изменения линии 1:\n"; // Сообщение о результате
    std::cout << line3.print() << "\n"; // Вывод измененной линии 3

    // Обновление координат для линии 2
    int newHeight = 12, newX2Start = 6, newX2End = 26; // Новые координаты для линии 2
    line2.setStart(Point(newX2Start, newHeight)); // Установка новой начальной точки для линии 2
    line2.setEnd(Point(newX2End, newHeight)); // Установка новой конечной точки для линии 2
    std::cout << "После изменения линии 2:\n"; // Сообщение о результате
    std::cout << line2.print() << "\n"; // Вывод измененной линии 2
    line3.setEnd(Point(newX2End, newHeight)); // Установка конца линии 3
    std::cout << "Линия 3 после изменения линии 2:\n"; // Сообщение о результате
    std::cout << line3.print() << "\n"; // Вывод измененной линии 3
}

void task3() { // Функция для задачи 3
    std::cout << "Задача 3:\n"; // Вывод заголовка задачи
    std::string name1 = getStudentName("Введите имя первого студента: "); // Получение имени первого студента
    std::vector<int> grades1 = { // Вектор для хранения оценок первого студента
        getValidGrade(), // Запрос оценки 1
        getValidGrade(), // Запрос оценки 2
        getValidGrade()  // Запрос оценки 3
    };
    Student student1(name1, grades1); // Создание первого студента
    
    std::string name2 = getStudentName("Введите имя второго студента: "); // Получение имени второго студента
    Student student2(name2, student1.getGrades()); // Создание второго студента, копирующего оценки из первого
    student2.setGrade(0, 5); // Установка первой оценки второго студента на 5
    
    std::cout << student1.print() << "\n"; // Вывод первого студента
    std::cout << student2.print() << "\n"; // Вывод второго студента
    std::string name3 = getStudentName("Введите имя третьего студента: "); // Получение имени третьего студента
    Student student3(name3, student1.getGrades()); // Создание третьего студента, копирующего оценки из первого
    
    student1.setGrade(0, 4); // Изменение первой оценки первого студента на 4
    std::cout << "После изменения оценок:\n"; // Вывод сообщения о результате
    std::cout << student1.print() << "\n"; // Вывод первого студента
    std::cout << student2.print() << "\n"; // Вывод второго студента
    std::cout << student3.print() << "\n"; // Вывод третьего студента
}

void task4() { // Функция для задачи 4
    std::cout << "Задача 4:\n"; // Вывод заголовка задачи
    int numberOfPoints = getValue<int>("Введите количество точек, которые вы хотите ввести: "); // Запрос количества точек
    std::vector<Point> points; // Вектор для хранения введенных точек
    for (int i = 0; i < numberOfPoints; ++i) { // Цикл по количеству точек
        int x, y; // Переменные для хранения координат
        std::cout << "Введите координаты точки " << (i + 1) << " (x y): "; // Запрос координат точки
        std::cin >> x >> y; // Ввод координат точки
        if (std::cin.fail()) { // Проверка на ошибки
            std::cin.clear(); // Очистка состояния потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование некорректного ввода
            std::cout << "Ошибка! Ввод должен быть числом. Попробуйте снова.\n"; // Сообщение об ошибке
            i--; // Уменьшить индекс для повторного ввода
            continue; // Пропустить оставшуюся часть цикла
        }
        points.emplace_back(x, y); // Добавление точки в вектор
    }
    std::cout << "Точки:\n"; // Вывод заголовка для точек
    for (const auto& point : points) { // Цикл по всем точкам
        std::cout << point.print() << "\n"; // Вывод текущей точки
    }
}

void task5() { // Функция для задачи 5
    std::cout << "Задача 5:\n"; // Вывод заголовка задачи
    std::string name1 = getStudentName("Введите имя первого студента: "); // Получение имени первого студента
    std::vector<int> grades1; // Вектор для хранения оценок первого студента
    int grade; // Переменная для хранения одной оценки
    while (true) { // Бесконечный цикл для ввода оценок
        grade = getValidGrade(); // Запрос оценки
        grades1.push_back(grade); // Сохранение оценки в вектор
        std::cout << "Введите следующую оценку для " << name1 << " (или введите -1 для завершения ввода): "; // Запрос на ввод следующей оценки
        std::cin >> grade; // Ввод следующей оценки
        if (grade == -1) break; // Если введено -1, выходим из цикла
        grades1.push_back(grade); // Сохранение новой оценки в вектор
    }
    Student student1(name1, grades1); // Создание первого студента с введенными оценками
    
    std::string name2 = getStudentName("Введите имя второго студента: "); // Получение имени второго студента
    std::vector<int> grades2; // Вектор для хранения оценок второго студента
    while (true) { // Бесконечный цикл для ввода оценок
        grade = getValidGrade(); // Запрос оценки
        grades2.push_back(grade); // Сохранение оценки в вектор
        std::cout << "Введите следующую оценку для " << name2 << " (или введите -1 для завершения ввода): "; // Запрос на ввод следующей оценки
        std::cin >> grade; // Ввод следующей оценки
        if (grade == -1) break; // Если введено -1, выходим из цикла
        grades2.push_back(grade); // Сохранение новой оценки в вектор
    }
    Student student2(name2, grades2); // Создание второго студента с введенными оценками
    
    std::cout << student1.print() << "\n"; // Вывод первого студента
    std::cout << "Средний балл студента " << name1 << ": " << student1.averageGrade() << "\n"; // Вывод среднего балла первого студента
    std::cout << "Является ли студент " << name1 << " отличником: " << std::boolalpha << student1.isExcellent() << "\n"; // Проверка, является ли студент отличником
    std::cout << student2.print() << "\n"; // Вывод второго студента
    std::cout << "Средний балл студента " << name2 << ": " << student2.averageGrade() << "\n"; // Вывод среднего балла второго студента
    std::cout << "Является ли студент " << name2 << " отличником: " << std::boolalpha << student2.isExcellent() << "\n"; // Проверка, является ли студент отличником
}

void task6() { // Функция для задачи 6
    std::cout << "Задача 6:\n"; // Вывод заголовка задачи
    std::string name1 = getStudentName("Введите имя первого студента: "); // Получение имени первого студента
    std::vector<int> grades1; // Вектор для хранения оценок первого студента
    int grade; // Переменная для хранения одной оценки
    
    while (true) { // Бесконечный цикл для ввода оценок
        grade = getValidGrade(); // Запрос оценки
        grades1.push_back(grade); // Сохранение оценки в вектор
        
        std::cout << "Введите следующую оценку для " << name1 << " (или введите -1 для завершения ввода): "; // Запрос на ввод следующей оценки
        std::cin >> grade; // Ввод следующей оценки
        
        if (grade == -1) break; // Если введено -1, выходим из цикла
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
    
    Student student1(name1, grades1); // Создание первого студента с введенными оценками
    std::cout << student1.print() << "\n"; // Вывод первого студента
    std::string name2 = getStudentName("Введите имя второго студента: "); // Получение имени второго студента
    Student student2(name2); // Создание второго студента без оценок
    std::cout << student2.print() << "\n"; // Вывод второго студента
}

int main() { // Главная функция программы
    int choice; // Переменная для хранения выбора пользователя
    while (true) { // Бесконечный цикл для меню
        std::cout << "\nМеню:\n";  
        std::cout << "1. Точка\n"; 
        std::cout << "2. Линия\n"; 
        std::cout << "3. Студенты\n"; 
        std::cout << "4. Точка (измененные требования)\n"; 
        std::cout << "5. Студенты (измененные требования)\n"; 
        std::cout << "6. Студенты (новые требования)\n"; 
        std::cout << "0. Выход\n"; 
        choice = getValue<int>("Выберите задачу: "); 
        
        switch (choice) { // Switch для обработки выбранной задачи
            case 1: task1(); break; 
            case 2: task2(); break; 
            case 3: task3(); break; 
            case 4: task4(); break; 
            case 5: task5(); break; 
            case 6: task6(); break; 
            case 0: return 0; 
            default: std::cout << "Некорректный выбор. Попробуйте еще раз.\n"; 
        }
    }
}
