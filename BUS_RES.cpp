#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constants
const int TOTAL_SEATS = 30;

// "Base class"
class ReservationSystem {
protected:
    struct Reservation {
        int seatNumber;
        string passengerName;
    };

    vector<Reservation> reservations;  // reservations is a vector of type Reservation (struct)
    
    //reservations is a member of class BusReservationSystem()

public:
    ReservationSystem() {
        // Initialize reservations vector with empty seats
        for (int i = 0; i < TOTAL_SEATS; ++i) {
            reservations.push_back({i + 1, ""});  // push_back is used to add elements to the end of the vector
        }
        //for loop iterates from 0 to TOTAL_SEATS - 1, so i + 1 will give the seat numbers from 1 to TOTAL_SEATS
        
        //"" initializes the 'passengerName' member of the Reservation structure with an empty string so that initially the seat is empty
    }

    void displaySeats() const {
        cout << "Bus Seat Status:\n";
        cout << "----------------\n";
        for (int i = 0; i < TOTAL_SEATS; ++i) {
            cout << "Seat " << reservations[i].seatNumber << ": ";
            if (reservations[i].passengerName.empty()) {
                cout << "Available\n";
            } else {
                cout << "Occupied by " << reservations[i].passengerName << "\n";
            }
        }
        cout << "----------------\n";
    }

    virtual void makeReservation() = 0;  //Pure virtual function declaration

    virtual void cancelReservation() = 0;
};

// "Derived class"

//function is meant to override a virtual function from the base class
class BusReservationSystem : public ReservationSystem {
public:
    void makeReservation() override {
        int seatNumber;
        string passengerName;

        cout << "Enter seat number: ";
        cin >> seatNumber;

        if (seatNumber < 1 || seatNumber > TOTAL_SEATS) {
            cout << "Invalid seat number. Please try again.\n";
            return;
        }

        if (!reservations[seatNumber - 1].passengerName.empty()) {
            cout << "Seat " << seatNumber << " is already occupied by " << reservations[seatNumber - 1].passengerName << ".\n";
            return;
        }

        cout << "Enter passenger name: ";
        cin.ignore(); // Ignore the newline character left in the buffer from previous input
        //used after reading data from standard input to clear any remaining characters in the input buffer, 
        getline(cin, passengerName);

        reservations[seatNumber - 1].passengerName = passengerName;
        cout << "Reservation for seat " << seatNumber << " made for " << passengerName << ".\n";
    }

    void cancelReservation() override {
        int seatNumber;
        cout << "Enter seat number to cancel reservation: ";
        cin >> seatNumber;

        if (seatNumber < 1 || seatNumber > TOTAL_SEATS) {
            cout << "Invalid seat number. Please try again.\n";
            return;
        }

        if (reservations[seatNumber - 1].passengerName.empty()) {
            cout << "Seat " << seatNumber << " is already vacant.\n";
            return;
        }

        string passengerName = reservations[seatNumber - 1].passengerName;
        reservations[seatNumber - 1].passengerName = "";
        cout << "Reservation for seat " << seatNumber << " made by " << passengerName << " has been canceled.\n";
    }
};

int main() {
    BusReservationSystem busReservationSystem;

    int choice;
    do {
        cout << "\nBus Reservation System Menu:\n";
        cout << "1. Display Seat Availability\n";
        cout << "2. Make a Reservation\n";
        cout << "3. Cancel Reservation\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                busReservationSystem.displaySeats();
                break;
            case 2:
                busReservationSystem.makeReservation();
                break;
            case 3:
                busReservationSystem.cancelReservation();
                break;
            case 4:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}