#include <iostream>
#include<windows.h>
#include<mysql.h>
#include<sstream>
using namespace std;
class database{
    MYSQL* conn;

public:
    int connection(MYSQL* conn);
    int insert(string name,int age, int phone, MYSQL* conn);

};
int database::connection(MYSQL* conn){
    if(conn){
        cout<<"database connected"<<endl;
        return 1;
    }else
        cout<<"not connected";
        return 0;
}
int database::insert(string name,int age, int phone, MYSQL* conn){

    int qstate=0;
    stringstream ss;
    ss<<"INSERT INTO userdata(name,age,phone) VALUES('"<<name<<"','"<<age<<"','"<<phone<<"')";
    string query= ss.str();
    const char* q=query.c_str();
    qstate=mysql_query(conn,q);
    if(qstate){
         return 0;//if inserted
    }
    else return 1;//if not inserted

}
int main()
{

    //---------------------Database Authentication--------------------------
     database obj;
     MYSQL* conn;
     conn = mysql_init(0);
     string ip_s= "127.0.0.1";              const char* ip= ip_s.c_str();
     string user_s="root";                  const char* user= user_s.c_str();
     string password_s="";                  const char* password= password_s.c_str();
     string database_name_s="mysqlwithc++"; const char* database_name= database_name_s.c_str();
     //-------------calling connection function----------------
     conn = mysql_real_connect(conn,ip,user,password,database_name,0,NULL,0);
     obj.connection(conn);
   //-----------------------------------------
     string name;
     int age=100;
     int phone=1234567890;
     //-------------taking input from user----------------------
     int n=0;
     cout<<"No of record you want insert "; cin>>n;
     for(int i=0;i<n;i++){
        cout<<"Name-->";
        cin>>name;
        cout<<"Age-->";
        cin>>age;
        cout<<"Phone-->";
        cin>>phone;

    //---------------inserting record to database----------------
     int record=obj.insert(name,age,phone,conn);
     if(record){
        cout<<"Record Inserted"<<endl;
     }else cout<<"Failed"<<endl;
     }
    //---------------- selecting records record--------------------------------
    MYSQL_ROW row;
    MYSQL_RES* res;
    int qstate =mysql_query(conn,"Select id,name,age From userdata");
    //----------------showing records-------------------------------------
    cout<<"------------------TABLE RECORD---------------------"<<endl;
    if (!qstate){
        res=mysql_store_result(conn);
        cout<<endl;
        while(row= mysql_fetch_row(res)){
            cout<<row[0]<<" "<<row[1]<<" "<<row[2]<<endl;
        }
    }
    cout<<"---------------------------------------------------";
    //------------------end--------------------------------------------------
    return 0;
}
