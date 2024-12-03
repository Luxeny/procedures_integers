#include <iostream>
#include <string>
using namespace std;

// Убираем нули в начале
string removeLeadingZeros(string str) {
    while (str.size() > 1 && str[0] == '0') 
        str.erase(0, 1);
    return str;
}

// Добавляем нули в начале, чтобы строки стали одинаковой длины
void equalizeLengths(string &a, string &b) {
    while (a.size() < b.size()) a = "0" + a;
    while (b.size() < a.size()) b = "0" + b;
}

// Сравниваем числа
int compare(string a, string b) {
    a = removeLeadingZeros(a);
    b = removeLeadingZeros(b);

    if (a.size() > b.size()) return 1;   // первое число больше
    if (a.size() < b.size()) return -1;  // первое число меньше
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;  // числа равны
}

// Складываем числа
string add(string a, string b) {
    equalizeLengths(a, b);
    string result = "";
    int carry = 0;

    for (int i = a.size() - 1; i >= 0; i--) {
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        result = char(sum % 10 + '0') + result;
        carry = sum / 10;
    }

    if (carry) result = "1" + result;
    return removeLeadingZeros(result);
}

// Вычитаем числа
string subtract(string a, string b) {
    equalizeLengths(a, b);
    string result = "";
    int borrow = 0;

    for (int i = a.size() - 1; i >= 0; i--) {
        int diff = (a[i] - '0') - (b[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result = char(diff + '0') + result;
    }

    return removeLeadingZeros(result);
}

// Умножаем числа
string multiply(string a, string b) {
    string result = "0";
    int shift = 0;  // смещение для добавления нулей

    for (int i = b.size() - 1; i >= 0; i--) {
        string temp = "";
        int carry = 0;

        for (int j = a.size() - 1; j >= 0; j--) {
            int product = (a[j] - '0') * (b[i] - '0') + carry;
            temp = char(product % 10 + '0') + temp;
            carry = product / 10;
        }

        if (carry) temp = char(carry + '0') + temp;

        for (int k = 0; k < shift; k++) temp += "0";  // добавляем нули
        shift++;
        result = add(result, temp);
    }

    return removeLeadingZeros(result);
}

// Делим числа (целочисленно)
string divide(string a, string b) {
    if (compare(b, "0") == 0) 
        throw invalid_argument("Деление на ноль!");

    string result = "";
    string current = "0";

    for (size_t i = 0; i < a.size(); i++) {
        current += a[i];
        current = removeLeadingZeros(current);
        int count = 0;

        while (compare(current, b) >= 0) {
            current = subtract(current, b);
            count++;
        }

        result += char(count + '0');
    }

    return removeLeadingZeros(result);
}

int main() {
    string num1, num2;
    cout << "Введите первое число: ";
    cin >> num1;
    cout << "Введите второе число: ";
    cin >> num2;

    cout << "\nСложение: " << add(num1, num2) << endl;

    if (compare(num1, num2) >= 0)
        cout << "Вычитание: " << subtract(num1, num2) << endl;
    else
        cout << "Вычитание: -" << subtract(num2, num1) << endl;

    cout << "Умножение: " << multiply(num1, num2) << endl;

    if (num2 == "0") {
        cout << "Деление: ОШИБКА!!! На ноль делить нельзя." << endl;
    } else {
        cout << "Деление: " << divide(num1, num2) << endl;
    }

    int cmp = compare(num1, num2);
    cout << "Сравнение: " << (cmp == 0 ? "Равны" : (cmp > 0 ? "Больше" : "Меньше")) << endl;

    return 0;
}