#include<iostream>
#include<windows.h>
#include<mysql.h>
#include <string>
#include "employee.h"
#include "admin.h"
#include<vector>
#include<sstream>

int main();
int GetCompany_Name (MYSQL* conn,string cid);
int GetCompany_ID(MYSQL* conn,int cid);
int GetRole_Name (MYSQL* conn,string cid);

bool allocationCheck(MYSQL* conn,string comID,string JobCode,string username){
    int qstate = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;

    string selectQuery = "SELECT * FROM alloted;";

    char* c2 = const_cast<char*>(selectQuery.c_str());
    qstate = mysql_query(conn,c2);

    res = mysql_store_result(conn);

    int totalrows = mysql_num_rows(res);
    int numfields = mysql_num_fields(res);
    MYSQL_FIELD *mfield;

    int count = 0;

    while((row = mysql_fetch_row(res)))
    {
        for(int i = 0; i < numfields; i+=3)
        {
            if(comID == row[i] && JobCode == row[i+1] && username == row[i+2]){
                return false;
            }
        }
    }

    return true;


}

bool checkAvailable(MYSQL* conn,string ID){

    stringstream ss;

    int qstate = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;
    string selectQuery = "SELECT vacancy FROM jobs WHERE company_ID=";
    selectQuery = selectQuery + ID;
    char* c = const_cast<char*>(selectQuery.c_str());
    qstate = mysql_query(conn,c);

    res = mysql_store_result(conn);
    int totalrows = mysql_num_rows(res);
    int numfields = mysql_num_fields(res);
    MYSQL_FIELD *mfield;
    string temp;
    while((row = mysql_fetch_row(res)))
    {
        for(int i = 0; i < numfields; i+=5)
        {
            temp = row[i];
        }
    }

    stringstream guess(temp);
    int x=0;
    guess >> x;

    if(x == 0)
        return false;
    else
        return true;


}

void listAll(MYSQL* conn){
    stringstream ss;

    int qstate = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;

    //string selectQuery = "SELECT * FROM jobs";

    string selectQuery = "SELECT * FROM companylist";

    char* c = const_cast<char*>(selectQuery.c_str());
    qstate = mysql_query(conn,c);
    res = mysql_store_result(conn);

    int totalrows = mysql_num_rows(res);
    int numfields = mysql_num_fields(res);
    MYSQL_FIELD *mfield;

    cout << "Company ID\t\tCompany Name\t\t" << endl;
    int nums = 0;
    while((row = mysql_fetch_row(res)))
    {
        for(int i = 0; i < numfields; i+=2)
        {
            cout  << row[i] << "\t\t\t" << row[i+1]<< endl;
        }
    }

    cout << endl;

    cout << "Use Search Option to see avaiability of the Jobs" << endl;
}

void searchByCompany(MYSQL* conn)
{

    stringstream ss;

    int qstate = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;
    string com;
    cout << "Enter the Company Name : ";
    cin >> com;
    int GOTValue = GetCompany_Name(conn,com);

    ss<<GOTValue;

    string yes = ss.str();

    string selectQuery = "SELECT role,vacancy FROM jobs WHERE company_ID=";
    selectQuery = selectQuery+yes;

    char* c = const_cast<char*>(selectQuery.c_str());
    qstate = mysql_query(conn,c);
    res = mysql_store_result(conn);

    int totalrows = mysql_num_rows(res);
    int numfields = mysql_num_fields(res);
    MYSQL_FIELD *mfield;

    cout << "Results for Company :" + com << endl;
    cout << "S.No\t\tDesignations\t\tVacancy"<< endl;
    int nums = 0;
    while((row = mysql_fetch_row(res)))
    {
        for(int i = 0; i < numfields; i+=2)
        {
            cout  << i+1 << "\t\t" << row[i]<< "\t\t" << row[i+1]<<endl;
        }
    }

}

