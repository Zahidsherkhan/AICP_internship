#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Struct to represent items
struct Item {
    string code;
    string description;
    double price;
};

// Function to display the available items
void displayItems(const vector<Item>& items) {
    cout << "Item Code\tDescription\tPrice ($)" << endl;
    for (const Item& item : items) {
        cout << item.code << "\t\t" << item.description << "\t\t" << item.price << endl;
    }
}

// Function to calculate the total price
double calculateTotalPrice(const Item& caseItem, const Item& ram, const Item& hdd, const vector<Item>& additionalItems) {
    double totalPrice = caseItem.price + ram.price + hdd.price;

    for (const Item& item : additionalItems) {
        totalPrice += item.price;
    }

    return totalPrice;
}

int main() {
    // Initialize items
    vector<Item> items = {
        {"A1", "Compact Case", 75.00},
        {"A2", "Tower Case", 150.00},
        {"B1", "8 GB RAM", 79.99},
        {"B2", "16 GB RAM", 149.99},
        {"B3", "32 GB RAM", 299.99},
        {"C1", "1 TB HDD", 49.99},
        {"C2", "2 TB HDD", 89.99},
        {"C3", "4 TB HDD", 129.99},
        {"D1", "240 GB SSD", 59.99},
        {"D2", "480 GB SSD", 119.99},
        {"E1", "1 TB HDD", 49.99},
        {"E2", "2 TB HDD", 89.99},
        {"E3", "4 TB HDD", 129.99},
        {"F1", "DVD/Blu-Ray Player", 50.00},
        {"F2", "DVD/Blu-Ray Re-writer", 100.00},
        {"G1", "Standard Version", 100.00},
        {"G2", "Professional Version", 175.00}
    };

    // Display available items
    displayItems(items);

    // Variables to store user's choices
    Item selectedCase, selectedRAM, selectedHDD;
    vector<Item> additionalItems;

    // Task 1 - Selecting main items
    cout << "Task 1 - Select one Case, one RAM, and one Main Hard Disk Drive:" << endl;
    
    // Input validation for item codes
    bool validCase = false, validRAM = false, validHDD = false; // Add validation variables
    while (true) {
        string caseCode, ramCode, hddCode;
        cout << "Enter the item code for the Case: ";
        cin >> caseCode;
        for (const Item& item : items) {
            if (item.code == caseCode) {
                selectedCase = item;
                validCase = true;
                break;
            }
        }

        cout << "Enter the item code for the RAM: ";
        cin >> ramCode;
        for (const Item& item : items) {
            if (item.code == ramCode) {
                selectedRAM = item;
                validRAM = true;
                break;
            }
        }

        cout << "Enter the item code for the Hard Disk Drive: ";
        cin >> hddCode;
        for (const Item& item : items) {
            if (item.code == hddCode) {
                selectedHDD = item;
                validHDD = true;
                break;
            }
        }
        
        if (validCase && validRAM && validHDD) {
            break;
        } else {
            cout << "Invalid item code(s). Please try again." << endl;
        }
    }

    // Task 2 - Ordering additional items
    cout << "Task 2 - Order additional items (Y/N): ";
    char orderAdditionalItems;
    cin >> orderAdditionalItems;

    if (orderAdditionalItems == 'Y' || orderAdditionalItems == 'y') {
        cout << "Available additional items to select from:" << endl;
        displayItems(items);
        
        while (true) {
            cout << "Enter the item code for an additional item (or 'N' to finish): ";
            string additionalItemCode;
            cin >> additionalItemCode;
            
            if (additionalItemCode == "N" || additionalItemCode == "n") {
                break;
            }

            // Validate and add the additional item based on the item code
            for (const Item& item : items) {
                if (item.code == additionalItemCode) {
                    additionalItems.push_back(item);
                    break;
                }
            }
        }
    }

    // Calculate the total price
    double totalPrice = calculateTotalPrice(selectedCase, selectedRAM, selectedHDD, additionalItems);

    // Task 3 - Offering discounts
    double discount = 0.0;
    if (additionalItems.size() == 1) {
        discount = 0.05; // 5% discount
    } else if (additionalItems.size() >= 2) {
        discount = 0.10; // 10% discount
    }

    double discountedPrice = totalPrice - (totalPrice * discount);

    // Output the chosen items and the price
    cout << "Chosen items:" << endl;
    // Display the selected items and additional items
    // ...

    cout << "Total Price: $" << totalPrice << endl;
    cout << "Discount: " << fixed << setprecision(2) << (discount * 100) << "%" << endl;
    cout << "Discounted Price: $" << discountedPrice << endl;

    return 0;
}
