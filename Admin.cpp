#include <iostream>
#include <vector>
#include<fstream>
#include "file.h"

using namespace std;


class AdminSystem {
private:

	vector <Admin> admins;
	vector <Vehicle> vehicles;
	vector <User> users;
	int index = -1;

public:

	void addAdmin() {
		string newUser, newPass;
		bool newManeger;
		cout << "Enter New Admin Username: ";
		cin >> newUser;
		cout << "Enter New Admin Password: ";
		cin >> newPass;
		cout << "Set as Manager? (1 for Yes / 0 for No): ";
		cin >> newManeger;
		Admin newAdmin;
		newAdmin.setUser(newUser);
		newAdmin.setPass(newPass);
		newAdmin.setManeger(newManeger);
		cout << "New Admin added!" << endl;
		admins.push_back(newAdmin);
	}
	void loadFromFile() {
		ifstream adminFile("admins.txt");
		if (adminFile.is_open()) {
			admins.clear();
			string username, password;
			bool isMgr;
			while (adminFile >> username >> password >> isMgr) {
				Admin admin;
				admin.setUser(username);
				admin.setPass(password);
				admin.setManeger(isMgr);
				admins.push_back(admin);
			}
			adminFile.close();
		}
		if (admins.empty()) {
			Admin defaultAdmin;
			defaultAdmin.setUser("admin");
			defaultAdmin.setPass("1234");
			defaultAdmin.setManeger(true);
			admins.push_back(defaultAdmin);
		}

		ifstream vehicleFile("vehicles.txt");
		if (vehicleFile.is_open()) {
			vehicles.clear();
			int id;
			string type;
			float rent;
			int availability;
			int days;
			int renter;
			while (vehicleFile >> id >> type >> rent >> availability >> days >> renter) {
				Vehicle vehicle;
				vehicle.setID(id);
				vehicle.setType(type);
				vehicle.setRent(rent);
				vehicle.setAvailability(availability);
				vehicle.setDays(days);
                vehicle.setRenter(renter);
				vehicles.push_back(vehicle);
			}
			vehicleFile.close();
		}

		ifstream userFile("users.txt");
		if (userFile.is_open()) {
			users.clear();
			int id;
			string username, password;
			double balance;
			while (userFile >> id >> username >> balance >> password) {
				User u;
				u.setId(id);
				u.setUser(username);
				u.setBalance(balance);
				u.setPass(password);
				users.push_back(u);
			}
			userFile.close();
		}
	}
	void saveToFile() {
		ofstream adminFile("admins.txt");
		for (int i = 0; i < admins.size(); i++) {
			adminFile << admins[i].getUsername() << " "
			          << admins[i].getPassword() << " "
			          << admins[i].getManeger() << endl;
		}
		adminFile.close();

		ofstream vehicleFile("vehicles.txt");
		for (int i = 0; i < vehicles.size(); i++) {
			vehicleFile << vehicles[i].getID() << " "
			            << vehicles[i].getType() << " "
			            << vehicles[i].getRent() << " "
			            << vehicles[i].getAvailability() << " "
			            << vehicles[i].getDays() << " "
						<< vehicles[i].getRenter() << endl;
		}
		vehicleFile.close();
		ofstream userFile("users.txt");
		for (int i = 0; i < users.size(); i++) {
			userFile << users[i].getID() << " "
			         << users[i].getUsername() << " "
			         << users[i].getBalance() << " "
			         << users[i].getPassword() << endl;
		}
		userFile.close();
	}
	void deleteAdmin() {

		if(admins.size() <= 1) {
			cout<<"Number of admins must be 1 aleast!";
			return;
		}

		string username;
		cout<<"Enter Username: ";
		cin>> username;

		for(int i = 0; i < admins.size(); i++) {
			if(admins[i].getUsername() == username) {
				admins.erase(admins.begin() + i);
				cout<<"Admin deleted succesfully!";
				return;
			}
		}
		cout<<"There is no such Username!"<<endl;
	}
	bool login() {
		int attempts = 0;
		string EnterUsern;
		string EnterPassw;

		while(attempts < 3) {
			cout<<"Enter username:";
			cin>>EnterUsern;

			cout<<"Enter password:";
			cin>>EnterPassw;

			bool found = false;

			for(int i = 0; i < admins.size(); i++) {
				if(EnterUsern == admins[i].getUsername() && EnterPassw == admins[i].getPassword()) {
					found = true;
					index = i;
					break;
				}
			}
			if(found == true) {
				cout << "Welcome Admin!\n";
				return true;
			} else {
				cout << "Invalid username or password try again.\n";
				attempts++;
			}
		}
		return false;
	}
	void addVehicle() {
		int newID;
		string newType;
		float newRent;
		bool duplicate = false;

		if(vehicles.empty()) {
			newID = 1;
		}
		else {
			newID = vehicles.back().getID() + 1;
		}


		cout<<"Enter Vehicle type: ";
		cin>>newType;
		cout<<"Enter rent days: ";
		cin>>newRent;

		Vehicle newVehicle;
		newVehicle.setID(newID);
		newVehicle.setType(newType);
		newVehicle.setRent(newRent);
		newVehicle.setAvailability(true);
		newVehicle.setRenter(0);
		vehicles.push_back(newVehicle);

		cout<<"Vehicle created successfully with ID: " << newID << "!\n";

	}
	void deleteVehicle() {
		int DeleteID;
		cout<<"Enter vehicle ID to delete: ";
		cin>>DeleteID;
		int index=-1;

		for(int i=0; i < vehicles.size(); i++) {
			if(vehicles[i].getID() == DeleteID) {
				index = i;
				break;
			}
		}

		if(index == -1) {
			cout<<"Vehicle not found";
		}
		else {
			vehicles.erase(vehicles.begin() + index);
			cout << "Vehicle deleted successfully.\n";
		}
	}
	void updateRent()
	{
		int id;
		float newRate;

		cout << "Enter vehicle ID: ";
		cin >> id;

		for(int i = 0; i < vehicles.size(); i++)
		{
			if(vehicles[i].getID() == id)
			{
				cout << "Enter new rate: ";
				cin >> newRate;

				vehicles[i].setRent(newRate);

				cout << "Updated successfully";
				return;
			}
		}

		cout << "Vehicle not found";
		for(int i = 0; i < vehicles.size(); i++)
		{
			cout << "Vehicle ID: " << vehicles[i].getID() << endl;
			cout << "Type: " << vehicles[i].getType() << endl;
			cout << "Rental Rate: " << vehicles[i].getRent() << endl;

			if(vehicles[i].getAvailability() == true)
				cout << "Status: Available" << endl;
			else
				cout << "Status: Rented" << endl;

		}
	}

