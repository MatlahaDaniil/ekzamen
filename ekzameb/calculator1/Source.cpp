#include <iostream>
#include <iomanip>
 
double number();
double factor();
double expr();
double brackets();
 
int main()
{
    double n;
 
    setlocale(LC_ALL, "Rus");
 
    std::cout << "Введите выражение: ";
 
    n = expr();
 
    std::cout << "Результат вычисления: " << std::setprecision(8) << n << std::endl;
 
    std::cin.get();
    return 0;
}
 
double number()
{
    double result = 0.0;
    double k = 10.0;
    int sign = 1;
    char c;
 
    c = std::cin.get();
 
    while (c == ' ')
        c = std::cin.get();
 
    if (c == '-')
        sign = -1;
    else
        std::cin.putback(c);
 
    while (true)
    {
        c = std::cin.get();
 
        while (c == ' ')
            c = std::cin.get();
 
        if (c >= '0' && c <= '9')
            result = result * 10.0 + (c - '0');
        else
        {
            std::cin.putback(c);
            break;
        }
    }
 
    c = std::cin.get();
 
    if (c == '.')
    {
        while (true)
        {
            c = std::cin.get();
 
            if (c >= '0' && c <= '9')
            {
                result += (c - '0') / k;
                k *= 10.0;
            }
            else
            {
                std::cin.putback(c);
                break;
            }
        }
    }
    else
        std::cin.putback(c);
 
    return sign * result;
}
 
double factor()
{
    double result = brackets();
    double temp;
    char c;
 
    while (true)
    {
        c = std::cin.get();
 
        while (c == ' ')
            c = std::cin.get();
 
        switch (c)
        {
        case '*':
            result *= brackets();
            break;
        case '/':
            temp = brackets();
 
            if (temp == 0.0)
            {
                std::cout << "Деление на нуль!" << std::endl;
                exit(-1);
            }
 
            result /= temp;
            break;
        default:
            std::cin.putback(c);
            return result;
        }
    }
}
 
double expr()
{
    double result = factor();
    char c;
 
    while (true)
    {
        c = std::cin.get();
 
        while (c == ' ')
            c = std::cin.get();
 
        switch (c)
        {
        case '+':
            result += factor();
            break;
        case '-':
            result -= factor();
            break;
        default:
            std::cin.putback(c);
            return result;
        }
    }
}
 
double brackets()
{
    double result;
    int sign = 1;
    char c;
 
    c = std::cin.get();
 
    while (c == ' ')
        c = std::cin.get();
 
    if (c == '-')
    {
        sign = -1;
        c = std::cin.get();
    }
 
    while (c == ' ')
        c = std::cin.get();
 
    if (c == '(')
    {
        result = sign * expr();
 
        c = std::cin.get();
 
        if (c != ')')
        {
            std::cout << "Неверная расстановка скобок!" << std::endl;
            exit(-1);
        }
 
        return result;
    }
    else
    {
        std::cin.putback(c);
 
        return sign * number();
    }
}