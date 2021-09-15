// SimpleLoggerProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
#include "log.h"


/*
Example of console output:
23.02.2020 18:06:06; INFO; (1020): Starting the app
23.02.2020 18:06:06; DEBUG; (2561): Running a thread

Example of log.txt output:
23.02.2020 18:06:06; INFO; (2561): Running a thread
23.02.2020 18:06:06; DEBUG; f2(3444): Running a thread
23.02.2020 18:06:06; WARNING; f2(3444): Time spent in the thread: 10.0 seconds

Example of log2.txt:
23.02.2020 18:06:06; INFO; f3(3444): Running a thread
23.02.2020 18:06:06; ERROR; f3(3444): My int is 123;
*/

void f1() {
    auto consoleLogger = getLogger(); // Log to console
    // Console output: 23.02.2020 18:06:06; DEBUG; (2561): Running a thread
    consoleLogger(DEBUG) << "Running a thread";

    auto fileLogger = getLogger("log.txt"); // Log to file with name log.txt
    // File output: 23.02.2020 18:06:06; INFO; (2561): Running a thread
    fileLogger << "Running a thread"; // Default log level INFO
}

void f2() {
    auto logger = getLogger("log.txt", "f2"); // Log to file with name log.txt. Each message has f2 prefix
    // File output: 23.02.2020 18:06:06; DEBUG; f2(3444): Running a thread
    logger(DEBUG) << "Running a thread";

    double timeSpent = 10.0;
    // File output: 23.02.2020 18:06:06; WARNING; f2(3444): Time spent in the thread: 10.0 seconds
    logger(WARNING) << "Time spent in the thread: " << timeSpent << " seconds";
}

void f3() {
    auto logger = getLogger("log2.txt", "f3");  // Log to file with name log2.txt. Each message has f3 prefix
    // File output: 23.02.2020 18:06:06; INFO; f3(3444): Running a thread
    logger << "Running a thread"; // Default log level INFO

    int i = 123;
    // File output: 23.02.2020 18:06:06; ERROR; f3(3444): My int is 123;
    logger(ERROR) << "My int is " << i;
}

int main()
{
    auto logger = getLogger(); // Log to console
// Console output: 23.02.2020 18:06:06; INFO; (1020): Starting the app
   logger << "Starting the app"; // Default log level INFO


    std::thread t1(f1);
    std::thread t2(f2);
    std::thread t3(f3);

    t1.join();
    t2.join();
    t3.join();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
