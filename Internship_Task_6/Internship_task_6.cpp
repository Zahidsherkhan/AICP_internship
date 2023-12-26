#include <iostream>
#include <vector>

using namespace std;

// Constants for weight limits
const double MIN_GRAVEL_SAND_WEIGHT = 49.9;
const double MAX_GRAVEL_SAND_WEIGHT = 50.1;
const double MIN_CEMENT_WEIGHT = 24.9;
const double MAX_CEMENT_WEIGHT = 25.1;

// Prices for each sack
const double CEMENT_PRICE = 3.0;
const double GRAVEL_PRICE = 2.0;
const double SAND_PRICE = 2.0;

// Discount price for special pack
const double SPECIAL_PACK_PRICE = 10.0;
const int SPECIAL_PACK_CEMENT = 1;
const int SPECIAL_PACK_SAND = 2;
const int SPECIAL_PACK_GRAVEL = 2;

// Structure to represent a sack
struct Sack {
    char content;
    double weight;
};

// Function to check a single sack
bool checkSingleSack(Sack& sack) {
    bool validInput = false;

    do {
        cout << "Enter content (C = Cement, G = Gravel, S = Sand): ";
        cin >> sack.content;

        // Check if the input for content is valid
        if (sack.content == 'C' || sack.content == 'G' || sack.content == 'S') {
            validInput = true;
        } else {
            cout << "Error: Invalid content. Please select C for Cement, G for Gravel, and S for Sand.\n";
        }
    } while (!validInput);

    // Display weight range message based on content
    if (sack.content == 'G' || sack.content == 'S') {
        cout << "Sand/Gravel Weight should be between " << MIN_GRAVEL_SAND_WEIGHT << " and " << MAX_GRAVEL_SAND_WEIGHT << " kilograms." << endl;
    } else if (sack.content == 'C') {
        cout << "Cement Weight should be between " << MIN_CEMENT_WEIGHT << " and " << MAX_CEMENT_WEIGHT << " kilograms." << endl;
    }

    cout << "Enter weight for the sack: ";
    cin >> sack.weight;

    // Check the weight
    if ((sack.content == 'G' || sack.content == 'S') && (sack.weight > MIN_GRAVEL_SAND_WEIGHT && sack.weight < MAX_GRAVEL_SAND_WEIGHT)) {
        return true;
    } else if (sack.content == 'C' && (sack.weight > MIN_CEMENT_WEIGHT && sack.weight < MAX_CEMENT_WEIGHT)) {
        return true;
    } else {
        // Display rejection reason
        cout << "Sack rejected. ";
        if (!(sack.content == 'G' || sack.content == 'S' || sack.content == 'C')) {
            cout << "Invalid content. ";
        }
        if (!(sack.weight > MIN_GRAVEL_SAND_WEIGHT && sack.weight < MAX_GRAVEL_SAND_WEIGHT) && !(sack.weight > MIN_CEMENT_WEIGHT && sack.weight < MAX_CEMENT_WEIGHT)) {
            cout << "Weight out of range. ";
        }
        cout << "Adding the sack to the rejected list.\n";
        return false;
    }
}

// Function to check a customer's order for delivery
void checkCustomerOrder(int& numCement, int& numGravel, int& numSand, double& totalWeight, int& numRejectedSacks, vector<Sack>& rejectedSacks, double& totalWeightRejected) {
    cout << "Enter the number of sacks of Cement: ";
    cin >> numCement;

    cout << "Enter the number of sacks of Gravel: ";
    cin >> numGravel;

    cout << "Enter the number of sacks of Sand: ";
    cin >> numSand;

    totalWeight = 0.0;
    numRejectedSacks = 0;
    totalWeightRejected = 0.0;

    rejectedSacks.clear(); // Clear the list of rejected sacks

    // Check each sack in the order
    for (int i = 0; i < numCement; ++i) {
        Sack sack;
        cout << "\nProcessing Cement sack #" << i + 1 << ":\n";
        if (checkSingleSack(sack)) {
            totalWeight += sack.weight;
        } else {
            numRejectedSacks++;
            totalWeightRejected += sack.weight;
            rejectedSacks.push_back(sack);
        }
    }

    for (int i = 0; i < numGravel; ++i) {
        Sack sack;
        cout << "\nProcessing Gravel sack #" << i + 1 << ":\n";
        if (checkSingleSack(sack)) {
            totalWeight += sack.weight;
        } else {
            numRejectedSacks++;
            totalWeightRejected += sack.weight;
            rejectedSacks.push_back(sack);
        }
    }

    for (int i = 0; i < numSand; ++i) {
        Sack sack;
        cout << "\nProcessing Sand sack #" << i + 1 << ":\n";
        if (checkSingleSack(sack)) {
            totalWeight += sack.weight;
        } else {
            numRejectedSacks++;
            totalWeightRejected += sack.weight;
            rejectedSacks.push_back(sack);
        }
    }

    cout << "\nOrder processed.\n";
}

// Function to calculate the price for a customer's order
void calculateOrderPrice(int numCement, int numGravel, int numSand, double totalWeight, double totalWeightRejected) {
    double regularPrice = numCement * CEMENT_PRICE + numGravel * GRAVEL_PRICE + numSand * SAND_PRICE;
    int numSpecialPacks = min(min(numCement / SPECIAL_PACK_CEMENT, numGravel / SPECIAL_PACK_GRAVEL), numSand / SPECIAL_PACK_SAND);

    double discountPrice = numSpecialPacks * SPECIAL_PACK_PRICE;
    double totalPrice = regularPrice - discountPrice;

    cout << "\nRegular Price for the Order: $" << regularPrice << endl;
    cout << "Number of Special Packs: " << numSpecialPacks << endl;

    if (numSpecialPacks > 0) {
        cout << "Discount Price: -$" << discountPrice << endl;
        cout << "New Price for the Order: $" << totalPrice << endl;
        cout << "Amount Saved: $" << discountPrice << endl;
    } else {
        cout << "No special packs in the order. Final Price: $" << regularPrice << endl;
    }

    cout << "\nWeight of Rejected Sacks: " << totalWeightRejected << " kg\n";
}

// Function to display the rejected sacks
void displayRejectedSacks(const vector<Sack>& rejectedSacks) {
    cout << "\nRejected Sacks:\n";
    for (size_t i = 0; i < rejectedSacks.size(); ++i) {
        cout << "Content: " << rejectedSacks[i].content << ", Weight: " << rejectedSacks[i].weight << " kg\n";
    }
}

int main() {
    // Task 2 - Check a customer’s order for delivery
    int numCement, numGravel, numSand, numRejectedSacks;
    double totalWeight, totalWeightRejected;
    vector<Sack> rejectedSacks;

    checkCustomerOrder(numCement, numGravel, numSand, totalWeight, numRejectedSacks, rejectedSacks, totalWeightRejected);

    cout << "\nTotal Weight of the Order: " << totalWeight << " kg\n";
    cout << "Number of Rejected Sacks: " << numRejectedSacks << "\n";

    if (numRejectedSacks > 0) {
        displayRejectedSacks(rejectedSacks);
        cout << "Total Weight of Rejected Sacks: " << totalWeightRejected << " kg\n";
    }

    // Task 3 - Calculate the price for a customer’s order
    calculateOrderPrice(numCement, numGravel, numSand, totalWeight, totalWeightRejected);

    return 0;
}
