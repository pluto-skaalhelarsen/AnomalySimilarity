/*
  SpParamFile.hpp, Read and make available parameters in a file
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

#include <map>
#include <string>

#include <nupic/types/Types.hpp>

using namespace std;
using namespace nupic;

/*
  Use a parameter file to set the working parameters for invocation of the SpatialPooler:

          SpatialPooler(vector<UInt> inputDimensions,
                        vector<UInt> columnDimensions,
                        UInt potentialRadius=16,
                        Real potentialPct=0.5,
                        bool globalInhibition=true,
                        Real localAreaDensity=-1.0,
                        UInt numActiveColumnsPerInhArea=10,
                        UInt stimulusThreshold=0,
                        Real synPermInactiveDec=0.008,
                        Real synPermActiveInc=0.05,
                        Real synPermConnected=0.1,
                        Real minPctOverlapDutyCycles=0.001,
                        Real minPctActiveDutyCycles=0.001,
                        UInt dutyCyclePeriod=1000,
                        Real maxBoost=10.0,
                        Int seed=1,
                        UInt spVerbosity=0,
                        bool wrapAround=true);
*/

class SpatialPoolerParams
{
  public:
  SpatialPoolerParams() { InitTables(); };
  ~SpatialPoolerParams() {};
  SpatialPoolerParams(string InName);

  bool ParamBool(string QString);
  UInt ParamUInt(string QString);
  Real ParamReal(string QString);
  int ParamInt(string QString);

  void EchoParams(void);

  private:
  void InitTables(void);

  map<string, bool> ParamTblBool;
  map<string, UInt> ParamTblUInt;
  map<string, Real> ParamTblReal;
  map<string, int> ParamTblInt;

};



