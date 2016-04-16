/*
  InputData, Get input data frames from a file
  Copyright (C) 2016 David Merrell

  BufferSummary is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  InputData is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <string>

#include <nupic/types/Types.hpp>

using namespace std;
using namespace nupic;

  class InputData {
    public:
    InputData() {};
    ~InputData() {};
    InputData(string InFileName);

    void SetFrameSize(UInt InFrameSize);
    bool GetFrame(UInt *OutBuf, UInt FrameNumber);

    bool GoodData = false;
    UInt DataCount = 0;		// count of UInt in entire file (or complete buffer)
    UInt FrameCount = 0;	// count of the number of frames in input file (or complete buffer)
    UInt FrameSize = 0;		// count of UInt in a single input frame

    private:;
    UInt *DataBuffer;
  };

