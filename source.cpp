//Hi! This is a simple c++ mini project_
//which I found in web and wanted to implement for learning purposes.
//I added a part of me to this project.
//Thank you for watching.I hope,I got it.
//git - areg-ilp
//inst - _areg_01

#include "structures.h"
using namespace std;

//This is a cpp file function.
//Other functions were defined in another file.

//start func//
void StartMenu();
void SignIn();
void Registration();
void MainMenu(RootUser*);
//start func//

//menu func//
void PrintMenu();
bool MyProfile(RootUser*);
bool MyBooks(RootUser*);
book_info TakeBook(RootUser*);
book_info ReturnBook(RootUser*);
book_info BookAdding();
book_info BookDeleting(RootUser*);
//menu func//

int main()
{	
	StartMenu();	
	return 0;
}

void StartMenu()
{
	system("clear");
	cout << "!~~~  Welcome our Library  ~~~!\n\n";
	cout << "[1] Login\n[2] Registration \n";

	char ch;	
	do {		
		cout << "\nChoose one: ";
		cin >> ch;
		if(ch != '1' && ch != '2')
			cout << "[Warning] Not correct input";
	}while(ch != '1' && ch != '2');
	
	(ch == '1') ? SignIn() : Registration();	
}

void SignIn()
{
	system("clear");
	ifstream read;
	read.open("dataus.txt");	
	if (!read.is_open())
	{
		cout << "[Warning] Database closed , Login falling \n";
		exit(1);
	}

	int _id;		
	string log, pass,copy_l,copy_p;
	cout << "!~~~ Sign in ~~~!\n\n";
	cout << "Login: ";
	cin >> log;
	cout << "Password: ";
	cin >> pass;
		
	while (read >> _id >> copy_l >> copy_p)
	{
		if(_id == 0 && copy_l == log && copy_p == pass)
		{
			read.close();
			LibUpdate ad;
			ad.id = _id;
			ad.login = log;
			ad.password = pass;
			ad.state = "Administrator";
			MainMenu(&ad);		
		}
		if (log == copy_l && pass == copy_p)
		{			
			read.close();			
			User us;
			us.id = _id;
			us.login = log;
			us.password = pass;
			us.state = "Standart user";
			MainMenu(&us);
		}
	}

	cout << "\n[Not Correct login or password]\n";
	read.close();
	exit(1);
}

void Registration()
{
	ofstream write;
	write.open("dataus.txt", ofstream::app);
	string login, password;
	system("clear");

	cout << "!~~~~  Registartion  ~~~~!\n\n";
	cout << "Input your login: ";
	cin >> login;
	cout << "Input your password: ";
	cin >> password;

	if (!write.is_open())
	{
		cout << "[Warning] Database closed , registartion falling \n";
		exit(1);
	}
	
	User user;
	write << user.id << " " + login + " " + password;
	write << "\n";
	write.close();

	user.login = login;
	user.password = password;
	user.state = "Standart user";
	user.books.clear();
	
	MainMenu(&user);
}

void MainMenu(RootUser* user)
{
    char ch;
	book_info B;	
	LibUpdate BooksUpdate;	
	do {
		ch = 0;
		user->DefineBooks();
		if(user->GetState() == "Standart user")
			BooksUpdate.DefineBooks();
		system("clear");	
		cout << "=============================\n";
		cout << "||        Main Menu        ||\n";	
		cout << "||                         ||\n";
		cout << "||   [1] My Profile.       ||\n";
		if(user->GetState() == "Standart user")
		{
			cout << "||   [2] Take Book.        ||\n";	
			cout << "||   [3] My Books.         ||\n";	
			cout << "||   [4] Return Book.      ||\n";
		}
		else
		{
			cout << "||   [2] Add Book.         ||\n";	
			cout << "||   [3] Book Base.        ||\n";	
			cout << "||   [4] Delete Book.      ||\n";
		}											
		cout << "||   [5] Exit.             ||\n";	
		cout << "||                         ||\n";
		cout << "=============================\n";
		cout << "\nChoose one: ";
		cin >> ch;					
			switch (ch)
			{
			case '1':
				if(!MyProfile(user))
					exit(0);
				break;
			case '2':
				if(user->GetState() == "Standart user")
				{
					if(BooksUpdate.GetBookSize()!= 0)
					{
						B = TakeBook(&BooksUpdate);
						BooksUpdate.DelBook(B);
						user->AddBook(B);
					}
				}
				else
				{	
					B = BookAdding();
					user->AddBook(B);									
				}																													
				break;
			case '3':
				if(!MyBooks(user))
					exit(0);
				break;
			case '4':
				if(user->GetState() == "Standart user")
				{
					if(user->GetBookSize() != 0)
					{
						B = ReturnBook(user);
						user->DelBook(B);
						BooksUpdate.AddBook(B);
					}
				}
				else
				{
					if(user->GetBookSize() != 0)
					{
						B = BookDeleting(user);
						user->DelBook(B);
					}					
				}														
				break;
			case '5':
				exit(0);
			default:
				cout << "\a";	
			}					
	}  while(ch != '5');
}

