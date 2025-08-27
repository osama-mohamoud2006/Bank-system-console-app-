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