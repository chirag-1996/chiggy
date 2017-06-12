//C++ Project
#include<iostream>
#include<fstream>
#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
using namespace std;

COORD coord={0,0}; // this is global variable
                                    //center of axis is set to the top left cornor of the screen
 void gotoxy(int x,int y)
 {
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }

class Restaurant
{
    char name[20];
    float rating;
    char code[10];
    char loc[20];
public:
    void add_res();
    void modify_res();
    void display_res();
};
Restaurant r;
fstream res;

class FoodItem
{
    char name[20];
    float price;
    char type[20];
public:
    void add_item();
    void modify_item();
    void display_item();
    char* getname()
    {
        return name;
    }
    float getprice()
    {
        return price;
    }
};
FoodItem fd;
fstream fi;

class Order
{
    char name[20];
    int qty;
    float amt;

public:
    static float bill_amt;
    void enter(char*);
    void display();
};
Order o;
fstream ord;

float Order::bill_amt=0;

void Restaurant::add_res()
{
    char ch='y';
    char ans;
    res.open("RESTAURANT",ios::binary|ios::app|ios::out);
    while(tolower(ch)=='y')
    {
        system("cls");
        cout<<"\nEnter the Restaurant's name:";
        cin.ignore();
        cin.getline(name,20);
        cout<<"\nEnter the rating of the Restaurant:";
        cin>>rating;
        cout<<"\nEnter the Restaurant code:";
        cin.ignore();
        cin.getline(code,10);
        cout<<"\nEnter the loaction of the Restaurant:";
        cin.getline(loc,20);
        res.write((char*)&r, sizeof(r));
        fi.open(code,ios::out|ios::binary);
        cout<<"\nEnter the menu:-";
        do
        {
            fd.add_item();
            fi.write((char*)&fd,sizeof(fd));
            cout<<"\nWant to add more food items(y/n):";
            cin>>ans;
            cin.ignore();
        }while(tolower(ans)!='n');
        cout<<"\nDo you want to enter more Restaurant(y/n):";
        cin>>ch;
    }
    res.close();
    fi.close();
}

void Restaurant::display_res()
{
    int i = 3;
    system("cls");
    res.open("RESTAURANT",ios::in|ios::binary);
    res.read((char*)&r,sizeof(r));
    gotoxy(1,1);
    cout<<"CODE";
    gotoxy(10,1);
    cout<<"RESTAURANT NAME";
    gotoxy(30,1);
    cout<<"LOCATION";
    gotoxy(45,1);
    cout<<"RATING";
    while(!res.eof())
    {
        gotoxy(1,i);
        cout<<code;
        gotoxy(10,i);
        cout<<name;
        gotoxy(30,i);
        cout<<loc;
        gotoxy(45,i);
        cout<<rating;
        i+=2;
        res.read((char*)&r,sizeof(r));
    }
    res.close();
}
void Restaurant::modify_res()
{
    system("cls");
    Restaurant r1;
    int ch,s;
    char val[20];
    float rat;
    char cd[20];
    cout<<"\nEnter the Restaurant Code:";
    cin.ignore();
    cin.getline(cd,20);
    res.open("RESTAURANT",ios::in|ios::out|ios::binary);
    res.read((char*)&r1,sizeof(r1));
    while(res)
    {
        if(strcmp(r.code,cd) == 0)
        {
            cout<<"\nCODE:"<<r1.code;
            cout<<"\nNAME:"<<r1.name;
            cout<<"\nLOCATION:"<<r1.loc;
            cout<<"\nRATING:"<<r1.rating;
            cout<<"\n\nWhat do you want to edit:-";
            cout<<"\n1.Code";
            cout<<"\n2.Name";
            cout<<"\n3.Location";
            cout<<"\n4.Rating";
            cout<<"\n\nEnter your choice:";
            cin>>ch;
            cin.ignore();
            switch(ch)
            {
            case 1:
                cout<<"\nEnter the new code:";
                cin.getline(r1.code,20);
                break;
            case 2:
                cout<<"\nEnter the new Name:";
                cin.getline(r1.name,20);
                break;
            case 3:
                cout<<"\nEnter the new Location:";
                cin.getline(r1.loc,20);
                break;
            case 4:
                cout<<"\nEnter the new rating:";
                cin>>r1.rating;
                break;
            default:
                cout<<"Incorrect choice:";

            }
            break;
        }
        s = res.tellg();
        res.read((char*)&r1,sizeof(r1));
    }
    res.seekp(s-1,ios::beg);
    res.write((char*)&r1,sizeof(r1));
    res.close();
}
void FoodItem::add_item()
{
        cout<<"\nEnter the type of food:";
        cin.getline(type,20);
        cout<<"\nEnter the name of food item:";
        cin.getline(name,20);
        cout<<"\nEnter the price of the food item:";
        cin>>price;
}
void FoodItem::display_item()
{
    if (strcmp(type,"Drinks")==0)
    {
            cout<<"\nDRINKS";
            cout<<"\n"<<name<<"\t"<<price;
    }
    else if(strcmp(type,"Starter")==0)
    {
            cout<<"\nSTARTER";
            cout<<"\n"<<name<<"\t"<<price;
    }
    else if (strcmp(type,"Main Course")==0)
    {
            cout<<"\nMAIN COURSE";
            cout<<"\n"<<name<<"\t"<<price;
    }
    else if(strcmp(type,"Desserts")==0)
    {
            cout<<"\nDESSERTS";
            cout<<name<<"\t"<<price;
    }
}
void Order::enter(char *cd)
{
    fi.open(cd,ios::in|ios::binary);
    cout<<"\n\n\nSelect your food item:";
    cin.getline(name,20);
    cout<<"\nQuantity:";
    cin>>qty;
    fi.read((char*)&fd,sizeof(fd));
    while(fi)
    {
        if((strcmp(fd.getname(),name))== 0)
        {
            amt=qty*fd.getprice();
            break;
        }
        fi.read((char*)&fd,sizeof(fd));
    }
    fi.close();
    bill_amt+=amt;
}
void Order::display()
{
    cout<<"BILL!!";
    cout<<"\nITEM"<<"\t"<<"QTY"<<"\t"<<"AMT";
    ord.open("Bill",ios::in|ios::binary);
    ord.read((char*)&o,sizeof(o));
    while(!ord.eof())
    {
        cout<<"\n"<<name<<"\t"<<qty<<"\t"<<amt;
        ord.read((char*)&o,sizeof(o));
    }
    ord.close();
    cout<<"\nTotal bill amount:-"<<bill_amt;
}
void modify()
{
    system("cls");
    int ch;
    do
    {

        cout<<"\nWant to Modify";
        cout<<"\n1.Restaurant Details";
        cout<<"\n2.Menu";
        cout<<"\n3.Previous Page";
        cout<<"\nEnter your choice:";
        cin>>ch;
        switch(ch)
        {
            case 1:
                r.modify_res();
                break;
            /*case 2:
                fd.modify_item();
                break;*/
            case 3:
                break;
            default:
                cout<<"\nIncorrect choice!";
        }
    }while(ch!=3);
}

