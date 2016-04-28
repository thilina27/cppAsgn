#include <iostream>
#include <string.h>

using namespace std;

const int MAXREQ=10;
const int NUMOFCUSTOMERS=2;
const int NUMOFTUTORS=2;
const int NUMOFADMINS=1;

int mainMenu();
bool loginMenu(string &username , string &password);
bool login(string username, string password, int loginType, struct Tutor tutors[], struct Customer customers[], int &loggedID);
void navigateUser(int logintype, bool &back, struct Tutor tutors[], struct Customer customers[], struct Request requests[], int &reqElemnts, int loggedID);
int customerMenu();
int adminMenu();
void requestTutor(struct Request requests[], int &reqElemnts, int loggedID);
void assignTutors(struct Request requests[], int &reqElemnts, struct Tutor tutors[], struct Customer customers[]);
int findTutor(int lession, int day, float maxRate, struct Tutor tutors[]);
void calculateBills(struct Tutor tutors[], struct Customer customers[], int loggedID);
void showCustomerBill(struct Customer customers[], int loggedID);
void showTutorBill(struct Tutor tutors[], int loggedID);
void checkvalid(bool &flag,int mini, int maxi, int choice);
void setValue(struct Tutor tutors[], struct Customer customers[]);


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

int main()
{
    //array to store tutors
    Tutor tutors[NUMOFTUTORS];

    //Customer array
    Customer customers[NUMOFCUSTOMERS];

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
        if(loginType == 4){
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
                    cout << requests[0].day<<"dadadad"<<endl;
                    navigateUser(loginType,back,tutors,customers,requests,reqElemnts,loggedID);
                    if(back){
                        isLogged = false;
                        loginType = 0;
                    }

            }


        }
    }

    //int a = 4;
    //int b = 7;
    // int c = b & a; this is > 0 if b have values in a



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
    if(loginType == 1){
        if(username == "Admin" && password == "admin") {
            return true;
        }
        else {
            cout <<endl<< "Loggin failed. Try agin! "<<endl;
            return false;
        }
    }
    else if(loginType == 2){
        //customers
        for(int i=0; i<NUMOFCUSTOMERS; i++) {

                string a=customers[i].name;

            if(a==username){

                    string b=customers[i].password;

                if(b==password){

                    loggedID = customers[i].id;
                    cout << "Login Success"<<endl;
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
        for(int i=0; i<NUMOFTUTORS; i++) {

            if(tutors[i].name == username){

                if(tutors[i].password == password){
                    cout << "Login Success"<<endl;
                    cout << "Rederecting......"<<endl;
                    return true;
                }

            }

        }
        cout << "Loggin failed. Try agin! ";
        return false;

    }//end tutor type log
}

//redirect to correct menu based on login type
void navigateUser(int logintype, bool &back, struct Tutor tutors[], struct Customer customers[], struct Request requests[], int &reqElemnts, int loggedID){

    int selection;

    while(!back){

        if(logintype==1){
            //admin menu
            selection = adminMenu();

            if(selection == 1) {
                assignTutors(requests,reqElemnts,tutors,customers);

            }
            else if(selection == 2) {
                //manage tutor
            }
            else if(selection == 3) {
                //mange customers
            }
            else {
                back = true;
            }

        }
        else if(logintype==2){
            //customer menu
            selection = customerMenu();

            if(selection == 1) {
                requestTutor(requests,reqElemnts,loggedID);
            }
            else if(selection == 2) {
                showCustomerBill(customers,loggedID);
            }
            else {
                back = true;
            }
        }
        else{
            //tutor menu
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
        cout <<"Enter day of the week (1 for mon ,2 for tues etc) : ";
        cin  >>day;
        cout <<"Select lession 1- bla 2 - bla so on :";
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
                cout<<tutorID<<"idd"<<endl;
                if(tutorID != -1) {

                    // remove assigned day from tutor
                    int work = tutors[tutorID].workingDays - day;
                    tutors[tutorID].workingDays = work;

                    //assign tutor to customer
                    customers[custID].tutorID = tutorID;
                    customers[custID].hours = hours;

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


    for(int i=0; i<NUMOFTUTORS; i++) {

        id = tutors[i].id;
        workingDays = tutors[i].workingDays;
        hourlyPayment = tutors[i].hourlyPayment;
        experties = tutors[i].experties;

        int work = (workingDays & day);
        int les =experties & lession;

        if( (work > 0) && (hourlyPayment <= maxRate) && (les > 0)) {
            cout<<id;
            return id;
        }
    }
    cout <<endl<<endl;
    cout << "No sutable tutor found";
    return -1;
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
        cout << "Total bill "<<total<<endl<<endl;
    }
    else {
        cout << "No bill for now"<<endl<<endl;
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

        int i=0;

        tutors[i].id = i;
        tutors[i].name = "Sam";
        tutors[i].workingDays = 7;
        tutors[i].hourlyPayment = 100.00;
        tutors[i].experties = 7;
        tutors[i].email = "sjnsjs.ccm";
        tutors[i].password = "1234";
        tutors[i].total = 0.0;

        i++;
        tutors[i].id = i;
        tutors[i].name = "Jam";
        tutors[i].workingDays = 8;
        tutors[i].hourlyPayment = 170.00;
        tutors[i].experties = 4;
        tutors[i].email = "sjnsjs.ccm";
        tutors[i].password = "5678";
        tutors[i].total = 0.0;

        i=0;
        customers[i].id=i;
        customers[i].name="trc";
        customers[i].password = "7897";
        customers[i].total = 0.0;

        i++;
        customers[i].id=i;
        customers[i].name="trc2";
        customers[i].password = "7891";
        customers[i].total = 0.0;
}
