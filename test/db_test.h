#include <gtest/gtest.h>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <list>
#include <memory>
#include "../src/unit_of_work.h"
#include "../src/drawing_mapper.h"
#include "../src/painter_mapper.h"
#include "../src/drawing.h"

class DBSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {
        create_drawing_table();
        create_painter_table();
        populate_drawings();
        populate_painters();
        dm = DrawingMapper::instance();
        dm->setDB("resource/drawing.db");
        pm = PainterMapper::instance();
        pm->setDB("resource/painter.db");
    }

    void TearDown() override
    {
        drop_drawing_table();
        drop_painter_table();
        sqlite3_close(db);
        sqlite3_close(db_p);
    }

    void create_drawing_table()
    {
        ASSERT_EQ(0, sqlite3_open("resource/drawing.db", &db));
        const char *stmt = "CREATE TABLE drawing ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "painter    varchar(50)             not null,"
                           "shapes varchar(1028),"
                           "FOREIGN KEY(painter) REFERENCES painter(ID))";
        int rc = sqlite3_exec(db, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_drawing_table()
    {
        const char *dropStmt = "DROP TABLE drawing";
        int rc = sqlite3_exec(db, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void create_painter_table()
    {
        ASSERT_EQ(0, sqlite3_open("resource/painter.db", &db_p));
        const char *stmt = "CREATE TABLE painter ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "name    varchar(50)             not null)";
        int rc = sqlite3_exec(db_p, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_painter_table()
    {
        const char *dropStmt = "DROP TABLE painter";
        int rc = sqlite3_exec(db_p, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void populate_drawings()
    {
        const char *s1 = "INSERT INTO drawing"
                         "(ID, painter, shapes)"
                         "values"
                         "('d_0001', 'p_0001', 'triangle 1 1 1')";
        int rc = sqlite3_exec(db, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0002', 'p_0001', 'triangle 2 2 2')";
        rc = sqlite3_exec(db, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s3 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0003', 'p_0002', 'compound { triangle 1 1 1 triangle 2 2 2 } triangle 3 3 3')";
        rc = sqlite3_exec(db, s3, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void populate_painters()
    {
        const char *s1 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0001', 'Patrick')";
        int rc = sqlite3_exec(db_p, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0002', 'Mary')";
        rc = sqlite3_exec(db_p, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void display_err_msg_and_fail_if_any(int rc)
    {
        if (rc)
        {
            std::cout << "db error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        }
        ASSERT_EQ(SQLITE_OK, rc);
    }

    sqlite3 *db;
    sqlite3 *db_p;
    char *err_msg = nullptr;
    DrawingMapper *dm;
    PainterMapper *pm;
};

TEST_F(DBSuite, Sanity)
{
}

TEST_F(DBSuite, findDrawing)
{
    Drawing *drawing = dm->find("d_0001");
    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0001"));

    pm->find("p_0001");
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0001"));

    ASSERT_EQ(drawing->id(), "d_0001");

    ASSERT_EQ(drawing->getShape(0)->perimeter(), 3);
    ASSERT_EQ(drawing->painter()->id(), "p_0001");
    ASSERT_EQ(drawing->painter()->name(), "Patrick");
}

TEST_F(DBSuite, NotFound)
{
    ASSERT_EQ(nullptr, DrawingMapper::instance()->find("d_9999"));
}

TEST_F(DBSuite, UnitOfWorkRegisterCleanNotFound)
{
    UnitOfWork *uow = UnitOfWork::instance();
    dm->find("d_9999");
    ASSERT_FALSE(uow->inClean("d_9999"));
}

TEST_F(DBSuite, UnitOfWorkRegisterDirty)
{
    UnitOfWork *uow = UnitOfWork::instance();
    Drawing *drawing = dm->find("d_0001");
    Painter *painter = PainterMapper::instance()->find("p_0002");
    drawing->setPainter(painter);
    ASSERT_EQ(painter, drawing->painter());
    ASSERT_FALSE(uow->inClean("d_0001"));
    ASSERT_TRUE(uow->inDirty("d_0001"));

    uow->commit();
    ASSERT_EQ(painter, drawing->painter());
    ASSERT_TRUE(uow->inClean("d_0001"));
    ASSERT_FALSE(uow->inDirty("d_0001"));
}

TEST_F(DBSuite, UnitOfWorkRegisterNew)
{
    UnitOfWork *uow = UnitOfWork::instance();
    Painter *painter = new Painter("p_0003", "Howard");
    Drawing *drawing = new Drawing("d_0012", painter);
    uow->registerNew(painter);
    uow->registerNew(drawing);
    ASSERT_TRUE(uow->inNew(painter->id()));
    uow->commit();
    ASSERT_FALSE(UnitOfWork::instance()->inNew(painter->id()));
    ASSERT_TRUE(UnitOfWork::instance()->inClean(painter->id()));
    ASSERT_EQ(pm->find(painter->id())->id(), painter->id());
    ASSERT_EQ(dm->find(drawing->id())->id(), drawing->id());
}

TEST_F(DBSuite, findPainterAndUpdate)
{
    Painter *painter = pm->find("p_0001");
    ASSERT_EQ(painter->id(), "p_0001");
    painter->setName("Patrick-edit");
    ASSERT_FALSE(UnitOfWork::instance()->inClean(painter->id()));
    ASSERT_TRUE(UnitOfWork::instance()->inDirty(painter->id()));

    UnitOfWork::instance()->commit();
    ASSERT_FALSE(UnitOfWork::instance()->inDirty(painter->id()));
    ASSERT_TRUE(UnitOfWork::instance()->inClean(painter->id()));
}

TEST_F(DBSuite, DeletePainterInNewWithoutCommit)
{
    auto uow = UnitOfWork::instance();
    Painter *painter = new Painter("p_0003", "Howard");
    uow->registerNew(painter);
    ASSERT_TRUE(uow->inClean(painter->id()));
    ASSERT_TRUE(uow->inNew(painter->id()));
    uow->registerDeleted(painter);
    ASSERT_TRUE(uow->inDeleted(painter->id()));
    ASSERT_FALSE(uow->inClean(painter->id()));
    ASSERT_FALSE(uow->inNew(painter->id()));
    Painter *it = pm->find(painter->id());
    ASSERT_EQ(it, nullptr);
}

TEST_F(DBSuite, DeletePainterInClean)
{
    auto uow = UnitOfWork::instance();
    Painter *painter = pm->find("p_0001");
    ASSERT_TRUE(uow->inClean(painter->id()));
    uow->registerDeleted(painter);
    ASSERT_FALSE(uow->inClean(painter->id()));
    ASSERT_EQ(pm->find(painter->id()), nullptr);
}

TEST_F(DBSuite, NewDrawingAndPainterThroughUoWAndFind)
{
    auto uow = UnitOfWork::instance();
    Painter *painter = new Painter("p_0123", "seanwascoding");
    Drawing *drawing = new Drawing("d_3312", painter);
    ASSERT_FALSE(uow->inClean(painter->id()));
    ASSERT_FALSE(uow->inClean(drawing->id()));
    uow->registerNew(painter);
    uow->registerNew(drawing);
    ASSERT_TRUE(uow->inNew(drawing->id()));
    ASSERT_TRUE(uow->inNew(painter->id()));
    ASSERT_EQ(dm->find(drawing->id()), nullptr);
    ASSERT_EQ(pm->find(painter->id()), nullptr);

    uow->commit();
    dm->cleanCache();
    pm->cleanCache();
    ASSERT_EQ(dm->find(drawing->id())->id(), drawing->id());
    ASSERT_TRUE(uow->inClean(drawing->id()));
    ASSERT_EQ(dm->find(drawing->id())->painter()->id(), painter->id());
    // dm->find(drawing->id())->getShape(0)->perimeter();
    
    // ASSERT_EQ(pm->find("p_0123")->id(), painter->id());

    // ASSERT_FALSE(uow->inNew(drawing->id()));
    // ASSERT_FALSE(uow->inNew(painter->id()));
    // ASSERT_TRUE(uow->inClean(painter->id()));
}