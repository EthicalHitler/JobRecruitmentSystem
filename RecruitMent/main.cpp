#include <iostream>
#include<windows.h>
#include <mysql.h>
#include "employee.h"
#include "admin.h"
#include "applicant.h"

using namespace std;
int main();

string currentUser,currentPass;

void mainAdmin(MYSQL* conn){
    string user,pwd;
    cout << "****ADMIN PAGE****" << endl;
    start:
    cout << "Enter Your Admin ID : ";
    cin >> user;
    cout << "Enter Your Secret Key : ";
    cin >> pwd;

    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;
    string name = user;
    string selectQuery = "SELECT password FROM Users where username='";
    selectQuery = selectQuery + name + "'";
    char* c = const_cast<char*>(selectQuery.c_str());
    mysql_query(conn,c);
    res = mysql_store_result(conn);
    int totalrows = mysql_num_rows(res);
    int numfields = mysql_num_fields(res);
    MYSQL_FIELD *mfield;

    string val;
    while((row = mysql_fetch_row(res)))
    {
        for(int i = 0; i < numfields; i++)
        {
            val+= row[i];
        }
    }

    if(user == "admin" && val == pwd ){
        cout << "****Welcome Mr.Admin****" << endl;
        system("CLS");
        admin();
        }
    else{
        cout << "Better Luck Next time " << endl;
        exit(1);
        }

    if(res != NULL)
        mysql_free_result(res);

    mysql_close(conn);

}

void signin(MYSQL* conn){
    string user,pwd;
    int i,count = 0;
    cout << "****LOGIN PAGE****" << endl;
    start:
    cout << "Enter Your Username : ";
    cin >> user;
    cout << "Enter Your Password : ";
    cin >> pwd;

    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;
    string name = user;
    string selectQuery = "SELECT password FROM Users where username='";
    selectQuery = selectQuery + name + "'";
    char* c = const_cast<char*>(selectQuery.c_str());
    mysql_query(conn,c);
    res = mysql_store_result(conn);
    int totalrows = mysql_num_rows(res);
    int numfields = mysql_num_fields(res);
    MYSQL_FIELD *mfield;

    string val;
    while((row = mysql_fetch_row(res)))
    {
        for(int i = 0; i < numfields; i++)
        {
            val+= row[i];
        }
    }




    if(val == pwd){
        system("CLS");
        cout << "****Welcome "<< user <<"****" << endl;
        //resume("arunkumar","arun@gmail.com",1234,"ashoknagar");
        applicant(user);
    }
    else{
        ++count;
        if(count == 3){
        cout << "Trying to BruteForce huh ? " << endl;
            exit(1);
        }
        cout << "Incorrect Credentials" << endl;
        goto start;
    }


}



void signup(MYSQL* conn){
    cout << "****SIGNUP PAGE****" << endl;
    string fulname,user,pwd;
    cout << "Enter Your Name : ";
    cin >> fulname;
    cout << "Enter Your Username : ";
    cin >> user;
    cout << "Enter Your Password : ";
    cin >> pwd;
    cout << "Creating your Account";
    for(int i=0;i<5;i++){
        cout << ".";
        Sleep(1000);
    }
    int qstate = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;
    string name = user;
    string password = pwd;
    string selectQuery = "INSERT INTO Users values ('";
    selectQuery = selectQuery + name + "','" + password +"')";
    char* c = const_cast<char*>(selectQuery.c_str());
    qstate = mysql_query(conn,c);
    if(qstate == 0)
    cout << "Account Created Successfully !!!" << endl;
        else
        cout << "Failed to create !!!" << endl;

    Sleep(1000);
    system("CLS");
    signin(conn);

}



int main()
{

    MYSQL* conn;
    MYSQL_RES *res;
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn,"localhost","root","arun123","crecruit",0,NULL,0) !=0)
    {
        //cout << "Succesfully  Connected to MySQL database crecruit" << endl;
    }

    cout << "****WELCOME TO JOB RECRUITMENT SYSTEM****" << endl;
    int i,n;
    string username,password;
    cout << "1. Create a New User" << endl;
    cout << "2. Already a member ? Sign In" << endl;
    cout << "3. Admin Panel " << endl;
    cout << "4. Exit " << endl;
    cout << "Enter Your Selection : ";
    cin >> n;
    switch(n){
    case 1:
        signup(conn);
        break;
    case 2:
        signin(conn);
        break;
    case 3:
        mainAdmin(conn);
        break;
    case 4:
        cout << endl;
        cout << "Thank You !!! "<< endl;
        break;
    default:
        cout << "\t\nPlease select a valid option\n";
    }
    return 0;
}
