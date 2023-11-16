#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/beautify_visitor.h"
#include "../src/json_scanner.h"
#include "../src/json_parser.h"
#include "../src/json_builder.h"

TEST(StringValueSuite, ToString)
{
    Value *v = new StringValue("value1");
    ASSERT_EQ("\"value1\"", v->toString());
}

TEST(JSonSuite, OneKeyStringValue)
{
    JsonObject *jo = new JsonObject;
    Value *v1 = new StringValue("value1");
    jo->set("key1", v1);
    ASSERT_EQ(v1, jo->getValue("key1"));
    ASSERT_EQ("{\n\"key1\":\"value1\"\n}", jo->toString());
}

TEST(JSonSuite, TwoKeyStringValue)
{
    JsonObject *jo = new JsonObject;
    Value *v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value *v2 = new StringValue("value2");
    jo->set("key2", v2);
    ASSERT_EQ("\"value1\"", jo->getValue("key1")->toString());
    ASSERT_EQ("\"value2\"", jo->getValue("key2")->toString());
    ASSERT_EQ("{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}", jo->toString());
}

TEST(JSonSuite, Composite)
{
    JsonObject *jo = new JsonObject;
    Value *v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value *v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);
    ASSERT_EQ(jo, j_composite->getValue("keyc"));
    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", j_composite->toString());
}

TEST(JSonSuite, Iterator)
{
    JsonObject *jo = new JsonObject;
    Value *v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value *v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *jo2 = new JsonObject;
    Value *v3 = new StringValue("value3");
    jo2->set("key3", v3);
    Value *v4 = new StringValue("value4");
    jo2->set("key4", v4);

    jo->set("compound", jo2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);

    JsonIterator *it = j_composite->createIterator();
    for (it->first(); !it->isDone(); it->next())
    {
        std::cout << it->currentKey() << ":" << it->currentValue()->toString() << std::endl;
    }
}

TEST(JSonSuite, Visitor)
{
    JsonObject *jo = new JsonObject;
    Value *v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value *v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *jo2 = new JsonObject;
    Value *v3 = new StringValue("value3");
    jo2->set("key3", v3);
    Value *v4 = new StringValue("value4");
    jo2->set("key4", v4);

    jo->set("compound", jo2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);

    BeautifyVisitor *visit = new BeautifyVisitor();

    // v1->accept(visit);
    // std::string result = visit->getResult();
    // std::cout << result;

    j_composite->accept(visit);
    std::string result = visit->getResult();
    std::cout << result << std::endl;
}

TEST(JSonSuite, Parser)
{
    JsonObject *jo = new JsonObject;
    Value *v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value *v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *jo2 = new JsonObject;
    Value *v3 = new StringValue("value3");
    jo2->set("key3", v3);
    Value *v4 = new StringValue("value4");
    jo2->set("key4", v4);

    jo->set("compound", jo2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);

    JsonScanner *scanner = new JsonScanner();
    JsonBuilder *builder = new JsonBuilder();
    JsonParser *parser = new JsonParser(scanner, builder);

    parser->setInput("{\n      \"key1\": \"value1\",\n      \"key2\":\"value2\"\n}");

    parser->parse();

    Value *temp = parser->getJsonObject();

    std::cout << temp->toString() << std::endl;
}