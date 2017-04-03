#include "NameServer.h"
#include "VendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ):
						printer(&prt),numVendingMachines(numVendingMachines),numStudents(numStudents)
{
	vendingMachines = new VendingMachine*[numVendingMachines];
	getIndexStudent = new unsigned int[numVendingMachines];
	for (unsigned int i = 0;i < numStudents;i++)
		getIndexStudent[i] = i % numVendingMachines;
}

NameServer::~NameServer()
{
	delete[] vendingMachines;
	delete[] getIndexStudent;
}

void NameServer::main()
{
	printer->print(Printer::Kind::NameServer, 'S');


	// Setting up all the initial vending machines that each student will receive
	unsigned int getIndexStudent[numStudents];


	// Allow all vending machines to register immediately before letting others do work
	for (unsigned int i = 0;i < numVendingMachines;i++)
	{
		_Accept(VMregister)
		{
			vendingMachines[i] = recentlyRegisteredVM;
			printer->print(Printer::Kind::NameServer, 'R', i);
		}
	}

	NameServerLoop: while (true)
	{
		_Accept(~NameServer)
		{
			break NameServerLoop;
		}
		or _Accept(getMachine)
		{
			printer->print(Printer::Kind::NameServer, 'N', getIndexStudent[recentStudentIdRequest]);
			getIndexStudent[recentStudentIdRequest] = (getIndexStudent[recentStudentIdRequest] + 1) % numVendingMachines;
		}
		or _Accept(getMachineList)
		{}
	}
	printer->print(Printer::Kind::NameServer, 'F');
}

void NameServer::VMregister(VendingMachine *vendingmachine)
{
	recentlyRegisteredVM = vendingmachine;
}

VendingMachine *NameServer::getMachine( unsigned int id )
{
	recentStudentIdRequest = id;
	return vendingMachines[getIndexStudent[id]];
}

VendingMachine **NameServer::getMachineList()
{
	return vendingMachines;
}
