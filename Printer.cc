#include "Printer.h"
#include <iostream>

using namespace std;

#define STATE_UNDEFINED '~'

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ):
		numStudents(numStudents),numVendingMachines(numVendingMachines),numCouriers(numCouriers)
{
	single_Buffer = new char[Kind::Student];
	single_Value1Buffer = new int[Kind::Student];
	single_Value2Buffer = new int[Kind::Student];

	student_Buffer = new char[numStudents];
	student_Value1Buffer = new int[numStudents];
	student_Value2Buffer = new int[numStudents];

	vending_Buffer = new char[numVendingMachines];
	vending_Value1Buffer = new int[numVendingMachines];
	vending_Value2Buffer = new int[numVendingMachines];

	courier_Buffer = new char[numCouriers];
	courier_Value1Buffer = new int[numCouriers];
	courier_Value2Buffer = new int[numCouriers];

	// Printing the header
	cout << "Parent" << '\t';
	cout << "Gropoff" << '\t';
	cout << "WATOff" << '\t';
	cout << "Names" << '\t';
	cout << "Truck" << '\t';
	cout << "Plant" << '\t';
	for (unsigned int i = 0;i < numStudents;i++)
		cout << "Stud" << i << '\t';
	for (unsigned int i = 0;i < numVendingMachines;i++)
		cout << "Mach" << i << '\t';
	for (unsigned int i = 0;i < numCouriers;i++)
		cout << "Cour" << i << '\t';
	cout << endl;
	for (unsigned int i = 0; i < Kind::Student;i++)
		cout << "*******" << '\t';
	for (unsigned int i = 0; i < numStudents;i++)
		cout << "*******" << '\t';
	for (unsigned int i = 0; i < numVendingMachines;i++)
		cout << "*******" << '\t';
	for (unsigned int i = 0; i < numCouriers;i++)
		cout << "*******" << '\t';
	cout << endl;

	resetBuffer();
}

Printer::~Printer()
{
	flush();

	delete single_Buffer;
	delete single_Value1Buffer;
	delete single_Value2Buffer;

	delete student_Buffer;
	delete student_Value1Buffer;
	delete student_Value2Buffer;

	delete vending_Buffer;
	delete vending_Value1Buffer;
	delete vending_Value2Buffer;

	delete courier_Buffer;
	delete courier_Value1Buffer;
	delete courier_Value2Buffer;
}

void Printer::resetBuffer()
{
	for (unsigned int i = 0;i < (unsigned int)Kind::Student;i++)
		single_Buffer[i] = STATE_UNDEFINED;

	for (unsigned int i = 0;i < numStudents;i++)
		student_Buffer[i] = STATE_UNDEFINED;

	for (unsigned int i = 0;i < numVendingMachines;i++)
		vending_Buffer[i] = STATE_UNDEFINED;

	for (unsigned int i = 0;i < numCouriers;i++)
		courier_Buffer[i] = STATE_UNDEFINED;
}

void Printer::flush()
{
	// NOTE : Implemented the 'F' cases of each type, but 'F' should not pass through here!
	switch (single_Buffer[Kind::Parent])			// Parent
	{
		case 'D':
			cout << single_Buffer[Kind::Parent] << single_Value1Buffer[Kind::Parent] << ',' << single_Value2Buffer[Kind::Parent];
			break;
		case 'S':
		case 'F':
			cout << single_Buffer[Kind::Parent];
			break;
	}
	cout << '\t';

	switch (single_Buffer[Kind::Groupoff])			// Groupoff
	{
		case 'D':
			cout << single_Buffer[Kind::Groupoff] << single_Value1Buffer[Kind::Groupoff];
			break;
		case 'S':
		case 'F':
			cout << single_Buffer[Kind::Groupoff];
			break;
	}
	cout << '\t';

	switch (single_Buffer[Kind::WATCardOffice])		// WATCardOffice
	{
		case 'C':
		case 'T':
			cout << single_Buffer[Kind::WATCardOffice] << single_Value1Buffer[Kind::WATCardOffice] << ',' << single_Value2Buffer[Kind::WATCardOffice];
			break;
		case 'S':
		case 'W':
		case 'F':
			cout << single_Buffer[Kind::WATCardOffice];
			break;
	}
	cout << '\t';

	switch (single_Buffer[Kind::NameServer])		// NameServer
	{
		case 'N':
			cout << single_Buffer[Kind::NameServer] << single_Value1Buffer[Kind::NameServer] << ',' << single_Value2Buffer[Kind::NameServer];
			break;
		case 'R':
			cout << single_Buffer[Kind::NameServer] << single_Value1Buffer[Kind::NameServer];
			break;
		case 'S':
		case 'F':
			cout << single_Buffer[Kind::NameServer];
			break;
	}
	cout << '\t';

	switch (single_Buffer[Kind::Truck])				// Truck
	{
		case 'd':
		case 'U':
		case 'D':
			cout << single_Buffer[Kind::Truck] << single_Value1Buffer[Kind::Truck] << ',' << single_Value2Buffer[Kind::Truck];
			break;
		case 'P':
			cout << single_Buffer[Kind::Truck] << single_Value1Buffer[Kind::Truck];
			break;
		case 'S':
		case 'F':
			cout << single_Buffer[Kind::Truck];
			break;
	}
	cout << '\t';

	switch (single_Buffer[Kind::BottlingPlant])		// Bottling Plant
	{
		case 'G':
			cout << single_Buffer[Kind::BottlingPlant] << single_Value1Buffer[Kind::BottlingPlant];
			break;
		case 'S':
		case 'F':
		case 'P':
			cout << single_Buffer[Kind::BottlingPlant];
			break;
	}
	cout << '\t';

	for (unsigned int i = 0;i < numStudents;i++)	// Student
	{
		switch (student_Buffer[i])
		{
			case 'S':
			case 'G':
			case 'B':
				cout << student_Buffer[i] << student_Value1Buffer[i] << ',' << student_Value2Buffer[i];
				break;
			case 'V':
				cout << student_Buffer[i] << student_Buffer[i];
				break;
			case 'L':
			case 'F':
				cout << student_Buffer[i];
				break;
		}
		cout << '\t';
	}

	for (unsigned int i = 0;i < numVendingMachines;i++)	// Vending Machine
	{
		switch (vending_Buffer[i])
		{
			case 'G':
			case 'B':
				cout << vending_Buffer[i] << vending_Value1Buffer[i] << ',' << vending_Value2Buffer[i];
				break;
			case 'S':
				cout << vending_Buffer[i] << vending_Value1Buffer[i];
				break;
			case 'r':
			case 'R':
			case 'F':
				cout << vending_Buffer[i];
				break;
		}
		cout << '\t';
	}

	for (unsigned int i = 0;i < numCouriers;i++)	// Courier
	{
		switch (courier_Buffer[i])
		{
			case 't':
			case 'T':
				cout << courier_Buffer[i] << courier_Value1Buffer[i] << ',' << courier_Value2Buffer[i];
				break;
			case 'L':
				cout << courier_Buffer[i] << courier_Value1Buffer[i];
				break;
			case 'S':
			case 'F':
				cout << courier_Buffer[i];
				break;
		}
		cout << '\t';
	}

	cout << endl;

	resetBuffer();
}

