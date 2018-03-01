#include <iostream>
using namespace std;
#include <fstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <string>
#include <ctime>
#include <unistd.h>
#include <cmath>
#include "EmployeeHashData.h"

//Max size of Hash Table
const int TableSize = 37;

//-|----------------------------------
//-| 1. Construct a New Hash Table
//-|----------------------------------
HashRecords :: HashRecords()
{
	//Initialize TotalAnnualSalary & TotalRecords to 0
	TotalAnnualSalary = 0.00;
    TotalRecords = 0;

	//Create a New Hash Table with 37 elements
	LinkedHash = new HashNode*[TableSize];
	
	//Assign all 37 records & CollisionCount[] to NULL
	for(int i = 0; i < TableSize; i++)
	{
		LinkedHash[i] = NULL;
		CollisionCount[i] = 0;
	}//for
}//HashRecords() 


//-|--------------------------------
//-| 2. Read Records from a File
//-|--------------------------------
void HashRecords :: ReadRecords()
{
	//Declare variables
	ifstream inF; //Variable for Input File                 
	char last_name6[15]; //Variable for Last Name
	char first_name6[15]; //Variable for First Name
	unsigned int account_num6; //Variable for Account Number
	unsigned int month6; //Variable for Month
	unsigned int day6; //Variable for Day
	unsigned int year6; //Variable for Year
	float annual_salary6; //Variable for Annual Salary
	char dept_code6; //Variable for Department Code
	char phone_number6[12];//Variable for Phone Number

	//Open File
	inF.open("Data.txt");
	
	//Test File For Error
	if(inF.fail())
	{
		   cout << endl << "FATAL ERROR: UNABLE TO OPEN FILE \"Data.txt\". TERMINATING..."
                << endl << endl;
           exit (1);
	}//if
	else
	{
		while(inF >> last_name6 >> first_name6 >> account_num6 >> month6 >> day6 >> year6 >> annual_salary6 >> dept_code6 >> phone_number6)
		{
			//Validate That Annual Salary is Greater than 0
			if(annual_salary6 < 0.0)
				continue;
			
			//Capitalize dept_code3
			dept_code6 = toupper(dept_code6);
			
			//Add One TotalRecords
		    TotalRecords++;
			
			//Add annual_salary6 to TotalAnnualSalary
			TotalAnnualSalary += annual_salary6;
		
			//Send Data to Insert() Function
			Insert(last_name6, first_name6, account_num6, month6, day6, year6, annual_salary6, dept_code6, phone_number6);
		}//while
	}//else	  
	//Create ofstream OutF
	ofstream OutF;
	OutF.open("HashTableOutPut.txt");
	//Call PrintSubtitle() Function
	PrintSubtitles(OutF);
	//Call Print() Function
	Print(OutF);
	//Call PrintTotalAnnualSalary() Function
	PrintTotalAnnualSalary(OutF);
	//Print TotalRecords() Function
	PrintTotalRecords(OutF);
}//ReadRecords

//-|-----------------------------------------------------------
//-| 3. Generate Location for Account Number to Be Stored In
//-|-----------------------------------------------------------
int HashRecords :: HashFunction(int key)
{
	  //Compute & Return Index to Insert Function
	  return key % TableSize;
}//HashFunction
			  
//-|---------------------------------
//-| 4. Insert Records into Table
//-|---------------------------------
void HashRecords :: Insert(char last_name2[15],char first_name2[15], unsigned int account_num2, unsigned int month2, unsigned int day2,
		            unsigned int year2, float annual_salary2, char dept_code2, char phone_number2[12])
{
	//Create a new Node to Hold Inserted Data
	HashNode *newNode = new HashNode (last_name2, first_name2, account_num2, month2, day2,
		                              year2, annual_salary2, dept_code2, phone_number2, NULL);
	
	//Create Hash Key
	int Hash_Key = HashFunction(account_num2);
	
	//Check for Unused Slot, IF NULL, Insert Data into Slot
	if(LinkedHash[Hash_Key] == NULL)
	{
		//Insert Data Into Slot
		LinkedHash[Hash_Key] = newNode;
	}//if
	
	//Else, There is a collision, so, add data in the chain
	else
	{
		//Create a temp Node
		HashNode *tempEntry = new HashNode;
		tempEntry = LinkedHash[Hash_Key];
		
		//Traverse through chain to find the next empty slot
		while(tempEntry->next != NULL)
		{
			tempEntry = tempEntry->next;
		}//while
		
		//Once a Empty Slot is Found, input data into the slot
		tempEntry->next = newNode;
		
		//Add 1 to CollisionCount
		CollisionCount[Hash_Key]++;
	}//else
}//Insert

