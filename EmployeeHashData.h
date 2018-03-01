#ifndef HASHRECORDS_H
#define HASHRECORDS_H
#include "HashNode.h"

class HashNode; //HashNode exists without defining it


class HashRecords
{
	private:
		HashNode **LinkedHash; //Variable for HashNode Linked List
		double TotalAnnualSalary; //Variable for Total Annual Salary
		int TotalRecords; //Variable for Total Record Count
		int CollisionCount[37]; //Array to hold how many collisions are in each slot
		
	public:
	        //Construct a New Hash Table
		HashRecords();
		//Read Records from a File
		void ReadRecords(); 
		//Generate Location for Account Number to Be Stored In
		int HashFunction(int key); 
		//Insert Records into Table
		void Insert(char last_name2[15], char first_name2[15], unsigned int account_num2, unsigned int month2, unsigned int day2,
		            unsigned int year2, float annual_salary2, char dept_code2, char phone_number2[12]); 
		//Function to convert the Month number into its abbreviation
		string Date(unsigned int month3);
		//Get Today's Date
		void GetDate(unsigned int &Month4, unsigned int &Day4, unsigned int &Year4);
		//Get Age of Employee
		int GetAge(unsigned int &Month5, unsigned int &Day5, unsigned int &Year5);
		//Print Subtitles
		void PrintSubtitles(ostream& OutF);
		//Print Total Records
		void PrintTotalRecords(ostream& OutF);
		//Print Total Annual Salary
		void PrintTotalAnnualSalary(ostream& OutF);
		//Print HashRecords Table
		void Print(ostream& OutF);
		//PrintData Depending on Collisions
		void PrintDataCollisions(HashNode*, ostream& OutF);
		//Print the Data in the First Slot
		void PrintFirstData(HashNode*, ostream& OutF);
	        //Delete Memory for ALL Internal Components
		~HashRecords();
};//HashRecords
#endif
