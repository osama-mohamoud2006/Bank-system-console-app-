#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include"E:\projects\my library\AllStuff.h"  
using namespace AllStuff;
using namespace std;

///////    esstinals for the project//////////////////////////////////////
struct stdata
{
	string account_number = " "; // this is the main key which is very importat to manage data 
	string pin = " ";
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

stdata fill_data(string account_number) {
	stdata data;
	data.account_number = account_number;
	data.pin = read_string("\nenter pin: ");
	data.name = read_full_line("\nenter name: ");
	data.phone = read_string("\nenter your phone number: ");
	data.account_balance = read_string("\nenter account balance: ");
	return data;
	

}

// split line(from file)  into raw data (very imp )
vector<string> split_string(string new_client_line , string delmi) {

	vector<string> vdata;
	short pos = 0; 
	string sword;
	 
	while ((pos = new_client_line.find(delmi)) != string::npos) {

		sword = new_client_line.substr(0, pos);

		if (sword != "") vdata.push_back(sword);

		new_client_line.erase(0, pos + delmi.length());
	}

	if (new_client_line != "") vdata.push_back(new_client_line);

	return vdata;

}

//convert line of file into data filled in struct (return stdata which filled with data)
stdata convert_line_into_record(string new_client_line) {

	vector<string> dataSplited;
	stdata data;
	dataSplited = split_string(new_client_line, delmi);

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
	fstream write;
	write.open(path, ios::in); //read mode 

	if (write.is_open()) {

		string ld=" "; // line of data 
		stdata data;
		while (getline(write, ld)) {
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

//print header for show client list (FOR "SHOW ALL CLIENT (1) ) 
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

	cout << string(77, '-') << endl; 
}

//print data (FOR "SHOW ALL CLIENT (1) ) 
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
	vprint = Vector_have_all_data(path); // bring all data from file to print 

	print_header(vprint.size()); // print header
	for (const stdata& client : vprint) {

		
		printStruct(client); // print clients data 
	}

	
}

// check if the account number (entered by user) is exist in file or not 
bool check_the_account_number(string account_number_by_user ) {
	stdata data; 
	data.account_number = account_number_by_user;
	vector<stdata> search_account_number;
	search_account_number = Vector_have_all_data(path);

	for (stdata &vd : search_account_number) {
		if (vd.account_number == data.account_number) {
			//Client = vd;
			return true;
		}
	}
	
	return false;
}

//convert stdata into single line to store in file 
string convert_stdata_into_single_line(stdata data) {
	return (data.account_number + delmi + (data.pin) + delmi + data.name + delmi + data.phone + delmi + (data.account_balance));
}

//take vector with edited data and write it into file
void edit_file(vector <string> &lines_of_data) {

	

	fstream write;
	write.open(path, ios::out); //write mode

	if (write.is_open()) {

		for (const string &new_client_line : lines_of_data) {

			if(new_client_line!="") write << new_client_line << endl;
         
		}
		write.close();
	}

}

char choice_add_new_or_not() {
	char c = ' ';
	cin >> c;
	 c=toupper(c);
	 return c; 
}

void add_client() {
	cout << "\n_________________________________________________\n\n\n";
	cout << "\t adding new client\n";
	cout << "\n_________________________________________________\n";
	string account_number =" "; 
	stdata Client_data;
	
	
	char choice = 'Y';
	do {

		account_number = read_string("\n\nenter account number: ");

		// if the check == true then the account number exist and ask the user to enter another one
		while (check_the_account_number(account_number) != false) {

			cout << "\nthe account number " << "[ " << account_number << " ]" << " is exist!, ";
			cout << "\a";
			account_number = read_string("enter correct account number again : ");
		}

		/// if the account number isn't exist 
		cout << "\n________________________\n";
		cout << endl;
		Client_data = fill_data(account_number); // fill data into empty stdata

		string new_client_line = convert_stdata_into_single_line(Client_data); // convert the data into single line

		vector<stdata> all_data_from_file_in_vector;

		all_data_from_file_in_vector = Vector_have_all_data(path); // make copy of all data into vector to edit it 

		vector<string> Nlines_of_data; // empth vector to push the existing data with new data also

		for (stdata& d : all_data_from_file_in_vector) {
			string record = convert_stdata_into_single_line(d); // convert struct into line 
			Nlines_of_data.push_back(record); // push lines of data (in empty vector )
		}
		Nlines_of_data.push_back(new_client_line); // push the new client into file 

		edit_file(Nlines_of_data); // write the new data with update

		cout << "\ndata successfully added,do you want to add another clients [y],[n]? : ";
		choice = choice_add_new_or_not();

	} while (choice == 'Y');



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
	cout << "\t\t\t\t Say Good bye to me , mewo :)" << endl;
	cout << "\t________________________________________________________________________" << endl;
	system("pause");
}
void do_job_according_to_number(enOption option) {
	system("cls");
	
	switch (option) {

	case enOption::showClientList:
		show_client_list(); // option[1]
		back_to_menu(); // to back to main menu again 
		break;

	case enOption::addNewClient:
		add_client(); // option[2]
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
////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

	start();


}