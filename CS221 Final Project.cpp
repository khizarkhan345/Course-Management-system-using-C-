#include<iostream>
#include<iomanip>
#include<fstream>

using namespace std;

int main();
void admin();
void student();

int showMenu_main();
int showMenu_admin();
int showMenu_student();

void courses_display_menu();

void registeration_display_menu();
void add_display_menu();
void drop_display_menu();

void printShashkaLine(char, int);


class Admin;
class Courses;
class Student;
struct Data;

class Courses
{
	string code;
	string name;
	Courses *next;
	Courses *previous;
	
	public:
		friend class Student;
		Courses();
		Courses(string CODE, string NAME);
		void generate_linked_list();
		void save_file();
		void bubble_sort(int type);
		void show_courses();
		void remove();
		bool exist_already(string Code);
		void insert();
		
};
Courses::Courses()						// constructor for header node
{
	this->next=this;
	this->previous=this;
}
Courses::Courses(string CODE, string NAME)	// constructor for new node while creating linked list
{
	code=CODE;
	name=NAME;
}
void Courses::generate_linked_list()	// function uses ifstream file to read data from file and store in Sorted linked list
{
	string Code;
	string Name;
	
	ifstream courses_file;
	courses_file.open("Courses.txt",ios::in);
	while(courses_file >> Code )
	{
		
		courses_file.ignore();
		getline(courses_file,Name);
		Courses *Node = new  Courses(Code,Name);
		
		Node->next=this->next;
		Node->previous=this;
		
		this->next->previous=Node;
		this->next=Node;
	}
	courses_file.close();
}
void Courses::save_file()				// function uses ofstream file to write data from linked list to file
{
	Courses *P=this;
	ofstream courses_file;
	courses_file.open("Courses.txt",ios::out | ios::trunc);
	
	do
	{
		courses_file << P->code << "\t" << P->name << "\n";
		P=P->next;
	}while(P!=this);
	
	courses_file.close();
}
void Courses::bubble_sort(int type)
{
	
	Courses* temp = this;				//new node for Swapping
	Courses* temp2 = this->next;
	Courses* loop = this;
	Courses* swap = new Courses;
	do
	{
		while(temp2 != this)		//Using Bubble Sort
		{
			if(type==1)
			{
				if(temp->code > temp2->code)
				{
					swap->name=temp2->name;
					swap->code=temp2->code;
					
					temp2->name=temp->name;
					temp2->code=temp->code;
					
					temp->name=swap->name;
					temp->code=swap->code;
				}
			}
			
			if(type==2)
			{
				if(temp->name > temp2->name)
				{
					swap->name=temp2->name;
					swap->code=temp2->code;
					
					temp2->name=temp->name;
					temp2->code=temp->code;
					
					temp->name=swap->name;
					temp->code=swap->code;
				}
			}

			temp=temp->next;
			temp2=temp2->next;
		}
		temp=this;
		temp2=this->next;
		loop=loop->next;
	}while(loop!=this);
	delete swap;
}
void Courses::show_courses()			// displaing courses data by traversing linked list
{
	Courses *P;
	P=this;
	
	bool again=true;
	system("cls");
	courses_display_menu();
	int choice;
	cin>>choice;
	
	
	while(again)
	{
		system("cls");
		courses_display_menu();
		
		
		switch(choice)
		{
			case 0:
					cout<<"Going Back"<<endl<<endl;
					again=false;
					break;
					
			case 1:
					cout<<"Displaying Courses Sorted By Code"<<endl<<endl;
					P->bubble_sort(1);
					break;
					
			case 2:
					cout<<"Displaying Courses Sorted By Name"<<endl<<endl;
					P->bubble_sort(2);
					break;		
			
			default:
					cout<<"Invalid Choice"<<endl;
					break;
		}
		if(!again)
		break;
		if(again && choice == 1 || choice == 2)
		{
			int a=0;
			cout<<setw(5)<<"Sr#"<<setw(8)<<"Code"<<setw(50)<<"Name\n";
			while(P->next!=this)
			{
				P=P->next;
				cout<<setw(5)<<++a<<setw(8)<<P->code<<setw(50)<<P->name<<endl;
			}
			P=this;
		}
		cout<<endl<<endl<<endl<<"Enter Your Choice :";
		cin>>choice;
		system("pause");
	}
	
	
}
void Courses::remove()					// removing user from linked list
{
	cout<<"Enter Course Code To Remove : ";
	string Code;
	cin >> Code;
	
	Courses *P;
	P=this;
	
	while(P->next!=this)
	{
		P=P->next;
		if(P->code == Code)
		{
			P->previous->next=P->next;
			P->next->previous=P->previous;
			delete(P);
			break;
		}
	}	
}
bool Courses::exist_already(string Code)
{
	Courses *P=this->next;
	while(P!=this)
	{
		if(P->code==Code)
		return true;
		
		P=P->next;
	}
	if(P->code==Code)
	return true;
	
	else
	return false;
}
void Courses::insert()					// inserting new course sorted as simple insert in linked list
{
	cout<<"Enter Data of New Corse :-"<<endl;
	cout<<"\t"<<"Enter New Course Code :";
	string Code;
	cin.ignore();
	getline(cin,Code);
	if(!exist_already(Code))
	{
		cout<<"\t"<<"Enter New Course Name :";
		string Name;
		getline(cin,Name);
		
		Courses *Node = new  Courses(Code,Name);
			
		Node->next=this->next;
		Node->previous=this;
		this->next->previous=Node;
		this->next=Node;
	}
	else
	cout<<"This Code Is Already Occupied\n";
	
}

class Admin
{
	string id;
	string Password;
	Admin *next;
	Admin *previous;
	