	void displayVehicles() {
		if (vehicles.size() == 0) {
			cout << "\n[!] No vehicles available to display.\n";
			return;
		}

		cout << "\n====================================\n";
		cout << "          VEHICLES LIST             \n";
		cout << "====================================\n";

		for (int i = 0; i < vehicles.size(); i++) {
			cout << "Vehicle ID  : " << vehicles[i].getID() << "\n";
			cout << "Type        : " << vehicles[i].getType() << "\n";
			cout << "Rent : " << vehicles[i].getRent() << "\n";
			if (vehicles[i].getAvailability() == true) {
				cout << "Status      : Available\n";
			} else {
				string renterName = "Unknown";
				for (int j = 0; j < users.size(); j++) {
					if (users[j].getID() == vehicles[i].getRenter()) {
						renterName = users[j].getUsername();
						break;
					}
				}
				cout << "Status      : Rented " << vehicles[i].getDays() << " days by: " << renterName << " (ID: " << vehicles[i].getRenter() << ")\n";
			}

			cout << "------------------------------------\n";
		}
	}
	void displayUsers() {
		cout << "\n--- All Registered Users ---\n";
		for(int i = 0; i < users.size(); i++) {
			cout << "ID: "<<users[i].getID()<<" | Username: "<<users[i].getUsername()<<" | Balance: $"<<users[i].getBalance()<<endl;
		}
	}
	void deleteUser() {
		int DeleteID;
		cout<<"Enter User ID to delete: ";
		cin>>DeleteID;
		int index=-1;

		for(int i=0; i < users.size(); i++) {
			if(users[i].getID() == DeleteID) {
				index = i;
				break;
			}
		}

		if(index == -1) {
			cout<<"User not found"<<endl;
		}
		else {
			users.erase(users.begin() + index);
			cout << "User deleted successfully.\n";
		}
	}
	bool isManeger() {
		if (index != -1) {
			return admins[index].getManeger();
		}
		return false;
	}
};
int main() {

	AdminSystem system;

	system.loadFromFile();

	if (system.login()) {
		if(system.isManeger()) {
			int choice = 0;

			while (choice != 9) {
				cout << "\n=== Admin Dashboard ===\n";
				cout << "1. Display Vehicles\n";
				cout << "2. Add Vehicle\n";
				cout << "3. Delete Vehicle\n";
				cout << "4. Update Rent\n";
				cout << "5. Add Admin\n";
				cout << "6. Delete Admin\n";
				cout << "7. Display Users\n";
				cout << "8. Delete User\n";
				cout << "9. Exit\n";
				cout << "Enter your choice: ";
				cin >> choice;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Invalid input! Please enter a valid number." << endl;
					continue;
				}
				switch (choice) {
				case 1:
					system.displayVehicles();
					break;
				case 2:
					system.addVehicle();
					break;
				case 3:
					system.deleteVehicle();
					break;
				case 4:
					system.updateRent();
					break;
				case 5:
					system.addAdmin();
					break;
				case 6:
					system.deleteAdmin();
					break;
				case 7:
					system.displayUsers();
					break;
				case 8:
					system.deleteUser();
					break;
				case 9:
					cout << "Exiting system..." <<endl;
					system.saveToFile();
					break;
				default:
					cout << "Invalid choice. Try again." <<endl;
				}
			}
		}
		else {
			int choice = 0;
			while (choice != 5) {
				cout << "\n=== Admin Dashboard ===\n";
				cout << "1. Display Vehicles\n";
				cout << "2. Add Vehicle\n";
				cout << "3. Delete Vehicle\n";
				cout << "4. Update Rent\n";
				cout << "5. Exit\n";
				cout << "Enter your choice: ";
				cin >> choice;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Invalid input! Please enter a valid number." << endl;
					continue;
				}
				switch (choice) {
				case 1:
					system.displayVehicles();
					break;
				case 2:
					system.addVehicle();
					break;
				case 3:
					system.deleteVehicle();
					break;
				case 4:
					system.updateRent();
					break;
				case 5:
					cout << "Exiting system..." <<endl;
					system.saveToFile();
					break;
				default:
					cout << "Invalid choice. Try again." <<endl;
				}
			}
		}
	} else {
		cout <<endl << "Access Denied. Exiting program..." <<endl;
	}

	return 0;
}