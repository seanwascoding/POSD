#include "../src/file.h"
#include "../src/folder.h"

TEST(BFSIteratorSuite, TestRecusive)
{
    Node *folder = new Folder("/asdsadasd/adsadsads/1");
    Node *folder2 = new Folder("/asdsadasd/adsadsads/2");
    Node *folder3 = new Folder("/asdsadasd/adsadsads/3");
    folder->switchState(1);
    folder2->switchState(1);
    folder3->switchState(1);


    folder3->add(new File("/3-1"));
    folder3->add(new File("/3-2"));

    folder2->add(new File("/2-1"));
    folder2->add(new File("/2-2"));
    folder2->add(folder3);

    folder->add(new File("/asdsadasd/adsadsads/1/1-1"));
    folder->add(folder2);
    folder->add(folder3);
    folder->add(new File("/asdsadasd/adsadsads/1/1-3"));

    Iterator *it = folder->createIterator();

    it->first();
    cout << it->currentItem()->name() << endl;

    for (int i = 0; i < 1; i++)
    {
        it->next();
        cout << it->currentItem()->name() << endl;
    }

    it->next();

    ASSERT_TRUE(it->isDone());

    delete folder;
    delete folder2;
    delete folder3;
    delete it;
}