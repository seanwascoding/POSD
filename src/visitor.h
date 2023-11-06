#pragma once

#include <string>

class Expression;
class Operand;

class Visitor {
public:
  virtual void visit(Expression * e) = 0;
  virtual void visit(Operand * o) = 0;
  virtual std::string result() const = 0;
};
