// ---------------------------------------------------------------------------
// File name:   travel_algorithm.cpp
//
// Assign ID:   PROG1
//
// Due Date:    9/12/11 at 10 am
//
// Purpose:     Capture student algorithm for PROG1_travel assignment.
//
// Author:      cop3014cjoe Edward Jones
//
// ---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

char unixCmd[100];
char assignID[] = "PROG1b";
char progname[] = "travel";
char ALGMfname[] = "travel.algm";
char BBSfname[] = "travel.bbs";
char ALGMname[] = "TRAVEL";
string algmCAPTION = "TRAVEL ALGORITHM:\n";

#define NINVARS 3
#define INVARS  "Distance","Gallons","GasPrice"
#define NOUTVARS 3
#define OUTVARS  "MPG","GasCost","CostPerMile"
#define NWORKVARS 0
#define WORKVARS  ""
#define NINPUTVERBS 2
#define INPUTVERBS "Read","Get"
#define NOUTPUTVERBS 2
#define OUTPUTVERBS "Write","Display"
#define NCOMPUTEVERBS 2
#define COMPUTEVERBS "Compute","Calculate"
#define NCONTROLVERBS 5
#define CONTROLVERBS "Repeat","If","Then","Else","Otherwise"
#define NSTOPVERBS 1
#define STOPVERBS "Terminate"
#define NOMORE NOMORE


void Feedback(string AStep, string InVars[], int nIn, string OutVars[], int nOut,
              string Verbs[], int nV)
{
    cout << endl << "Feedback: Checking algorithm step: '"
         << AStep << endl << "' ... (Under Construction) " << endl;
}

int main()
{

   // ----------------------------------------------------------------------
   //  Declare variables
   // ----------------------------------------------------------------------
   char unixCmd[100];

   string Algm[100];
   for (int q=0; q<100; q++) Algm[q] = "";

   Algm[0] = algmCAPTION;
   int nSteps = 0;

   strcpy(unixCmd,"CPcopy ");
   strcat(unixCmd, BBSfname);
   system(unixCmd);


   //-| ----------------------------------------------------------
   //-| Use travel algorithm in directory, if present.
   //-| ----------------------------------------------------------
   
   ifstream chekF(ALGMfname);
   if (chekF.fail())
   {
      strcpy(unixCmd,"CS get ");
      strcat(unixCmd, ALGMfname);
      system(unixCmd);
      ifstream chek2F(ALGMfname);
      if (chek2F.fail())
      {
         system("rm -f old_algm");
      }
      else 
      {
         chek2F.close();
         strcpy(unixCmd,"cp ");
         strcat(unixCmd, ALGMfname);
         strcat(unixCmd, " old_algm");
         system(unixCmd);
      }
   }
   else
   {
      chekF.close();
      strcpy(unixCmd,"cp ");
      strcat(unixCmd, ALGMfname);
      strcat(unixCmd, " old_algm");
      system(unixCmd);
   }
       
   system("clear");

   ifstream oldalgmF("old_algm");
   if ( ! oldalgmF.fail() )
   {    
      getline(oldalgmF, Algm[nSteps]);
      if (Algm[nSteps].size() > 7)
          nSteps++;
      while (! oldalgmF.eof() )
      {
         getline(oldalgmF, Algm[nSteps]);
         if (Algm[nSteps].size() > 7)
            nSteps++;
      }
      oldalgmF.close();
   }

   ofstream algmF(ALGMfname);


   //-| ----------------------------------------------------------------------
   //-| Print the copyright notice declaring authorship.
   //-|
   //-|    Copyright contains: unixlogin, First Last
   //-| ----------------------------------------------------------------------
   cout << endl << "(c) 2012, cop3014cjoe Edward Jones" << endl << endl; 

   cout << "PROVIDE THE ALGORITHM FOR THE " << ALGMname << " PROGRAM BELOW:" << endl << endl;

   strcpy(unixCmd, "more ");
   strcat(unixCmd, BBSfname);
   system(unixCmd);

   string InputVariables[] = {INVARS};
   string OutputVariables[] = {OUTVARS};
   string WorkVariables[] = {WORKVARS};
   string Verbs[] = {INPUTVERBS , COMPUTEVERBS , OUTPUTVERBS, STOPVERBS };
   int nInVariables = NINVARS, nOutVariables = NOUTVARS;
   int nVerbs = NINPUTVERBS + NOUTPUTVERBS + NCOMPUTEVERBS + NSTOPVERBS;

   bool stopNow = false;
   char stepStr[8];
   string Digit[] = {"0","1","2","3","4","5","6","7","8","9"};
   string throwaway;
   string Step;
   int step;
   char go;

   while (! stopNow)
   {
      //for (int n = 0; n <= nSteps; n++)
      for (int n = 0; n <= nSteps; n++)
      {
         cout << Algm[n] << endl;
      }

      cout << endl <<  "-------- Enter C to CONTINUE; S to STOP: ";
      cin >> go;
      stopNow = (go == 'S' || go == 's');

      if (! stopNow)
      {
          do
          {
             cout << "Enter STEP# [1.." << nSteps+1 << "]: "; 
             cin >> stepStr; getline(cin,throwaway);
             step = atoi(stepStr); 
          }
          while (step == 0 || step > nSteps+1);
      
          Step = ""; 
          if (step > 10) Step = Step + Digit[step/10];
          Step = Step + Digit[step%10];
          Step = Step + ". ";

          cout << endl << endl;
          cout << "==================" << endl;
          cout << "**** ALGORITHM STEP is an IMPERATIVE statement starting with a VERB." << endl;
          cout << "     VERBS: ";
          for (int v=0; v<nVerbs; v++)
              cout << Verbs[v] << "  ";
          cout << endl << endl;
          cout << "**** ALGORITHM STEP must reference problem VARIABLES. " << endl;
          cout << endl << "     INPUT VARIABLES: ";
          for (int m=0; m<nInVariables; m++)
              cout << InputVariables[m] << "  ";
          cout << endl << "     OUTPUT VARIABLES: ";
          for (int m=0; m<nOutVariables; m++)
              cout << OutputVariables[m] << "  ";
          cout << endl << "==================" << endl << endl;
             
cout << "#STEPS SO FAR = " << nSteps << endl << endl;
          cout << "Enter algorithm STEP: " << Step;
          
          getline(cin, Algm[step]);     

          Feedback(Algm[step], InputVariables, nInVariables, OutputVariables, nOutVariables,
                   Verbs, nVerbs);

          Algm[step] = Step + Algm[step];
          //if (step >= nSteps) nSteps++;
          if (step > nSteps) nSteps++;
      }
      
   } //while
   

   //-| --------------------------------------------------------------------------------------
   //-| Save algorithm.
   //-| --------------------------------------------------------------------------------------
   for (int k = 0; k <= nSteps; k++)
   {
      algmF << Algm[k] << endl;
   }
   algmF.close();


   strcpy(unixCmd,"CSsubmit ");
   strcat(unixCmd, assignID);
   strcat(unixCmd, " ");
   strcat(unixCmd, BBSfname);
   system(unixCmd);
   system("clear");

   //-| ----------------------------------------------------------------------
   //-| Print the copyright notice again.
   //-| ----------------------------------------------------------------------
   cout << endl << "(c) 2012, cop3014cjoe Edward Jones" << endl << endl; 

   cout << endl << endl
        << ALGMname << " ALGORITHM" << endl
        << "=========================" << endl;

   strcpy(unixCmd,"more ");
   strcat(unixCmd, ALGMfname);
   system(unixCmd);

   cout << "=========================" << endl;

   return 0;

}//main

