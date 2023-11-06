#pragma once

#include <string>
#include "visitor.h"

using namespace std;

class Term
{
public:
  virtual int evaluate() const = 0;
  virtual std::string str() const = 0;
  virtual std::string post_str() const = 0;
  virtual void accept(Visitor *v) = 0;
};