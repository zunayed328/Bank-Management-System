#include <iostream>
#include <iomanip>
#include "sqlite3.h"
using namespace std;

void connection();
void insertR();
void retrieve();
void deletR();
void update();
sqlite3 *db;
sqlite3_stmt *stmt;
int result;
int acountnumber;
string query, name, email, password;

int main()
{
    connection();
    int menu;
    cout<<"\n------------------------------------------\n";

    cout<<"Press[1] To Insert New Data\n";
    cout<<"Press[2] To Read All Data \n";
    cout<<"Press[3] TO Delet a Record\n";
     cout<<"Press[4] TO Update a Record\n";
    cout<<"Press[5] Exist\n";
    cout<<"\n------------------------------------------\n";
    cin>>menu;
    getchar();
    if(menu==1){
        insertR();
        main();
    }
    else if(menu==2){

         retrieve();
             main();
    }
        else if(menu==3){

        deletR();
        main();
    }
     else if(menu==4){

        update();
        main();
    }
    else if(menu==5){

         return 0;
    }
    else{
        cout<<"Invalid Command \n";
    }
    if (result == SQLITE_OK)
    {

    }
    sqlite3_close(db);
    return 0;
}

void connection()
{
    if (sqlite3_open("Bank Managment System.db", &db) == SQLITE_OK)
    {
        result = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS user(name varchar(50), acountnumber INT, email varchar(80),password INT);", -1, &stmt, NULL);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result != SQLITE_OK)
        {
            cout << "Error: " << sqlite3_errmsg(db) << "\n";
        }
        else
        {
            cout << "Table created successfully.\n";
        }
    }
    else
    {
        cout << "Error opening database.\n";
    }
}

void insertR()
{
    cout << "Type your name:\n";
    getline(cin, name);

    cout << "Type your Account Number:\n";
    cin >> acountnumber;
    cin.ignore();
    cout << "Type your Email:\n";
    getline(cin, email);
    cout << "Type your Password:\n";
    getline(cin, password);

    query = "INSERT INTO user(name, acountnumber, email,password) VALUES (?, ?, ?,?);";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name.c_str(), name.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, acountnumber);
    sqlite3_bind_text(stmt, 3, email.c_str(), email.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, password.c_str(), password.length(), SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_OK)
    {
        cout << "ERROR: " << sqlite3_errmsg(db) << "\n";
    }
    else
    {
        cout << "Data inserted successfully.\n";
    }
}

void retrieve()
{
    query = "SELECT rowid ,* FROM user ";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        cout << "ERROR: " << sqlite3_errmsg(db) << "\n";
    }
    else
    {
        cout<<"-----------------------------------------------------------------------------------------------\n";
        cout<<left<<"\t"<<setw(10)<<"Id"<<setw(20)<<"Name"<<setw(15)<<"Acountnumber"<<setw(25)<<" Email"<<setw(15)<<"Password \n";
        cout<<"-----------------------------------------------------------------------------------------------\n";
        while ((result = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            cout <<left<<"\t"<<setw(10)<<sqlite3_column_text(stmt, 0)<<setw(20)
                 << sqlite3_column_text(stmt, 1) <<setw(15)
                 << sqlite3_column_text(stmt, 2) <<setw(25)
                 << sqlite3_column_text(stmt, 3) <<setw(15)
                 << sqlite3_column_text(stmt, 4) <<"  \n";
        }
        cout<<"-----------------------------------------------------------------------------------------------\n";
    }
}
void deletR(){
    int id;
    cout<< "\nWhich Record You Want To Delet? Type [id] Number \n";
    cin>> id;
    getchar();
    query ="DELETE FROM user WHERE rowid=?";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt,1,id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if(result==SQLITE_OK){
        cout<<"\nData Deleted Sucessfully!\n";
    }
    else{
        cout<<"\nFaild:"<<sqlite3_errmsg(db)<<"\n";

    }

}
void update(){
int id;
cout<< "\nWhich Record You Want To Update? Type [id] Number \n";
cin>>id;
getchar();
cout<<"Type New Name:\n ";
getline(cin,name);
cout<<"Type New Acount Number:\n ";
    cin >> acountnumber;
    cin.ignore();
    cout << "Type New Email:\n";
    getline(cin, email);
    cout << "Type New Password:\n";
    cin>> password;
     query ="UPDATE  user SET name=?,acountnumber=?,email=?,password=?WHERE rowid=?;";
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt,1,name.c_str(),name.length(),SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,2,acountnumber);
    sqlite3_bind_text(stmt,3,email.c_str(),email.length(),SQLITE_TRANSIENT);
   sqlite3_bind_text(stmt, 4, password.c_str(), password.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,5,id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if(result!=SQLITE_OK){
             cout<<"\nFaild:"<<sqlite3_errmsg(db)<<"\n";

    }
    else{

cout<<"\nData Update Sucessfully!\n";
    }


}
