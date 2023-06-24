#include <fstream>
#include <conio.h>
#include <iostream>
#include <string.h>
using namespace std;

class contact{
private:
    char fName[25];
    char lName[25];
    char email[50];
    char address[50];
    char label[25];
    long long phNo;
public:
    void createContact(){
        cout<<"Creating new contact :"<<endl;
        cout<<"Enter first name : ";
        cin>>fName;
        cout<<"Enter last name : ";
        cin>>lName;
        cout<<"Enter email : ";
        cin>>email;
        cout<<"Enter address (write $ at the end): ";
		cin.getline(address, 51,'$');
       // fgets(address, 51, stdin);
        //gets(address); //enable us to take input containing space
        cout<<"Enter label : ";
        cin>>label;
        cout<<"Enter phone number : ";
        cin>>phNo;
    }

    void showContact(){
        cout<<"First name : "<<fName<<endl;
        cout<<"Last name : "<<lName<<endl;
        cout<<"Email : "<<email<<endl;
        cout<<"Address : ";
        puts(address);
        cout<<"Label : "<<label<<endl;
        cout<<"Phone number : "<<phNo<<endl;
    }

    void writeOnFile(){
        char op;
        ofstream file1;
        file1.open("CMS.dat",ios::binary|ios::app); /*to open a file , 
        it takes two input 1.name of file 2.mode in which open a file
        File is in .dat format, so mode will be binary 
        To append new data on existing file, we will use ios::app
         */
        do{
            createContact();
            file1.write(reinterpret_cast<char*>(this),sizeof(*this));
            cout<<"Do yo want to save another contact (y/n) : ";
            cin>>op;
            while(op!='n'&&op!='y'){
                cout<<op<<endl;
                cout<<"Please enter correct character"<<endl;
                cout<<"Do yo want to save another contact (y/n) : ";
                cin>>op;
            }
        }while(op=='y');
        cout<<"Contact(s) created"<<endl;
        file1.close();
    }

    void readFromFile() {
		ifstream file2;
		file2.open("CMS.dat",ios::binary);

		cout<<"\n---------------------------------------------\n";
		cout<<"CONTACT LIST";
		cout<<"\n---------------------------------------------\n";

		while(!file2.eof()) {
			if(file2.read(reinterpret_cast<char*>(this),sizeof(*this)))
			{
				showContact();
				cout<<"\n---------------------------------------------\n";
			}
		}
        cout<<"END OF CONTACT LIST";
		cout<<"\n---------------------------------------------\n";
		file2.close();
	}
		
	void searchByPhoneNo() {
		ifstream file3;
		long long phone;

		cout<<"\n---------------------------------------------\n\n";
		cout<<"Enter phone no. : ";
		cin>>phone;
		file3.open("CMS.dat",ios::binary);

		while(!file3.eof()) {
			if(file3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (phone==phNo) {
					showContact();
					return;
				}
			}
		}
		cout<<"\nNo record founded\n";
		file3.close(); 
	}

    void searchByfName() {
		ifstream file3;
		char name[25];

		cout<<"\n---------------------------------------------\n\n";
		cout<<"Enter first name : ";
		cin>>name;
		file3.open("CMS.dat",ios::binary);

		while(!file3.eof()) {
			if(file3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (strcmp(name,fName)==0) {
					showContact(); 
					return;
				}
			}
		}
		cout<<"\nNo record founded\n";
		file3.close(); 
	}
		
	void deleteByPhoneNo() {
		long long num;
		int flag = 0;
		ofstream file4;
		ifstream file5;

		file5.open("CMS.dat",ios::binary);
		file4.open("temp.dat",ios::binary);

		cout<<"\n---------------------------------------------\n\n";
		cout<<"Enter phone no. to be deleted : ";
		cin>>num;

		while(!file5.eof()) {
			if(file5.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if(phNo!=num) {
					file4.write(reinterpret_cast<char*>(this),sizeof(*this));
				}
				else 
					flag = 1;
			}
		}
		file5.close();
		file4.close();
		remove("CMS.dat");
		rename("temp.dat","CMS.dat");

		flag==1?
		cout<<endl<<endl<<"\tContact Deleted...":
		cout<<endl<<endl<<"\tContact Not Found...";
	}

    void deleteByfName() {
		char name[25];
		int flag = 0;
		ofstream file4;
		ifstream file5;

		file5.open("CMS.dat",ios::binary);
		file4.open("temp.dat",ios::binary);

		cout<<"\n---------------------------------------------\n\n";
		cout<<"Enter name of contact to be deleted : ";
		cin>>name;

		while(!file5.eof()) {
			if(file5.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if(strcmp(name,fName)!=0) {
					file4.write(reinterpret_cast<char*>(this),sizeof(*this));
				}
				else 
					flag = 1;
			}
		}
		file5.close();
		file4.close();
		remove("CMS.dat");
		rename("temp.dat","CMS.dat");

		flag==1?
		cout<<endl<<endl<<"\tContact Deleted...":
		cout<<endl<<endl<<"\tContact Not Found...";
	}
		
