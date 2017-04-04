#include "Config.h"
#include "NameServer.h"
#include "VendingMachine.h"
#include "Student.h"
#include "GroupOff.h"
#include "Parent.h"
#include "Bank.h"
#include "BottlingPlant.h"
#include "WATCardOffice.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

void usageError(string cmd)
{
	cerr << "Usage: " << cmd << " [ config-file [ random-seed (> 0) ] ]" << endl;
	exit(EXIT_FAILURE);
}

void uMain::main()
{
	string configFile = "soda.config";
	unsigned int seed = getpid();

	// Getting values from command line parameters (if any)
	if (argc > 3) usageError(argv[0]);
	switch (argc)
	{
		case 3:
		{
			int i;
			stringstream ss(argv[2]);
			if (!(ss >> i) || i < 0)
				usageError(argv[0]);
			seed = (unsigned int)i;
		}
		case 2:
			configFile = argv[1];
		default:
			break;
	}

	// Setting up command line parameter related values
	RandomGenerator *rng = &RandomGenerator::getInstance();
	rng->generator.set_seed(seed);
	ConfigParms configuration;
	processConfigFile(configFile.c_str(), configuration);

	// In case we want to use it
#ifdef __U_MULTI__
	uProcessor p[3] __attribute__(( unused )); // create 3 kernel thread for a total of 4
#endif

	/* Setting up the entire soda process
	 * NOTE: Using pointers because order of deletion is different than initialization
	 */
	Printer printer(configuration.numStudents, configuration.numVendingMachines, configuration.numCouriers);

	// Production-related setup
	NameServer *nameServer = new NameServer(printer, configuration.numVendingMachines, configuration.numStudents);
	VendingMachine *vendingMachines[configuration.numVendingMachines];
	for (unsigned int i = 0;i < configuration.numVendingMachines;i++)
	{
		vendingMachines[i] = new VendingMachine(printer, *nameServer, i, configuration.sodaCost, configuration.groupoffDelay);
	}
	BottlingPlant *bottlingPlant = new BottlingPlant(printer, *nameServer, configuration.numVendingMachines, configuration.maxShippedPerFlavour,
			configuration.maxStockPerFlavour, configuration.timeBetweenShipments);

	// Financial-related setup
	Bank *bank = new Bank(configuration.numStudents);
	Parent *parent = new Parent(printer, *bank, configuration.numStudents, configuration.parentalDelay);
	WATCardOffice *watCardOffice = new WATCardOffice(printer, *bank, configuration.numCouriers);
	Groupoff *groupoff = new Groupoff(printer, configuration.numStudents, configuration.sodaCost, configuration.groupoffDelay);

	// Consumption-related setup
	Student *students[configuration.numStudents];
	for (unsigned int i = 0;i < configuration.numStudents;i++)
	{
		students[i] = new Student(printer, *nameServer, *watCardOffice, *groupoff, i, configuration.maxPurchases);
	}

	// Waiting for soda process to end
	for (unsigned int i = 0;i < configuration.numStudents;i++)
	{
		delete students[i];
	}
	delete bottlingPlant;
	delete nameServer;
	for (unsigned int i = 0;i < configuration.numVendingMachines;i++)
	{
		delete vendingMachines[i];
	}
	delete groupoff;
	delete watCardOffice;
	delete parent;
	delete bank;
}
