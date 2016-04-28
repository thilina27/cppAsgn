#include <iostream>
#include <string.h>

using namespace std;

const int MAXREQ=10;
const int NUMOFCUSTOMERS=2;
const int NUMOFTUTORS=2;
const int NUMOFADMINS=1;

int mainMenu();
void checkvalid(bool &flag,int mini, int maxi, int choice);
void setValue(struct Tutor tutors[], struct Customer customers[]);
bool loginMenu(string &username , string &password);
bool login(string username , string password, int loginType, struct Tutor tutors[], struct Customer customers[], int &loggedID);
void navigateUser(int logintype, bool &back)


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

//Structure for admins
struct Admin
{
    int id;
    string name;
    string password;
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

    //Admin array
    Admin admins[NUMOFADMINS];

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
                    isLogged = login(username,password,loginType,tutors,customers);
                }
            }//end login

            //if not need to go back to main menu and logged in
            if(!back && isLogged){
                    navigateUser(logintype,back);
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
bool login(string username, string password, int loginType, struct Tutor tutors[], struct Customer customers[], int loggedID){

    cout<<username<<endl;
    cout<<password<<endl;
    //log user based on loggin type
    if(loginType == 1){

        //to do admin
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
                selection = customerMenu();

                if(selection == 1) {
                    requestTutor(requests[],reqElemnts);
                }
                else if(selection == 2) {


                }
                else {
                    back = true;
                }

            }
            else if(logintype==2){
                //customer menu
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

        cout <<" 1. Request tutor"<<endl;
        cout <<" 2. Show bill"<<endl;
        cout <<" 3. Back"<<endl;
        cout <<"Enter choice : ";
        cin  >>selection;

        checkvalid(valid,1, 3, selection);

    }

    return selection;
}

//request tutor
void requestTutor(struct Request requests[], int &reqElemnts, int loggedID){

    int day;
    int lession;
    int numberOfHours;
    float maxRate;


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
        cin  >>numberOfHours

        //add values to request array
        reqElemnts++;
        requests[reqElemnts].day = day;
        requests[reqElemnts].lession = lession;
        requests[reqElemnts].maxRate = maxRate;
        requests[reqElemnts].hours = numberOfHours;
        requests[reqElemnts].id = loggedID;
    }

}

//calculate bill for customer
void calculateBills(struct Tutor tutors[], struct Customer customers[], int loggedID){

    int tutorID = customers[loggedID-1].tutorID;
    float totalCus = customers[loggedID-1].total;
    float totalTu =  tutors[tutorID].total;

    if(totalCus != -1){

        int hrs = customers[loggedID-1].hours;
        float rate = tutors[tutorID].hourlyPayment;

        totalCus = hrs*rate;
        totalTu += totalCus;
    }
    else {
        cout <<"This customer dosent have any assigned tutors ";
    }
}
//print bill for customers
void showCustomerBill(){


}


// check validity of inputs if values are in between the given range for menu items
void checkvalid(bool &flag,int mini, int maxi, int choice){

    if(choice >= mini && choice <= maxi){
        flag = true;
    }
    else{
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
        i++;
        tutors[i].id = i;
        tutors[i].name = "Jam";
        tutors[i].workingDays = 8;
        tutors[i].hourlyPayment = 170.00;
        tutors[i].experties = 4;
        tutors[i].email = "sjnsjs.ccm";
        tutors[i].password = "5678";

        i=0;
        customers[i].id=i;
        customers[i].name="trc";
        customers[i].password = "7897";

        i++;
        customers[i].id=i;
        customers[i].name="trc2";
        customers[i].password = "7891";
}
