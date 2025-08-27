#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "local db.text";

void ShowMainMenue();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

vector< string> SplitString(string S1, string Delmi= "#//#") {
    vector<string> vstring;
    short pos = 0;
    string sword; 

    while ((pos = S1.find(Delmi)) != string::npos) {

        sword = S1.substr(0, pos);
        if (sword != "") vstring.push_back(sword);

        S1.erase(0, pos + Delmi.size());
    }

    if (S1 != "") vstring.push_back(S1);

    return vstring;
}

sClient ConvertLinetoRecord(string line, string delmi = "#//#") {

    sClient data;

    vector<string> data_of_lines = SplitString(line);

    data.AccountNumber = data_of_lines[0];
    data.PinCode= data_of_lines[1];
    data.Name= data_of_lines[2];
    data.Phone= data_of_lines[3];
    data.AccountBalance= stod(data_of_lines[4]);

    return data; 

}

string ConvertRecordToLine(sClient Client, string delmi = "#//#") {
    string ClientLine = " ";

    ClientLine += Client.AccountNumber + delmi;
    ClientLine+=Client.PinCode + delmi;
    ClientLine+=Client.Name + delmi;
    ClientLine +=Client.Phone+ delmi;
    ClientLine +=to_string(Client.AccountBalance)+ delmi;

    return ClientLine;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName) {

    sClient data; 
    vector<sClient> Vclients; 
  
    fstream read; 
    read.open(FileName, ios::in); // read mode 
    if (read.is_open()) {

        string Line;

        while (getline(read, Line)) {

            data= ConvertLinetoRecord(Line);

            if (data.AccountNumber == AccountNumber) {
                read.close();
                return true;
            }
            Vclients.push_back(data);
        }
        read.close();
    }
    return false; 
}

// for add new client 
sClient ReadNewClient() {

    sClient data;

    cout << "Enter account number: ";
    getline(cin >> ws, data.AccountNumber);

    while (ClientExistsByAccountNumber(data.AccountNumber, "local db.text")) {

        cout << "\nClient with [" << data.AccountNumber << "] already exists, Enter another Account Number? ";

        getline(cin >> ws, data.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, data.PinCode);

    cout << "Enter Name? ";
    getline(cin, data.Name);

    cout << "Enter Phone? ";
    getline(cin, data.Phone);

    cout << "Enter AccountBalance? ";
    cin >> data.AccountBalance;

    return data;

}

//vector of structure that have all data from file 
vector<sClient> LoadCleintsDataFromFile(string FileName) {

    vector< sClient> VectorOFStructure;
    fstream read;
    read.open(FileName, ios::in); // read mode 

    if (read.is_open()) {
        sClient data;
        string record = " ";

        while (getline(read, record)) {
            data = ConvertLinetoRecord(record);
            VectorOFStructure.push_back(data);
        }
        read.close();
    }

    return VectorOFStructure;
}

// will use it in show all client menu 
void PrintClientRecordLine(sClient client) {
    // print Client  data 
    cout << "|" << setw(15) << client.AccountNumber;
    cout << "|" << setw(10) << left << client.PinCode;
    cout << "|" << setw(40) << left << client.Name;
    cout << "|" << setw(12) << left << client.Phone;
    cout << "|" << setw(12) << left << client.AccountBalance;
}

//option 1 
void ShowAllClientsScreen() {
    vector<sClient> Vclient= LoadCleintsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t\tClient List (" << Vclient.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
        << endl;


    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
        << endl;

    if(Vclient.size()==0)  cout << "\t\t\t\tNo Clients Available In the System!";

    else {

        for (const sClient &clientData : Vclient) {

            PrintClientRecordLine(clientData);
            cout << endl;
        }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
            << endl;
    }

}

void PrintClientCard(sClient client) {
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << client.AccountNumber;
    cout << "\nPin Code     : " << client.PinCode;
    cout << "\nName         : " << client.Name;
    cout << "\nPhone        : " << client.Phone;
    cout << "\nAccount Balance: " << client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> Vclients, sClient& client) {

    for (sClient& foundClient : Vclients) {

        if (foundClient.AccountNumber == AccountNumber) {

            client = foundClient;
            return true; 
        }
    }
    
    return false; 
}

// fill to update data 
sClient ChangeClientRecord(string AccountNumber) {

    sClient client;
    client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, client.PinCode);

    cout << "Enter Name? ";
    getline(cin, client.Name);

    cout << "Enter Phone? ";
    getline(cin, client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> client.AccountBalance;

    return client;

}

// the main logic of delete client
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& Vclient) {

    for (sClient& c : Vclient) {
        if (c.AccountNumber == AccountNumber) {
            c.MarkForDelete = true;
            return true; 
        }
    }

    return false; 
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> Vclients) {

    fstream write;
    write.open(FileName, ios::out); // write mode 

    string DataLine = " ";
    if (write.is_open()) {

        for (sClient client : Vclients) {

            if (client.MarkForDelete == false) {
                DataLine = ConvertRecordToLine(client);
                write << DataLine << endl; // push to file 
            }
        }
        write.close();
    }
    return Vclients;
}



