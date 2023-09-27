/*BEGIN_LEGAL 
Intel Open Source License 

Copyright (c) 2002-2015 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */

#define PIN_DEPRECATED_WARNINGS 0

#include <iostream>
#include <fstream>
#include "pin.H"
#include "bimodal.H"
#include "at.H"
#include "cbp.H"
#include "gp.H"

using namespace std;

LOCALVAR BIMODAL bimodal;
LOCALVAR AT at;
LOCALVAR CBP cbp;
LOCALVAR GP gp;

ofstream OutFile;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "bpred.out", "specify output file name");

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    // Write to a file since cout and cerr maybe closed by the application
    OutFile.setf(ios::showbase);
      
    OutFile << endl;
    OutFile << "===== USC EE557 Spring 2016 - Project 1 =====" << endl;
    OutFile << "Name: " << "Dongyang Wu" << endl;
    OutFile << "Email: " << "wudongya@usc.edu" << endl;
  
    OutFile << endl;
    OutFile << "Always Taken Predictor" << endl;
    OutFile << "Total Prediction: " << (double)at.References() << endl;
    OutFile << "Prediction Rate: " << (double)at.Predicts() / (double)at.References() << endl;

    OutFile << endl;
    OutFile << "Global Predictor" << endl;
    OutFile << "Total Prediction: " << (double)gp.References() << endl;
    OutFile << "Prediction Rate: " << (double)gp.Predicts() / (double)gp.References() << endl;


    OutFile << endl;
    OutFile << "Bimodal Predictor" << endl;
    OutFile << "Total Prediction: " << (double)bimodal.References() << endl;
    OutFile << "Prediction Rate: " << (double)bimodal.Predicts() / (double)bimodal.References() << endl;

    OutFile << endl;
    OutFile << "Correlated Predictor" << endl;
    OutFile << "Total Prediction: " << (double)cbp.References() << endl;
    OutFile << "Prediction Rate: " << (double)cbp.Predicts() / (double)cbp.References() << endl;
    
    OutFile << "=============================================" << endl;
    
    OutFile.close();
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */
/*   argc, argv are the entire command line: pin -t <toolname> -- ...    */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    // Initialize pin
    PIN_Init(argc, argv);

    OutFile.open(KnobOutputFile.Value().c_str());
    
    bimodal.Activate();
    at.Activate();
    cbp.Activate();
    gp.Activate();

    // Register Instruction to be called to instrument instructions
    //INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}
