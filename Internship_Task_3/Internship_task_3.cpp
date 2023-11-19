#include <iostream>
using namespace std;

// Function prototypes
void displayStudentID();
void costSlab1(const int matrix[][3]);
void costSlab2(const int matrix[][3]);
void costSlab3(const int matrix[][3]);

int main() {
    // Source data
    int electricityMatrix[3][3] = {
        {55, 65, 75},
        {120, 150, 170},
        {210, 230, 240}
    };

    char choice;

    do {
        // Display student's ID
        displayStudentID();

        // Display menu
        cout << "1. Display bill for Slab 1 and Slab 2\n";
        cout << "2. Display bill for Slab 3\n";
        cout << "Any other key to exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case '1':
                costSlab1(electricityMatrix);
                costSlab2(electricityMatrix);
                break;
            case '2':
                costSlab3(electricityMatrix);
                break;
            default:
                cout << "Exiting program.\n";
                break;
        }

    } while(choice == '1' || choice == '2');

    return 0;
}

// Function to display student's ID
void displayStudentID() {
    cout << "Student's ID: xyz123\n";
}

// Function to calculate and display cost for slab 1
void costSlab1(const int matrix[][3]) {
    cout << "Cost for Slab 1: Rs. " << (matrix[0][0] * 10 + matrix[0][1] * 10 + matrix[0][2] * 10) << endl;
}

// Function to calculate and display cost for slab 2
void costSlab2(const int matrix[][3]) {
    cout << "Cost for Slab 2: Rs. " << (matrix[1][0] * 15 + matrix[1][1] * 15 + matrix[1][2] * 15) << endl;
}

// Function to calculate and display cost for slab 3
void costSlab3(const int matrix[][3]) {
    cout << "Cost for Slab 3: Rs. " << (matrix[2][0] * 20 + matrix[2][1] * 20 + matrix[2][2] * 20) << endl;
}
