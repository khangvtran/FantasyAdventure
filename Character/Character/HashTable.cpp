/*
 * HashTable.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: Khang Vinh Tran, Tri Doan
 */


# include "HashTable.h"
/************* Access Functions *************/
int HashTable::hash(string key) const
{
    int index, sum = 0;
    for(int i = 0; i < key.length(); i++)
        sum += (int) key[i]; //summing the ASCII values for each character in the string
    index = sum % SIZE; //dividing the summed ASCII values by 35 && storing remainder as my index
    return index;
}

int HashTable::countBucket(int index) const
{
	assert(index >= 0);
	assert(index < SIZE);
	return Table[index].getSize();
}

int HashTable::search(Book b) const
{
	string key = b.get_title() + b.get_author();
	int index = hash(key);

	if (Table[index].isEmpty()) return -1;
	else if (Table[index].linearSearch(b) == -1) return -1;
	else return index;
}

void HashTable::printBucket(ostream& out, int index) const
{
	assert(index >= 0);
	assert(index < SIZE);
	Table[index].print();
}


void HashTable::printTable(ostream& out) const
{
	out << "Books in the Catalogue:" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		if (!Table[i].isEmpty())
		{
			out << "Group " << i+1 << endl;
			out << Table[i].getStart() << endl;
			out << "+" << countBucket(i) - 1 <<" more similar book(s)" << endl << endl << endl;
			//cout << "+" << Table.countBucket(i) - 1 <<" more similar book(s)" << endl << endl << endl;
		}
	}
}
# include "HashTable.h"



/************* Manipulation Procedures *************/

void HashTable::insert(Book b)
{
	string key = b.get_title() + b.get_author();
	int index = hash(key);
	Table[index].insertStop(b);
}

void HashTable::remove(Book b)
{
//removes b from the table
//calls the hash function on the key to determine
//the correct bucketƒ
//pre: b is in the table
	assert(search(b) != -1);
	int index = search(b);
	int Index_In_Bucket = Table[index].linearSearch(b);
	Table[index].pointIterator();
	for (int i = 1; i < Index_In_Bucket; i++)
	{
		Table[index].advanceIterator();
	}
	Table[index].removeIterator();

}