void admin()
{

    int ch;
    do
    {
        system("cls");
        cout<<"\n1.Add a Restaurant";
        cout<<"\n2.Modify Restaurant details";
        cout<<"\n3.Display details of a Restaurant";
        cout<<"\n4.Home Page";
        cout<<"\nEnter your choice:";
        cin>>ch;
        switch(ch)
        {
        case 1:
            r.add_res();
            break;
       case 2:
            modify();
            break;
        case 3:
            r.display_res();
            break;
        case 4:
               break;

        default:
            cout<<"Incorrect choice!!!";
            cout<<"Enter again";
        }
    }while(ch!=4);
}

void order()
{
    system("cls");
    char cd[10];
    char ch;
    char food[20];
    r.display_res();
    cout<<"\n\n\nSelect your Restaurant:";
    cin.ignore();
    cin.getline(cd,10);
    system("cls");
    fi.open(cd,ios::in|ios::binary);
    fi.read((char*)&fd,sizeof(fd));
    while(!fi.eof())
    {
        fd.display_item();
        fi.read((char*)&fd,sizeof(fd));
    }
    fi.close();
    ord.open("Bill",ios::out|ios::binary);
    do
    {

        o.enter(cd);
        ord.write((char*)&o,sizeof(o));
        cout<<"Want to Order More(y/n)";
        cin>>ch;
        cin.ignore();
    }while(tolower(ch)!='n');
    ord.close();
    o.display();
    o.bill_amt = o.bill_amt*0;
    getch();

}

int main()
{

    int ch;
    do
    {
        system("cls");
        cout<<"\nWELCOME TO FOOD ORDERING APPLICATION";
        cout<<"\n1.Admin";
        cout<<"\n2.Order Food";
        cout<<"\n3.Exit";
        cout<<"\nEnter your option:-";
        cin>>ch;
        switch(ch)
        {

        case 1:
            admin();
            break;
        case 2:
            order();
            break;
        case 3:
            break;
        default:
            cout<<"\nIncorrect choice!!!";
            cout<<"\nEnter again:";

        }
    }while(ch!=3);
    return 0;

}