	public:
		Admin();
		Admin(string ID);
		Admin(string ID, string pass);
		void generate_linked_list();
		void save_file();
		void show_admin();
		void remove();
		bool exist_already(string Id);
		void insert_new_user();
		void change_pass(string Id);
		bool match_password(string old_pass);
		bool sign_in(string id, string pass);
};
Admin::Admin()							// constructor for header node
{
	this->next=this;
	this->previous=this;
}
Admin::Admin(string ID)					// cnstructor for new user
{
	id=ID;
	Password=ID;
}
Admin::Admin(string ID, string pass)	// constructor for new node while creating linked list
{
	id=ID;
	Password=pass;
}
void Admin::generate_linked_list()		// function uses ifstream file to read data from file and store in linked list
{
	string id;
	string pass;
	int a=0;
	ifstream admin_file;
	admin_file.open("Admin.txt",ios::in);
	while(admin_file >> id >> pass)
	{
		
		Admin *Node = new  Admin(id,pass);
		if(this->next==this)
		{
			Node->next=this;
			Node->previous=this;
			this->next=Node;
			this->previous=Node;
		}
		else
		{
			Node->next=this;
			Node->previous=this->previous;
			this->previous->next=Node;
			this->previous=Node;
		}
	}
	admin_file.close();
}
void Admin::save_file()					// function uses ofstream file to write data from linked list to file
{
	Admin *P=this;
	ofstream admin_file;
	admin_file.open("Admin.txt",ios::out | ios::trunc);
	
	do
	{
		admin_file << P->id << "\t" << P->Password << "\n";
		P=P->next;
	}while(P!=this);
	
	admin_file.close();
}
bool Admin::sign_in(string ID, string PASS) // matches user id and password by traversing linked list
{
	Admin *P=this->next;
	do
	{
		if(P->id==ID)
		break;
		P=P->next;
	}while(P!=this);
	
	if(P->id==ID)
	return P->Password==PASS;
	
	else
	return false;
}
void Admin::show_admin()				// displaing admin user ids by traversing linked list
{
	Admin *P;
	P=this;
	int a=0;
	cout<<setw(5)<<"Sr#"<<setw(10)<<"Id"<<endl;
	while(P->next!=this)
	{
		P=P->next;
		cout<<setw(5)<<++a<<setw(10)<<P->id<<endl;
	}
}
bool Admin::exist_already(string Id)
{
	Admin *P=this->next;
	while(P!=this)
	{
		if(P->id==Id)
		return true;
		
		P=P->next;
	}
	if(P->id==Id)
	return true;
	
	else
	return false;
}
void Admin::insert_new_user()			// inserting new user as simple insert in linked list
{
	cout<<"Enter User Id of New Admin Member :";
	string id;
	cin >> id;
	if(!exist_already(id))
	{
		Admin *Node = new  Admin(id);
	
		Node->next=this;
		Node->previous=this->previous;
		this->previous->next=Node;
		this->previous=Node;
	}
	else
	cout<<"Admin ID:"<<id<<" Already Occupied"<<endl;
}
void Admin::change_pass(string Id)	// changing password again by changning data in linked list
{
	cout<<"Enter Your New Password : ";
	string new_pass;
	cin >> new_pass;
	Admin *P=this;
	while(P->next!=this)
	{
		P=P->next;
		if(P->id == Id)
		{
			P->Password=new_pass;
			cout<<"Password Changed";
			break;
		}
	}

}
void Admin::remove()				// removing user from linked list
{
	cout<<"Enter User-Id Of Admin Member To Remove : ";
	string Id;
	cin >> Id;
	
	Admin *P;
	P=this;
	
	while(P->next!=this)
	{
		P=P->next;
		if(P->id == Id)
		{
			P->previous->next=P->next;
			P->next->previous=P->previous;
			delete(P);
			break;
		}
	}
}
bool Admin::match_password(string user_pass)	// matching password of already signed in user before executing some admin tasks
{
	cout<<"Enter Your Existing Password : ";
	string pass;
	cin >> pass;
	return user_pass==pass;
}

struct Data
{
		string code;
		string name;
		bool applied_status;
		bool registered_status;
		bool add_status;
		bool drop_status;
};

class Student
{
	string Reg;
	string Password;
	bool new_student;
	int no_of_courses;
	Data *C;
	Student *next;
	Student *previous;
//	friend struct Data;
//	friend class Courses;
	
