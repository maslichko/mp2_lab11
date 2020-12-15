#ifndef _POLISH_
#define _POLISH_

#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "Stack.h"

class IOper
{
public:
  virtual int Prioritet() = 0;
  virtual int GetNumber() = 0;
  virtual IOper* Calc(IOper* a, IOper* b) = 0;
};

class TNum : public IOper
{
protected:
  int data;
public:
  TNum(int _d);
  TNum(TNum& _v);
  TNum(char* s);

  virtual int Prioritet();
  virtual int GetNumber();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TOper : public IOper
{
protected:
  char data;
public:
  TOper(char _d);
  TOper(TOper& _v);

  virtual int GetNumber();
};

class TPlus : public TOper
{
public:
  TPlus(char _d) : TOper(_d) {}

  virtual int Prioritet();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TMinus : public TOper
{
public:
  TMinus(char _d) : TOper(_d) {}

  virtual int Prioritet();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TMultiplication : public TOper
{
public:
  TMultiplication(char _d) : TOper(_d) {}

  virtual int Prioritet();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TDivision : public TOper
{
public:
  TDivision(char _d) : TOper(_d) {}

  virtual int Prioritet();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TBracketOpen : public TOper
{
public:
  TBracketOpen(char _d) : TOper(_d) {}

  virtual int Prioritet();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TBracketClose : public TOper
{
public:
  TBracketClose(char _d) : TOper(_d) {}

  virtual int Prioritet();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TPow : public TOper
{
public:
  TPow(char _d) : TOper(_d) {}

  virtual int Prioritet();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TOperFactory
{
public:
  static void Create(char* s, int& n, IOper**& opers);
};

class TPolish
{
public:
  static int Calculation(char* s);
};

#endif