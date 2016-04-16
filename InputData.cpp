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
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

#include "InputData.hpp"


bool GetInputData(const char *InFileName, UInt *Len, UInt **Buffer)
{
  int InFile;
  struct stat statbuf;
  int SampleLen;
  UInt *LocalBuf;

  if(stat(InFileName, &statbuf) != 0)
    return(false);
  SampleLen = statbuf.st_size / sizeof(int);

  if((InFile = open(InFileName, O_RDONLY)) < 0)
  {
    printf("Cannot open input file %s\n", InFileName);
    return(false);
  } // if

  if((LocalBuf = (UInt *) calloc(SampleLen, sizeof(UInt))) == NULL)
  {
    printf("Cannot allocate output buffer len %d\n", SampleLen);
    return(false);
  } // if

  if(read(InFile, LocalBuf, (int) statbuf.st_size) <= 0)
    return(false);

  close(InFile);

  *Len = SampleLen;	// count of UInt
  *Buffer = LocalBuf;

  return(true);
}

	// constructor with a file name
InputData::InputData(string InFileName)
{
  if(!GetInputData(InFileName.c_str(), &DataCount, &DataBuffer))
    GoodData = false;
  else
    GoodData = true;


};

void InputData::SetFrameSize(UInt InFrameSize)
{
  FrameSize = InFrameSize;
  if(FrameSize == 0)
    FrameCount = 0;
  else
    FrameCount = DataCount / FrameSize;
}

bool InputData::GetFrame(UInt *OutBuf, UInt FrameNumber)
{
  UInt *src, *dest;

  src = &DataBuffer[FrameNumber * FrameSize];
  dest = OutBuf;

  for(UInt i=0; i < FrameSize; i++)
    *dest++ = *src++;

  return(true);
}