//-|----------------------------------------------------------------
//-| 5. Function to convert the Month number into its abbreviation
//-|----------------------------------------------------------------
string HashRecords :: Date(unsigned int month3)
{
   //Declare Array To Hold Month Abbreviation
   const string DateAbbr[12] = {"Jan. ", "Feb. ", "Mar. ", "Apr. ", 
		                        "May ", "Jun. ", "Jul. ", "Aug. ", 
						        "Sep. ", "Oct. ", "Nov. ", "Dec. "};
	
   //Convert Month into Abbreviation
   switch(month3)
   {
	   case 1:  return DateAbbr[0];
		        break;
	   case 2:  return DateAbbr[1];
		        break;
	   case 3:  return DateAbbr[2];
		        break;
	   case 4:  return DateAbbr[3];
			    break;
	   case 5:  return DateAbbr[4];
		        break;
	   case 6:  return DateAbbr[5];
			    break;
	   case 7:  return DateAbbr[6];
			    break;
	   case 8:  return DateAbbr[7];
			    break;
	   case 9:  return DateAbbr[8];
		        break;
	   case 10: return DateAbbr[9];
			    break;
	   case 11: return DateAbbr[10];
				break;
	   case 12: return DateAbbr[11];
				break;
	   default: return ("Wrong Month Inserted....");
		        break;
   }//Switch
}//Date
			  
//-|-------------------------
//-| 6. Get Today's Date
//-|-------------------------
void HashRecords :: GetDate(unsigned int &Month4, unsigned int &Day4, unsigned int &Year4)
{
	//Get Today's Date
	time_t t = time(0);
	tm* ltm = localtime(&t);
	
	//Assign Today's Month, Day, & Year
	Month4 = (ltm->tm_mon + 1);
	Day4 = ltm->tm_mday;
	Year4 = (ltm->tm_year + 1900);
}//GetDate

//-|----------------------------
//-| 7. Get Age of Employee
//-|----------------------------
int HashRecords :: GetAge(unsigned int &Month5, unsigned int &Day5, unsigned int &Year5)
{
	//Declare Variables
	unsigned int Month2, Day2, Year2;
	
	//Call GetDate()
	GetDate(Month2, Day2, Year2);
	
	//Declare Array to Hold Employee's Birthday
	unsigned int Date1[] = {Month5, Day5, Year5};
	
	//Declare Array to Hold Today's Date
	unsigned int Date2[] = {Month2, Day2, Year2};

	//Subtract Date From Given Date
    tm a = {0,0,0,Day5,Month5,Year5};
	tm b = {0,0,0,Day2,Month2,Year2};
	time_t x = mktime(&a);
	time_t y = mktime(&b);
	
	//Get Employee's Birthday
	if(x != (time_t)(-1) && y != (time_t)(-1))
	{
		    //Declare Variables to Convert Employee's Birthday into Their Age
            double difference = difftime(y,x)/(60*60*24);
		    int rounding = (int)round(difference);
			int year = rounding/365;
			int days = rounding%365;
			int months = days/30;
		
			//Convert The Date into Age
			if(year >= 1 && months >= 6 && days >= 183)
				return (year+1);
		    else if(year >= 1 && months <= 5 && days <= 182)
				return (year);
		    else
				return 0;
	}//if
}//GetAge()
			  
//-|----------------------			 
//-| 8. Print Subtitles
//-|----------------------
void HashRecords :: PrintSubtitles(ostream& OutF)
{ 
	//Print Title & Subtitles
	OutF << setw(66) << "Employee Report" << endl;
	OutF << setw(66) << "***************" << endl << endl;
	OutF << left << "Last Name" << right << setw(16) << "Acct. Number" 
		 << right << setw(24) << "Date of Birth" << right << setw(24) << "Annual Salary"
		 << right << setw(23) << "Department Code" << right << setw(12) << "Age" << endl; 
		
}//PrintSubtitles
			  
//-|-------------------------
//-| 9. Print Total Records
//-|-------------------------
void HashRecords :: PrintTotalRecords(ostream& OutF)
{
	//Print the Total Records
	OutF << endl << endl << left << "Total Record Count: " << TotalRecords << endl << endl << endl;
}//PrintTotalRecords
			  
