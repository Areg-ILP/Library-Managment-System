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
	int book_id;
	string name_after;
	string name_book;
};

//rootclass
class RootUser
{
protected:
	int id;
	string login;
	string password;
	string state;
	vector<book_info> books;
public:	
	//root functions//
	RootUser();	
	int GetId();
	string GetLogin();
	string GetPassword();	
	string GetState();
	size_t GetBookSize();	

	//inheritance functions//
	virtual void DefineBooks() = 0;	
	virtual void PrintBooks() = 0;
	virtual void DefUser() = 0;
	virtual	void AddBook() = 0;
	virtual void DelBook() = 0;		

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

////// ROOT CLASS DEFINED //////

//basic user
class User : public RootUser
{	
public:
	//this class functions//
	User();				

	//inheritance functions//	
	void DefineBooks() override;
	void DefUser() override;
	void AddBook() override;
	void DelBook() override;
	void PrintBooks() override;	
};

////// USER CLASS DEFINED //////
User::User()
{	
}

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
	while(rub >> id >> copy.book_id >> copy.name_after >> copy.name_book)
	{
		if(this->id == id)
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
		cout << " [" << this->books[i].book_id << "]" << " :: " <<
				this->books[i].name_after << " :: " <<
				this->books[i].name_book << "\n";
	}
}

void User::DefUser()
{
}

void User::AddBook()
{
}

void User::DelBook()
{
}

////// USER CLASS DEFINED //////

//vip user
class Admin : public RootUser
{
public:
	//this class functions//
	Admin();	
	
	//inheritance functions//	
	void DefineBooks() override;
	void DefUser() override;
	void AddBook() override;
	void DelBook() override;
	void PrintBooks() override;
};

Admin::Admin()
{		
}

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
	while(rlib >> copy.book_id >> copy.name_after >> copy.name_book)	
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
		cout << " [" << this->books[i].book_id << "]" << " :: " <<
				this->books[i].name_after << " :: " <<
				this->books[i].name_book << "\n";
	}
}

void Admin::DefUser() 
{
}

void Admin::AddBook() 
{
}

void Admin::DelBook()
{
}
#endif // !_structures_h_
