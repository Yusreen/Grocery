#include <iostream>;
#include <string>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
using namespace std;

fstream fp; //Stream for file

class item {
	string Id;
	string name;
	float price;
	float qty;
	float disc;
	float tax;

public:
	void createItem() {
		cout << "Enter the name of the product" << endl;
		cin >> name;
		cout << "Enter the ID of the product" <<endl;
		cin >> Id;
		cout << "Enter the price of the product" << endl;
		cin >> price;
		cout << "Enter the discount for the product" << endl;
		cin >> disc;
	}

	void showItem() {
		cout << "The ID of the product is:"<<Id <<endl;
		cout << "The name of the product is:"<<name <<endl;
		cout << "The price of the product is:" << price <<endl;
		cout << "The discount of the product is:" << disc<<endl;
	}
	string getId()
	{
		return Id;
	}

	float getPrice()
	{
		return price;
	}

	string getName()
	{
		return name;
	}

	float getDisc()
	{
		return disc;
	}

};

item pr; //item
/**
This function adds the items to the file of items.
*/
void writeItem()
{
	cout << "\n\n\n\tAdd an item to the inventory."<<endl;
	fp.open("Inventory.dat", ios::out | ios::app);
	pr.createItem();
	fp.write((char*)&pr, sizeof(item));
	fp.close();
	cout << "\n\nThe item has been added successfully! ";

}

/**
This function shows all the items in the inventory.
*/
void showAll() {
	cout << "\n\n\n\t\tShowing all the items in inventory\n\n";
	fp.open("Inventory.dat", ios::in);
	while (fp.read((char*)&pr, sizeof(item)))
	{
		pr.showItem();
		cout << "\n\n====================================\n";

	}
	fp.close();
}
/** 
This function shows a specific item from the inventory.
It is looked up using the ID.
*/
void showRecord(string rec) {
	cout << "\n\n\n\tSearch for an item"<<endl;
	int flag = 0;
	fp.open("Inventory.dat", ios::in);
	while (fp.read((char*)&pr, sizeof(item)))
	{
		if (pr.getId().compare(rec) == 0)
		{
			flag = 1;
			cout << "" << endl;
           pr.showItem();
			
		}
	}
	fp.close();
	if (flag == 0)
		cout << "\n\n\tSorry! We do not have the item.";
}
void updateItem()
{
	string no;
    int found = 0;
	cout << "\n\n\n\tUpdate Record"<<endl;
	cout << "Please enter the product ID: ";
	cin >> no;
	fp.open("Inventory.dat", ios::in | ios::out);
	while (fp.read((char*)&pr, sizeof(item)) && found == 0)
	{
		if (pr.getId().compare(no)==0)
		{
			pr.showItem();
			cout << "\nPlease enter the new details here:" << endl;
			pr.createItem();
			int pos = 1 * sizeof(pr);
			fp.seekp(pos, ios::cur);
			fp.write((char*)&pr, sizeof(item));
			cout << "\n\n\t Record updated successfully!";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
		cout << "\n\n We could not find the record to update.";
}
void placeOrder()
{
	string order_arr[50];
	int quan[50], c = 0;
	float amt, damt, total = 0;
	char ch = 'Y';
	//menu();
	cout << "\n============================";
	cout << "\n Place your order here.";
	cout << "\n============================\n";
	do
	{
		cout << "\n\nEnter the name of the product : ";
		cin >> order_arr[c];
		cout << "\nEnter the quantity (max 15) : ";
		cin >> quan[c];
		c++;
		cout << "\nDo you want to order another items ? (y/n)";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << "\n\nThank You For Placing The Order";


	cout << "\n\n************************** Here Is Your Bill ************************\n";
	cout << "\nItem Id\tItem Name\tQuantity \tPrice \tAmount \tAmount after discount\n ";
	for (int x = 0; x <= c; x++)
	{
		fp.open("Inventory.dat", ios::in);
		fp.read((char*)&pr, sizeof(item));
		while (!fp.eof())
		{
			if (pr.getName().compare( order_arr[x]) ==0)
			{
				amt = pr.getPrice() * quan[x];
				damt = amt - (amt * pr.getDisc() / 100);
				cout << "\n" << pr.getId() << "\t" << pr.getName() <<
					"\t\t" << quan[x] << "\t\t" << pr.getPrice() << "\t" << amt << "\t\t" << damt;
				total += damt;
			}
			
			fp.read((char*)&pr, sizeof(item));
		}

		fp.close();
	}
	cout << "\n\n\t\t\t\t\tYour Total is :$  " << total;

}

void deleteItem() {
	string no;

	cout << "\n\n\n\tDelete Record"<<endl;
	cout << "\n\nPlease enter the ID of the item to be deleted: ";
	cin >> no;
	fp.open("Inventory.dat", ios::in | ios::out);
	fstream fp2;
	fp2.open("Temp.dat", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&pr, sizeof(item)))
	{
		if (pr.getId().compare(no) != 0)
		{
			fp2.write((char*)&pr, sizeof(item));
		}
	}
	fp2.close();
	fp.close();
	remove("Inventory.dat");
	rename("Temp.dat", "Inventory.dat");
	cout << "\n\n\n\tItem removed!";
}
void admin() {
	char ch2;
	string name;
	cout << "\n\n\n\tThis is the admin menu";
	cout << "\n\n\t1.Add a new item";
	cout << "\n\n\t2.Show all items in inventory";
	cout << "\n\n\t3.Search item by ID ";
	cout << "\n\n\t4.Modify an item";
	cout << "\n\n\t5.Delete an item";
	cout << "\n\n\tPlease Enter Your Choice (1-5) ";
	cin >> ch2;
	switch (ch2)
	{
	case '1':

		writeItem();
		break;
	case '2':
		showAll();
		break;
	case '3':
		cout << "\n\n\tPlease enter product ID:  ";
		cin >> name;
		showRecord(name);
		break;
	case '4':
		updateItem();
		break;
	case '5':
		deleteItem();
		break;
	default:
		cout << "\a";
		//admin_menu();
	}
}

void main()
{
	char ch;

	do
	{

		cout << "\n\n\n\tWelcome to Jumbo Grocery Store. This is our main menu.";
		cout << "\n\n\t1. CUSTOMER MENU";
		cout << "\n\n\t2. ADMINISTRATOR MENU";
		cout << "\n\n\t3. EXIT";
		cout << "\n\n\tPlease Select Your Option (1-3) ";
		cin >> ch;
		switch (ch)
		{
		case '1':
			placeOrder();
			break;
		case '2':
			admin();
			break;
		case '3':
			cout << "\n\n\tThank you for shopping. See you later!"<< endl;
			exit(0);
		default:
			cout << "\a";
		}
	} while (ch != '3');
}