bool MyProfile(RootUser* user)
{	
	system("clear");
	cout << "# # # # # # # # # # # # # # # #\n";
	cout << "#                             #\n";
	cout << "#    $     My Profile     $   #\n";
	cout << "#                             #\n";
	cout << "# # # # # # # # # # # # # # # #\n\n";	
	cout << "       State: " << user->GetState() << "\n";
	cout << "       Your id: " << user->GetId() << "\n";
	cout << "       Login: " << user->GetLogin() << "\n";
	cout << "       Password: " << user->GetPassword() << "\n";
	cout << "       Books: " << user->GetBookSize() << "\n\n";
	cout << "# # # # # # # # # # # # # # # #\n\n";
	cout << "[1] Exit main menu \n";
	cout << "[2] Exit Program \n";
	
	char ch;
	do {		
		cout << "\nChoose one: ";
		cin >> ch;
		if(ch != '1' && ch != '2')
			cout << "[Warning] Not correct input";
	} while(ch != '1' && ch != '2');

	return (ch == '1')?true:false;
}

bool MyBooks(RootUser* user)
{
	system("clear");			
	if (user->GetBookSize()==0)
		cout << "     OOPS! Books are over \n";
	else		
		user->PrintBooks();
			
		cout << "\n++++++++++++++++++++++++++++++++\n\n";
		cout << "[1] Exit main menu \n";
		cout << "[2] Exit Program \n";	
	
	char ch;	
	do {		
		cout << "\nChoose one: ";
		cin >> ch;
		if(ch != '1' && ch != '2')
			cout << "[Warning] Not correct input";
	}while(ch != '1' && ch != '2');

	return (ch == '1') ? true:false;
}

//user func
book_info TakeBook(RootUser* update)
{
	system("clear");		
	update->PrintBooks();		
	int option;
loop:
	try
	{
		cout << "\nChoose one: ";
		cin >> option;
		if (option == int())
			throw option;
	}
	catch (int option)
	{
		cout << "[Error] Not correct input , program closed , restart!\n";
		exit(1);
	}
	if (!(option > 0 && option < update->GetBookSize() + 1))
	{
		cout << "[Warning] Answer out of distance ";
		goto loop;
	}
	
	book_info book = update->GetBook(option);
	return book;
}

//user func
book_info ReturnBook(RootUser* user)
{
	system("clear");		
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "|                               |\n";
	cout << "|           Return book         |\n";
	cout << "|         back to library       |\n";
	cout << "|                               |\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";		
	user->PrintBooks();	
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";				
	
	int option;
	try
	{
		cout << "\nChoose one: ";
		cin >> option;
		if (option == int())
			throw option;
	}
	catch (int option)
	{
		cout << "[Error] Not correct input , program closed , restart!";
		exit(1);
	}
	if (!(option > 0 && option < user->GetBookSize() + 1))
		cout << "[Warning] Answer out of distance ";	

	book_info book = user->GetBook(option);
	return book;
}

//admin func
book_info BookAdding()
{
	book_info book;
	system("clear");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "|                               |\n";
	cout << "|           Adding book         |\n";
	cout << "|                               |\n";	
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";		

	cout << "~~ Input author of the book ~~: ";
	cin >> book.name_author;
	cout << "~~ Input book name ~~: ";
	cin >> book.name_book;
	
	return book;	
}

//admin func
book_info BookDeleting(RootUser* update)
{
	int option;
	system("clear");			
	if (update->GetBookSize() == 0)
		cout << "     Library is empty \n";
	else		
		update->PrintBooks();				
		cout << "\n++++++++++++++++++++++++++++++++\n\n";
	
loop:
	try
	{
		cout << "\nChoose one: ";
		cin >> option;
		if (option == int())
			throw option;
	}
	catch (int option)
	{
		cout << "[Error] Not correct input , program closed , restart!\n";
		exit(1);
	}
	if (!(option > 0 && option < update->GetBookSize() + 1))
	{
		cout << "[Warning] Answer out of distance ";
		goto loop;
	}
	
	book_info book = update->GetBook(option);
	return book;		
}