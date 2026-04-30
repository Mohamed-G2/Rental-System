#include <iostream>
#include <string>
#include <iomanip>
#include<fstream>
#include<vector>
#include<algorithm>
#include "file.h"

using namespace std;




// const int CAR_COUNT = 3;
// string carNames[CAR_COUNT] = { "BMW" , "Toyota" , "Mercedes" };
// double carPrices[CAR_COUNT] = { 500 , 5000 , 700 };

// enum Status { AVAILABLE, RENTED };
// Status carStatus[CAR_COUNT] = { AVAILABLE, AVAILABLE, AVAILABLE };
// int rentedDays[CAR_COUNT] = { 0 };

enum Menu {
    SHOW_BALANCE = 1,
    SHOW_CARS,
    SEARCH,
    RENT,
    RETURN_CAR,
    SHOW_GRID,
    EXIT
};

// class Account {
// protected:
//     double balance;
// public:
//     Account() : balance(0) {}
// };

class RentalSystem {
private:
    vector <User> users;
    vector <Vehicle> vehicles;
    int currentIndex = -1;
public:
    // static int userCount;
    // static int loginAttempts;


    // void init() {
    //     userCount++;
    //     // id = userCount;
    // }
    void signup(){
        int newID;
        if(users.empty()){
			newID = 1;
		}
		
        else{
			newID = users.back().getID() + 1;
		}

        double balance = 0;
        string user, password;
        cout << "Enter Username: ";
        cin >> user;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter balance: ";
        cin >> balance;

        User newUser;
        newUser.setUser(user);
        newUser.setPass(password);
        newUser.setBalance(balance);
        newUser.setId(newID);
        users.push_back(newUser);
        cout << "Welcome!" << endl;

    }
    bool login(){
        int attempts = 0;
		string EnterUsern;
		string EnterPassw;

		while(attempts < 3) {
			cout<<"Enter username:";
			cin>>EnterUsern;

			cout<<"Enter password:";
			cin>>EnterPassw;

			bool found = false;

			for(int i = 0; i < users.size(); i++) {
				if(EnterUsern == users[i].getUsername() && EnterPassw == users[i].getPassword()) {
					found = true;
                    currentIndex = i;
					break;
				}
			}
			if(found == true) {
				cout << "Welcome!\n";
				return true;
			} else {
				cout << "Invalid username or password try again.\n";
				attempts++;
			}
		}
		return false;
    }
    //load
    void load() {
		ifstream usersFile("users.txt");
		if (usersFile) {
			users.clear();
			int id;
			string username, pass;
			double bal;

			while (usersFile >> id >> username >> bal >> pass) {
				User u;
				u.setId(id);
				u.setUser(username);
				u.setBalance(bal);
				u.setPass(pass);
				users.push_back(u);
			}
			usersFile.close();
		}

		ifstream vehicleFile("vehicles.txt");
		if (vehicleFile) {
			vehicles.clear();
			int id;
			string type;
			float rent;
			int availability;
			int days;

			while (vehicleFile >> id >> type >> rent >> availability >> days) {
				Vehicle vehicle;
				vehicle.setID(id);
				vehicle.setType(type);
				vehicle.setRent(rent);
				vehicle.setAvailability(availability);
				vehicle.setDays(days);
				vehicles.push_back(vehicle);
			}
			vehicleFile.close();
		}
	}
    //save
    //save the users[i].getUsername in users.txt & users[i].getPassword() in passwords.txt
    void save() {
		ofstream usersFile("users.txt");
		for (int i = 0; i < users.size(); i++) {
			usersFile << users[i].getID() << " "
			          << users[i].getUsername() << " "
			          << users[i].getBalance() << " "
			          << users[i].getPassword() << "\n";
		}
		usersFile.close();

		ofstream vehicleFile("vehicles.txt");
		for (int i = 0; i < vehicles.size(); i++) {
			vehicleFile << vehicles[i].getID() << " "
			            << vehicles[i].getType() << " "
			            << vehicles[i].getRent() << " "
			            << vehicles[i].getAvailability() << " "
			            << vehicles[i].getDays() << endl;
		}
		vehicleFile.close();
	}
    
    void showBalance() {
        if (currentIndex != -1) {
            cout << "Your balance: $" << users[currentIndex].getBalance() << endl;
        }
    }


