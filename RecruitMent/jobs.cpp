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
void jobs(int n);




void add_job(MYSQL* conn,int n){

        stringstream ss1;
        stringstream ss2;
        stringstream ss3;

        int id,vac,allot;
        string jobcode,role;
        cout << "Enter Job Code : " ;
        cin >> jobcode;
        cout << "Enter the Role : " ;
        cin >> role;

        cout << "Enter the Vacancy : " ;
        cin >> vac;

        cout << "Enter the Allotment : " ;
        cin >> allot;

        int qstate = 0;
        MYSQL_RES *res; /* holds the result set */
        MYSQL_ROW row;

        ss1 << n;
        string cID = ss1.str();
        ss2 << vac;
        string Vacc = ss2.str();
        ss3 << allot;
        string Allotment = ss3.str();


        string selectQuery = "INSERT INTO jobs values ('";
        selectQuery = selectQuery + cID + "','" + jobcode +"','" + role +"','" + Vacc +"','" + Allotment +"')";
        char* c = const_cast<char*>(selectQuery.c_str());
        qstate = mysql_query(conn,c);
         if(qstate == 0)
            cout << "Job Added Successfully !!!" << endl;
         else
            cout << "Failed to add !!!" << endl;
        return;
}

void del_job(MYSQL* conn,int n){
    string jobcode;
    cout << "Enter the Job Code to  delete that Job :";
    cin >> jobcode;
    int qstate = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;

    string name = jobcode;

    string selectQuery = "DELETE FROM jobs WHERE job_code='";
    selectQuery = selectQuery + name + "'";
    char* c = const_cast<char*>(selectQuery.c_str());
    qstate = mysql_query(conn,c);
    if(qstate == 0)
        cout << "Deleted Successfully !!!" << endl;
    else
        cout << "Failed to delete !!!" << endl;



    cout << endl;
}


void display(MYSQL* conn,int n){
    stringstream ss;
    ss << n;
    string number = ss.str();
    int qstate = 0;
    MYSQL_RES *res; /* holds the result set */
    MYSQL_ROW row;
    string selectQuery = "SELECT * FROM jobs WHERE company_ID=";
    selectQuery = selectQuery + number;
    char* c = const_cast<char*>(selectQuery.c_str());
    qstate = mysql_query(conn,c);
    res = mysql_store_result(conn);
    int totalrows = mysql_num_rows(res);
    int numfields = mysql_num_fields(res);
    MYSQL_FIELD *mfield;

    cout << "Company ID\tJob Code\tRole\t\tVacancy\t\tAllotment" << endl;
    while((row = mysql_fetch_row(res)))
    {
        for(int i = 0; i < numfields; i+=5)
        {
            cout  << row[i] << "\t\t" << row[i+1] << "\t\t" << row[i+2] << "\t\t" << row[i+3] << "\t\t" << row[i+4] << endl;
        }
    }

}

//
//
void modifyRecord(MYSQL* conn,int n)
{
        stringstream ss;
        int vac;
        string jobcode;
        cout << "Enter the Job Code whose Vacancy to be changed :";
        cin >> jobcode;

        cout << "Enter the Vacancy :";
        cin >> vac;

        ss<<vac;

        string Vacc = ss.str();

        int qstate = 0;
        MYSQL_RES *res; /* holds the result set */
        MYSQL_ROW row;

        string selectQuery = "UPDATE jobs set vacancy = '";
        selectQuery = selectQuery + Vacc + "' where job_code ='" + jobcode + "'";

        char* c = const_cast<char*>(selectQuery.c_str());
        qstate = mysql_query(conn,c);
         if(qstate == 0)
            cout << "Updated Successfully !!!" << endl;
         else
            cout << "Failed to update !!!" << endl;


    cout << endl;

}


void jobs(int n){

    MYSQL* conn;
    MYSQL_RES *res;
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn,"localhost","root","arun123","crecruit",0,NULL,0) !=0)
    {
        //cout << "Succesfully  Connected to MySQL database crecruit" << endl;
    }
    int choice;
    do{
        cout << "***** JOBS PANEL *****";
        cout << "\n1. Add a Job Record";
        cout << "\n2. List Jobs Records";
        cout << "\n3. Modify a Job Record";
        cout << "\n4. Delete a Job Record";
        cout << "\n5. Exit Job Panel"<<endl;
        cout << "Select Your Choice (1 to 5) : ";

        cin>>choice;

            switch (choice)
            {
            case 1:
                cout<<"\n";
                add_job(conn,n);
                break;
            case 2:
                cout<<"\n";
                display(conn,n);
                break;
            case 3:
                cout<<"\n";
                modifyRecord(conn,n);
                break;
            case 4:
                cout<<"\n";
                del_job(conn,n);
                break;
            case 5:
                cout  << endl;
                cout << "SHUTTING DOWN ADMIN - JOBS PANNEL ";
                for(int k=0;k<5;k++){
                    cout <<".";
                    Sleep(500);
                }
                system("CLS");
                break;
            default:
                cout<<"Invalid!!!"<<endl;
            }
        }while(choice!=5);
        admin();

    if(res != NULL)
        mysql_free_result(res);
    mysql_close(conn);
}


