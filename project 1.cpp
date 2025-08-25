#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include"E:\projects\my library\AllStuff.h"  
using namespace AllStuff;
using namespace std;

//esstinals for the project/////////////////////////////////////////////////
struct stdata
{
	string account_number = " ";
	string pin = "";
	string name = " ";
	string phone = " ";
	string account_balance = " ";
};
enum enOption{ none =0,showClientList=1 , addNewClient=2 , Exit=6 };
const string path = "local db.text";
const string delmi = "#//#";
void  back_to_menu() {
	cout << "\npress any key to back to main menu ! " << endl;
	system("pause>0");
}
//////////////////////////////////////////////////////////////////////////////////

// split line(from file)  into raw data (very imp )
vector<string> split_string(string line , string delmi) {

	vector<string> vdata;
	short pos = 0; 
	string sword;
	 
	while ((pos = line.find(delmi)) != string::npos) {

		sword = line.substr(0, pos);

		if (sword != "") vdata.push_back(sword);

		line.erase(0, pos + delmi.length());
	}

	if (line != "") vdata.push_back(line);

	return vdata;

}

//convert line of file into data filled in struct (return stdata which filled with data)
stdata convert_line_into_record(string line) {

	vector<string> dataSplited;
	stdata data;
	dataSplited = split_string(line, delmi);

	data.account_number = dataSplited[0];
	data.pin = dataSplited[1];
	data.name= dataSplited[2];
	data.phone =dataSplited[3];
	data.account_balance = dataSplited[4];

	return data;

}

//read file then push all data into vector of struct 
vector<stdata> Vector_have_all_data(string path){
	
	vector<stdata> v_with_all_data;
	fstream read;
	read.open(path, ios::in); //read mode 

	if (read.is_open()) {

		string ld=" "; // line of data 
		stdata data;
		while (getline(read, ld)) {
			if (ld != "") 
			{

            data = convert_line_into_record(ld); // fill empty struct with data after convert line into raw data
			v_with_all_data.push_back(data); // push the data in vector 

			}
			
		}
	}
	else {
		cout << "file couldn't open!" << endl;
		cout << "\a";
		screen_color(red);
	}
	return v_with_all_data;
}

//print header for show client list
void print_header(int num) {
	cout << "\n\n";
	cout << setw(35) << right << " CLIENTS LIST (" << num << ")\n\n";

	cout << left;
	cout << setw(15) << "Account Num"
		<< setw(10) << "Pin"
		<< setw(22) << "Name"
		<< setw(18) << "Phone"
		<< setw(12) << "Balance"
		<< endl;

	cout << string(77, '-') << endl; // ?? ???? ??? ????????
}
//print data 
void printStruct(const stdata& data)
{
	cout << "| " << left
		<< setw(13) << data.account_number << " | "
		<< setw(8) << data.pin << " | "
		<< setw(18) << data.name << " | "
		<< setw(13) << data.phone << " | "
		<< right
		<< setw(10) << data.account_balance << " |"
		<< endl;
	cout << "+---------------+----------+--------------------+---------------+------------+" << endl;
}

// option [1] in main menu 
void show_client_list() {

	vector<stdata> vprint;
	vprint = Vector_have_all_data(path);

	print_header(vprint.size()); // print header
	for (stdata& client : vprint) {

		
		printStruct(client); // print clients data 
	}

	
}


/// main menu stuff ////////////////////////////////////////////////////////////////
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
		show_client_list();
		back_to_menu(); // to back to main menu again 
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