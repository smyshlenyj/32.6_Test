#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>

class IDBConnection
{
private:
public:
   IDBConnection() {}
   virtual ~IDBConnection() {}

   virtual void open() = 0;
   virtual bool execQuery(const std::string &) = 0;
   virtual void close() = 0;
};

class classThatUsesDB : public IDBConnection
{
private:
   IDBConnection *DBConnection;

public:
   classThatUsesDB(IDBConnection *connection) : DBConnection(connection) {}
   ~classThatUsesDB();

   void openConnection()
   {
      return DBConnection->open();
   }

   bool useConnection(const std::string &query)
   {
      return DBConnection->execQuery(query);
   }

   void closeConnection()
   {
      return DBConnection->close();
   }
};

void createTable(IDBConnection *dbconnect, const std::string &query)
{
   dbconnect->open();
   dbconnect->execQuery(query);
   dbconnect->close();
}

class mockClass : public IDBConnection
{
public:
   MOCK_METHOD(void, open, (), (override));
   MOCK_METHOD(bool, execQuery, (const std::string &query), (override));
   MOCK_METHOD(void, close, (), (override));
};

TEST(DBConnectionTest, _testDB)
{
   mockClass mock;
   EXPECT_CALL(mock, open).Times(1);
   EXPECT_CALL(mock, execQuery).Times(1);
   EXPECT_CALL(mock, close()).Times(1);

   createTable(&mock, "CREATE TABLE IF NOT EXISTS users (login varchar(100) not null,	name varchar(100), hashedPassword varchar(100)");
}

int main(int argc, char *argv[])
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}