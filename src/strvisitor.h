#pragma once

#include "visitor.h"

class StrVisitor : public Visitor
{
public:
  void visit(Expression *e) override
  {
    _result = "(";

    _result += e->left()->str();
    _result += e->getOperator();
    _result += e->right()->str();

    _result += ")";
  }

  void visit(Operand *o) override
  {
    _result += to_string(o->evaluate());
  }

  std::string result() const override { return _result; }

private:
  std::string _result;
};