//-|-------------------------------			  
//-| 10. Print Total Annual Salary
//-|-------------------------------
void HashRecords :: PrintTotalAnnualSalary(ostream& OutF)
{
	//Print the Annual Salary
	OutF << endl << endl << left << "Total Annual Salary: " << TotalAnnualSalary;
}//PrintTotalAnnualSalary
			    
//-|-----------------------------
//-| 11. Print HashRecords Table
//-|-----------------------------
void HashRecords :: Print(ostream& OutF)
{
	//Declare Variable
	int CollisionSize = 0; //Hold the Count of How Many Collisions That They Are

	//Create a Temp Node
	HashNode *Temp = new HashNode;
	
	cout << endl;
	
	//Print Out Contents of Hash Table
	for(int i = 0; i < TableSize; i++)
	{
		//Assign CollisionSize to CollisionCount[i]
		CollisionSize = CollisionCount[i];

		//Assign Temp to first element of Hash Table
		Temp = LinkedHash[i];
		
		//Check for if CollisionSize > 0
		if(CollisionSize > 0)
		{
		   //Call PrintFirstData()
		   PrintFirstData(Temp, OutF);
					
		   //Print Collision Data
		   PrintDataCollisions(Temp, OutF);
		}//if
		
		//Else, Print the First Slot Data
		else
		{
			//Call PrintFirstData()
			PrintFirstData(Temp, OutF);		
		}//else
	}//for
}//Print
			 
//-|-------------------------------------------------
//-| 12. Delete Memory for ALL Internal Components
//-|-------------------------------------------------
HashRecords :: ~HashRecords()
{
	//Declare a Temp & Current Node
	HashNode * Current, *Temp;
	 
	//Delete The Hash Map
	for(int i = 0; i < TableSize; i++)
	{
		//Check for if Hash Map Position is NULL
		if(LinkedHash[i] != NULL)
		{
			//Assign Current to LinkedHash[i]
			Current = LinkedHash[i];
			
			//Traverse through the Table to Delete each position
			while(Current != NULL)
			{
				Temp = Current;
				Current = Current->next;
				delete Temp;
			}//while
		}//if
	}//for
}//HashRecords Destructor

//-|------------------------------------------
//-| 13. PrintData Depending on Collisions
//-|------------------------------------------
void HashRecords :: PrintDataCollisions(HashNode *Temp, ostream& OutF)
{				    			
		//Move to Next Node BEFORE entering While Loop
		Temp = Temp->next;
	
	    //While Temp != NULL, Print out the CCollision ontents
		while(Temp != NULL)
		{
			OutF << left << Temp->last_name << "\t\t\t"; 
		    OutF << '*'<< setfill('0') << right << setw(4) << Temp->account_num;
		    OutF << setfill(' ') << right << setw(20) << Date(Temp->month);
			OutF << setfill('0') << setw(2) << Temp->day << ", " << Temp->year;
			OutF << setfill(' ') << right << setw(21) << fixed << setprecision(2) << Temp->annual_salary;
		    OutF << right << setw(19) << Temp->dept_code;
			OutF << right << setw(19) << GetAge(Temp->month, Temp->day, Temp->year) << endl; 
			
			//Move to Next Node
			Temp = Temp->next;
		}//while
}//PrintData8Collisions

//-|----------------------------------------
//-| 14. Print the Data in the First Slot
//-|----------------------------------------
void HashRecords :: PrintFirstData(HashNode* Temp, ostream& OutF)
{
		//If Temp != NULL, Print out the Contents
		if(Temp != NULL)
		{
			OutF << left << Temp->last_name << "\t\t\t";		    
			OutF << " " << setfill('0') << right << setw(4) << Temp->account_num;
		    OutF << setfill(' ') << right << setw(20) << Date(Temp->month);
			OutF << setfill('0') << setw(2) << Temp->day << ", " << Temp->year;
			OutF << setfill(' ') << right << setw(21) << fixed << setprecision(2) << Temp->annual_salary;
		    OutF << right << setw(19) << Temp->dept_code;
			OutF << right << setw(19) << GetAge(Temp->month, Temp->day, Temp->year)<< endl; 
				    			
		    //Move to Next Node
		    Temp = Temp->next;
		}//if
}//PrintFirstData()