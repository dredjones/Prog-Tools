// -----------------------------------------------------------------
// File name:   format.cpp
// Assign ID:   DEMO
// Date:        March 24, 2012
//
// Invocation:  format.run basefilename
// Example:     format.run myGPA
//
// Purpose:     Format source code, replacing tabs with 3 spaces.
//              Write an anomalies file:
//               a) Lines longer than 80
//               b) BAD indentation inside main.
//               c) switch/case/break indentation;
//               d) Count #lines longer than 80 characters.
//
// Author:      Dr. Jones
//
// ------------------------------------------------------------------

#include <iostream>
#include <fstream>
using namespace std;

// ------------------------------------------------------------------
// Return true if line is all whitespace.
// ------------------------------------------------------------------
bool WhiteSpace(char L[])
{
   int count = 0;
   for (int k=0; k<strlen(L); k++)
      if (L[k] != ' ' && L[k] != '\t') count++;
   if (count == strlen(L)) return true;
   return false;
}

// ------------------------------------------------------------------
// Return position of first non-blank char in line.
// ------------------------------------------------------------------
int firstNonBlank(char L[])
{
   int k;
   for (k=0; k<strlen(L); k++)
      if (L[k] != ' ') return k+1;
}

int main (int argc, char * argv[])
{
   
   //  ---------------------------------------------
   //  Declare variables num1, num2, num3 and Total.
   //  ---------------------------------------------
   int k;             // Loop variable.
   int longlines;     // #lines longer than 80 chars.
   int lineno;        // Input line number.
   int indentation;   // Input line number.
   bool foundMAIN;    // TRUE when main has been scanned. 
   bool insideMAIN;   // TRUE when main has been entered via {.

   char Line [1025];   // Source file line.
   const string SPACES = "   ";
 
   char srcfilename[80];    // Source code file.
   char lstfilename[80];    // Source listing file.
   char anomfilename[80];   // Anomalies file.
   char indentfilename[80]; // Anomalies file.

   //-|  Extract arguments, names of source and output files.
   if (argc == 1)
   {
      cout << "\nUSAGE:   format.run basename \n"
           << "\nExample: format.run myGPA    "    
           << "// when source file is myGPA.cpp\n\n";
      exit(2);
   }

   //-|  Extract arguments, names of source and output files.
   if (argc == 2)
   {
      strcpy(srcfilename,argv[1]);
      strcpy(lstfilename,srcfilename);
      strcpy(anomfilename,srcfilename);
      strcpy(indentfilename,srcfilename);
      strcat(srcfilename,".cpp");
      strcat(lstfilename,".lst");
      strcat(anomfilename,".anom");
      strcat(indentfilename,".indent");

      cout << "IN = " << srcfilename << endl
           << " ... OUT = " << lstfilename << endl
           << " ... OUT = " << anomfilename << endl
           << " ... OUT = " << indentfilename << endl;
   }

   
   ifstream srcF(srcfilename); 
   if (srcF.fail())
   {
      cout << "CAN NOT FIND FILE '" << srcfilename << "' ..." << endl;
      exit(1);
   }

   ofstream lstF (lstfilename); 
   ofstream anomF (anomfilename); 
   ofstream indentF (indentfilename); 

   lineno = 0;
   longlines = 0;
   foundMAIN = false;
   insideMAIN = false;

   //-| --------------------------------------------------
   //-| 4. Read file, line by line. Print each character 
   //-|    of line, replacing tab with spaces.
   //-| --------------------------------------------------
   while (! srcF.eof())
   {
      lineno++;

      srcF.getline(Line,1024,'\n');
      if (! WhiteSpace(Line) )
      {
         indentation = firstNonBlank(Line);
         indentF << lineno << " : " << indentation << endl;
         anomF << indentation << " : " << lineno << " : " << Line << endl;
      }
  
      if (! foundMAIN)
      {
         foundMAIN = (strstr(Line,"main") != NULL);
         if (foundMAIN) foundMAIN = (strstr(Line,"(") != NULL);
      } 
      if (! insideMAIN && foundMAIN)
      {
         insideMAIN = (strstr(Line,"{") != NULL);
      } 

      if (strlen(Line) > 80)
      {
         longlines++;
         anomF << "Line " << lineno << " LONGER TO 80 characters" << endl;
      }

      for (k=0; k<strlen(Line); k++)
      {
         if (Line[k] == '\t')
            lstF << SPACES;
         else
            lstF << Line[k];
      }
      lstF << endl;

    }



   //-| --------------------------------------------------
   //-| 4. Display formatted file.
   //-| --------------------------------------------------
   char cmd[80];
   strcpy(cmd,"cat ");
   strcat(cmd,lstfilename);
   system(cmd); 


   //-| --------------------------------------------------
   //-| 4. Print WARNINGS.
   //-| --------------------------------------------------
   cout << endl << endl;
   anomF << "SOURCE CODE ANOMALIES (subject to deductions)" << endl <<  endl;
   if (longlines > 2)
   {
       anomF << longlines << " LINES OVER 80 CHARACTERS " << endl;
   }

   //-| --------------------------------------------------
   //-| 4. Close files.
   //-| --------------------------------------------------
   srcF.close();
   lstF.close();
   anomF.close();
   indentF.close();

   cout << "IN = " << srcfilename << endl
        << " ... OUT = " << lstfilename << endl
        << " ... OUT = " << anomfilename << endl
        << " ... OUT = " << indentfilename << endl;

   if (longlines > 3)
   {
      cout << "\nLineLENGTH STDSviolation: " << longlines 
           << " LINES OVER 80 CHARACTERS " << endl;
   }

   return 0;

}//main