void Printer::finishFlush(Kind kind, unsigned int lid)
{
	for (int i = 0;i <= (int)Kind::BottlingPlant;i++)
	{
		if (i == (int)kind)
			cout << 'F';
		else
			cout << "...";
		cout << '\t';
	}
	for (unsigned int j = 0;j < numStudents;j++)
	{
		if (Kind::Student == (int)kind && j == lid)
			cout << 'F';
		else
			cout << "...";
		cout << '\t';
	}
	for (unsigned int j = 0;j < numVendingMachines;j++)
	{
		if (Kind::Vending == (int)kind && j == lid)
			cout << 'F';
		else
			cout << "...";
		cout << '\t';
	}
	for (unsigned int j = 0;j < numCouriers;j++)
	{
		if (Kind::Courier == (int)kind && j == lid)
			cout << 'F';
		else
			cout << "...";
		cout << '\t';
	}
	cout << endl;
}

void Printer::storeSingleKind(Kind kind, char state, int value1, int value2)
{
	// TODO: Should never occur, but just safeguarding this
	if ((int)kind >= (int)Kind::Student)
	{
		cerr << "FAILED: storeSingleKind(" << kind << ',' << state << ',' << value1 << ',' << value2 << ')' << endl;
		_Throw InvalidOperation();
	}

	// Special scenario, where finishes are on its own special line
	if (state == 'F')
	{
		flush();
		finishFlush(kind);
		return;
	}

	if (single_Buffer[(int)kind] != STATE_UNDEFINED)
		flush();

	single_Buffer[(int)kind] = state;
	single_Value1Buffer[(int)kind] = value1;
	single_Value2Buffer[(int)kind] = value2;
}

void Printer::storeMultiKind(Kind kind, unsigned int lid, char state, int value1, int value2)
{
	// TODO: Should never occur, but just safeguarding this
	if ((int)kind <= (int)Kind::BottlingPlant)
	{
		cerr << "FAILED: storeMultiKind(" << kind << ',' << state << ',' << value1 << ',' << value2 << ')' << endl;
		_Throw InvalidOperation();
	}

	// Special scenario, where finishes are on its own special line
	if (state == 'F')
	{
		flush();
		finishFlush(kind, lid);
		return;
	}

	switch (kind)
	{
		case (Kind::Student):
			if (student_Buffer[lid] != STATE_UNDEFINED)
				flush();
			student_Buffer[lid] = state;
			student_Value1Buffer[lid] = value1;
			student_Value2Buffer[lid] = value2;
			break;
		case (Kind::Vending):
			if (student_Buffer[lid] != STATE_UNDEFINED)
				flush();
			vending_Buffer[lid] = state;
			vending_Value1Buffer[lid] = value1;
			vending_Value2Buffer[lid] = value2;
			break;
		case (Kind::Courier):
			if (student_Buffer[lid] != STATE_UNDEFINED)
				flush();
			courier_Buffer[lid] = state;
			courier_Value1Buffer[lid] = value1;
			courier_Value2Buffer[lid] = value2;
			break;
		default:
			break;
	}
}

void Printer::print(Kind kind, char state)
{
	storeSingleKind(kind, state);
}

void Printer::print(Kind kind, char state, int value1)
{
	storeSingleKind(kind, state, value1);
}

void Printer::print(Kind kind, char state, int value1, int value2)
{
	storeSingleKind(kind, state, value1, value2);
}

void Printer::print(Kind kind, unsigned int lid, char state)
{
	storeMultiKind(kind, lid, state);
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1)
{
	storeMultiKind(kind, lid, state, value1);
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1, int value2)
{
	storeMultiKind(kind, lid, state, value1, value2);
}
