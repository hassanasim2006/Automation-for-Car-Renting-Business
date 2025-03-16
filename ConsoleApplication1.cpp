#include <iostream>
#include <vector>
using namespace std;

class Vehicle {
    int vehicleID;
    string vehicleType;
    double rentalRate;
    static int totalNumberOfVehiclesRented;
    int rentedDays;

public:
    Vehicle(int, string, double);
    void display();
    void rentVehicle(int);
    void returnVehicle();
    static int getTotalRentedVehicles();
    double getTotalCost();
};

int Vehicle::totalNumberOfVehiclesRented = 0;

Vehicle::Vehicle(int id, string type, double rent) {
    vehicleID = id;
    vehicleType = type;
    rentalRate = rent;
    rentedDays = 0;
}

void Vehicle::display() {
    cout << "\033[95m"; // Purple color
    cout << "Vehicle ID: " << vehicleID << "\n";
    cout << "Type: " << vehicleType << "\n";
    cout << "Rental Rate: $" << rentalRate << " per day\n";
    cout << "Rented Days: " << rentedDays << "\n";
    cout << "Total Cost: $" << getTotalCost() << "\n";
    cout << "----------------------------------------------\n";
    cout << "\033[0m"; // Reset color
}

void Vehicle::rentVehicle(int days) {
    rentedDays = days;
    totalNumberOfVehiclesRented++;
}

void Vehicle::returnVehicle() {
    rentedDays = 0;
}

int Vehicle::getTotalRentedVehicles() {
    return totalNumberOfVehiclesRented;
}

double Vehicle::getTotalCost() {
    double totalCost = rentalRate * rentedDays;
    if (rentedDays >= 365) {
        totalCost *= 1.09; // 9% inflation for 1-year rentals
    }
    return totalCost;
}

int main() {
    vector<Vehicle*> rentedVehicles;
    int choice, days;
    char more;
    double grandTotal = 0;

    do {
        cout << "Select a vehicle to rent:\n";
        cout << "1. Car ($200 per day)\n2. Bike ($100 per day)\n3. Truck ($300 per day)\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        cout << "Enter number of days to rent: ";
        cin >> days;

        Vehicle* v;
        switch (choice) {
        case 1: v = new Vehicle(1, "Car", 200.0); break;
        case 2: v = new Vehicle(2, "Bike", 100.0); break;
        case 3: v = new Vehicle(3, "Truck", 300.0); break;
        default: cout << "Invalid choice! Try again.\n"; continue;
        }

        v->rentVehicle(days);
        v->display();
        grandTotal += v->getTotalCost();
        rentedVehicles.push_back(v);

        cout << "Do you want to rent another vehicle? (yes/no): ";
        cin >> more;
    } while (more == 'yes' || more == 'Yes');

    cout << "\033[95mGrand Total Cost for all rented vehicles: $" << grandTotal << "\033[0m\n";
    cout << "\033[95mTotal Vehicles Rented: " << Vehicle::getTotalRentedVehicles() << "\033[0m\n";

    for (auto v : rentedVehicles) {
        delete v; // Free allocated memory
    }

    return 0;
}

