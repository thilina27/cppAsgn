#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

const int MAXREQ = 10;
const int MAX_NUM_OF_CUSTOMERS = 1000;
const int MAX_NUM_OF_TUTORS = 500;
const int NUMOFADMINS = 1;

//current count
//number of customers currently in
int numberOfCustomers = 0;
//number of tutors currently in
int numberOfTutors = 0;

int mainMenu();
bool loginMenu(string &username , string &password);
bool login(string username, string password, int loginType, struct Tutor tutors[], struct Customer customers[], int &loggedID);
void navigateUser(int logintype, bool &back, struct Tutor tutors[], struct Customer customers[], struct Request requests[], int &reqElemnts, int loggedID);
int customerMenu();
int tutorMenu();
int adminMenu();
void requestTutor(struct Request requests[], int &reqElemnts, int loggedID);
void assignTutors(struct Request requests[], int &reqElemnts, struct Tutor tutors[], struct Customer customers[]);
int findTutor(int lession, int day, float maxRate, struct Tutor tutors[]);
void calculateBills(struct Tutor tutors[], struct Customer customers[], int loggedID);
void showCustomerBill(struct Customer customers[], int loggedID);
void showTutorBill(struct Tutor tutors[], int loggedID);
void checkvalid(bool &flag,int mini, int maxi, int choice);
void setValue(struct Tutor tutors[], struct Customer customers[]);
void initCustomers(struct Customer customers[]);
void initTutors(struct Tutor tutors[]);
void exitSystem(struct Tutor tutors[], struct Customer customers[]);
void saveCustomers(struct Customer customers[]);
void saveTutors(struct Tutor tutors[]);
void manageTutorMenu(struct Tutor tutors[]);
void addTutor(struct Tutor tutors[]);

//stuctures
//create structure for tutors
struct Tutor
{
    int id;
    string name;
    int workingDays;
    float hourlyPayment;
    int experties;
    string email;
    string password;
    float total;
};

//create structure for customer
struct Customer
{
    int id;
    string name;
    string password;
    int hours;
    float total;
    int tutorID;
};

//structure for customer requests
struct Request
{
    int id;
    int hours;
    int custID;
    int day;
    int lession;
    float maxRate;
};

//enums
enum logtype{ ADMIN=1, CUSTOMER, TUTOR, EXIT};
enum menuItems{ ITEM1=1, ITEM2, ITEM3, ITEM4};

int main()
{
    //array to store tutors
    Tutor tutors[MAX_NUM_OF_TUTORS];

    //Customer array
    Customer customers[MAX_NUM_OF_CUSTOMERS];

    //request array
    Request requests[MAXREQ];

    //request array num elements
    int reqElemnts = 0;

    //login type (1 - Admin, 2 - Customer, 3 - Tutor)
    int loginType = 0;

    //logged in user id
    int loggedID = -1;

    //logged in or not
    bool isLogged = false;

    //exit
    bool exit = false;

    setValue(tutors,customers);

    while(!exit){

        //get login type
        loginType = mainMenu();
        //if exit
        if(loginType == EXIT){
            exit = true;
        }
        else{
            //username pasword holder
            string username;
            string password;
            bool back = false;

            //login for user
            while(!isLogged && !back){
                //show login menu
                back = loginMenu(username,password);
                //loged in user
                if(!back){
                    isLogged = login(username,password,loginType,tutors,customers,loggedID);
                }
            }//end login

            //if not need to go back to main menu and logged in
            if(!back && isLogged){

                navigateUser(loginType,back,tutors,customers,requests,reqElemnts,loggedID);

                if(back){
                    isLogged = false;
                    loginType = 0;
                }

            }

        }
    }
    exitSystem(tutors,customers);

    return 0;
}

//Show main menu to select the login type
int mainMenu(){

    //get and return user selection
    int selection;
    //boolean to check validity of the input
    bool valid = false;

    while(!valid){
        cout <<endl<<endl;
        cout << " ABC Company"<<endl;
        cout << "1. Admin"<<endl;
        cout << "2. Customer"<<endl;
        cout << "3. Tutor"<<endl;
        cout << "4. Exit"<<endl;
        cout << "Enter Your choice :";
        cin  >> selection;
        checkvalid(valid,1, 4, selection);

    }

    return selection;

}

//login menu
bool loginMenu(string &username , string &password){

    cin.get();
    cout <<endl<<endl;
    char c='e';
    cout << " Login "<<endl;
    cout << "User Name  : ";
    cin  >>username;
    cout << "Password   : ";
    cin  >>password;
    cout <<"enter e to exit or s to submit : ";
    cin  >>c;

    if(c == 's'){
        return false;
    }
    else {
        return true;
    }

}

