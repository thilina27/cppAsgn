#include <iostream>
#include <string.h>

using namespace std;

const int maxReq=10;
const int numOfCustomers=2;
const int numOfTutors=2;

int mainMenu();
void checkvalid(bool &flag,int mini, int maxi, int choice);
void setValue(struct Tutor tutors[], struct Customer customers[]);
bool loginMenu(string &username , string &password);
bool login(string username , string password, int loginType, struct Tutor tutors[], struct Customer customers[]);


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
};

//create structure for customer
struct Customer
{
    int id;
    string name;
    string password;
};

//structure for customer requests
struct Request
{
    int custID;
    int day;
    int lession;
    float maxRate;
};

int main()
{


    //array to store tutors
    Tutor tutors[numOfTutors];

    //Customer array
    Customer customers[numOfCustomers];

    //request array
    Request requests[maxReq];

    //request array num elements
    int reqElemnts = 0;

    //Admin array

    //login type (1 - Admin, 2 - Customer, 3 - Tutor)
    int loginType = 0;

    //logged in or not
    bool isLogged = false;

    //exit
    bool exit=false;

    setValue(tutors,customers);

    while(!exit){

        //get login type
        loginType = mainMenu();

        if(loginType == 4){
            exit = true;
        }
        else{
            //username pasword holder
            string username;
            string password;
            bool back=false;

            while(!isLogged && !back){
                //show login menu
                back=loginMenu(username,password);
                //loged in user
                if(!back){
                    isLogged=login(username,password,loginType,tutors,customers);
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
bool login(string username, string password, int loginType, struct Tutor tutors[], struct Customer customers[]){

    cout<<username<<endl;
    cout<<password<<endl;
    //log user based on loggin type
    if(loginType == 1){

        //to do admin
    }
    else if(loginType == 2){
        //customers
        for(int i=0; i<numOfCustomers; i++) {
            string a=customers[i].name;
            cout<<a<<endl;
            if(a==username){
                string b=customers[i].password;
                cout<<b<<endl;
                if(b==password){
                    cout << "Login Success"<<endl;
                    cout << "Rederecting......"<<endl;
                    return true;
                }

            }

        }
        cout << "Loggin failed. Try agin! ";
        return false;

    }//end customer type log
    else{
        //customers
        for(int i=0; i<numOfTutors; i++) {

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

//customer menu
int CustomerMenu(int prvSelection){

    int selection;
    bool valid = false;

    while(!valid){

        cout <<" 1. Request tutor"<<endl;
        cout <<" 2. Show bill"<<endl;
        cout <<" 3. Back"<<endl;
        cout <<"Enter choice : ";
        cin  >>selection;

        checkvalid(valid,1, 4, selection);

        if(selection == 3){
            selection = prvSelection;
        }
    }

    return selection;
}

//request tutor menu
void requestTutorMenu(int prvSelection, struct Request requests[], int &reqElemnts){

    int day;
    int lession;
    float maxRate;


    if(reqElemnts == maxReq){
        cout << "Cannot make request contact Administrator ";
    }
    else{
        cout <<"Enter day of the week (1 for mon ,2 for tues etc) : ";
        cin  >>day;
        cout <<"Select lession 1- bla 2 - bla so on :";
        cin  >>lession;
        cout <<"Max hourly rate willing to play : ";
        cin  >>maxRate;

        //add values to request array
        reqElemnts++;
        requests[reqElemnts].day = day;
        requests[reqElemnts].lession = lession;
        requests[reqElemnts].maxRate = maxRate;
    }

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
