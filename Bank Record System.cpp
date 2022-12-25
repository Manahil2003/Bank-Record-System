//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<iostream>
#include<fstream> //file processing
#include<cctype> //classify (and transform) individual characters
#include<iomanip> //format the output 
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class account
{
    int acno; // account number
    char name[50]; // name of account
    int deposit; // amount to deposit
    char type; // type of account
public: // can use this functions globally
    void create_account();  //function to get data from user
    void show_account() const;  //function to show data on screen
    void modify();  //function to add new data
    void dep(int);  //function to accept amount and add to balance amount
    void draw(int); //function to accept amount and subtract from balance amount
    void report() const;    //function to show data in tabular format
    int retacno() const;    //function to return account number
    int retdeposit() const; //function to return balance amount
    char rettype() const;   //function to return type of account
};         //class ends here

//function to create account
void account::create_account()
{
    cout<<"\nEnter The account No. :";
    cin>>acno;
    cout<<"\n\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name,50);  //read a string or a line from an input stream , part of the <string> header
    cout<<"\nEnter Type of The account (C/S) : "; //current account / saving account
    cin>>type;
    type=toupper(type);
    cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
    cin>>deposit;
    cout<<"\n\n\nAccount Has Been Created..";
}

//show accounts
void account::show_account() const
{
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nAccount Holder Name : ";
    cout<<name;
    cout<<"\nType of Account : "<<type;
    cout<<"\nBalance amount : "<<deposit;
}

//modify acoounts
void account::modify()
{
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nModify Type of Account : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify Balance amount : ";
    cin>>deposit;
}

//deposit amount
void account::dep(int x)
{
    deposit+=x;
}

//credit amount
void account::draw(int x)
{
    deposit-=x;
}

//amount check
void account::report() const
{
    cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

//return account number
int account::retacno() const
{
    return acno;
}

//return deposit amount
int account::retdeposit() const
{
    return deposit;
}

//return account type
char account::rettype() const
{
    return type;
}

//***************************************************************
//      function declaration
//****************************************************************

void write_account();   //function to write record in binary file
void display_sp(int);   //function to display account details given by user
void modify_account(int);   //function to modify record of file
void delete_account(int);   //function to delete record of file
void display_all();     //function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();   //introductory screen 

//***************************************************************
//      THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
    char ch;
    int num;
    intro(); // calling intro function
    do
    {
        system("cls");
        cout<<"\n\n\n\t *********************************************";
        cout<<"\n\t *********************************************";
        cout<<"\n\n\n\t\tMAIN MENU";
        cout<<"\n\n\n\t *********************************************";
        cout<<"\n\n\t\t01. NEW ACCOUNT";
        cout<<"\n\n\t\t02. DEPOSIT AMOUNT";
        cout<<"\n\n\t\t03. WITHDRAW AMOUNT";
        cout<<"\n\n\t\t04. BALANCE ENQUIRY";
        cout<<"\n\n\t\t05. ALL ACCOUNT HOLDER LIST";
        cout<<"\n\n\t\t06. CLOSE AN ACCOUNT";
        cout<<"\n\n\t\t07. MODIFY AN ACCOUNT";
        cout<<"\n\n\t\t08. EXIT";
        cout<<"\n\n\n\t *********************************************";
        cout<<"\n\t *********************************************";
        cout<<"\n\n\t\tSelect Your Option (1-8) ";
        cin>>ch;
        system("cls");
        switch(ch)
        {
        case '1': //create account
            write_account();
            break;
        case '2': //Deposit amount
            cout<<"\n\n\tAccount Number : "; cin>>num;
            deposit_withdraw(num, 1);
            break;
        case '3': //Withdraw amount
            cout<<"\n\n\tAccount Number  : "; cin>>num;
            deposit_withdraw(num, 2);
            break;
        case '4': //Balance enquiry
            cout<<"\n\n\tAccount Number : "; cin>>num;
            display_sp(num);
            break;
        case '5': //Holder list
            display_all();
            break;
        case '6': //Close account
            cout<<"\n\n\tAccount Number : "; cin>>num;
            delete_account(num);
            break;
         case '7': //Modify account
            cout<<"\n\n\tAccount Number : "; cin>>num;
            modify_account(num);
            break;
         case '8': //End
            cout<<"\n\n\tThanks for using our service";
            cout<<"\n\n\tProgram Ends ... !!!";
            break;
         default :cout<<"a";
        }
        cin.ignore(); //used to ignore or clear one or more characters from the input buffer
        cin.get(); //accessing character array
    }while(ch!='8');
    return 0;
}
//***************************************************************
//      function to write in file
//****************************************************************
void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
    outFile.close();
}
//***************************************************************
//      function to read specific record from file
//****************************************************************
void display_sp(int n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\nBALANCE DETAILSn";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retacno()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}
//***************************************************************
//      function to modify record of file
//****************************************************************
void modify_account(int n)
{
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=true;
          }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}
//***************************************************************
//      function to delete record of file
//****************************************************************
void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retacno()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\n\tRecord Deleted ..";
}
//***************************************************************
//      function to display all accounts deposit list
//****************************************************************
void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\n\n\t\tACCOUNT HOLDER LISTnn";
    cout<<"====================================================n";
    cout<<"A/c no.      NAME           Type  Balancen";
    cout<<"====================================================n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}
//***************************************************************
//      function to deposit and withdraw amounts
//****************************************************************
void deposit_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                cout<<"n\n\Enter The amount to be deposited";
                cin>>amt;
                ac.dep(amt);
            }
            if(option==2)
            {
                cout<<"\n\n\tTO WITHDRAW AMOUNT ";
                cout<<"\n\nEnter The amount to be withdraw";
                cin>>amt;
                int bal=ac.retdeposit()-amt;
                if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                    cout<<"Insufficience balance";
                else
                    ac.draw(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=true;
           }
         }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}
//***************************************************************
//      INTRODUCTION FUNCTION
//****************************************************************
void intro()
{
	cout<<"\n\n\n\t *********************************************";
	cout<<"\n\t *********************************************";
	cout<<"\n\n\n\t\t\t FINAL PROJECT";
	cout<<"\n\n\n\t *********************************************";
    cout<<"\n\n\n\t\t BANK";
    cout<<"\n\n\t\t\tRECORD";
    cout<<"\n\n\t\t\t\tSYSTEM";
    cout<<"\n\n\n\t *********************************************";
    cout<<"\n\n\n\n\t\tBy:";
    cout<<"\n\n\t\t Manahil habib 47876";
    cout<<"\n\n\t\t Rahat Qadeer 47234";
    cout<<"\n\n\t\t Wajeeha Nadeem 47328";
   cout<<"\n\n\n\t *********************************************";
   	cout<<"\n\t *********************************************";
    cin.get();
}
//***************************************************************
//              END OF PROJECT
//*
