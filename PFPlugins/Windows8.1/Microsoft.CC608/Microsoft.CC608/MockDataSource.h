/*********************************************************************************************************************
Microsft HLS SDK for Windows

Copyright (c) Microsoft Corporation

All rights reserved.

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

***********************************************************************************************************************/
#pragma once

#include <queue>
#include <string>
#include <utility>

#include "pch.h"
#include "Timestamp.h"
#include "CC608CharColor.h"

namespace Microsoft { namespace CC608 {

// simple struct to hold data for later display
struct BytePair 
{
  byte_t byte1;
  byte_t byte2;
  Timestamp ts;  // actual timestamp to display the data
  bool valid;

  BytePair(byte_t b1, byte_t b2, const Timestamp timestamp) : byte1(b1), byte2(b2), ts(timestamp), valid(true)
  {
  }
};

class MockDataSource
{
public:
  MockDataSource(void);
  ~MockDataSource(void);

  void RollUpSample();
  void PopOnSample();
  void PaintOnSample();

  void AllRows();

  void Channel2Data();

  void TestPattern01_Colors();
  void TestPattern02_PacIndents();
  void TestPattern03_MidRowCodes();

  BytePair GetNextPair();

  // exposed only for testing
  byte_t AddOddParityBit(byte_t b) const;
  void AddPac(const short row, const BYTE indent, const CC608CharColor color, const bool underline, const bool italics, const int channel = 1);

private:
  std::queue<BytePair> _byteCodes;
  Timestamp _addClock;

  // low level method to add a byte pair
  void SaveBytePair(const byte_t byte1, const byte_t byte2);

  // low-level method to add a specified delay to the running clock for adding data
  void ClockIt(const unsigned long long delayInMilliseconds = 1);

  // low-level channel implementation
  byte_t GetFirstByteMiscCommand(const int channel);
  byte_t GetFirstByteMidRowCode(const int channel);

  void AddStringAndPerhapsANull(std::string s, const unsigned long long delayInMilliseconds);
  void AddTransparentSpace();
  void AddResumeCaptionLoading(const unsigned long long delayInMilliseconds, const int channel = 1);
  void AddRollUpCaptions(short rows, const int channel = 1);
  void AddBackspace(const unsigned long long delayInMilliseconds, const int channel = 1);
  void AddMidRowCode(const CC608CharColor color, const bool underline, const int channel = 1);
  void AddMidRowCode(const bool underline, const bool italics, const int channel = 1);
  void AddDeleteToEndOfRow(const unsigned long long delayInMilliseconds, const int channel = 1);
  void AddFlashOn(const int channel = 1);
  void AddResumeDirectCaptioning(const unsigned long long delayInMilliseconds, const int channel = 1);
  void AddEraseDisplayedMemory(const unsigned long long delayInMilliseconds, const int channel = 1);
  void AddEraseNonDisplayedMemory(const int channel = 1);
  void AddCarriageReturn(const unsigned long long delayInMilliseconds, const int channel = 1);
  void AddEndOfCaption(const unsigned long long delayInMilliseconds, const int channel = 1);
  void AddTabOffset(const BYTE columns, const int channel = 1);
  void AddNulls();
  void AddNullPaddedString(const std::string s, const unsigned long long delayInMilliseconds);
};

}}