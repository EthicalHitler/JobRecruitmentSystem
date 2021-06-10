#include<iostream>
#include<windows.h>
#include <mysql.h>
#include<vector>
#include<string.h>
#include<sstream>

#include "employee.h"
#include "admin.h"
#include "jobs.h"


int main();
void admin();

void get_Job(){
    int n;
    cout << "Enter the Company ID : ";
    cin >> n;
    jobs(n);

}


void add_Company(MYSQL* conn){
        stringstream ss;

        int id,vac;
        string companyName,Role;
        cout << "Enter ID of the company : " ;
        cin >> id;
        cout << "Enter the company Name : " ;
        cin >> companyName;
        int qstate = 0;
        MYSQL_RES *res; /* holds the result set */
        MYSQL_ROW row;

        ss << id;
        string cID = ss.str();
        string cName = companyName;


        string selectQuery = "INSERT INTO companylist values ('";
        selectQuery = selectQuery + cID + "','" + cName +"')";
        char* c = const_cast<char*>(selectQuery.c_str());
        qstate = mysql_query(conn,c);
         if(qstate == 0)
            cout << "Company Added Successfully !!!" << endl;
         else
            cout << "Failed to add !!!" << endl;

        Sleep(3000);
        system("CLS");

}

void del_Company(MYSQL* conn){
    string user,pwd;
    cout << "Enter the Company Name to be deleted :";
    cin >> user;
    int qstate = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;

    string name = user;

    string selectQuery = "DELETE FROM companylist WHERE company_name='";
    selectQuery = selectQuery + name + "'";
    char* c = const_cast<char*>(selectQuery.c_str());
    qstate = mysql_query(conn,c);
    if(qstate == 0)
        cout << "Deleted Successfully !!!" << endl;
    else
        cout << "Failed to delete !!!" << endl;


    cout << endl;
    Sleep(3000);
    system("CLS");
}


void display(MYSQL* conn){
    int qstate = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;
    string selectQuery = "SELECT * FROM companylist;";
    char* c = const_cast<char*>(selectQuery.c_str());
    qstate = mysql_query(conn,c);
    res = mysql_store_result(conn);
    int totalrows = mysql_num_rows(res);
    int numfields = mysql_num_fields(res);
    MYSQL_FIELD *mfield;

    cout << "Company ID\tCompany Name\t" << endl;
    while((row = mysql_fetch_row(res)))
    {
        for(int i = 0; i < numfields; i+=2)
        {
            cout  << row[i] << "\t\t" << row[i+1] << endl;
        }
    }

}

void disp_allocated(MYSQL* conn){

    int qstate = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;
    string selectQuery = "SELECT * FROM alloted;";
    char* c = const_cast<char*>(selectQuery.c_str());
    qstate = mysql_query(conn,c);
    res = mysql_store_result(conn);
    int totalrows = mysql_num_rows(res);
    int numfields = mysql_num_fields(res);
    MYSQL_FIELD *mfield;

    cout << "Company ID\tJob Code\tUsername\t" << endl;
    while((row = mysql_fetch_row(res)))
    {
        for(int i = 0; i < numfields; i+=3)
        {
            cout  << row[i] << "\t\t" << row[i+1] << "\t\t" << row[i+2] << endl;
        }
    }

}

//
//
void modifyRecord(MYSQL* conn)
{
        stringstream ss;
        int id;
        string user,role;
        cout << "Enter the Company name whose data to be changed :";
        cin >> user;

        cout << "Enter the Company ID :";
        cin >> id;

        ss<<id;

        string ID = ss.str();

        int qstate = 0;
        MYSQL_RES *res; /* holds the result set */
        MYSQL_ROW row;

        string selectQuery = "UPDATE companylist set company_name = '";
        selectQuery = selectQuery + user + "' where company_ID ='" + ID + "'";

        char* c = const_cast<char*>(selectQuery.c_str());
        qstate = mysql_query(conn,c);
         if(qstate == 0)
            cout << "Updated Successfully !!!" << endl;
         else
            cout << "Failed to update !!!" << endl;



    cout << endl;
    Sleep(3000);
    system("CLS");

}


void admin(){

    MYSQL* conn;
    MYSQL_RES *res;
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn,"localhost","root","arun123","crecruit",0,NULL,0) !=0)
    {
        //cout << "Succesfully  Connected to MySQL database crecruit" << endl;
    }
    char Y;
    int choice;
    do
    {
        cout << "***** ADMIN PANEL *****";
        cout << "\n1. Add Company Records";
        cout << "\n2. List Company Records";
        cout << "\n3. Modify Company Records";
        cout << "\n4. Delete Company Records";
        cout << "\n5. Jobs Section";
        cout << "\n6. Display Allocated Table";
        cout << "\n7. Exit Admin Panel"<<endl;
        cout << "Select Your Choice (1 to 7) : ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"\n";
            add_Company(conn);
            break;
        case 2:
            cout<<"\n";
            display(conn);
            break;
        case 3:
            cout<<"\n";
            modifyRecord(conn);
            break;
        case 4:
            cout<<"\n";
            del_Company(conn);
            break;
        case 5:
            cout<<"\n";
            get_Job();
            break;
        case 6:
            cout<<"\n";
            disp_allocated(conn);
            break;
        default:
            cout  << endl;
            cout << "SHUTTING DOWN ADMIN PANNEL ";
            for(int k=0;k<5;k++){
                cout <<".";
                Sleep(500);
            }
            system("CLS");
            break;
            break;
        }
    }while(choice!=7);

    main();

    if(res != NULL)
        mysql_free_result(res);
    mysql_close(conn);

}


