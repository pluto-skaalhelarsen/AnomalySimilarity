/* ---------------------------------------------------------------------
 * Numenta Platform for Intelligent Computing (NuPIC)
 * Copyright (C) 2013-2015, Numenta, Inc.  Unless you have an agreement
 * with Numenta, Inc., for a separate license for this software code, the
 * following terms and conditions apply:
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Affero Public License for more details.
 *
 * You should have received a copy of the GNU Affero Public License
 * along with this program.  If not, see http://www.gnu.org/licenses.
 *
 * http://numenta.org/licenses/
 * ---------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <algorithm>    // std::generate
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <cmath> 	// pow

#include "CmdLineParse.hpp"
#include "BufferSummary.hpp"
#include "SpParamFile.hpp"
#include "Paragon.hpp"
#include "InputData.hpp"

#include "nupic/algorithms/SpatialPooler.hpp"
#include "nupic/algorithms/Cells4.hpp"
#include "nupic/os/Timer.hpp"

using namespace std;
using namespace nupic;
using nupic::algorithms::spatial_pooler::SpatialPooler;
using nupic::algorithms::Cells4::Cells4;


int main(int argc, const char * argv[])
{
const UInt DIM = 2048; // number of columns in SP, TP
const UInt DIM_INPUT = 10000;
const UInt EPOCHS = pow(10, 4); // number of iterations (calls to SP/TP compute() )

const UInt RNGSEQUENCECOUNT = 100;	//number of buffers in the rng sequence

  UInt Epochs = EPOCHS;
  UInt EpochsTwo = EPOCHS;
  UInt SequenceCount = RNGSEQUENCECOUNT;

  CmdLineParse *CmdLine = new CmdLineParse(argc, argv);
  if(CmdLine->Vars("Epochs"))
    Epochs = CmdLine->Vars("Epochs");
  if(CmdLine->Vars("SequenceCount"))
    SequenceCount = CmdLine->Vars("SequenceCount");
  if((SequenceCount) > 10000) SequenceCount = 10000;

	// build the data frames
  InputData inDat = InputData(CmdLine->Names("InputData"));
  if(!inDat.GoodData) {
    cout << "Could not get data" << endl;
    return(-1);
  }
  inDat.SetFrameSize(DIM_INPUT);

  vector<UInt> inputDim = {DIM_INPUT};
  vector<UInt> colDim = {DIM};

  // generate random input
  vector<UInt> input(DIM_INPUT);
  vector<UInt> outSP(DIM); // active array, output of SP/TP

  Paragon Classifier(SequenceCount, DIM);
  BufferSummary SpSummary = BufferSummary();

  SpatialPoolerParams Params = SpatialPoolerParams(CmdLine->Names("SpParams"));
//  Params.EchoParams();

  SpatialPooler sp(
        inputDim,
        colDim,
        Params.ParamUInt("potentialRadius"),
        Params.ParamReal("potentialPct"),
        Params.ParamBool("globalInhibition"),
        Params.ParamReal("localAreaDensity"),
        Params.ParamUInt("numActiveColumnsPerInhArea"),
        Params.ParamUInt("stimulusThreshold"),
        Params.ParamReal("synPermInactiveDec"),
        Params.ParamReal("synPermActiveInc"),
        Params.ParamReal("synPermConnected"),
        Params.ParamReal("minPctOverlapDutyCycles"),
        Params.ParamReal("minPctActiveDutyCycles"),
        Params.ParamUInt("dutyCyclePeriod"),
        Params.ParamReal("maxBoost"),
        Params.ParamInt("seed"),
        Params.ParamUInt("spVerbosity"),
        Params.ParamBool("wrapAround"));

  cout << "Num Inputs required is " << sp.getNumInputs() << endl;
  cout << "Num Outputs required is " << sp.getNumColumns() << endl;

	// Start a stopwatch timer
  Timer stopwatch(true);

	// ***** Run the learning sequence *****
  for (UInt e = 0; e < Epochs; e++) {
    inDat.GetFrame(input.data(), e % SequenceCount);

    fill(outSP.begin(), outSP.end(), 0);
    sp.compute(input.data(), true, outSP.data());
    sp.stripUnlearnedColumns(outSP.data());

    if(CmdLine->Flags("--display_while_learning"))
    if((e % (10*SequenceCount)) < SequenceCount)
     {
        cout << "----------------- ========= ------------------ Epoch " << e << endl;
	// SP
      SpSummary.SetupBuffer(outSP);
      cout << "Pattern sequence number = " << (e%SequenceCount) << endl;
      cout << "Non-zero elements of final SP output (location : length) " << endl;
      while(SpSummary.PrepareNextRunMsg())
        cout << SpSummary.Msg << endl;
      }
  }
	// ***** separate the sequences *****
  cout << endl;
  cout << "======================..................=======================............" << endl;
  cout << "======================..................=======================............" << endl;
  cout << endl;

	// ***** Initialize the classifier *****
  for (UInt e = 0; e < SequenceCount; e++) {
    inDat.GetFrame(input.data(), e % SequenceCount);
    fill(outSP.begin(), outSP.end(), 0);
    sp.compute(input.data(), false, outSP.data());	// no learning in sp
    sp.stripUnlearnedColumns(outSP.data());
    Classifier.PatternSet[e] = new SparsePlutoVector(outSP);
  }

	// ***** Run the classifier sequence *****
  for (UInt e = 0; e < SequenceCount; e++) {
    inDat.GetFrame(input.data(), e % SequenceCount);


    fill(outSP.begin(), outSP.end(), 0);
    sp.compute(input.data(), false, outSP.data());	// no learning in sp
    sp.stripUnlearnedColumns(outSP.data());

	// print classification result
    if(CmdLine->Flags("--classify"))
    {

      Classifier.Classify(outSP);
      cout << "Pattern sequence number = " << e << endl;
      for(int i=0; i < Classifier.MatchProbability.size(); i++)
        cout << i << ": " << Classifier.MatchProbability[i]  << endl;
      cout << "Match " << Classifier.MaxNdx << " with probability "
           << Classifier.MaxProbability << endl;
    }


	// print entire final arrays
    if(CmdLine->Flags("--dump_final"))
    {
      cout << "Pattern sequence number = " << e << endl;
      cout << "SP=" << outSP << endl;
    }
	// print a list of non-zero runs
    if(CmdLine->Flags("--sp_summary"))
    {
      SpSummary.SetupBuffer(outSP);
      cout << "Pattern sequence number = " << e << endl;
      cout << "Non-zero elements of final SP output (location : length) " << endl;
      while(SpSummary.PrepareNextRunMsg())
        cout << SpSummary.Msg << endl;
    }
  }

  stopwatch.stop();
  cout << "Total elapsed time = " << stopwatch.getElapsed() << " seconds" << endl;

  return 0;
}
