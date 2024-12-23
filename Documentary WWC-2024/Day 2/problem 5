#include <iostream>
#include <string>
using namespace std;

struct CompartmentNode {
    int compartmentId;
    int seats;
    CompartmentNode* next;

    CompartmentNode(int id, int totalSeats)
        : compartmentId(id), seats(totalSeats), next(nullptr) {}
};

struct TrainNode {
    int trainId;
    CompartmentNode* compartments;
    TrainNode* next;

    TrainNode(int id) : trainId(id), compartments(nullptr), next(nullptr) {}
};

class TrainReservationSystem {
private:
    TrainNode* head; // Head of the train list

public:
    TrainReservationSystem() : head(nullptr) {}

    // Add a train
    void addTrain(int trainId) {
        TrainNode* newTrain = new TrainNode(trainId);
        newTrain->next = head;
        head = newTrain;
    }

    // Add a compartment to a train
    void addCompartment(int trainId, int compartmentId, int seats) {
        TrainNode* train = findTrain(trainId);
        if (!train) {
            cout << "Train not found.\n";
            return;
        }

        CompartmentNode* newCompartment = new CompartmentNode(compartmentId, seats);
        newCompartment->next = train->compartments;
        train->compartments = newCompartment;
    }

    // Book a seat
    void bookSeat(int trainId, int compartmentId) {
        CompartmentNode* compartment = findCompartment(trainId, compartmentId);
        if (!compartment) {
            cout << "Compartment not found.\n";
            return;
        }

        if (compartment->seats > 0) {
            compartment->seats--;
            cout << "Seat booked successfully.\n";
        } else {
            cout << "No seats available.\n";
        }
    }

    // Cancel a booking
    void cancelBooking(int trainId, int compartmentId) {
        CompartmentNode* compartment = findCompartment(trainId, compartmentId);
        if (!compartment) {
            cout << "Compartment not found.\n";
            return;
        }

        compartment->seats++;
        cout << "Booking canceled successfully.\n";
    }

    // Check seat availability
    void checkAvailability(int trainId, int compartmentId) {
        CompartmentNode* compartment = findCompartment(trainId, compartmentId);
        if (!compartment) {
            cout << "Compartment not found.\n";
            return;
        }

        cout << "Available seats: " << compartment->seats << endl;
    }

private:
    TrainNode* findTrain(int trainId) {
        TrainNode* current = head;
        while (current && current->trainId != trainId) {
            current = current->next;
        }
        return current;
    }

    CompartmentNode* findCompartment(int trainId, int compartmentId) {
        TrainNode* train = findTrain(trainId);
        if (!train) return nullptr;

        CompartmentNode* compartment = train->compartments;
        while (compartment && compartment->compartmentId != compartmentId) {
            compartment = compartment->next;
        }
        return compartment;
    }
};

int main() {
    TrainReservationSystem system;

    system.addTrain(101);
    system.addCompartment(101, 1, 50);
    system.addCompartment(101, 2, 30);

    system.checkAvailability(101, 1);
    system.bookSeat(101, 1);
    system.checkAvailability(101, 1);

    system.cancelBooking(101, 1);
    system.checkAvailability(101, 1);

    return 0;
}
