/*
  Paragon.cpp, Simple pattern classifier
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

//#include <iostream>

#include "Paragon.hpp"


Paragon::Paragon(UInt InPatternCnt, UInt InPatternSize)
{
  PatternCnt = InPatternCnt;
  PatternSize = InPatternSize;

  PatternSet.resize(InPatternCnt);

  MatchProbability.resize(InPatternCnt);
  InputNonZeroCnt.resize(InPatternCnt);
  NonZeroMatchCnt.resize(InPatternCnt);
}

void Paragon::Classify(vector<UInt> &CurrentSpOut)
{
  vector<Real>::iterator MaxLocation;

  for(int CurPat=0; CurPat < PatternCnt; CurPat++)
  {
    InputNonZeroCnt[CurPat]=PatternSet[CurPat]->Ndx.size();
    NonZeroMatchCnt[CurPat] = 0;
    for(int i=0; i < PatternSet[CurPat]->Ndx.size(); i++)
      if(CurrentSpOut[PatternSet[CurPat]->Ndx[i]])
        NonZeroMatchCnt[CurPat]++;

    if(InputNonZeroCnt[CurPat] == 0)
      MatchProbability[CurPat] = 0.0;
    else
      MatchProbability[CurPat] = ((Real) NonZeroMatchCnt[CurPat]) / ((Real) InputNonZeroCnt[CurPat]);
  }

  MaxLocation = max_element(MatchProbability.begin(), MatchProbability.end());
  MaxProbability = *MaxLocation;
  MaxNdx = MaxLocation - MatchProbability.begin();

}