//loggin function
bool login(string username, string password, int loginType, struct Tutor tutors[], struct Customer customers[], int &loggedID){

    cout <<endl<<endl;
    //log user based on loggin type
    if(loginType == ADMIN){
        if(username == "Admin" && password == "admin") {
            cout<<"Login success Admin"<<endl;
            return true;
        }
        else {
            cout <<endl<< "Loggin failed. Try agin! "<<endl;
            return false;
        }
    }
    else if(loginType == CUSTOMER){
        //customers
        for(int i=0; i<numberOfCustomers; i++) {

                string a=customers[i].name;

            if(a==username){

                    string b=customers[i].password;

                if(b==password){

                    loggedID = customers[i].id;
                    cout << "Login Success "<<username<<endl;
                    cout << "Rederecting......"<<endl;
                    return true;
                }

            }

        }
        cout <<endl<< "Loggin failed. Try agin! "<<endl;
        return false;

    }//end customer type log
    else{
        //customers
        for(int i=0; i<numberOfTutors; i++) {

            if(tutors[i].name == username){

                if(tutors[i].password == password){
                    loggedID = tutors[i].id;
                    cout << "Login Success "<<username<<endl;
                    cout << "Rederecting......"<<endl;
                    return true;
                }

            }

        }
        cout << "Loggin failed. Try again! ";
        return false;

    }//end tutor type log
}

//redirect to correct menu based on login type
void navigateUser(int logintype, bool &back, struct Tutor tutors[], struct Customer customers[], struct Request requests[], int &reqElemnts, int loggedID){

    int selection;

    while(!back){

        if(logintype == ADMIN){
            //admin menu
            selection = adminMenu();

            if(selection == ITEM1) {
                assignTutors(requests,reqElemnts,tutors,customers);

            }
            else if(selection == ITEM2) {
                manageTutorMenu(tutors);
            }
            else if(selection == ITEM3) {
                //mange customers
            }
            else {
                back = true;
            }

        }
        else if(logintype == CUSTOMER){
            //customer menu
            selection = customerMenu();

            if(selection == ITEM1) {
                requestTutor(requests,reqElemnts,loggedID);
            }
            else if(selection == ITEM2) {
                showCustomerBill(customers,loggedID);
            }
            else {
                back = true;
            }
        }
        else{
            //tutor menu
            selection = tutorMenu();

            if(selection == ITEM1){
                //show bill
                showTutorBill(tutors,loggedID);

            }
            else{
                back = true;
            }
        }
    }

}

//customer menu
int customerMenu(){

    int selection;
    bool valid = false;

    while(!valid){
        cout <<endl<<endl;
        cout <<" 1. Request tutor"<<endl;
        cout <<" 2. Show bill"<<endl;
        cout <<" 3. Back"<<endl;
        cout <<"Enter choice : ";
        cin  >>selection;

        checkvalid(valid,1, 3, selection);

    }

    return selection;
}

//tutor menu
int tutorMenu(){

    int selection;
    bool valid = false;

    while(!valid){
        cout <<endl<<endl;
        cout <<" 1. Show payslip"<<endl;
        cout <<" 2. Back"<<endl;
        cout <<"Enter choice : ";
        cin  >>selection;

        checkvalid(valid,1, 2, selection);

    }

    return selection;
}

//Admin menu
int adminMenu(){

    int selection;
    bool valid = false;

    while(!valid){

        cout <<endl<<endl;
        cout <<" 1. Assign tutor"<<endl;
        cout <<" 2. Manage tutors"<<endl;
        cout <<" 3. Manage Customers"<<endl;
        cout <<" 4. Exit"<<endl;
        cout <<"Enter choice : ";
        cin  >>selection;

        checkvalid(valid,1, 4, selection);

    }

    return selection;
}

//request tutor
void requestTutor(struct Request requests[], int &reqElemnts, int loggedID){

    int day;
    int lession;
    int numberOfHours;
    float maxRate;

    cout <<endl<<endl;

    if(reqElemnts == MAXREQ){
        cout << "Cannot make request contact Administrator ";
    }
    else{
        cout <<"Enter day of the week (1 for Monday ,2 for Tuesday, etc) : ";
        cin  >>day;
        cout <<"Select lesion (1 - Computer Science, 2 - Mathematics, 3 - Statistics, 4 - Physics) :";
        cin  >>lession;
        cout <<"Max hourly rate willing to play : ";
        cin  >>maxRate;
        cout <<"Number of hours : ";
        cin  >>numberOfHours;

        //add values to request array
        requests[reqElemnts].day = day;
        requests[reqElemnts].lession = lession;
        requests[reqElemnts].maxRate = maxRate;
        requests[reqElemnts].hours = numberOfHours;
        requests[reqElemnts].id = reqElemnts;
        requests[reqElemnts].custID = loggedID;
        reqElemnts++;
    }

}