	void editByPhoneNo() {
		long long num;
		fstream file6;

		cout<<"\n---------------------------------------------\n\n";
		cout<<"Enter the phone number to be edited : ";
		cin>>num;

		file6.open("CMS.dat",ios::binary|ios::out|ios::in);

		while(!file6.eof()) { //eof:end of file
			if(file6.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if (phNo==num) {
					cout<<"Enter new record\n";
					createContact();
					long long int pos=-1*sizeof(*this);
					file6.seekp(pos,ios::cur);
					file6.write(reinterpret_cast<char*>(this),sizeof(*this));
					cout<<endl<<endl<<"\tContact Successfully Updated...\n";
					return;
				}
			}
		}
		cout<<"\nNo record founded\n";
		file6.close(); 
	}

    void editByfName() {
		char name[25];
		fstream file6;

		cout<<"\n---------------------------------------------\n\n";
		cout<<"Enter the name of contact to be edited : ";
		cin>>name;

		file6.open("CMS.dat",ios::binary|ios::out|ios::in);

		while(!file6.eof()){
			if(file6.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if (strcmp(name,fName)==0) {
					cout<<"Enter new record\n";
					createContact();
					long long int pos=-1*sizeof(*this);
					file6.seekp(pos,ios::cur);
					file6.write(reinterpret_cast<char*>(this),sizeof(*this));
					cout<<endl<<endl<<"\tContact Successfully Updated...\n";
					return;
				}
			}
		}
		cout<<"\nNo record founded\n";
		file6.close(); 
	}
    
};

int main() {
	system("cls");
	system("Color DF"); // "Color XY", X - backgroung color, Y - text color

	cout<<"\n\n\n\n\n\n\n\n\t\t\t    *WELCOME TO CONTACT MANAGEMENT SYSTEM*"<<endl<<endl<<"\t\t\t\t(Press any key to continue)";
	getch();
    
	system("cls");
    system("Color 04");

	while(1) {
		contact c1;
		int choice;

		cout<<"\n---------------------------------------------\n";
		cout<<"\nCONTACT MANAGEMENT SYSTEM"<<endl;
        cout<<"\n\nMAIN MENU\n";
		cout<<"\n---------------------------------------------"<<endl;
        cout<<"[1] Add a new Contact"<<endl;
        cout<<"[2] List all Contacts"<<endl;
        cout<<"[3] Search for contact"<<endl;
        cout<<"[4] Delete a Contact"<<endl;
        cout<<"[5] Edit a Contact"<<endl;
        cout<<"[6] Exit"<<endl;
		cout<<"\n---------------------------------------------"<<endl;
        cout<<"Please enter your choice: ";
        cin>>choice;

        switch(choice) {
        	case 1:
        		c1.writeOnFile();
        		break;

        	case 2:
        		c1.readFromFile();
        		break;

			case 3:
                int op1;
				cout<<"\n---------------------------------------------\n";
				cout<<"Search contact";
                cout<<"\n---------------------------------------------"<<endl;
                cout<<"1. Search by Phone number of Contact"<<endl;
                cout<<"2. Search by Name of Contact"<<endl;
                cout<<"Please choose : "<<endl;
                cin>>op1;
                if(op1==1) c1.searchByPhoneNo();
                else if(op1==2) c1.searchByfName();
                else{
                    cout<<endl<<endl<<"\tInvalid....";
                }
        		break;

        	case 4:
        		int op2;
				cout<<"\n---------------------------------------------\n";
				cout<<"Delete contact";
                cout<<"\n---------------------------------------------"<<endl;
                cout<<endl<<"1. Delete by Phone number of Contact"<<endl;
                cout<<"2. Delete by Name of Contact"<<endl;
                cout<<"Please choose : "<<endl;
                cin>>op2;
                if(op2==1) c1.deleteByPhoneNo();
                else if(op2==2) c1.deleteByfName();
                else{
                    cout<<endl<<endl<<"\tInvalid....";
                }
        		break;

        	case 5:
        		int op3;
				cout<<"\n---------------------------------------------\n";
				cout<<"Edit contact";
                cout<<"\n---------------------------------------------"<<endl;
                cout<<endl<<"1. Edit by Phone number of Contact"<<endl;
                cout<<"2. Edit by Name of Contact"<<endl;
                cout<<"Please choose : "<<endl;
                cin>>op3;
                if(op3==1) c1.editByPhoneNo();
                else if(op3==2) c1.editByfName();
                else{
                    cout<<endl<<endl<<"\tInvalid....";
                }
        		break;

        	case 6:
				cout<<"\n---------------------------------------------\n";
        		cout<<"\n\n\n\t\t\tThank you for using CMS.";
                cout<<endl<<endl<<"\tProgram Ended Successfully...\n";
				cout<<"\n---------------------------------------------\n";
        		exit(0);
        		break;

        	default:
				cout<<endl<<"Please enter a correct choice"<<endl<<endl;	
		}
	}

	return 0;
}