	public:
		Student();
		Student(string reg);
		Student(string reg, string pass);
		Student(string reg, string pass, bool student_new, int courses_number, Data *Ptr);
		bool IsNewStudent();
		void generate_linked_list();
		Student* generate_pointer(string user_reg);
		void save_file();
		bool exist_already(string id);
		void insert();
		void remove();
		void show_info();
		void show_data();
		void show_data(string user_reg);
		void aproove_registeration();
		bool already_interacted(Student *S, string Code);
		void registeration(Courses *R, Student *S);
		void add_course(Courses *R, Student *S);
		void aproove_add();
		void drop_course(Courses *R, Student *S);
		void aproove_drop();
		bool match_course_drop(Student *S, string code);
		void remove_unregistered_courses(Student *S);
		bool is_max();
		bool is_min();
		void change_pass(string reg);
		bool match_password(string user_pass);
		bool sign_in(string reg, string pass);
};
Student::Student()
{
	this->next=this;
	this->previous=this;
	
	Reg="";
	Password="";
	no_of_courses=0;
	C=NULL;
}
Student::Student(string reg)
{
	Reg=reg;
	Password=reg;
	new_student=true;
	no_of_courses=0;
	C=NULL;
}
Student::Student(string reg, string pass)
{
	Reg=reg;
	Password=pass;
	new_student=NULL;
	no_of_courses=-1;
	C=NULL;
}
Student::Student(string reg,string pass, bool student_new, int courses_number, Data *Ptr)
{
	Reg=reg;
	Password=pass;
	new_student=student_new;
	no_of_courses=courses_number;
	C=Ptr;
}
bool Student::IsNewStudent()
{
	return this->new_student==true;
}
void Student::generate_linked_list()
{
	string reg;
	string pass;
	bool student_new;
	int courses_number;
	
	ifstream student_file;
	student_file.open("Student Record.txt",ios::in);
	
	
	
	while(student_file >> reg >> pass >> student_new >> courses_number)
	{
		Data *Ptr = new Data[7];
		for(int i=0; i<courses_number; i++)
		{
			student_file >> Ptr[i].code;
			student_file.ignore();
			getline(student_file,Ptr[i].name);
			student_file  >> Ptr[i].registered_status >> Ptr[i].applied_status;
			student_file  >> Ptr[i].add_status >> Ptr[i].drop_status;
		}
		for(int i=courses_number;i<7;i++)
		{
			Ptr[i].add_status=0;Ptr[i].applied_status=0;
			Ptr[i].add_status=0;Ptr[i].drop_status=0;
		}
		
		Student *Node = new Student(reg,pass,student_new,courses_number,Ptr); 
		
			Node->next=this->next;
			Node->previous=this;
			this->next->previous=Node;
			this->next=Node;
	}
	student_file.close();
}
Student* Student::generate_pointer(string user_reg)
{
	Student *Node=this->next;
	while(Node->next!=this)
	{
		if(Node->Reg==user_reg)
		return Node;
		
		Node=Node->next;
		
	}
	if(Node->Reg!=user_reg)
	return NULL;
	else
	return Node;
}
void Student::save_file()
{
	
	
	Student *P=this->next;
	ofstream student_file;
	student_file.open("Student Record.txt",ios::out | ios::trunc);
	
	while(P!=this)
	{
		student_file << P->Reg <<" "<< P->Password << " " << P->new_student << " " << P->no_of_courses <<"\n";
		for(int i=0; i<P->no_of_courses; i++)
		{
			student_file << P->C[i].code << " " << P->C[i].name<<"\n";
			student_file << P->C[i].registered_status << " " << P->C[i].applied_status<<" ";
			student_file << P->C[i].add_status << " " << P->C[i].drop_status<<"\n";
		}
		P=P->next;
	}
	
	student_file.close();
}
bool Student::exist_already(string id)
{
	Student *P=this->next;
	while(P!=this)
	{
		if(P->Reg==id)
		return true;
		
		P=P->next;
	}
	if(P->Reg==id)
	return true;
	
	else
	return false;
}
void Student::insert()
{
	cout<<"Enter Reg of New Student :";
	string id;
	cin >> id;
	
	if(!exist_already(id))
	{
		Student *Node = new Student(id);
	
		Node->next=this->next;
		Node->previous=this;
		this->next->previous=Node;
		this->next=Node;
	}
	else 
	cout<<"Student ID:"<<id<<" Already Occupied"<<endl;
	
}
void Student::remove()
{
	string id;
	cout<<"Enter Registeration Number Of The Student To Remove :";
	cin >> id;
	
	Student *P=this->next;
	while(P->next!=this)
	{
		if(P->Reg==id)
		break;
	}
	if(P->Reg==id)
	{
		P->previous->next=P->next;
		P->next->previous=P->previous;
		delete P;
		cout<<id+" Deleted\n";
		system("pause");
	}
	else
	{
		cout<<id+" Not found in database.\n";
		system("pause");
	}
	if(this->next==this || this->previous==this)
	{
		this->next=this;
		this->previous=this;
	}
	
	
}
void Student::show_data()
{
	string id;
	cout<<"Enter Registeration Number :";
	cin >> id;

	Student *P=this->next;
	while(P!=this)
	{
		if(P->Reg==id)
		break;
		P=P->next;
	}
	if(P->Reg==id)
	{
		if(P->no_of_courses>0)
		{
		int a=0;
		cout<<"\n\n"<<setw(5)<<"Sr#"<<setw(10)<<"Code"<<setw(50)<<"Name"<<setw(50)<<"Status\n\n";
		for(int i=0; i<P->no_of_courses; i++)
		{
				cout <<setw(5)<< ++a <<setw(10)<< P->C[i].code <<setw(50)<< P->C[i].name;
				if(P->C[i].registered_status && !P->C[i].applied_status && !P->C[i].add_status && !P->C[i].drop_status)//1000
				cout<<setw(50)<<"Registered\n";
				else if(!P->C[i].registered_status && P->C[i].applied_status && !P->C[i].add_status && !P->C[i].drop_status)//0100
				cout<<setw(50)<<"Applied For Registeration\n";
				else if(P->C[i].registered_status && P->C[i].applied_status && !P->C[i].add_status && P->C[i].drop_status)//1101
				cout<<setw(50)<<"Applied For Drop\n";
				else if(!P->C[i].registered_status && P->C[i].applied_status && P->C[i].add_status && !P->C[i].drop_status)//0110
				cout<<setw(50)<<"Applied For Add\n";
				else if(!P->C[i].registered_status && !P->C[i].applied_status && !P->C[i].add_status && !P->C[i].drop_status)//0000
				cout<<setw(50)<<"Registeration Declined\n";
				else if(!P->C[i].registered_status && !P->C[i].applied_status &&  P->C[i].add_status && !P->C[i].drop_status)//0010
				cout<<setw(50)<<"Add Declined\n";
				else if(P->C[i].registered_status && !P->C[i].applied_status && !P->C[i].add_status && P->C[i].drop_status)//1001
				cout<<setw(50)<<"Registered  (Drop Declined)\n";
				else if(!P->C[i].registered_status && !P->C[i].applied_status && !P->C[i].add_status && P->C[i].drop_status)//0001
				cout<<setw(50)<<"Droped\n";
		}
		}
		else
		cout<<"Registeration Not Yet Completed\n";		
	}
	else
	cout<<"Not found in database.\n";
	
}
void Student::show_data(string user_reg)
{
	Student *P=this->next;
	while(P!=this)
	{
		if(P->Reg==user_reg)
		break;
		P=P->next;
	}
	if(P->no_of_courses>0)
	{
		cout<<"\n\n"<<setw(5)<<"Sr#"<<setw(10)<<"Code"<<setw(50)<<"Name"<<setw(50)<<"Status\n\n";
		int a=0;
		for(int i=0; i<P->no_of_courses; i++)
		{
				cout <<setw(5)<< ++a <<setw(10)<< P->C[i].code <<setw(50)<< P->C[i].name;
				if(P->C[i].registered_status && !P->C[i].applied_status && !P->C[i].add_status && !P->C[i].drop_status)//1000
				cout<<setw(50)<<"Registered\n";
				else if(!P->C[i].registered_status && P->C[i].applied_status && !P->C[i].add_status && !P->C[i].drop_status)//0100
				cout<<setw(50)<<"Applied For Registeration\n";
				else if(P->C[i].registered_status && P->C[i].applied_status && !P->C[i].add_status && P->C[i].drop_status)//1101
				cout<<setw(50)<<"Applied For Drop\n";
				else if(!P->C[i].registered_status && P->C[i].applied_status && P->C[i].add_status && !P->C[i].drop_status)//0110
				cout<<setw(50)<<"Applied For Add\n";
				else if(!P->C[i].registered_status && !P->C[i].applied_status && !P->C[i].add_status && !P->C[i].drop_status)//0000
				cout<<setw(50)<<"Registeration Declined\n";
				else if(!P->C[i].registered_status && !P->C[i].applied_status &&  P->C[i].add_status && !P->C[i].drop_status)//0010
				cout<<setw(50)<<"Add Declined\n";
				else if(P->C[i].registered_status && !P->C[i].applied_status && !P->C[i].add_status && P->C[i].drop_status)//1001
				cout<<setw(50)<<"Registered  (Drop Declined)\n";
				else if(!P->C[i].registered_status && !P->C[i].applied_status && !P->C[i].add_status && P->C[i].drop_status)//0001
				cout<<setw(50)<<"Droped\n";
		}
	}
	else
	cout<<"You Have Not Yet Completed Registeration.\n";
}
void Student::show_info()
{
	Student *P=this->next;
	int b=0;
	cout<<setw(5)<<"Sr#"<<setw(10)<<"Reg"<<setw(30)<<"No. Of Courses Interacted"<<endl;
	while(P!=this)
	{
		cout << setw(5) << ++b << setw(10) << P->Reg << setw(30) << P->no_of_courses <<"\n";
		P=P->next;
	}
}
bool Student::already_interacted(Student *S, string Code)
{
	for(int i=0; i<S->no_of_courses; i++)
	{
		if(S->C[i].code==Code)
		return true;
	}
	return false;
}
void Student::registeration(Courses *R, Student *S)
{
	bool again=true;
	system("cls");
	registeration_display_menu();
	int choice;
	cin>>choice;
	string Code;
	Courses *P=R;
	bool interacted=false;
	bool exist=true;
	int final;
	
	while(again)
	{
		system("cls");
		registeration_display_menu();
		cout<<"You Can Register For "<< 7 - S->no_of_courses << endl;
		
		
		switch(choice)
		{
			case 0:
					cout<<"Going Back"<<endl<<endl;
					again=false;
					break;
					
			case 1:
					cout<<"Displaying Courses "<<endl<<endl;
					R->show_courses();
					break;
					
			case 2:
					cout<<"Registering For A Course"<<endl<<endl;
					cout<<"Enter Course Code To Register : ";
					cin.ignore();
					getline(cin,Code);
					interacted=already_interacted(S,Code);
					exist=R->exist_already(Code);
					break;		
			
			default:
					cout<<"Invalid Choice"<<endl;
					break;
		}
		if(!again)
		break;
		if(again && choice == 2 && !interacted && exist)
		{
			cout<<"Code"<<setw(50)<<"Name\n";
			while(P->next!=R)
			{
				P=P->next;
				if(P->code==Code)
				{
					cout<<P->code<<setw(50)<<P->name<<endl<<endl;
					cout<<"1. Yes\n";
					cout<<"2. No\n";
					cout<<"Do You Want To Register For This Course : ";
					cin>>final;
					if(S->no_of_courses<=7)
					{
						if(final==1)
						{
							cout<<endl<<"Applying For Registeration Of "<<P->code<<" "<<P->name<<" As Course Number "<<S->no_of_courses+1<<endl;
							system("pause");
							S->C[S->no_of_courses].code=P->code;           S->C[S->no_of_courses].name=P->name;
							S->C[S->no_of_courses].registered_status=0;    S->C[S->no_of_courses].applied_status=1;
							S->C[S->no_of_courses].add_status=0;           S->C[S->no_of_courses].drop_status=0;
							S->no_of_courses++;
						}
						else
						{
							cout<<"Aborting Registeration For "<<P->code<<" "<<P->name<<endl;
							system("pause");
						}
						
					}
					
				}
				
			}
			P=R;
		}
		else if(interacted)
		{
			cout<<"You Have Already Applied For This Course :"<<Code<<endl;
			system("pause");
		}
		else if(!exist)
		{
			cout<<"This Course Does Not Exist In The Given Choice Of Course :"<<Code<<endl;
			system("pause");
		}
		
		if(S->no_of_courses<7)
		{
			system("cls");
			registeration_display_menu();
			cout<<endl<<"Enter Your Choice :";
			cin>>choice;
		}
		else
		{
			system("cls");
			cout<<"Maximum Courses Apllied For Registeration"<<endl;
			cout<<"Exiting Registeration Portal";
			again=false;
			system("pause");
		}
	}
}
void Student::aproove_registeration()
{
	Student *P = this->next;
	int choice;
	while(P!=this)
	{
		if(P->new_student==true)
		{
			for(int i=0; i<P->no_of_courses; i++)
			{
				if(!P->C[i].registered_status && P->C[i].applied_status && !P->C[i].add_status && !P->C[i].drop_status)
				{
					system("cls");
					cout<<"Reg"<<setw(15)<<"Course Code"<<setw(50)<<"Course Name\n";
					cout<<P->Reg<<setw(15)<<P->C[i].code<<setw(50)<<P->C[i].name<<endl<<endl;
					cout<<"0. Do Nothing\n";
					cout<<"1. Aprrove Registeration\n";
					cout<<"2. Decline Registeration\n\n";
					cout<<"\nEnter Your Choice :";
					cin >> choice;
					
					if(choice==0)
					{
						cout<<"Doing Nothing\n";
					}
					else if(choice==1)
					{
						cout<<"Aproving For Registeration\n";
						P->C[i].registered_status=1;  P->C[i].applied_status=0; P->C[i].add_status=0; P->C[i].drop_status=0;
						P->new_student=false;
					}
					else if(choice==2)
					{
						cout<<"Declining Registeration\n";
						P->C[i].registered_status=0;  P->C[i].applied_status=0; P->C[i].add_status=0; P->C[i].drop_status=0;
						P->new_student=false;
					}
					else
					{
						cout<<"Invalid Choice\n";
						i--;
					}
					cout<<endl<<endl;
					system("pause");
						
				}
			}
		}
		P=P->next;
	}
	cout<<"No Courses For Registeration\n";
}
void Student::add_course(Courses *R, Student *S)
{
	bool again=true;
	system("cls");
	add_display_menu();
	int choice;
	cin>>choice;
	string Code;
	Courses *P=R;
	int final;
	bool exist=true;
	
	while(again)
	{
		system("cls");
		add_display_menu();
		cout<<"You Can Add "<<7-S->no_of_courses<<endl;
		
		
		switch(choice)
		{
			case 0:
					cout<<"Going Back"<<endl<<endl;
					again=false;
					break;
					
			case 1:
					cout<<"Displaying Courses "<<endl<<endl;
					R->show_courses();
					break;
					
			case 2:
					cout<<"Adding A Course"<<endl<<endl;
					cout<<"Enter Course Code To Add : ";
					cin.ignore();
					getline(cin,Code);
					exist=R->exist_already(Code);
					
					break;		
			
			default:
					cout<<"Invalid Choice"<<endl;
					break;
		}
		if(!again)
		break;
		if(!S->already_interacted(S,Code) && exist)
		{
				cout<<"Code"<<setw(50)<<"Name\n";
				while(P->next!=R)
				{
					P=P->next;
					if(P->code==Code)
					{
						cout<<P->code<<setw(50)<<P->name<<endl<<endl;
						cout<<"1. Yes\n";
						cout<<"2. No\n";
						cout<<"Do You Want To Add This Course : ";
						cin>>final;
						if(S->no_of_courses<7)
						{
							if(final==1)
							{
								cout<<endl<<"Applying For Addition Of "<<P->code<<" "<<P->name<<" As Course Number "<<S->no_of_courses+1<<endl;
								system("pause");
								S->new_student=false;
								S->C[S->no_of_courses].code=P->code; 				S->C[S->no_of_courses].name=P->name;
								S->C[S->no_of_courses].applied_status=1;			S->C[S->no_of_courses].add_status=1;
								S->C[S->no_of_courses].registered_status=0;			S->C[S->no_of_courses].drop_status=0;
								//0110
								S->no_of_courses++;
							}
							else
							{
								cout<<"Aborting Add For "<<P->code<<" "<<P->name<<endl;
								system("pause");
							}
							
						}
						
					}
					
				}
		}
		else if(!exist)
		{
			cout<<"This Course Does Not Exist In The Given Choice Of Course :"<<Code<<endl;
			system("pause");
		}
		else
		{
			cout<<"You Have Already Interacted With This Course : "<<Code<<endl;
			system("pause");
		}
		if(again && choice == 2)
		{
			P=R;
		}
		if(S->no_of_courses<7)
		{
			system("cls");
			add_display_menu();
			cout<<endl<<"Enter Your Choice :";
			cin>>choice;
		}
		else
		{
			system("cls");
			cout<<endl<<"Maximum Courses Apllied For "<<endl;
			cout<<"Exiting Add Portal"<<endl;
			system("pause");
			again=false;
		}
	}
}
void Student::aproove_add()
{
	Student *P = this->next;
	int choice;
	while(P!=this)
	{
		if(P->new_student==false)
		{
			for(int i=0; i<P->no_of_courses; i++)
			{
				if(!P->C[i].registered_status && P->C[i].applied_status && P->C[i].add_status)
				{
					system("cls");
					cout<<"Reg"<<setw(15)<<"Course Code"<<setw(50)<<"Course Name\n";
					cout<<P->Reg<<setw(15)<<P->C[i].code<<setw(50)<<P->C[i].name<<endl<<endl;
					cout<<"0. Do Nothing\n";
					cout<<"1. Aprrove Add\n";
					cout<<"2. Decline Add\n\n";
					cout<<"Enter Your Choice :";
					cin >> choice;
					
					if(choice==0)
					{
						cout<<"Doing Nothing\n";
					}
					else if(choice==1)
					{
						cout<<"Aproving For Add\n";
						P->C[i].registered_status=1; P->C[i].applied_status=0;  P->C[i].add_status=0; P->C[i].drop_status=0;//1000
					}
					else if(choice==2)
					{
						cout<<"Declining Add\n";
						P->C[i].registered_status=0; P->C[i].applied_status=0;  P->C[i].add_status=1; P->C[i].drop_status=0;//0010
					}
					else
					{
						cout<<"Invalid Choice\n";
						i--;
					}
					cout<<endl<<endl;
					system("pause");
						
				}
			}
		}
		P=P->next;
	}
	cout<<"No Courses For Add Approval\n";
}
void Student::drop_course(Courses *R, Student *S)
{
	bool again=true;
	int choice;
	
	string Code;
	Courses *P=R;
	int final;
	
	while(again)
	{
		system("cls");
		drop_display_menu();
		cin>>choice;
		
		switch(choice)
		{
			case 0:
					cout<<"Going Back"<<endl<<endl;
					again=false;
					break;
					
			case 1:
					cout<<"Displaying My Courses "<<endl<<endl;
					S->show_data(S->Reg);
					break;
					
			case 2:
					cout<<"Droping A Course"<<endl<<endl;
					cout<<"Enter Course Code To Drop : ";
					cin.ignore();
					getline(cin,Code);
					
					break;		
			
			default:
					cout<<"Invalid Choice"<<endl;
					break;
		}
		if(!again)
		break;
		if(S->match_course_drop(S,Code) && choice ==2)
		{
				cout<<"Code"<<setw(50)<<"Name\n";
				while(P->next!=R)
				{
					P=P->next;
					if(P->code==Code)
					{
						cout<<P->code<<setw(50)<<P->name<<endl<<endl;
						
						cout<<"1. Yes\n";
						cout<<"2. No\n";
						cout<<"Do You Want To Drop This Course : ";
						cin>>final;
						
							int i=0;
							if(final==1)
							{
								cout<<endl;
								cout<<endl<<"Applying For Drop Of "<<P->code<<" "<<P->name<<endl;
								system("pause");
								for( i=0; i<S->no_of_courses; i++)
								{
									if(S->C[i].code==Code)
									break;
								}
								S->C[i].applied_status=1; S->C[i].drop_status=1; S->C[i].registered_status=1; S->C[i].add_status=0;
							}
							else
							{
								cout<<endl;
								cout<<"Aborting Drop For "<<P->code<<" "<<P->name<<endl;
								system("pause");
							}
						
					}
					
				}
		}
		else if(!S->match_course_drop(S,Code) && choice ==2)
		{
			cout<<"You Have Not Yet Registered For This Course /nOR Drop Of This Code Is Pending : "<<Code<<endl<<endl;
			system("pause");
		}
		if(again && choice == 2)
		{
			P=R;
		}
		system("pause");
	}
}
void Student::aproove_drop()
{
	Student *P = this->next;
	int choice;
	while(P!=this)
	{
			for(int i=0; i<P->no_of_courses; i++)
			{
				if(P->C[i].registered_status && P->C[i].applied_status && P->C[i].drop_status)
				{
					system("cls");
					cout<<endl<<"Reg"<<setw(10)<<"Code"<<setw(50)<<"Name\n";
					cout<<P->Reg<<setw(10)<<P->C[i].code<<setw(50)<<P->C[i].name<<endl<<endl;
					
					cout<<"0. Do Nothing\n";
					cout<<"1. Aprrove Drop\n";
					cout<<"2. Decline Drop\n\n";
					cout<<"Enter Your Choice :";
					cin >> choice;
					
					if(choice==0)
					{
						cout<<"\nDoing Nothing\n\n";
					}
					else if(choice==1)
					{
						cout<<"\nAproving For Drop\n\n";
						P->C[i].registered_status=0; P->C[i].applied_status=0;  P->C[i].drop_status=1; P->C[i].add_status=0;//0001
					}
					else if(choice==2)
					{
						cout<<"\nDeclining Drop\n\n";
						P->C[i].registered_status=1; P->C[i].applied_status=0;  P->C[i].drop_status=1; P->C[i].add_status=0;//1001
					}
					else
					{
						cout<<"\nInvalid Choice\n\n";
						i--;
					}
					cout<<endl<<endl;
					system("pause");
				}
		}
		P=P->next;
	}
	cout<<"\nNo Courses For Drop Approval\n\n";
}
bool Student::match_course_drop(Student *S, string Code)
{
	for(int i=0; i<S->no_of_courses; i++)
	{
		if(S->C[i].code==Code && S->C[i].registered_status && !S->C[i].applied_status)
		return true;
	}
	return false;
}
void Student::remove_unregistered_courses(Student *S)
{
	Data *temp = new Data[7];
	int a=0;
	for(int i=0; i < S->no_of_courses; i++)
	{
		if(S->C[i].registered_status==0 && S->C[i].applied_status==0)
		{
			// dont copy
		}
		else
		{
			temp[a].code=S->C[i].code; 									temp[a].name=S->C[i].name;
			temp[a].registered_status=S->C[i].registered_status;			temp[a].applied_status=S->C[i].applied_status;
			temp[a].add_status=S->C[i].add_status;						temp[a].drop_status=S->C[i].drop_status;
			a++;
		}
	}
	S->no_of_courses=a;
	for(int i=a; i<7; i++)
	{
			temp[a].registered_status=0;		temp[a].applied_status=0;
			temp[a].add_status=0;				temp[a].drop_status=0;
	}
	S->C=temp;
}
bool Student::is_max()
{
	return this->no_of_courses==7;
}
bool Student::is_min()
{
	return this->no_of_courses==0;
}
void Student::change_pass(string reg)
{
	cout<<"Enter Your New Password : ";
	string new_pass;
	cin >> new_pass;
	Student *P=this;
	while(P->next!=this)
	{
		P=P->next;
		if(P->Reg == reg)
		{
			P->Password=new_pass;
			cout<<"Password Changed";
			break;
		}
	}
}
bool Student::match_password(string user_pass)
{
	cout<<"Enter Your Existing Password : ";
	string pass;
	cin >> pass;
	return user_pass==pass;
}
bool Student::sign_in(string reg, string pass) // matches user id and password by traversing linked list
{
	Student *P=this->next;
	do
	{
		if(P->Reg==reg)
		break;
		P=P->next;
	}while(P!=this);
	
	if(P->Reg==reg)
	return P->Password==pass;
	
	else
	return false;
}




