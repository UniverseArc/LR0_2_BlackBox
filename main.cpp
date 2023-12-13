#include <iostream>
#include <cmath>
#include <sstream>
#include <cctype>

const double M_PI = 3.1415926535;

class Test {
private: 
    std::stringbuf sbuf;
    std::streambuf* oldbuf;
    int n;

    void update_state() {
        this->n += 1;
        this->sbuf = std::stringbuf(std::ios::out);
        this->oldbuf = std::cout.rdbuf(std::addressof(this->sbuf));
    }
public:
    Test() {
        this->update_state();
    };
   void out_stream_to_be(std::string expect) {

      std::cout.rdbuf(this->oldbuf);

      std::string output = this->sbuf.str();

      if (output == expect) {
          std::cout << "Тест " << this->n << " пройден\n";
      }
      else {
          std::cout << "Тест " << this->n << " не пройден.\n" << "Ожидаемый результат: " << expect << "\n" << "Полученный результат: " << output << "\n";
      }
     this->update_state();
   }
};

int solve_linear(double a, double b) {
    double x = -b / a;
    std::cout << x << std::endl;
    return 0;
}

int solve_quadratic_equation(double a, double b, double c) {
    double D = std::pow(b, 2) - 4 * a * c;
    if (D < 0) {
        std::cout << "Нет вещественных корней" << std::endl;
        return 0;
    }
    if (D == 0) {
        double x = -b / (2 * a);
        std::cout << x << std::endl;
        return 0;
    }
    double x1 = (-b + sqrt(D)) / (2 * a);
    double x2 = (-b - sqrt(D)) / (2 * a);
    std::cout << x1 << " " << x2 << std::endl;

    return 0;
}

double croot(double x) {
    if (x < 0)
        return -std::pow(-x, 1.0 / 3.0);
    return std::pow(x, 1.0 / 3.0);
}

int solve_cubic_equation(double a, double b, double c, double d)
{
    double p = (3.0 * a * c - b * b) / (3.0 * a * a);
    double q = (2.0 * b * b * b - 9.0 * a * b * c + 27.0 * a * a * d) / (27.0 * a * a * a);
    double S = (q * q / 4.0) + (p * p * p / 27.0);

    double F;
    if (q == 0)
        F = M_PI / 2.0;
    if (q < 0)
        F = atan(-2.0 * sqrt(-S) / q);
    if (q > 0)
        F = atan(-2.0 * sqrt(-S) / q) + M_PI;

    if (S < 0) {
        double x1 = 2.0 * std::sqrt(-p / 3.0) * std::cos(F / 3.0) - b / (3.0 * a);
        double x2 = 2.0 * std::sqrt(-p / 3.0) * std::cos((F / 3.0) + 2.0 * M_PI / 3.0) - b / (3.0 * a);
        double x3 = 2.0 * std::sqrt(-p / 3.0) * std::cos((F / 3.0) + 4.0 * M_PI / 3.0) - b / (3.0 * a);

        std::cout << x1 << " " << x2 << " " << x3 << std::endl;
    }
    if (S == 0) {
        double x1 = 2.0 * croot(-q / 2.0) - b / (3.0 * a);
        double x2 = -croot(-q / 2.0) - b / (3.0 * a);
        std::cout << x1 << " " << x2 << std::endl;
    }
    if (S > 0) {
        double temp1 = croot((-q / 2.0) + std::sqrt(S)) + croot((-q / 2.0) - sqrt(S));
        double temp2 = croot((-q / 2.0) + std::sqrt(S)) - croot((-q / 2.0) - sqrt(S));
        double x1 = temp1 - b / (3.0 * a);

        std::cout << x1 << std::endl;
    }

    return 0;
}

int solve_equation(double a, double b, double c, double d) {
    if (a != 0) {
        return solve_cubic_equation(a, b, c, d);
    }
    if (b != 0) {
        return solve_quadratic_equation(b, c, d);
    }
    if (c != 0) {
        return solve_linear(c, d);
    }
    if (d != 0) {
        std::cout << "Нет решений" << std::endl;
        return 0;
    }

    std::cout << "Любое значение" << std::endl;
    return 0;
}

int main() {
    Test test = Test();
    setlocale(LC_ALL, "Russian");
    solve_equation(1, -3, -6, 8);
    test.out_stream_to_be("4 -2 1\n");
    solve_equation(1, -9, 24, -16);
    test.out_stream_to_be("1 4\n");
    solve_equation(2, -11, 12, 19);
    test.out_stream_to_be("-0.839222\n");
    solve_equation(0, 1, -5, 4);
    test.out_stream_to_be("4 1\n");
    solve_equation(0, 9, -6, 1);
    test.out_stream_to_be("0.333333\n");
    solve_equation(0, 9, 1, 9);
    test.out_stream_to_be("Нет вещественных корней\n");
    solve_equation(0, 0, 1, 9);
    test.out_stream_to_be("-9\n");
    solve_equation(0, 0, 0, 9);
    test.out_stream_to_be("Нет решений\n");
    solve_equation(0, 0, 0, 0);
    test.out_stream_to_be("Любое значение\n");
}

