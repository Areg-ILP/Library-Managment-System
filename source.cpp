#include "structures.h"
using namespace std;

vector<book_info> tmpBooks;

//start func//
void StartMenu();
void SignIn();
void Registration();
void MainMenu(RootUser* user);
//start func//

//menu func//
void PrintMenu();
bool MyProfile(RootUser* user);
book_info TakeBook();
bool MyBooks(RootUser* user);
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
			Admin ad;
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
	do {
		ch = 0;
		user->DefineBooks();
		system("clear");	
		cout << "=============================\n";
		cout << "||        Main Menu        ||\n";	
		cout << "||                         ||\n";
		cout << "||   [1] My Profile.       ||\n";	
		cout << "||   [2] Take Book.        ||\n";	
		cout << "||   [3] My Books.         ||\n";	
		cout << "||   [4] Return Book.      ||\n";	
		cout << "||   [5] Exit.             ||\n";	
		cout << "||                         ||\n";
		cout << "=============================\n";
		cout << "\nChoose one: ";
		cin >> ch;
		book_info B;		
			switch (ch)
			{
			case '1':
				if(!MyProfile(user))
						exit(0);
				break;
			case '2':
				if(user->GetState()== "Standart user")
				{
					B = TakeBook();
					//
					//
				}						
				break;
			case '3':
				if(!MyBooks(user))
					exit(0);
				break;
			case '4':
				if(user->GetState()== "Standart user")
					if(user->GetBookSize() != 0)
					{
						//
						//
					}
				break;
			case '5':
				exit(0);
			default:
				cout << "\a";	
			}		
					
	} while(ch != '5');		
}

bool MyProfile(RootUser* user)
{	
	system("clear");
	cout << "# # # # # # # # # # # # # # # #\n";
	cout << "#                             #\n";
	cout << "#    $     My Profile     $   #\n";
	cout << "#                             #\n";
	cout << "# # # # # # # # # # # # # # # #\n#\n";	
	cout << "#      State: " << user->GetState() << "\n";
	cout << "#      Your id: " << user->GetId() << "\n";
	cout << "#      Login: " << user->GetLogin() << "\n";
	cout << "#      Password: " << user->GetPassword() << "\n";
	cout << "#      Books: " << user->GetBookSize() << "\n#\n";
	cout << "# # # # # # # # # # # # # # # #\n\n";
	cout << "[1] Exit main menu \n";
	cout << "[2] Exit Program \n";
	
	char ch;
	do {		
		cout << "\nChoose one: ";
		cin >> ch;
		if(ch != '1' && ch != '2')
			cout << "[Warning] Not correct input";
	}while(ch != '1' && ch != '2');

	return (ch == '1')?true:false;
}

bool MyBooks(RootUser* user)
{
	system("clear");			
	if (user->GetBookSize()==0)
		cout << "     You dont have books \n";
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

book_info TakeBook()
{
	tmpBooks.clear();
	system("clear");
	ifstream rbook;
	rbook.open("databo.txt");

	if (!rbook.is_open())
	{
		cout << "[Warning] Database closed , proccess falling \n";
		exit(1);
	}

	cout << "#################################\n";
	cout << "#                               #\n";
	cout << "#     @      Library      @     #\n";
	cout << "#                               #\n";
	cout << "#################################\n\n";
	cout << " Book id::After Name::book name\n\n";
	
	book_info book;
	int count = 0;
	while (rbook >> book.book_id >> book.name_after >> book.name_book)
	{
		cout << " [" << book.book_id << "]" << " :: " <<
			book.name_after << " :: " <<
			book.name_book << "\n";
		tmpBooks.push_back(book);
		count++;
	}	
	rbook.close();

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
	if (!(option > 0 && option < count + 1))
	{
		cout << "[Warning] Answer out of distance ";
		goto loop;
	}

	book.book_id = tmpBooks[option - 1].book_id;
	book.name_after = tmpBooks[option - 1].name_after;
	book.name_book = tmpBooks[option - 1].name_book;

	return book;
}

//1 BellHooks AllAboutLove
//2 EdwardAbbey DesertSolitaire
//3 Coetzee Disgrace
//4 KatherineDunn GeekLove
//5 RobinsonMarlyne Gilead
//6 DavidFoster InfiniteJest
//7 VladmirNabokov Lolita
//8 ArtSpiegelman Maus