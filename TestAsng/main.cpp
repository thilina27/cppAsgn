#include <iostream>

using namespace std;

int mainMenu();
void checkvalid(bool &flag,int mini, int maxi, int choice);

int main()
{
    //create structure for tutors
    struct Tutor
    {
        int id;
        char name[30];
        int workingDays;
        float hourlyPayment;
        int experties;
        string email;
        char password[20];
    };

    //array to store tutors
    Tutor tutors[10];

    //Customer array

    //Admin array

    //login type (1 - Admin, 2 - Customer, 3 - Tutor)
    int loginType = 0;

    //logged in or not
    bool isLogged = false;


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

        cout << " ABC BLA BLA"<<endl;
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
void login(char username[] , char password[]){

    cout << " Login "<<endl;
    cout << "User Name  : ";
    cin.getline(username,sizeof(username));
    cout << "Password   : ";
    cin.getline(password,sizeof(password));

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
