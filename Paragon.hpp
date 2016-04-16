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
#include <vector>
#include <map>
#include <algorithm> // sort

#include <nupic/types/Types.hpp>

#include "Sparse.hpp"

using namespace std;
using namespace nupic;

  class Paragon
  {
    public:
    Paragon() {};
    ~Paragon() {};
    Paragon(UInt InPatternCnt, UInt InPatternSize);

    void Classify(vector<UInt> &CurrentSpOut);

    UInt PatternCnt;
    UInt PatternSize;
    UInt MaxNdx;
    Real MaxProbability;

    vector<SparsePlutoVector *> PatternSet;
    vector<Real> MatchProbability;
    vector<UInt> InputNonZeroCnt;
    vector<UInt> NonZeroMatchCnt;
  };

