#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "headers.h"

// ����������� ������� f(x) = exp(x)
double f(double x) {
    return std::exp(x);
}

// ������ ����������� ������������ (e^x)
double f_prime(double x) {
    return std::exp(x);
}

// ������ ����������� ������������ (e^x)
double f_double_prime(double x) {
    return std::exp(x);
}

void printTableHeader() {
    std::cout << std::setw(12) << "x"
        << std::setw(15) << "Spline"
        << std::setw(15) << "f(x)"
        << std::setw(15) << "Error"
        << std::setw(15) << "Spline'"
        << std::setw(15) << "f'(x)"
        << std::setw(15) << "Error'"
        << std::setw(15) << "Spline''"
        << std::setw(15) << "f''(x)"
        << std::setw(15) << "Error''"
        << std::endl;
    std::cout << std::string(147, '-') << std::endl;
}

void printTableRow(double x, const CubicSpline& spline, double true_val,
    double true_deriv, double true_dderiv) {
    double spline_val = spline.evaluate(x);
    double spline_deriv = spline.derivative1(x);
    double spline_dderiv = spline.derivative2(x);

    std::cout << std::setw(12) << std::setprecision(4) << x
        << std::setw(15) << std::setprecision(6) << spline_val
        << std::setw(15) << true_val
        << std::setw(15) << std::abs(spline_val - true_val)
        << std::setw(15) << spline_deriv
        << std::setw(15) << true_deriv
        << std::setw(15) << std::abs(spline_deriv - true_deriv)
        << std::setw(15) << spline_dderiv
        << std::setw(15) << true_dderiv
        << std::setw(15) << std::abs(spline_dderiv - true_dderiv)
        << std::endl;
}

void conductResearch(double a, double b, int baseSegments, const std::string& label) {
    std::cout << "\n" << label << " (��� h = " << (b - a) / baseSegments << "):" << std::endl;

    // ��������� �����
    auto grid = GridGenerator::generateRegularGrid(a, b, baseSegments);

    // ���������� �������� ������� � �����
    std::vector<double> values;
    for (double node : grid) {
        values.push_back(f(node));
    }

    // ���������� �������
    CubicSpline spline;
    spline.initialize(grid, values);

    // ����� ��� ������������
    std::vector<double> test_points;
    int num_points = 12;
    for (int i = 1; i <= num_points; ++i) {
        double point = a + (b - a) * i / (num_points + 1);
        test_points.push_back(point);
    }

    printTableHeader();
    for (double point : test_points) {
        printTableRow(point, spline, f(point), f_prime(point), f_double_prime(point));
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    const double a = 0.08;
    const double b = 0.32;
    const double epsilon = 0.001;

    // ������������ �� ��������� ������
    int base_segments = 10;
    conductResearch(a, b, base_segments, "����� h");
    conductResearch(a, b, base_segments * 2, "����� h/2");
    conductResearch(a, b, base_segments * 4, "����� h/4");

    // ���������� ����������� � ����������� ����� ��������� ����������
    double center = (b - a) / 2.0;
    std::cout << "\n\n���������� ����������� � ����������� ����� x = " << center << std::endl;
    std::cout << "������������� ��������: " << f_prime(center) << std::endl;

    double h = (b - a) / 10.0;

    std::cout << "\n��������� ������� �������� ���������:" << std::endl;
    std::cout << std::setw(20) << "�����"
        << std::setw(15) << "��������"
        << std::setw(15) << "������"
        << std::setw(15) << "���" << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    auto printMethod = [&](const std::string& name, double (*method)(std::function<double(double)>, double, double), double h) {
        double result = method(f, center, h);
        double error = std::abs(result - f_prime(center));
        std::cout << std::setw(20) << name
            << std::setw(15) << std::setprecision(8) << result
            << std::setw(15) << error
            << std::setw(15) << h << std::endl;
        };

    printMethod("������������� O(h)", FiniteDifference::forwardDifference, h);
    printMethod("������������� O(h)", FiniteDifference::backwardDifference, h);
    printMethod("����������� O(h^2)", FiniteDifference::centralDifference, h);
    printMethod("����������� O(h^4)", FiniteDifference::centralDifference4, h);

    std::cout << "\n����������� ��� ��� �������� " << epsilon << ": h = " << h << std::endl;

    return 0;
}