/*
		main function will just show option for either admin login or student log in
*/
int main()
{
	int choice;
	bool again = true;
	int x;
	int a;
	while(again){
		choice = showMenu_main();
		switch(choice)
		
		{
			case 0: //exit program
				cout<<"Exit Program called"<<endl;
				again = false;
				break;
				
			case 1:
				cout<<"Admin Login called"<<endl;
				admin();
				break;
				
			case 2:
				cout<<"Student Login Called"<<endl;
				student();
				break;
		
			default:
				cerr<<"Invalid choice"<<endl;
				cout<<"Kindly select a valid number from menu"<<endl;
				break;
		}
		system("pause");
		system("cls");
	}
	cout<<"Thank you for using our program"<<endl;
	return 0;
}
int showMenu_main()
{
	int choice;
	printShashkaLine('=', 50);
	cout<<"\t\t Main Menu"<<endl;
	printShashkaLine('=', 50);
	
	cout<<"0. Exit Program"<<endl;
	cout<<"1. Admin Login"<<endl;
	cout<<"2. Student Login"<<endl;
	printShashkaLine('=', 50);
	cout<<"Enter your choice: ";
	cin>>choice;
	return choice;
}
void admin()
{
	system("cls");
	int choice;
	bool again = true;
	
	Admin *L = new Admin;
	Student *S= new Student;
	Courses *C = new Courses;

	L->generate_linked_list();
	S->generate_linked_list();
	C->generate_linked_list();
	
	string user_id;
	string user_pass;
	bool match=false;
	
	//	password and id matching code
	
	
	while(!match)
	{
		printShashkaLine('=', 50);
		cout<<"\t\t Admin Sign-in"<<endl;
		printShashkaLine('=', 50);
		cout<<"Enter Your Admin ID : ";
		cin >> user_id;
		cout<<"Enter Your Password : ";
		cin >> user_pass;
		cout<<endl<<"Getting Your Info"<<endl;
		match=L->sign_in(user_id, user_pass);
		
		if(!match)
		{
			system("cls");
			printShashkaLine('=', 50);
			cout<<endl<<endl<<"Id and Password not matched"<<endl<<endl;
			printShashkaLine('=', 50);
			
			cout<<"0. Leave"<<endl;
			cout<<"1. Retry"<<endl;
			printShashkaLine('=', 50);
			cout<<"Enter your choice: ";
			cin>>choice;
			
			if(choice==0)
			{
				match=true;
				again=false;
			}
		}
		
		system("pause");
		system("cls");
	}
	 
	// main admin code 
	
	while(again){
		choice = showMenu_admin();
		switch(choice)
		
		{
			case 0:
				cout<<"Sign Out"<<endl;
				L->save_file();
				S->save_file();
				C->save_file();
				again=false;
				break;
				
			case 1:
				cout<<"Change Password Called"<<endl;
				if(L->match_password(user_pass))
				{
					L->change_pass(user_id);
				}
				else
				cout<<"Password Not Matched";
				break;
				
			case 2:
				cout<<"Add New Admin Member Called"<<endl;
				if(L->match_password(user_pass))
				{
					L->insert_new_user();
				}
				else
				cout<<"Password Not Matched";
				break;
				
			case 3:
				cout<<"Generate Admin List Called"<<endl;
				system("cls");
				L->show_admin();
				break;
			
			case 4:
				cout<<"Remove Admin Member Called"<<endl;
				if(L->match_password(user_pass))
				{
					L->remove();
				}
				else
				cout<<"Password Not Matched";
				break;
				
			case 5:
				cout<<"Generate Courses List Called"<<endl;
				system("cls");
				C->show_courses();
				break;
				
			case 6:
				cout<<"Add Course Called"<<endl;
				C->insert();
				break;
				
			case 7:
				cout<<"Remove Course Called"<<endl;
				C->remove();
				break;
				
			case 8:
				cout<<"Add Student Called"<<endl;
				S->insert();
				break;
				
			case 9:
				cout<<"Generate Student List Called"<<endl;
				system("cls");
				S->show_info();
				break;
				
			case 10:
				cout<<"Generate Student Data Called"<<endl;
				system("cls");
				S->show_data();
				break;
			
			case 11:
				cout<<"Remove Student Called"<<endl;
				S->remove();
				break;
				
			case 12:
				cout<<" Aproove Registeration Called"<<endl;
				S->aproove_registeration();
				break;
				
			case 13:
				cout<<" Aproove Add Called"<<endl;
				S->aproove_add();
				break;
				
			case 14:
				cout<<" Aproove Drop Called"<<endl;
				S->aproove_drop();
				break;
		
			default:
				cout<<"Invalid choice"<<endl;
				cout<<"Kindly select a valid number from menu"<<endl;
				break;
		}
		system("pause");
		system("cls");
	}
	cout<<"Logging Out"<<endl;
}
void student()
{
	system("cls");
	int choice;
	bool again = true;
	
	Student *L = new Student;
	Courses *C = new Courses;

	L->generate_linked_list();
	C->generate_linked_list();
	
	string user_reg;
	string user_pass;
	bool match=false;
	
	//	password and id matching code
	
	
	while(!match)
	{
		printShashkaLine('=', 50);
		cout<<"\t\t Student Sign-in"<<endl;
		printShashkaLine('=', 50);
		cout<<"Enter Your Student Id : ";
		cin >> user_reg;
		cout<<"Enter Your Password : ";
		cin >> user_pass;
		cout<<endl<<"Getting Your Info"<<endl;
		match=L->sign_in(user_reg, user_pass);
		
		if(!match)
		{
			system("cls");
			printShashkaLine('=', 50);
			cout<<endl<<endl<<"Id and Password not matched"<<endl<<endl;
			printShashkaLine('=', 50);
			
			cout<<"0. Leave"<<endl;
			cout<<"1. Retry"<<endl;
			printShashkaLine('=', 50);
			cout<<"Enter your choice: ";
			cin>>choice;
			
			if(choice==0)
			{
				match=true;
				again=false;
			}
		}
		
		system("pause");
		system("cls");
	}
	 
	// main admin code 
	Student *Node=L->generate_pointer(user_reg);
	while(again){
		choice = showMenu_student();
		switch(choice)
		
		{
			case 0:
				cout<<"Sign Out Called"<<endl;
				L->save_file();
				again=false;
				break;
				
			case 1:
				cout<<"Change Password Called"<<endl;
				if(L->match_password(user_pass))
				{
					L->change_pass(user_reg);
				}
				else
				cout<<"Password Not Matched";
				break;
				
			case 2:
				cout<<"Register Courses Called"<<endl;
				if(Node->is_min())
				{
					L->registeration(C,Node);
				}
				else
				cout<<"You Have Already Applied For Registeration"<<endl;
				break;
				
			case 3:
				cout<<"Showing Courses Status"<<endl;
				L->show_data(user_reg);
				break;
				
			case 4:
				cout<<"Add Course Called"<<endl;
				if(!Node->IsNewStudent() && !Node->is_max())
				{
					L->add_course(C,Node);
				}
				else if(Node->IsNewStudent())
				cout<<"You Have Not Yet Completed Registeration Process"<<endl;
				else if(Node->is_max())
				cout<<"You Have Interacted With Maximum Courses"<<endl;
				break;
			
			case 5:
				cout<<"Drop Course Called"<<endl;
				if(!Node->IsNewStudent() && !Node->is_min())
				{
					L->drop_course(C,Node);
				}
				else if(Node->IsNewStudent())
				cout<<"You Have Not Yet Completed Registeration Process"<<endl;
				else if(Node->is_min())
				cout<<"You Have No Registered Course To Drop"<<endl;
				break;
				
			case 6:
				cout<<"Remove Unregistered Courses Called"<<endl;
				if(!Node->IsNewStudent())
				{
					L->remove_unregistered_courses(Node);
				}
				else
				cout<<"You Have Not Yet Completed Registeration Process"<<endl;
				break;
					
			case 7:
				cout<<"Generate Courses List Called"<<endl;
				C->show_courses();
				break;
		
			default:
				cerr<<"Invalid choice"<<endl;
				cout<<"Kindly select a valid number from menu"<<endl;
				break;
		}
		system("pause");
		system("cls");
	}
	cout<<"Logging Out"<<endl;
}
int showMenu_admin()
{
	int choice;
	printShashkaLine('=', 50);
	cout<<"\t\t Admin Menu"<<endl;
	printShashkaLine('=', 50);
	
	cout<<"0. Sign Out"<<endl;
	cout<<"1. Change Password"<<endl;
	cout<<"2. Add New Admin Member"<<endl;
	cout<<"3. Generate Admin List"<<endl;
	cout<<"4. Remove Admin Member"<<endl;
	cout<<"5. Generate Courses List"<<endl;
	cout<<"6. Add Course"<<endl;
	cout<<"7. Remove Course"<<endl;
	cout<<"8. Add Student"<<endl;
	cout<<"9. Generate Student List"<<endl;
	cout<<"10. Generate Student Data"<<endl;
	cout<<"11. Remove Student"<<endl;
	cout<<"12. Aproove Registeration"<<endl;
	cout<<"13. Aproove Add"<<endl;
	cout<<"14. Aproove Drop"<<endl;
	printShashkaLine('=', 50);
	cout<<"Enter your choice: ";
	cin>>choice;
	return choice;
}
int showMenu_student()
{
	int choice;
	printShashkaLine('=', 50);
	cout<<"\t\t Student Menu"<<endl;
	printShashkaLine('=', 50);
	
	cout<<"0. Sign Out"<<endl;
	cout<<"1. Change Password"<<endl;
	cout<<"2. Register Courses"<<endl;
	cout<<"3. Show My Courses Status"<<endl;
	cout<<"4. Add Course"<<endl;
	cout<<"5. Drop Course"<<endl;
	cout<<"6. Remove Unregisterd Courses"<<endl;
	cout<<"7. Generate Courses List"<<endl;
	printShashkaLine('=', 50);
	cout<<"Enter your choice: ";
	cin>>choice;
	return choice;
}
void courses_display_menu()
{
	printShashkaLine('=', 50);
	cout<<"\t\tCourses Display Menu\n";
	printShashkaLine('=', 50);
	cout<<"0. Go Back"<<endl;
	cout<<"1. Show Courses Sorted By Code"<<endl;
	cout<<"2. Show Courses Sorted By Name"<<endl;
	printShashkaLine('=', 50);
}
void registeration_display_menu()
{
	printShashkaLine('=', 50);
	cout<<"\t\tRegisteration Menu\n";
	printShashkaLine('=', 50);
	cout<<"0. End Registeration"<<endl;
	cout<<"1. Show Courses "<<endl;
	cout<<"2. Register For Course By Code 'Max 7' "<<endl;
	printShashkaLine('=', 50);
}
void add_display_menu()
{
	printShashkaLine('=', 50);
	cout<<"\t\tAdd Menu\n";
	printShashkaLine('=', 50);
	cout<<"0. Go Back"<<endl;
	cout<<"1. Show Courses "<<endl;
	cout<<"2. Add Course By Code 'Max 7' "<<endl;
	printShashkaLine('=', 50);
}
void drop_display_menu()
{
	printShashkaLine('=', 50);
	cout<<"\t\tAdd Menu\n";
	printShashkaLine('=', 50);
	cout<<"0. Go Back"<<endl;
	cout<<"1. Show My Courses "<<endl;
	cout<<"2. Drop Course By Code "<<endl;
	printShashkaLine('=', 50);
}
void printShashkaLine(char element, int noOfTimes)
{
	for(int i=0; i < noOfTimes; i++)
	{
		cout<<element;
	}
	cout<<endl;
}