//assign tutors
void assignTutors(struct Request requests[], int &reqElemnts, struct Tutor tutors[], struct Customer customers[]) {

    int hours;
    int custID;
    int day;
    int lession;
    float maxRate;
    int tutorID = -1 ;


    if(reqElemnts != 0) {

            for(int i=0; i<reqElemnts; i++){

                custID = requests[i].custID;
                lession = requests[i].lession;
                day = requests[i].day;
                maxRate = requests[i].maxRate;
                hours = requests[i].hours;

                tutorID = findTutor(lession,day,maxRate,tutors);
                if(tutorID != -1) {

                    // remove assigned day from tutor
                    int work = tutors[tutorID].workingDays - day;
                    tutors[tutorID].workingDays = work;

                    //assign tutor to customer
                    customers[custID].tutorID = tutorID;
                    customers[custID].hours = hours;

                    cout <<"For user "<<customers[custID].name<<", tutor "<<tutors[tutorID].name<<" is assigned. "<<endl;

                    //calculate bills
                    calculateBills(tutors,customers,custID);
                }
                else {
                    string name = customers[custID].name;
                    cout <<endl<<endl;
                    cout << "Failed to assign tutor to customer named " <<name<<endl<<endl;
                }

            }
            //reset requests
            reqElemnts = 0;

    }
    else {
        cout <<endl<<endl;
        cout << "No request to assign "<<endl<<endl;
    }

}

//find a tutor
int findTutor(int lession, int day, float maxRate, struct Tutor tutors[]) {

    int id;
    int workingDays;
    float hourlyPayment;
    int experties;


    for(int i=0; i<numberOfTutors; i++) {

        id = tutors[i].id;
        workingDays = tutors[i].workingDays;
        hourlyPayment = tutors[i].hourlyPayment;
        experties = tutors[i].experties;

        int work = (workingDays & day);
        int les =experties & lession;

        if( (work > 0) && (hourlyPayment <= maxRate) && (les > 0)) {
            return id;
        }
    }
    cout <<endl<<endl;
    cout << "No sutable tutor found";
    return -1;
}

//Mange tutor sub menu
void manageTutorMenu(struct Tutor tutors[]){

    bool isValid = false;
    bool back = false;
    int selection = 0;

    while(!back){
        cout <<endl<<endl;
        cout <<"1. Add tutor. "<<endl;
        cout <<"2. Edit tutor. "<<endl;
        cout <<"3. Delete tutor. "<<endl;
        cout <<"4. Back"<<endl;

        cout<<"Enter choice : ";
        cin >>selection;

        checkvalid(isValid,1,4,selection);

        if(isValid){
             if(selection == ITEM1){
                addTutor(tutors);
            }
            else if(selection == ITEM2){
                //Edit tutor
            }
            else if(selection == ITEM3){
                //delete tutor
            }
            else{
                back = true;
            }
        }

    }

}

void addTutor(struct Tutor tutors[]){

    int id;
    string name;
    int workingDays;
    float hourlyPayment;
    int experties;
    string email;
    string password;
    float total;

    if(numberOfTutors < MAX_NUM_OF_TUTORS){
        cout <<endl<<endl;
        cin.get();
        id = tutors[numberOfTutors-1].id + 1;
        cout <<"Enter Tutor name :";
        cin  >>name;
        cout <<"Enter password of the tutor "<<name<<" :";
        cin  >>password;
        cout <<"Enter email address of the tutor "<<name<<" :";
        cin  >>email;
        cout <<"Enter working days of the tutor "<<name<<" (as a single value):";
        cin  >>workingDays;
        cout <<"Enter hourly payment for the tutor "<<name<<" :";
        cin  >>hourlyPayment;
        cout <<"Enter expertise of the tutor "<<name<<" (as a single value):";
        cin  >>experties;
        total = 0;

        //save tutor to array
        tutors[numberOfTutors].id = id;
        tutors[numberOfTutors].name = name;
        tutors[numberOfTutors].workingDays = workingDays;
        tutors[numberOfTutors].hourlyPayment = hourlyPayment;
        tutors[numberOfTutors].experties = experties;
        tutors[numberOfTutors].email = email;
        tutors[numberOfTutors].password = password;
        tutors[numberOfTutors].total = total;
        numberOfTutors++;
        cout <<endl<<"Adding Tutor "<<name<<" success "<<endl;
    }
    else{
        cout<<"Can not add more tutors max limit reached"<<endl;
    }

}

//calculate bill for customer call by admin
void calculateBills(struct Tutor tutors[], struct Customer customers[], int loggedID){

    int tutorID = customers[loggedID].tutorID;
    float totalCus = customers[loggedID].total;
    float totalTu =  tutors[tutorID].total;

    int hrs = customers[loggedID].hours;
    float rate = tutors[tutorID].hourlyPayment;

    totalCus += (hrs*rate);
    totalTu += totalCus;

    tutors[tutorID].total = totalTu;
    customers[loggedID].total = totalCus;

}

