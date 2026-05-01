#include<iostream>
#include<string>
using namespace std;

class Admin {
private:
	string username;
	string password;
	bool maneger;
public:
	void setUser(string u) {
		username = u;
	}
	void setPass(string p) {
		password = p;
	}
	void setManeger(bool m) {
		maneger = m;
	}
	string getUsername() {
		return username;
	}
	string getPassword() {
		return password;
	}
	bool getManeger() {
		return maneger;
	}
};

class Vehicle {
private:
	int ID;
	string type;
	float rent;
	bool available;
	int days = 0;
	int renter = 0;
public:
	void setID(int id) {
		ID = id;
	}
	void setType(string Type) {
		type = Type;
	}
	void setRent(float Rent) {
		rent = Rent;
	}
	void setAvailability(bool a) {
		available = a;
	}
	void setDays(int d) {
		days = d;
	}
	void setRenter(int r) {
        renter = r;
    }
	int getID() {
		return ID;
	}
	string getType() {
		return type;
	}
	float getRent() {
		return rent;
	}
	bool getAvailability() {
		return available;
	}
	int getDays() {
		return days;
	}
	int getRenter() {
        return renter;
    }

};

class User {
private:
	int ID;
	string name;
	string password;
	double balance;

public:
	void setId(int id) {
		ID = id;
	}
	void setUser(string u) {
		name = u;
	}
	void setPass(string p) {
		password = p;
	}
	void setBalance(double b) {
		balance = b;
	}
	int getID() {
		return ID;
	}
	string getUsername() {
		return name;
	}
	string getPassword() {
		return password;
	}
	double getBalance() {
		return balance;
	}
};