    // Rent
    void rentCar() {
        if (vehicles.empty()) {
            cout << "No cars available for rent." << endl;
            return;
        }

        int c;
        cout << "Enter car id: ";
        cin >> c;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        int index = -1;
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i].getID() == c) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Error: Invalid car ID!" << endl;
            return;
        }
                    
        if (vehicles[index].getAvailability() == false) {
            cout << "Car already rented!" << endl;
            return;
        }
                    
        int days;
        cout << "Enter number of days: ";
        cin >> days;
                    
        if (days <= 0) {
            cout << "Invalid days" << endl;
            return;
        }

        double total = vehicles[index].getRent() * days;
 
        if(users[currentIndex].getBalance() >= total){
            double balance = users[currentIndex].getBalance();
            users[currentIndex].setBalance(balance - total);

            vehicles[index].setAvailability(false);
            vehicles[index].setDays(days);

            cout << "Car rented successfully for " << days << " day." << endl;
            cout << "Total charged: $" << total << endl;
            cout << "Remaining balance: $" << users[currentIndex].getBalance() << endl;
        }
        else {
            cout << "Error: Insufficient balance! You need $" << total << " to rent this car." << endl;
        }
    }

    // Return

    void returnCar() {
        if (vehicles.empty()) {
            cout << "No vehicles rented" << endl;
            return;
        }
        int c;
        cout << "Enter car id: ";
        cin >> c;

       if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        int index = -1;
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i].getID() == c) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Error: Invalid car ID!" << endl;
            return;
        }

        if (vehicles[index].getAvailability() == true) {
            cout << "Car is not rented" << endl;
            return;
        }

        int used;
        cout << "Enter days used: ";
        cin >> used;

        if (used < 0) {
            cout << "Days cannot be < 0" << endl;
            return;
        }

        int totalDays = vehicles[index].getDays();

        if (used > totalDays) {
            cout << "Days used exceed rented days!" << endl;
            return;
        }

        int remainingDays = totalDays - used;
        
        if (remainingDays > 0) {
            double refund = remainingDays * vehicles[index].getRent();
            double balance = users[currentIndex].getBalance();
            users[currentIndex].setBalance(balance + refund);

            cout << "Car returned successfully." << endl;
            cout << "Days rented: " << totalDays << " | Used: " << used << " | Refunded days: " << remainingDays << endl;
            cout << "Refund: $" << refund << endl;
        }
        else {
            cout << "Car returned successfully." << endl;
            cout << "Days rented: " << totalDays << " | Used: " << used << " | No refund." << endl;
        }

        vehicles[index].setAvailability(true);
        vehicles[index].setDays(0);
        cout << "New balance: $" << users[currentIndex].getBalance() << endl;
    }

    // Show Cars

    void showCars() {
        cout << endl << "--- Cars ---" << endl;
        for (int i = 0; i < vehicles.size(); i++) {
            cout << i + 1 << " - " << vehicles[i].getType() << " | $" << vehicles[i].getRent() << "/day";

            if (vehicles[i].getAvailability() == true) {
                if (users[currentIndex].getBalance() >= vehicles[i].getRent())
                    cout << " Available";
                else
                    cout << " Available - insufficient balance";
            }
            else {
                cout << " Rented";
            }
            cout << endl;
        }
    }

    // Parking Grid

    void showGrid() {
        int cols = 3;
        int W = 30;
        string border = "+------------------------------+";

        cout << endl << "--- VIP Parking Grid ---" << endl << endl;

        for (int rowStart = 0; rowStart < vehicles.size(); rowStart += cols) {
            int rowEnd = min((int)vehicles.size(), rowStart + cols);

            for (int i = rowStart; i < rowEnd; i++) {
                cout << border << "   ";
            }
            cout << endl;

            for (int i = rowStart; i < rowEnd; i++) {
                string spotLabel = " Spot " + to_string(i + 1) + ": " + vehicles[i].getType();

                if (spotLabel.length() > W) {
                    spotLabel = spotLabel.substr(0, W - 3) + "...";
                }
                cout << "|" << left << setw(W) << spotLabel << "|   ";
            }
            cout << endl;

            for (int i = rowStart; i < rowEnd; i++) {
                string status = (vehicles[i].getAvailability() == true) ? " [ FREE ]" : " [ TAKEN ]";
                cout << "|" << left << setw(W) << status << "|   ";
            }
            cout << endl;

            for (int i = rowStart; i < rowEnd; i++) {
                cout << border << "   ";
            }
            cout << endl << endl;
        }
    }

    // Search

    void searchCar() {
        string carname;
        cout << "Enter car name: ";
        cin >> carname;
        transform(carname.begin(), carname.end(), carname.begin(), ::tolower);
        for (int i = 0; i < vehicles.size(); i++) {
            string name = vehicles[i].getType();
            transform(name.begin(), name.end(), name.begin(), ::tolower);

            if (name == carname) {
                cout << "Car found: " << vehicles[i].getType() << endl;
                cout << "Price: $" << vehicles[i].getRent() << "/day" << endl;
                cout << "Status: " << (vehicles[i].getAvailability() == true ? "Available" : "Rented") << endl;
                return;
            }
        }
        cout << "Car not found." << endl;
    }

    bool getCarStatus(int i) {
        return vehicles[i].getAvailability();
    }

    int carCount(){
        return vehicles.size();
    }
};

// int RentalSystem::userCount = 0;
// int RentalSystem::loginAttempts = 0;

int main() {

    RentalSystem system;

    system.load();
    
    // RentalSystem* currentUser = &users[0];
    int n = 0;
    while(n != 3){
        cout << "\n--- Welcome to Car Rental System ---\n";
        cout << "1. Login\n";
        cout << "2. Sign Up\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid number." << endl;
            continue;
        }
        if (n == 1) {
            if(system.login()){
                int choice = 0;
                while(choice != 7) {
                    cout << endl;
                    cout << "1. Show Balance" << endl;
                    cout << "2. Show Cars" << endl;
                    cout << "3. Search Car" << endl;
                    cout << "4. Rent Car" << endl;
                    cout << "5. Return Car" << endl;
                    cout << "6. Show Parking Grid" << endl;
                    cout << "7. Logout"<<endl;
                    cout << "Enter your choice: ";
		            cin >> choice;
                    if (cin.fail() || choice < 0 || choice > 7) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid input! Please enter a valid number." << endl;
                        continue;
                    }
                    switch (choice)
                    {
                    case SHOW_BALANCE:
                        system.showBalance();
                        break;
                    case SHOW_CARS:
                        system.showCars();
                        break;
                    case SEARCH:
                        system.searchCar();
                        break;
                    case RENT:
                        system.rentCar();
                        break;
                    case RETURN_CAR:
                        system.returnCar();
                        break;
                    case SHOW_GRID:
                        system.showGrid();
                        break;
                    case EXIT:
                        cout << "Exiting system..." <<endl;
                        system.save();
                        break;
                    default:
                        break;
                    }
                }
                system.save();
            }
        }
        else if(n == 2){
            system.signup();
            system.save();
        }
        else{
            cout << endl << "Goodbye!" << endl;
        }
    }
    return 0;
}