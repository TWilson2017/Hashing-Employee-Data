//------------------------------------------------------------------
// File name:   HashingMain.cpp
// Assign ID:   Project 4A 
// Due Date:    03/01/2018 at 12:30 pm
//
// Purpose:     Write a C++ program that inputs an unknown number of records stored on a sequential file.
//              Write a C++ program to create a hash table (containing 37 slots to store records) store the
//              records using account_num as the key field. Use the method called chaining to handle collisions. 
//       
// Author:      Tishauna Wilson
//------------------------------------------------------------------
#include "EmployeeHashData.cpp"
using namespace std;

int main()
{
	
   //Declare Variables
   HashRecords Data; 

   //-| ----------------------------------------------------------------------
   //-| Print the copyright notice declaring authorship.
   //-| ----------------------------------------------------------------------
   cout << endl << "(c) 2018, Tishauna Wilson" << endl << endl; 

   //-| ----------------------------------------------------------------------
   //-| 1. Call ReadRecord() Function
   //-| ----------------------------------------------------------------------
   Data.ReadRecords();

   //-| ----------------------------------------------------------------------
   //-| Print the copyright notice declaring authorship again.
   //-| ----------------------------------------------------------------------
   cout << endl << "(c) 2018, Tishauna Wilson" << endl << endl; 

   return 0;
}//main
 
