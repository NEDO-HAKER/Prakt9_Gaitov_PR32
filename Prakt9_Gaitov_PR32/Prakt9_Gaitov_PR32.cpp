#include <iostream>
#include <string>
#include <math.h>

void WriteLine(int text) {
    std::cout << text << std::endl;
}

void Write(int text) {
    std::cout << text;
}

void WriteLine(double text) {
    std::cout << text << std::endl;
}

void Write(double text) {
    std::cout << text;
}

void WriteLine(std::string text) {
    std::cout << text << std::endl;
}

void Write(std::string text) {
    std::cout << text;
}

int Convert_to_Int(std::string text) {
    int number;

    try {
        number = std::stoi(text);

        if (number > 0) return number;
        else return -1;
    }
    catch (std::invalid_argument& e) {
        throw std::invalid_argument("Некорректный ввод данных");
        std::cout << "Некорректный ввод данных" << std::endl;
    }
}

void PrintMenu() {
    WriteLine("Выберите пункт меню");
    WriteLine("1. Ввести данные");
    WriteLine("2. Показать данные");
    WriteLine("3. Выбрать и выполнить обработку");
    WriteLine("4. Восстановить исходные данные");
    WriteLine("5. Выход");
    Write("Выберите действие: ");
}

void PrintMenu2() {
    WriteLine("Выберите пункт меню");
    WriteLine("1. Применить скидку 10%");
    WriteLine("2. Применить скидку 20%");
    WriteLine("3. Добавить фиксированную наценку");
    WriteLine("4. Округлить цены до целого значения");
    Write("Выберите действие: ");
}

void PrintData(double* A, int size) {
    WriteLine(" ");
    for (int i = 0; i < size; i++) {
        Write("Цена №"); Write(i + 1); Write(": "); Write(A[i]); WriteLine("руб.");
    }
}

void Add_10_proc(double* A, int size) {
    for (int i = 0; i < size; i++) {
        A[i] += A[i] / 10;
    }
}

void Add_20_proc(double* A, int size) {
    for (int i = 0; i < size; i++) {
        A[i] += A[i] / 5;
    }
}

void Add_fix_markup(double* A, int size) {
    try {
        double markup;
        std::string text;

        Write("Введите наценку: "); std::cin >> text;

        markup = Convert_to_Int(text);

        for (int i = 0; i < size; i++) {
            A[i] += markup;
        }

        WriteLine(" ");
    }
    catch(std::invalid_argument& e) {
        WriteLine("Некорректный ввод данных");
        WriteLine(" ");
    }
}

void Round_el(double* A, int size) {
    for (int i = 0; i < size; i++) {
        A[i] = round(A[i]);
    }
}

void (*processor)(double* A, int size) = nullptr;

void (*processors[])(double* A, int size) = {
    Add_10_proc,
    Add_20_proc,
    Add_fix_markup,
    Round_el
};

void applyProcessing(double* data, int size, void (*processor)(double*, int)) {
    if (processor != nullptr) {
        processor(data, size);
    }
    else WriteLine("Некорректный выбор действия");
}


int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    double price_A[10];
    double price_A_begin[10];

    double* A = price_A;
    double* A2 = price_A_begin;

    int x;
    std::string text;
    bool data_true = false;

    while (true) {
        try {
            PrintMenu();
            std::cin >> text;
            x = Convert_to_Int(text);

            if (x == 1) { 
                for (int i = 0; i < 10; i++) {
                    A[i] = static_cast<double>((rand() % 49000) + 1000) / 10;
                    A2[i] = A[i];
                }

                WriteLine("Данные введены успешно");
                
                data_true = true;            
            }
            else if (x == 2) {
                if (data_true == true) PrintData(A, 10);
                else WriteLine("Данные еще не введены");
            }
            else if (x == 3) {
                if (data_true == true) {
                    WriteLine(" ");
                    PrintMenu2();
                    std::cin >> text;
                    x = Convert_to_Int(text);

                    processor = processors[x - 1];
                    
                    applyProcessing(A, 10, processor);
                }
                else WriteLine("Данные еще не введены");
            }
            else if (x == 4) { A = A2; WriteLine("Данные восстановлены успешно"); }
            else if (x == 5) break;
            else WriteLine("Некорректный выбор действия");

            WriteLine(" ");
        }
        catch (std::invalid_argument& e) {
            WriteLine(" ");
            WriteLine("Некорректный ввод действия");
            WriteLine(" ");
        }
    }

    return 0;
}