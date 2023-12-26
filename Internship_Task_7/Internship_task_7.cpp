#include <iostream>
#include <iomanip> // for setprecision
#include <algorithm> // for sorting
#include <numeric> // for accumulate

using namespace std;

const int NUM_CHARITIES = 3;

// Function to set up the donation system
void setupDonationSystem(string charities[]) {
    cout << "Enter the names of three charities:\n";
    for (int i = 0; i < NUM_CHARITIES; ++i) {
        cout << "Charity " << (i + 1) << ": ";
        getline(cin, charities[i]);
    }
}

// Function to display the totals in descending order and calculate the grand total
void displayTotalsAndGrandTotal(const string charities[], const double charityTotals[]) {
    // Display totals and charity names in descending order
    cout << "\nCharity Totals (Descending Order):\n";
    pair<string, double> sortedCharityTotals[NUM_CHARITIES];
    for (int i = 0; i < NUM_CHARITIES; ++i) {
        sortedCharityTotals[i] = make_pair(charities[i], charityTotals[i]);
    }
    sort(sortedCharityTotals, sortedCharityTotals + NUM_CHARITIES,
         [](const pair<string, double> &a, const pair<string, double> &b) {
             return a.second > b.second;
         });

    for (int i = 0; i < NUM_CHARITIES; ++i) {
        cout << sortedCharityTotals[i].first << ": $" << sortedCharityTotals[i].second << endl;
    }

    // Calculate and display grand total
    double grandTotal = accumulate(charityTotals, charityTotals + NUM_CHARITIES, 0.0);
    cout << "\nGRAND TOTAL DONATED TO CHARITY: $" << grandTotal << endl;
}

// Function to record and total each donation
void recordAndTotalDonation(string charities[], double charityTotals[], int billNumber) {
    int chosenCharity;
    cout << "Choose a charity (1, 2, 3) or -1 to show totals after entering Bill " << billNumber << ": ";
    cin >> chosenCharity;

    // Check if the user wants to show totals
    if (chosenCharity == -1) {
        displayTotalsAndGrandTotal(charities, charityTotals);
        exit(EXIT_SUCCESS); // Exit the program after displaying totals
    }

    // Validate the choice
    if (chosenCharity < 1 || chosenCharity > NUM_CHARITIES) {
        cerr << "Invalid choice. Please choose a number between 1 and 3 or -1 to show totals." << endl;
        exit(EXIT_FAILURE);
    }

    // Input shopping bill
    double shoppingBill;
    cout << "Enter the customer's shopping bill for " << charities[chosenCharity - 1] << ": $";
    cin >> shoppingBill;

    // Calculate donation and update charity totals
    double donation = shoppingBill * 0.01;
    charityTotals[chosenCharity - 1] += donation;

    // Display donation
    cout << fixed << setprecision(2); // Display money values with two decimal places
    cout << "Donation to " << charities[chosenCharity - 1] << ": $" << donation << endl;
}

int main() {
    string charities[NUM_CHARITIES];
    double charityTotals[NUM_CHARITIES] = {0.0};

    setupDonationSystem(charities);

    // Record and total each donation
    for (int i = 1; i <= 3; ++i) {
        recordAndTotalDonation(charities, charityTotals, i);
    }

    // Ask if the user wants to add more charities
    char addMore;
    cout << "Do you want to add more charities? (y/n): ";
    cin >> addMore;

    while (addMore == 'y' || addMore == 'Y') {
        setupDonationSystem(charities);
        for (int i = 4; ; ++i) {
            recordAndTotalDonation(charities, charityTotals, i);
            cout << "Do you want to add more charities? (y/n): ";
            cin >> addMore;
            if (addMore != 'y' && addMore != 'Y') {
                break;
            }
        }
    }

    // Display totals and grand total if the user chooses not to add more charities
    displayTotalsAndGrandTotal(charities, charityTotals);

    return 0;
}
