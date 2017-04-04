#ifndef _PRINTER_H_
#define _PRINTER_H_

_Monitor Printer
{
	// TODO: Should never be thrown, just a safeguard to ensure our code does not do something wrong
	_Event InvalidOperation {};

	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;

	// The buffer used for the types that are will only have one running
	char *single_Buffer;
	int *single_Value1Buffer;
	int *single_Value2Buffer;

	char *student_Buffer;
	int *student_Value1Buffer;
	int *student_Value2Buffer;

	char *vending_Buffer;
	int *vending_Value1Buffer;
	int *vending_Value2Buffer;

	char *courier_Buffer;
	int *courier_Value1Buffer;
	int *courier_Value2Buffer;

	void resetBuffer();
	void flush();
  public:
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
  private:
    // Used to converge the multiple print functions into a single function
	void storeSingleKind(Kind kind, char state, int value1 = 0, int value2 = 0);
	void storeMultiKind(Kind kind, unsigned int lid, char state, int value1 = 0, int value2 = 0);
	void finishFlush(Kind kind, unsigned int lid = 0);
	void printTabs(char state, unsigned int &n);
};

#endif
