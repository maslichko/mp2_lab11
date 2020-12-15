#include "Polish.h"

void TOperFactory::Create(char* s, int& n, IOper**& opers)
{
  int l = strlen(s);
  for (int i = 0; i < l; i++)
  {
    if (isdigit(s[i]) == 0) //Операция или скобка
    {
      n++;
    }
  }
  n++;
  n = 2 * n - 1;

  IOper** res = new IOper * [n];
  int start = 0;
  int j = 0;

  for (int i = 0; i < l; i++)
  {
    if (s[i] == '(')
    {
      res[j] = new TBracketOpen('(');
      j++;
    }
    else if (s[i] == ')')
    {
      res[j] = new TBracketClose(')');
      j++;
    }
    else if (s[i] == '+')
    {
      res[j] = new TPlus('+');
      j++;
    }
    else if (s[i] == '-')
    {
      res[j] = new TMinus('-');
      j++;
    }
    else if (s[i] == '*')
    {
      res[j] = new TMultiplication('*');
      j++;
    }
    else if (s[i] == '/')
    {
      res[j] = new TDivision('/');
      j++;
    }
    else if (s[i] == '^')
    {
      res[j] = new TPow('^');
      j++;
    }
  }

  for (int i = 0; i < l; i++)
  {
    if (isdigit(s[i]) != 0)
    {
      res[j] = new TNum(s[i] - 48);
      j++;
    }
  }

  opers = new IOper * [j];
  for (int i = 0; i < j; i++)
  {
    opers[i] = res[i];
  }
  delete[] res;
}

int TPolish::Calculation(char* s)
{
  int n = 0;
  IOper** opers = 0;

  TOperFactory::Create(s, n, opers);

  int l = strlen(s);
  IOper** res = new IOper * [l];
  int j = 0;

  for (int i = 0; i < n; i++) //Записываем числа
  {
    if (opers[i]->Prioritet() == 1) //Скобка
    {
      res[j] = opers[i];
      j++;
    }
    else if (opers[i]->Prioritet() == -1)
    {
      res[j] = opers[i];
      j++;
    }
  }

  for (int i = 0; i < n; i++)
  {
    if (opers[i]->Prioritet() == 3)
    {
      res[j] = opers[i];
      j++;
    }
  }

  for (int i = 0; i < n; i++)
  {
    if (opers[i]->Prioritet() == 2)
    {
      res[j] = opers[i];
      j++;
    }
  }

  for (int i = 0; i < n; i++)
  {
    if (opers[i]->Prioritet() == 4)
    {
      res[j] = opers[i];
      j++;
    }
  }

  for (int i = 0; i < n; i++)
  {
    if (opers[i]->Prioritet() == 0) //Закр скобка
    {
      res[j] = opers[i];
      j++;
    }
  }

  TStack<IOper*> ns(n);

  for (int i = 0; i < j; i++)
  {
    if (res[i]->Prioritet() == -1)
    {
      ns.Push(res[i]);
    }
    else
    {
      IOper* b = ns.Get();
      IOper* a = ns.Get();
      IOper* c = res[i]->Calc(a, b);
      ns.Push(c);
    }
  }
  IOper* r = ns.Get();

  return r->GetNumber();
}

TNum::TNum(int _d)
{
  data = _d;
}

TNum::TNum(TNum& _v)
{
  data = _v.data;
}

TNum::TNum(char* s)
{
  if (strlen(s) == 0)
  {
    throw - 1;
  }
  data = atof(s);
}

int TNum::Prioritet()
{
  return -1;
}

int TNum::GetNumber()
{
  return data;
}

IOper* TNum::Calc(IOper* a, IOper* b)
{
   throw - 1;
}

TOper::TOper(char _d)
{
  data = _d;
}

TOper::TOper(TOper& _v)
{
  data = _v.data;
}

int TOper::GetNumber()
{
  throw - 1;
}

int TPlus::Prioritet()
{
  return 2;
}

IOper* TPlus::Calc(IOper* a, IOper* b)
{
  TNum* res = new TNum(a->GetNumber() + b->GetNumber());
  return res;
}

int TMinus::Prioritet()
{
  return 2;
}
IOper* TMinus::Calc(IOper* a, IOper* b)
{
  TNum* res = new TNum(a->GetNumber() - b->GetNumber());
  return res;
}

int TMultiplication::Prioritet()
{
  return 3;
}

IOper* TMultiplication::Calc(IOper* a, IOper* b)
{
  TNum* res = new TNum(a->GetNumber() * b->GetNumber());
  return res;
}

int TDivision::Prioritet()
{
  return 3;
}

IOper* TDivision::Calc(IOper* a, IOper* b)
{
  if (b->GetNumber() == 0)
  {
    throw - 2;
  }
  TNum* res = new TNum(a->GetNumber() / b->GetNumber());
  return res;
}

int TBracketOpen::Prioritet()
{
  return 1;
}

IOper* TBracketOpen::Calc(IOper* a, IOper* b)
{
  throw - 1;
}

int TBracketClose::Prioritet()
{
  return 0;
}

IOper* TBracketClose::Calc(IOper* a, IOper* b)
{
  throw - 1;
}

int TPow::Prioritet()
{
  return 4;
}

IOper* TPow::Calc(IOper* a, IOper* b)
{
  int temp = pow(a->GetNumber(), b->GetNumber());
  TNum* res = new TNum(temp);
  return res;
}