void apply(MYSQL* conn,string username){

        stringstream ss;

        int qstate = 0;

        MYSQL_RES *res; /* holds the result set */
        MYSQL_ROW row;

        MYSQL_RES *res1; /* holds the result set */
        MYSQL_ROW row1;

        MYSQL_RES *res2; /* holds the result set */
        MYSQL_ROW row2;

        string com;
        cout << "Enter the Company Name to apply :";
        cin >> com;

        int GOTValue = GetCompany_Name(conn,com);

        ss<<GOTValue;

        string yes = ss.str();

    //-------------------------------------------------------------------------------------------

        string selectQuery = "SELECT role FROM jobs WHERE company_ID=";
        selectQuery = selectQuery+yes;
        char* c = const_cast<char*>(selectQuery.c_str());
        qstate = mysql_query(conn,c);
        res = mysql_store_result(conn);

        int totalrows = mysql_num_rows(res);
        int numfields = mysql_num_fields(res);
        MYSQL_FIELD *mfield;
        cout << "Available Designations :" << endl;

        while((row = mysql_fetch_row(res)))
        {
            for(int i = 0; i < numfields; i++)
            {
                cout  << row[i]<<endl;
            }
        }

    //-------------------------------------------------------------------------------------------


        string designation;
        cout << "Enter the Designation to apply :";
        cin>>designation;

        int GOTValue1 = GetRole_Name(conn,designation);

        stringstream ss1;
        ss1<<GOTValue1;
        string yes1 = ss.str(); // company ID

        string selectQuery1 = "SELECT job_code FROM jobs WHERE company_ID=";
        selectQuery1 = selectQuery1+yes1;

        char* c1 = const_cast<char*>(selectQuery1.c_str());
        qstate = mysql_query(conn,c1);
        res1 = mysql_store_result(conn);

        int totalrows1 = mysql_num_rows(res1);
        int numfields1 = mysql_num_fields(res1);

        string JobCode;
        while((row1 = mysql_fetch_row(res1)))
        {
            for(int i = 0; i < numfields; i++)
            {
                JobCode = row1[i]; // Job Code
            }
        }
    //-------------------------------------------------------------------------------------------

    if (checkAvailable(conn,yes1))
        {
            if(allocationCheck(conn,yes1,JobCode,username))
            {
                string selectQuery2 = "INSERT INTO alloted values ('";
                selectQuery2 = selectQuery2+ yes1 + "','" + JobCode + "','" + username +"')";

                char* c2 = const_cast<char*>(selectQuery2.c_str());
                qstate = mysql_query(conn,c2);

                if(qstate == 0){
                    cout << "Job Allocated Successfully" << endl;
                }
                else{
                    cout << "Already Appiled For this Company" << endl;
                }
            }
            else{
                cout << "Sorry User Already Exists !!!";
            }
    }
    else{
        cout << "No Vacancy...Better Luck Next Time :) " << endl;
    }



}


int GetRole_Name (MYSQL* conn,string cid){
    stringstream ss;
    string temp;
    int query_state = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;
    string selectQuery;


    selectQuery = "SELECT company_ID FROM jobs WHERE role= '" + cid +"'" ;
    char* c = const_cast<char*>(selectQuery.c_str());
    query_state=mysql_query(conn,c);
   if(query_state!=0)
   {
      cout<<mysql_error(conn)<<endl<<endl;
   }
    res=mysql_store_result(conn);
    if (mysql_num_rows(res)>0) {
        while ( ( row = mysql_fetch_row(res)) != NULL )
        {
           temp = row[0];
        }

    }

    stringstream guess(temp);
    int x=0;
    guess >> x;
    return x;

    if(res != NULL)
        mysql_free_result(res);
    mysql_close(conn);

}

int GetCompany_Name (MYSQL* conn,string cid){
    stringstream ss;
    string temp;
    int query_state = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;
    string selectQuery;

    ss<<cid;

    string ID = ss.str();
    selectQuery = "SELECT company_ID FROM companylist WHERE company_name= '" + cid +"'" ;
    char* c = const_cast<char*>(selectQuery.c_str());
    query_state=mysql_query(conn,c);
   if(query_state!=0)
   {
      cout<<mysql_error(conn)<<endl<<endl;
   }
    res=mysql_store_result(conn);
    if (mysql_num_rows(res)>0) {
        while ( ( row = mysql_fetch_row(res)) != NULL )
        {
           temp = row[0];
        }

    }

    stringstream guess(temp);
    int x=0;
    guess >> x;
    return x;

    if(res != NULL)
        mysql_free_result(res);
    mysql_close(conn);

}


void applicant(string username){

    MYSQL* conn;
    MYSQL_RES *res;
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn,"localhost","root","arun123","crecruit",0,NULL,0) !=0)
    {
        //cout << "Succesfully  Connected to MySQL database crecruit" << endl;
    }
    int choice;
    do{
        cout << "1. List All Companies "<< endl;
        cout << "2. Search By Company Name " << endl;
        cout << "3. Apply for a Company " << endl;
        cout << "4. Logout " << endl;
        string supername = username;

        {
            cout << "Enter your selection : ";
            cin >> choice;
            switch(choice){
                case 1:
                    listAll(conn);
                    break;
                case 2:
                    searchByCompany(conn);
                    break;
                case 3:
                    apply(conn,supername);
                    break;
                case 4:
                    cout << "****Thank you for using our service****" << endl;
                    cout << "Loggin off";
                    for(int i=0;i<5;i++){
                        cout << ".";
                        Sleep(1000);
                    }
                    break;
                }
        }
    }while(choice!=4);

    main();

    if(res != NULL)
        mysql_free_result(res);
    mysql_close(conn);
}


