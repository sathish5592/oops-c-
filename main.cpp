#include <iostream>
#include <vector>
#include <string>
using namespace std;

class atm {
private:
	long int account_No;
	string name;
	int PIN;
	double balance;
	string mobile_No;
public:
	void setData(long int account_No_a, string name_a, int PIN_a, double balance_a, string mobile_No_a) {
		account_No = account_No_a;
		name = name_a;
		PIN = PIN_a;
		balance = balance_a;
		mobile_No = mobile_No_a;
	}

	long int getAccountNo() {
		return account_No;
	}

	string getName() {
		return name;
	}

	int getPIN() {
		return PIN;
	}

	double getBalance() {
		return balance;
	}

	string getMobileNo() {
		return mobile_No;
	}

	void setMobile(string mob_prev, string mob_new) {
		if (mob_prev != mobile_No) {
			cout << "Incorrect mobile number" << endl;
		}
		else {
			mobile_No = mob_new;
			cout << "Mobile number updated successfully!" << endl;
		}
	}

	void cashWithDraw(int amount_a) {
		if (amount_a > 0 && amount_a <= balance) {
			balance -= amount_a;
			cout << endl << "Amount successfully withdrawn!";
			cout << endl << "Available balance: " << balance << endl;
		}
		else {
			cout << endl << "Invalid amount or insufficient balance!" << endl;
		}
	}
};

vector<atm> users;  // Vector to store multiple ATM users

// Function to add a new user
void addNewUser() {
	long int accountNo;
	string name, mobileNo;
	int PIN;
	double balance;

	cout << "Enter account number: ";
	cin >> accountNo;
	cout << "Enter name: ";
	cin.ignore();  // To ignore the newline character left by previous input
	getline(cin, name);  // To take full name with spaces
	cout << "Enter PIN: ";
	cin >> PIN;
	cout << "Enter balance: ";
	cin >> balance;
	cout << "Enter mobile number: ";
	cin >> mobileNo;

	// Create a new atm object and add it to the users vector
	atm newUser;
	newUser.setData(accountNo, name, PIN, balance, mobileNo);
	users.push_back(newUser);

	cout << "New user added successfully!" << endl;
}

atm* findUser(long int accountNo, int PIN) {
	for (auto& user : users) {
		if (user.getAccountNo() == accountNo && user.getPIN() == PIN) {
			return &user;  // Return a pointer to the found user
		}
	}
	return nullptr;  // Return null if user is not found
}

int main() {
	int choice = 0;
	int enterPin;
	long int enterAccountNo;

	// Adding an initial user for testing
	atm user1;
	user1.setData(1234567, "Sathish", 1111, 45000.90, "9878765432");
	users.push_back(user1);

	do {
		cout << endl << "*** Welcome to ATM ***" << endl;
		cout << "1. Access Existing User" << endl;
		cout << "2. Add New User" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			cout << "Enter your Account No.: ";
			cin >> enterAccountNo;
			cout << "Enter PIN: ";
			cin >> enterPin;

			atm* currentUser = findUser(enterAccountNo, enterPin);

			if (currentUser != nullptr) {
				int atmChoice = 0;
				do {
					int amount = 0;
					string oldMobileNo, newMobileNo;

					// User interface
					cout << endl << "*** Welcome to ATM Menu ***" << endl;
					cout << "1. Check Balance" << endl;
					cout << "2. Cash Withdraw" << endl;
					cout << "3. Show User Details" << endl;
					cout << "4. Update Mobile No." << endl;
					cout << "5. Exit" << endl;
					cout << "Enter your choice: ";
					cin >> atmChoice;

					switch (atmChoice) {
					case 1:
						cout << "Your Bank balance is: " << currentUser->getBalance() << endl;
						break;
					case 2:
						cout << "Enter amount to withdraw: ";
						cin >> amount;
						currentUser->cashWithDraw(amount);
						break;
					case 3:
						cout << "*** User Details ***" << endl;
						cout << "Account No.: " << currentUser->getAccountNo() << endl;
						cout << "Name: " << currentUser->getName() << endl;
						cout << "Balance: " << currentUser->getBalance() << endl;
						cout << "Mobile No.: " << currentUser->getMobileNo() << endl;
						break;
					case 4:
						cout << "Enter old mobile number: ";
						cin >> oldMobileNo;
						cout << "Enter new mobile number: ";
						cin >> newMobileNo;
						currentUser->setMobile(oldMobileNo, newMobileNo);
						break;
					case 5:
						cout << "Exiting ATM Menu..." << endl;
						break;
					default:
						cout << "Invalid choice. Try again." << endl;
					}
				} while (atmChoice != 5);  // Exit menu when the user chooses option 5

			}
			else {
				cout << "Invalid account number or PIN!" << endl;
			}
			break;
		}
		case 2:
			addNewUser();
			break;
		case 3:
			cout << "Exiting..." << endl;
			break;
		default:
			cout << "Invalid choice. Try again." << endl;
		}

	} while (choice != 3);  // Exit the system when the user selects "Exit"

	return 0;
}