//print bill for customers
void showCustomerBill(struct Customer customers[], int loggedID){

    cout <<endl<<endl;
    float total = customers[loggedID].total;

    if(total != 0){
        cout << "Total bill "<<total<<endl<<endl;
    }
    else {
        cout << "No bill for now"<<endl<<endl;
    }
}

//print bill for tutors
void showTutorBill(struct Tutor tutors[], int loggedID){

    cout <<endl<<endl;
    float total = tutors[loggedID].total;

    if(total != 0){
        cout << "Total payslip "<<total<<endl<<endl;
    }
    else {
        cout << "No payslip for now"<<endl<<endl;
    }
}


// check validity of inputs if values are in between the given range for menu items
void checkvalid(bool &flag,int mini, int maxi, int choice){

    if(choice >= mini && choice <= maxi){
        flag = true;
    }
    else{
        cout <<endl<<endl;
        flag = false;
        cout <<endl<<"PLZ enter valid input "<<endl<<endl;
    }

}

//set values for arrays
void setValue(struct Tutor tutors[], struct Customer customers[]){

    initTutors(tutors);
    initCustomers(customers);
}

void initCustomers(struct Customer customers[]){

    int id =0;
    string name;
    string password;
    int hours;
    float total;
    int tutorID;

    int i =0;
    //open customer file
    string line;
    ifstream myfile ("customers.txt");

    if (myfile.is_open()){

        while (getline(myfile,line)){

            istringstream iss(line);

            iss >> id;
            iss >> name;
            iss >> password;
            iss >> hours;
            iss >> total;
            iss >> tutorID;

            customers[i].id = id;
            customers[i].name = name;
            customers[i].password = password;
            customers[i].hours = hours;
            customers[i].total = total;
            customers[i].tutorID = tutorID;
            i++;

    }
    numberOfCustomers=i;
    myfile.close();
  }

  else cout << "Unable to open customers file";

}

void initTutors(struct Tutor tutors[]){

    int id;
    string name;
    int workingDays;
    float hourlyPayment;
    int experties;
    string email;
    string password;
    float total;

    int i=0;
    //open customer file
    string line;
    ifstream myfile ("tutors.txt");

    if (myfile.is_open()){

        while (getline(myfile,line)){

            istringstream iss(line);

            iss >> id;
            iss >> name;
            iss >> workingDays;
            iss >> hourlyPayment;
            iss >> experties;
            iss >> email;
            iss >> password;
            iss >> total;

            tutors[i].id = id;
            tutors[i].name = name;
            tutors[i].workingDays = workingDays;
            tutors[i].hourlyPayment = hourlyPayment;
            tutors[i].experties = experties;
            tutors[i].email = email;
            tutors[i].password = password;
            tutors[i].total = total;
            i++;

    }
    numberOfTutors=i;
    myfile.close();
  }

  else cout << "Unable to open tutors file";

}

void exitSystem(struct Tutor tutors[], struct Customer customers[]){

    cout<<endl<<"Exiting System"<<endl;
    saveCustomers(customers);
    saveTutors(tutors);

}

void saveCustomers(struct Customer customers[]){

    ofstream myfile;
    myfile.open ("customers.txt");

    if (myfile.is_open()){

        int id =0;
        string name;
        string password;
        int hours;
        float total;
        int tutorID;

        cout << "Writing to customer file.\n";

        for(int i=0; i<numberOfCustomers; i++){

            id = customers[i].id;
            name = customers[i].name;
            password = customers[i].password;
            hours = customers[i].hours;
            total = customers[i].total;
            tutorID = customers[i].tutorID;

            myfile<<id<<" "<<name<<" "<<password<<" "<<hours<<" "<<total<<" "<<tutorID<<"\n";

        }


        myfile.close();

    }
    else{
        cout <<"unable to write customer file"<<endl;
    }
}

void saveTutors(struct Tutor tutors[]){

    ofstream myfile;
    myfile.open ("tutors.txt");

    if (myfile.is_open()){

        int id;
        string name;
        int workingDays;
        float hourlyPayment;
        int experties;
        string email;
        string password;
        float total;

        cout << "Writing to tutor file.\n";

        for(int i=0; i<numberOfTutors; i++){

            id = tutors[i].id;
            name = tutors[i].name;
            workingDays = tutors[i].workingDays;
            hourlyPayment = tutors[i].hourlyPayment;
            experties = tutors[i].experties;
            email = tutors[i].email;
            password = tutors[i].password;
            total = tutors[i].total;

            myfile<<id<<" "<<name<<" "<<workingDays<<" "<<hourlyPayment<<" "<<experties<<" "<<email<<" "<<password<<" "<<total<<"\n";

        }

        myfile.close();

    }
    else{
        cout <<"unable to write tutors file"<<endl;
    }
}
