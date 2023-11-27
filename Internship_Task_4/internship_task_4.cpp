#include <iostream>
#include <cmath>

using namespace std;

class Hexagon {
private:
    double sideLength;

public:
    Hexagon() {
        // Using the last digit of my CNIC (15101-81177655)
        sideLength = 5; // Replacing this with the last digit of my CNIC
    }

    double calcArea() {
        return 1.5 * 1.732 * sideLength;
    }

    double calcPeri() {
        return 6 * sideLength;
    }

    double calcAngleSum() {
        return 6 * 120;
    }

    void display() {
        cout << "Hexagon - Area: " << calcArea() << ", Perimeter: " << calcPeri()
             << ", Sum of Angles: " << calcAngleSum() << endl;
    }
};

class Square {
private:
    double sideLength;

public:
    Square() {
        // Using the last digit of my CNIC (15101-81177655)
        sideLength = 6; // Replacing this with the last digit + 1 of my CNIC
    }

    double calcAreaSquare() {
        return sideLength * sideLength;
    }

    double calcPeriSquare() {
        return 4 * sideLength;
    }

    void display() {
        cout << "Square - Area: " << calcAreaSquare() << ", Perimeter: " << calcPeriSquare() << endl;
    }
};

int main() {
    int choice;
    Hexagon hex;
    Square square;

    do {
        cout << "Menu:\n";
        cout << "1. Hexagon\n";
        cout << "2. Square\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hex.display();
                break;
            case 2:
                square.display();
                break;
            case 3:
                cout << "Exiting the program. Good day!!!" << endl;
                break;
            default:
                cout << "Invalid choice. Exiting the program Thanks for using the Program!!!." << endl;
                return 1;
        }
    } while (choice != 3);

    return 0;
}
