#include <iostream>
#include <iomanip>
#include <vector>
#include <cctype>
#include <string>
#include"E:\projects\my library\AllStuff.h"  
using namespace AllStuff;
using namespace std;

struct stdata
{
	string account_number = " ";
	string pin = "";
	string name = " ";
	string phone = " ";
	string account_balance = " ";
};
enum enOption{ none =0,showClientList=1 , addNewClient=2 , Exit=6 };


void  back_to_menu() {
	cout << "\npress any key to back to main menu ! " << endl;
	system("pause>0");
}

void testPrint() {
	cout << "hello" << endl;

	
}




enOption select_option() {
	bool is_ok = false;
	int number = 0;
	do {


		cin >> number;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\a";
			system("color 4F"); // red if number isn't in range 
			cout << "\nplease enter correct number which in range you assigned!\n";

		}

		else {
			is_ok = true;
		}
	} while (is_ok == false);
	system("color 0F"); //rest screen color 
	return (enOption)number;
}

void main_menu() {
	system("cls");
	cout << setw(5) << "\tWelcome to bank system! " ;
	cout << "\n_____________________________________________________\n\n";
	cout << setw(5) << "please enter the number of the option you want: \n"<<endl;

	cout << setw(4)<<"\t[1] print the clients list." << endl;
	cout << setw(4)<<"\t[2] add new client." << endl;
	cout << setw(4) << "\t[3] delete client." << endl;
	cout << setw(4) << "\t[4] update clients info." << endl;
	cout << setw(4) << "\t[5] find client." << endl;
	cout << setw(4) << "\t[6] exit." << endl;
	cout << "\n_____________________________________________________\n\n";
	cout << "Please enter the option you want: " ;

	
}

void exit_screen() {
	cout << "\t________________________________________________________________________" << endl;
	cout << "\t\t\t\t Say Good bye to me , mewo " << endl;
	cout << "\t________________________________________________________________________" << endl;
	system("pause");
}

void do_job_according_to_number(enOption option) {
	system("cls");
	
	switch (option) {
	case enOption::showClientList:
		testPrint();
		back_to_menu();
		break;

	case enOption::Exit:
		exit_screen();
		break;

	default:
    enOption::none;
			
	}
	
}


void start()
{
	system("cls");
	screen_color(black);
	enOption choice = none; // intial 

	do {

		main_menu(); // show main menu 
		
		// select option according to user then run selected job
		choice = select_option();
		do_job_according_to_number(choice);

		

	} while ( choice != enOption::Exit);
	

}
int main() {
	start();
}