#pragma once
#ifndef _structures_h_
#define _structures_h_
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

//type book
struct book_info
{	
	string name_after;
	string name_book;
};

//rootclass
class RootUser
{
private:
	int id;
	string login;
	string password;
	string state;
protected:
	vector<book_info> books;
public:	
	//root functions//
	RootUser();	
	int GetId();
	string GetLogin();
	string GetPassword();	
	string GetState();
	size_t GetBookSize();
	book_info GetBook(int i);	

	//inheritance functions//
	virtual void DefineBooks() = 0;	
	virtual void PrintBooks() = 0;	
	virtual	void AddBook(book_info) = 0;
	virtual void DelBook(book_info) = 0;		

	//friend functions//
	friend void SignIn();
	friend void Registration();	
};

////// ROOT CLASS DEFINED //////

RootUser::RootUser()
{
	this->state = "";
	int count = 0;
	ifstream readfile;
	readfile.open("dataus.txt");
	if (!readfile.is_open())
	{
		cout << "[Warning] Database closed , Login falling \n";
		exit(1);
	}
	string str;
	while (getline(readfile, str))
		count++;
	readfile.close();
	this->id = count;
}

int RootUser::GetId()
{
	return this->id;
}

string RootUser::GetLogin()
{
	return this->login;
}

string RootUser::GetPassword()
{
	return this->password;
}

size_t RootUser::GetBookSize()
{
	return this->books.size();
}

string RootUser::GetState()
{
	return this->state;
}

book_info RootUser::GetBook(int i)
{
	return this->books.at(i-1);
}

////// ROOT CLASS DEFINED //////

class LibUpdate : public RootUser
{
public:
	//this class functions//
	LibUpdate(){}	

	//inheritance functions//
	void DefineBooks() override;
	void AddBook(book_info) override;	
	void DelBook(book_info) override;
	void PrintBooks() override;		
};

/////// UPDATE FUNCTIONS///////
void LibUpdate::DefineBooks()
{
	this->books.clear();
	ifstream rlib;
	rlib.open("databo.txt");
	if (!rlib.is_open())
	{
		cout << "[Warning]: Database closed\a";
		exit(1);
	}
	
	book_info copy;
	while(rlib >> copy.name_after >> copy.name_book)	
		this->books.push_back(copy);
	
	rlib.close();
}

void LibUpdate::DelBook(book_info B)
{
	auto it = this->books.begin();
	for(size_t i = 0; i < this->books.size(); i++)
	{
		if(B.name_after == this->books[i].name_after && B.name_book == this->books[i].name_book)
		{
			advance(it,i);
			this->books.erase(it);
		}
	}

	ofstream clearF;
	clearF.open("databo.txt");
	clearF.clear();

	for(size_t i = 0; i < this->books.size(); i++)
		clearF << this->books[i].name_after << " " << this->books.at(i).name_book << "\n";

	clearF.close();
}

void LibUpdate::AddBook(book_info B)
{	
	ofstream rlb;
	rlb.open("databo.txt", ofstream::app);

	if (!rlb.is_open())
	{
		cout << "[Warning] Database closed , AddMYBooks() falling \n";
		exit(1);
	}

	rlb << B.name_after + " " + B.name_book << "\n";
	rlb.close();
}

void LibUpdate::PrintBooks()
{
	cout << "#################################\n";
	cout << "#                               #\n";
	cout << "#     @      Library      @     #\n";
	cout << "#                               #\n";
	cout << "#################################\n\n";
	cout << " Book id::After Name::book name\n\n";

	for(size_t i = 0; i < this->books.size(); i++)
	{
		cout << " [" << i+1 << "]" << " :: " <<
				this->books[i].name_after << " :: " <<
				this->books[i].name_book << "\n";
	}
}

/////// UPDATE FUNCTIONS///////

//Standart User
class User : public RootUser
{	
public:
	//this class functions//
	User(){};				

	//inheritance functions//	
	void DefineBooks() override;	
	void AddBook(book_info) override;
	void DelBook(book_info) override;
	void PrintBooks() override;	
};

////// USER CLASS DEFINED //////

void User::DefineBooks()
{
	this->books.clear();
	ifstream rub;
	rub.open("dataub.txt");

	if (!rub.is_open())
	{
		cout << "[Warning]: Database closed\a";
		exit(1);
	}

	book_info copy;
	int id;
	while(rub >> id >> copy.name_after >> copy.name_book)
	{
		if(this->GetId() == id)
			this->books.push_back(copy);
	}
	rub.close();
}

void User::PrintBooks()
{
	cout << "++++++++++++++++++++++++++++++++++\n";
	cout << "||                              ||\n";
	cout << "||     %     My Books     %     ||\n";
	cout << "||                              ||\n";
	cout << "++++++++++++++++++++++++++++++++++\n";
	cout << "\n Book id::After Name::book name\n\n";

	for(size_t i = 0; i < this->books.size(); i++)
	{
		cout << " [" << i+1 << "]" << " :: " <<
				this->books[i].name_after << " :: " <<
				this->books[i].name_book << "\n";
	}
}

void User::AddBook(book_info B)
{
	ofstream rmb;
	rmb.open("dataub.txt", ofstream::app);

	if (!rmb.is_open())
	{
		cout << "[Warning] Database closed , AddMYBooks() falling \n";
		exit(1);
	}
	rmb << this->GetId() << " " << B.name_after + " " + B.name_book << "\n";

	rmb.close();
}

void User::DelBook(book_info B)
{
	auto it = this->books.begin();
	for(size_t i = 0; i < this->books.size(); i++)
	{
		if(B.name_after == this->books[i].name_after && B.name_book == this->books[i].name_book)
		{
			advance(it,i);
			this->books.erase(it);
		}
	}

	ofstream clearUB;
	clearUB.open("dataub.txt");
	clearUB.clear();
	
	for(size_t i = 0; i < this->books.size(); i++)
		clearUB << this->GetId() << this->books[i].name_after << " " << this->books.at(i).name_book << "\n";

	clearUB.close();
}

////// USER CLASS DEFINED //////

//Administrator
class Admin : public RootUser
{
public:
	//this class functions//		
	Admin(){};

	//inheritance functions//	
	void DefineBooks() override;	
	void AddBook(book_info) override;
	void DelBook(book_info) override;
	void PrintBooks() override;
};

void Admin::DefineBooks()
{
	this->books.clear();
	ifstream rlib;
	rlib.open("databo.txt");
	if (!rlib.is_open())
	{
		cout << "[Warning]: Database closed\a";
		exit(1);
	}
	
	book_info copy;
	while(rlib >> copy.name_after >> copy.name_book)	
		this->books.push_back(copy);
	
	rlib.close();
}

void Admin::PrintBooks()
{
	cout << "++++++++++++++++++++++++++++++++++\n";
	cout << "||                              ||\n";
	cout << "||    %   Library Books   %     ||\n";
	cout << "||                              ||\n";
	cout << "++++++++++++++++++++++++++++++++++\n";
	cout << "\n Book id::After Name::book name\n\n";
	for(size_t i = 0; i < this->books.size(); i++)
	{
		cout << " [" << i+1 << "]" << " :: " <<
				this->books[i].name_after << " :: " <<
				this->books[i].name_book << "\n";
	}
}

void Admin::AddBook(book_info B) 
{
}

void Admin::DelBook(book_info B)
{	
}

#endif // !_structures_h_