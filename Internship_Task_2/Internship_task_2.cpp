#include <iostream>
#include <iomanip>

using namespace std;

const int NUM_TRAINS = 4;
const int NUM_COACHES = 6;
const int SEATS_PER_COACH = 80;
const int FREE_TICKET_THRESHOLD = 10;
const double TICKET_PRICE = 25.0;

struct Train {
    int availableSeats;
    double totalRevenue;
    int totalPassengers;
};

void initializeTrains(Train trains[]) {
    for (int i = 0; i < NUM_TRAINS; ++i) {
        trains[i].availableSeats = NUM_COACHES * SEATS_PER_COACH;
        trains[i].totalRevenue = 0.0;
        trains[i].totalPassengers = 0;
    }
}

void displayTrainInfo(const Train& train, const string& time) {
    if (train.availableSeats > 0) {
        cout << "Train at " << time << ": " << train.availableSeats << " seats available\n";
    } else {
        cout << "Train at " << time << ": Closed\n";
    }
}

void displayDaySummary(const Train trains[]) {
    int totalPassengers = 0;
    double totalRevenue = 0.0;
    int maxPassengersIndex = 0;

    for (int i = 0; i < NUM_TRAINS; ++i) {
        totalPassengers += trains[i].totalPassengers;
        totalRevenue += trains[i].totalRevenue;

        if (trains[i].totalPassengers > trains[maxPassengersIndex].totalPassengers) {
            maxPassengersIndex = i;
        }
    }

    cout << "\nDay Summary:\n";
    cout << "Total passengers: " << totalPassengers << "\n";
    cout << "Total revenue: $" << fixed << setprecision(2) << totalRevenue << "\n";
    cout << "Train journey with the most passengers: ";
    displayTrainInfo(trains[maxPassengersIndex], to_string(9 + maxPassengersIndex * 2) + ":00");
}

void purchaseTickets(Train trains[], int trainIndex, int numTickets) {
    if (trains[trainIndex].availableSeats >= numTickets) {
        double totalPrice = numTickets * TICKET_PRICE;

        // Group discount for every tenth passenger
        int freeTickets = (numTickets / FREE_TICKET_THRESHOLD) * (FREE_TICKET_THRESHOLD - 1);
        totalPrice -= freeTickets * TICKET_PRICE;

        // Update train data
        trains[trainIndex].availableSeats -= numTickets;
        trains[trainIndex].totalRevenue += totalPrice;
        trains[trainIndex].totalPassengers += numTickets;

        cout << "Tickets purchased successfully!\n";
        cout << "Total cost: $" << fixed << setprecision(2) << totalPrice << "\n";
        cout << "Free tickets awarded: " << freeTickets << "\n";
    } else {
        cout << "Not enough seats available for the selected train.\n";
    }
}

int main() {
    Train trains[NUM_TRAINS];
    initializeTrains(trains);

    // Task 1 - Start of the day
    cout << "Electric Mountain Railway - Start of the Day\n";
    for (int i = 0; i < NUM_TRAINS; ++i) {
        displayTrainInfo(trains[i], to_string(9 + i * 2) + ":00");
    }

    // Task 2 - Purchasing tickets
    int selectedTrain;
    int numTickets;

    cout << "\nElectric Mountain Railway - Ticket Purchase\n";
    cout << "Enter the train number (1 to 4): ";
    cin >> selectedTrain;

    if (selectedTrain >= 1 && selectedTrain <= NUM_TRAINS) {
        cout << "Enter the number of tickets to purchase: ";
        cin >> numTickets;

        // Task 2 - Purchase Tickets
        purchaseTickets(trains, selectedTrain - 1, numTickets);

        // Display updated train information after purchase
        displayTrainInfo(trains[selectedTrain - 1], to_string(9 + (selectedTrain - 1) * 2) + ":00");
    } else {
        cout << "Invalid train number.\n";
    }

    // Task 3 - End of the day
    displayDaySummary(trains);

    return 0;
}
