#include "../src/file.h"
#include "../src/folder.h"

TEST(BFSIteratorSuite, TestRecusive)
{
    try
    {
        Node *folder = new Folder("/asdsadasd/adsadsads/1");
        Node *folder2 = new Folder("/asdsadasd/adsadsads/1/2");
        Node *folder3 = new Folder("/asdsadasd/adsadsads/1/3");
        folder->switchState(2); // switch to BFS Iterator

        folder3->add(new File("/asdsadasd/adsadsads/1/3/3-1"));
        folder3->add(new File("/asdsadasd/adsadsads/1/3/3-2"));

        folder2->add(new File("/asdsadasd/adsadsads/1/2/2-1"));
        folder2->add(new File("/asdsadasd/adsadsads/1/2/2-2"));

        folder->add(new File("/asdsadasd/adsadsads/1/1-1"));
        folder->add(folder2);
        folder->add(folder3);
        folder->add(new File("/asdsadasd/adsadsads/1/1-3"));

        Iterator *it = folder->createIterator();
        for (it->first(); !it->isDone(); it->next())
        {
            cout << it->currentItem()->name() << endl;
        }
        ASSERT_TRUE(it->isDone());

        delete folder;
        delete folder2;
        delete folder3;
        delete it;
    }
    catch (const std::runtime_error &e)
    {
        EXPECT_STREQ("wrong path", e.what());
    }
}