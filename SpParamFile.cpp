/*
  SpParamFile.cpp, Read and make available parameters in a file
  Copyright (C) 2016 David Merrell

  BufferSummary is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  BufferSummary is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SpParamFile.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

  SpatialPoolerParams::SpatialPoolerParams(string InName)
  {
    string InBuf;
    string VarName;
    string VarVal;
    int SepLoc;

    InitTables();

    ifstream InStream(InName);
    if(!InStream)
    {
      cout << "No input file " << InName << "--- Using default parameter values" << endl;
    }
    else
    {
      do {
        getline(InStream, InBuf);
        if((InBuf[0] == '#') || (InBuf.length() == 0)) continue;	// comment
          if(((SepLoc=InBuf.find("=")) != string::npos) && (SepLoc > 2))
          {
            VarName = InBuf.substr(0, SepLoc);
            VarVal = InBuf.substr(SepLoc+1, InBuf.size());

            if(ParamTblBool.find(VarName) != ParamTblBool.end())
              ParamTblBool[VarName] = (VarVal == "true")?true:false; 

            if(ParamTblUInt.find(VarName) != ParamTblUInt.end())
              ParamTblUInt[VarName] = atoi(VarVal.c_str());

            if(ParamTblReal.find(VarName) != ParamTblReal.end())
              ParamTblReal[VarName] = atof(VarVal.c_str());

            if(ParamTblInt.find(VarName) != ParamTblInt.end())
              ParamTblInt[VarName] = atoi(VarVal.c_str());
          }
//cout << "Read: " << InBuf << "(" << VarName << ", " << VarVal << ")" << endl;
      } while(!InStream.eof());

      InStream.close();
    }
  }

  void SpatialPoolerParams::InitTables(void)
  {
    ParamTblBool["globalInhibition"] = true;
    ParamTblBool["wrapAround"] = true;

    ParamTblUInt["potentialRadius"] = 16;
    ParamTblUInt["numActiveColumnsPerInhArea"] = 10;
    ParamTblUInt["stimulusThreshold"] = 0;
    ParamTblUInt["dutyCyclePeriod"] = 1000;
    ParamTblUInt["spVerbosity"] = 0;

    ParamTblReal["potentialPct"] = 0.5;
    ParamTblReal["localAreaDensity"] = -1.0;
    ParamTblReal["synPermInactiveDec"] = 0.008;
    ParamTblReal["synPermActiveInc"] = 0.05;
    ParamTblReal["synPermConnected"] = 0.1;
    ParamTblReal["minPctOverlapDutyCycles"] = 0.001;
    ParamTblReal["minPctActiveDutyCycles"] = 0.001;
    ParamTblReal["maxBoost"] = 10.0;

    ParamTblInt["seed"] = 1;

  }

  bool SpatialPoolerParams::ParamBool(string QString)
  {
    map<string, bool>::iterator QVal;
 
    if((QVal = ParamTblBool.find(QString)) == ParamTblBool.end())
     return(0);

    return(QVal->second);
  }

  UInt SpatialPoolerParams::ParamUInt(string QString)
  {
    map<string, UInt>::iterator QVal;
 
    if((QVal = ParamTblUInt.find(QString)) == ParamTblUInt.end())
     return(0);

    return(QVal->second);
  }

  Real SpatialPoolerParams::ParamReal(string QString)
  {
    map<string, Real>::iterator QVal;
 
    if((QVal = ParamTblReal.find(QString)) == ParamTblReal.end())
     return(0);

    return(QVal->second);
  }

  int SpatialPoolerParams::ParamInt(string QString)
  {
    map<string, int>::iterator QVal;
 
    if((QVal = ParamTblInt.find(QString)) == ParamTblInt.end())
     return(0);

    return(QVal->second);
  }

  void SpatialPoolerParams::EchoParams(void)
  {

cout << "Params:" << endl
        << "vector<UInt> inputDimensions" << endl
        << "vector<UInt> columnDimensions" << endl
        << ParamUInt("potentialRadius") << endl
        << ParamReal("potentialPct") << endl
        << ParamBool("globalInhibition") << endl
        << ParamReal("localAreaDensity") << endl
        << ParamUInt("numActiveColumnsPerInhArea") << endl
        << ParamUInt("stimulusThreshold") << endl
        << ParamReal("synPermInactiveDec") << endl
        << ParamReal("synPermActiveInc") << endl
        << ParamReal("synPermConnected") << endl
        << ParamReal("minPctOverlapDutyCycles") << endl
        << ParamReal("minPctActiveDutyCycles") << endl
        << ParamUInt("dutyCyclePeriod") << endl
        << ParamReal("maxBoost") << endl
        << ParamInt("seed") << endl
        << ParamUInt("spVerbosity") << endl
        << ParamBool("wrapAround") << endl;
  }



