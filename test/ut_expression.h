#include "../src/operand.h"
#include "../src/expression.h"
#include "../src/strvisitor.h"
#include "../src/postvisitor.h"
#include "../src/parser.h"

TEST(expression, normal)
{
    try
    {
        // The structure according to Figure1
        Term *s = new Operand(3);
        Term *t = new Operand(5);
        Term *u = new Operand(7);

        Expression *e = new Expression(s, new Expression(t, u), '*');

        ASSERT_EQ(36, e->evaluate());
        ASSERT_EQ("(3*(5+7))", e->str());
        ASSERT_EQ("3 5 7 + *", e->post_str());
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
}

TEST(expression, visitor)
{
    try
    {
        // The structure according to Figure1
        Term *s = new Operand(3);
        Term *t = new Operand(5);
        Term *u = new Operand(7);

        Expression *e = new Expression(s, new Expression(t, u), '*');

        StrVisitor *visit = new StrVisitor();
        e->accept(visit);

        PostVisitor *g = new PostVisitor();
        e->accept(g);

        ASSERT_EQ("(3*(5+7))", visit->result());
        ASSERT_EQ("3 5 7 + *", g->result());
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
}

// TEST(expression, Parser)
// {
//     try
//     {
//         // The structure according to Figure1
//         Term *s = new Operand(3);
//         Term *t = new Operand(5);
//         Term *u = new Operand(7);

//         Expression *e = new Expression(s, new Expression(t, u), '*');

//         Builder *builder = new Builder();
//         Scanner *scanner = new Scanner();

//         Parser *parser = new Parser(scanner, builder);
//         parser->setInput("( 10 + ( ( 11 + 12 ) * ( 5 * 4 ) ) )");
//         parser->parse();

//         // ASSERT_EQ("(3*(5+7))", visit->result());
//         // ASSERT_EQ("3 5 7 + *", g->result());
//     }
//     catch (const char *e)
//     {
//         std::cerr << e << '\n';
//     }
// }
