#pragma once

#include "visitor.h"

class PostVisitor : public Visitor
{
public:
  void visit(Expression *e) override
  {
    _result += e->left()->post_str() + " " + e->right()->post_str() + " " + e->getOperator();
  }

  void visit(Operand *o) override
  {
    _result += to_string(o->evaluate());
  }

  std::string result() const override { return _result; }

private:
  std::string _result;
};
