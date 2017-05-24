﻿#include "CReader.h"
#include "CBook.h"
#include "CUser.h"
#include "CBookManager.h"
#include "CReaderManager.h"
#include <iostream>
CBookManager bookManager;
CReaderManager readerManager;
int landbook()
{
	string readerName, bookName;
	int readerSubscript, bookSubscript;
	cout << "请输入读者名称" << endl;
	cin >> readerName;
	readerSubscript = readerManager.findreader(readerName);
	if (readerSubscript == -1)
	{
		cout << "读者不存在" << endl;
		return 0;
	}
	cout << "请输入书籍名称" << endl;
	cin >> bookName;
	bookSubscript = bookManager.findbook(bookName);
	if (bookSubscript == -1)
	{
		cout << "书籍不存在" << endl;
		return 0;
	}
	else if (bookSubscript == -2)
	{
		cout << "书籍已借出" << endl;
		return 0;
	}
	bookManager.editbook(bookSubscript, false);
	readerManager.editreader(readerSubscript, bookManager.getbook(bookSubscript));
	readerManager.editreader(readerSubscript, true);
	cout << "借书成功" << endl;
	return 0;
}
int returnbook()
{
	cout << "请输入读者名称" << endl;
	string readername;
	cin >> readername;
	int readersubscript = readerManager.findreader(readername);
	if (readersubscript == -1)
	{
		cout << "读者不存在" << endl;
		return 0;
	}
	CReader reader = readerManager.getreader(readersubscript);
	CBook book = reader.getbrbook();
	int booksubscript = bookManager.findbook(book.getname());
	bookManager.editbook(booksubscript, true);
	readerManager.editreader(readersubscript, false);
	return 0;
}
int filemanage()
{
	cout << "1.文件存储" << endl << "2.文件读取" << endl;
	int command;
	cin >> command;
	if (command == 1)
	{
		readerManager.save();
		bookManager.save();
		cout << "已存储在books.db和readers.db中" << endl;
		return 0;
	}
	else if (command == 2)
	{
		readerManager.load();
		bookManager.load();
		cout << "文件已读取" << endl;
		bookManager.listbooks();
		readerManager.listreaders();
		return 0;
	}
	else
	{
		cout << "文件未操作" << endl;
		return 1;
	}
	return 0;
}
int bookmanage()
{
	return 0;
}
int readermanage()
{
	return 0;
}
int main()
{
	cout << "欢迎使用图书馆管理系统" << endl;
	cout << "1.借书" << endl;
	cout << "2.还书" << endl;
	cout << "3.图书管理" << endl;
	cout << "4.读者管理" << endl;
	cout << "5.文件存储" << endl;
	cout << "其他退出" << endl;
	bool flag = true;
	while (flag)
	{
		int command;
		cout << "请输入指令" << endl;
		cin >> command;
		switch (command)
		{
		case 1:
			landbook();
			break;
		case 2:
			returnbook();
			break;
		case 3:
			bookmanage();
			break;
		case 4:
			readermanage();
			break;
		case 5:
			filemanage();
			break;
		default:
			flag = false;
		}
	}
	bookManager.save();
	readerManager.save();
	return 0;
}