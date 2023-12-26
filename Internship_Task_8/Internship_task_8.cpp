#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>  // Add this line for std::any_of
#include <ctime>

using namespace std;

const int NUM_BOATS = 10;
const int OPENING_HOUR = 10;
const int CLOSING_HOUR = 17;
const double HOURLY_RATE = 20.0;
const double HALF_HOUR_RATE = 12.0;
const int MAX_HIRE_HOURS = 7;

struct Boat {
    int boatNumber;
    double moneyTaken;
    int totalHoursHired;
    int returnTime;
    bool isHired; // Added flag to track whether the boat is currently hired
};

void initializeBoats(vector<Boat>& boats) {
    for (int i = 0; i < NUM_BOATS; ++i) {
        boats.push_back({i + 1, 0.0, 0, OPENING_HOUR, false});
    }
}

void printBoatStatus(const Boat& boat) {
    cout << "Boat " << boat.boatNumber << ": $" << boat.moneyTaken
         << " | Total Hours Hired: " << boat.totalHoursHired << endl;
}

bool isBoatAvailable(const Boat& boat, int currentTime) {
    return !boat.isHired && currentTime >= boat.returnTime && currentTime <= CLOSING_HOUR;
}

int findNextAvailableBoat(const vector<Boat>& boats, int currentTime) {
    for (const Boat& boat : boats) {
        if (isBoatAvailable(boat, currentTime)) {
            return boat.boatNumber;
        }
    }
    return -1; // No available boats, return -1
}

void hireBoat(Boat& boat, int duration, int currentTime) {
    double rate = (duration == 1) ? HOURLY_RATE : HALF_HOUR_RATE;
    double cost = rate * duration;

    boat.moneyTaken += cost;
    boat.totalHoursHired += duration;
    boat.returnTime = currentTime + duration;
    boat.isHired = true;

    cout << "Boat " << boat.boatNumber << " hired for $" << cost << endl;
}

void calculateDailySummary(const vector<Boat>& boats) {
    double totalMoneyTaken = 0.0;
    int totalHoursHired = 0;
    int unusedBoats = 0;
    int mostUsedBoat = 1;

    for (const Boat& boat : boats) {
        totalMoneyTaken += boat.moneyTaken;
        totalHoursHired += boat.totalHoursHired;

        if (boat.totalHoursHired == 0) {
            unusedBoats++;
        }

        if (boat.totalHoursHired > boats[mostUsedBoat - 1].totalHoursHired) {
            mostUsedBoat = boat.boatNumber;
        }
    }

    cout << "\nDaily Summary:\n";
    cout << "Total Money Taken: $" << totalMoneyTaken << endl;
    cout << "Total Hours Hired: " << totalHoursHired << " hours\n";
    cout << "Unused Boats: " << unusedBoats << " boats\n";
    cout << "Most Used Boat: Boat " << mostUsedBoat << " ("
         << boats[mostUsedBoat - 1].totalHoursHired << " hours)\n";
}

int main() {
    vector<Boat> boats;
    initializeBoats(boats);

    cout << "Available Boat Hiring Hours: " << OPENING_HOUR << ":00 to " << CLOSING_HOUR << ":00\n";

    int currentTime;
    do {
        cout << "Enter the current time (24-hour format): ";
        cin >> currentTime;

        if (currentTime < OPENING_HOUR || currentTime > CLOSING_HOUR) {
            cerr << "Boat hiring hours are from 10:00 to 17:00. Please enter a valid time.\n";
        }
    } while (currentTime < OPENING_HOUR || currentTime > CLOSING_HOUR);

    char hireAnother;
    do {
        // TASK 1
        int boatNumber;
        cout << "\nTASK 1 - Calculate the money taken in a day for one boat:\n";
        cout << "Enter the boat number (1 to 10): ";
        cin >> boatNumber;

        if (boatNumber < 1 || boatNumber > NUM_BOATS) {
            cerr << "Invalid boat number. Program terminated.\n";
            return 1;
        }

        Boat& selectedBoat = boats[boatNumber - 1];

        while (!isBoatAvailable(selectedBoat, currentTime)) {
            cerr << "Selected boat is not available at the current time. Please select another available boat.\n";
            cout << "Available boats: ";
            for (const Boat& boat : boats) {
                if (isBoatAvailable(boat, currentTime)) {
                    cout << "Boat " << boat.boatNumber << " ";
                }
            }
            cout << "\nEnter the boat number: ";
            cin >> boatNumber;

            if (boatNumber < 1 || boatNumber > NUM_BOATS) {
                cerr << "Invalid boat number. Program terminated.\n";
                return 1;
            }

            selectedBoat = boats[boatNumber - 1];
        }

        int duration;
        do {
            cout << "Enter the duration of hire (up to 7 hours): ";
            cin >> duration;

            if (duration < 1 || duration > MAX_HIRE_HOURS) {
                cerr << "Invalid duration. Please enter a value between 1 and 7.\n";
            }
        } while (duration < 1 || duration > MAX_HIRE_HOURS);

        if (selectedBoat.returnTime + duration <= CLOSING_HOUR) {
            hireBoat(selectedBoat, duration, currentTime);
        } else {
            cerr << "Boat cannot be hired for that duration, it will exceed closing hours. Program terminated.\n";
            return 1;
        }

        // Ask if the user wants to hire another boat
        cout << "Do you want to hire another boat? (y/n): ";
        cin >> hireAnother;

    } while ((hireAnother == 'y' || hireAnother == 'Y') && any_of(boats.begin(), boats.end(), [](const Boat& boat) { return !boat.isHired; }));

    // TASK 2
    cout << "\nTASK 2 - Find the next boat available:\n";
    int nextAvailableBoat = findNextAvailableBoat(boats, currentTime);

    if (nextAvailableBoat != -1) {
        cout << "Next available boat: Boat " << nextAvailableBoat << endl;
    } else {
        cout << "No boats are currently available. Earliest available time: "
             << boats[0].returnTime << ":00\n";
    }

    // TASK 3
    cout << "\nTASK 3 - Calculate the money taken for all the boats at the end of the day:\n";
    calculateDailySummary(boats);

    return 0;
}
