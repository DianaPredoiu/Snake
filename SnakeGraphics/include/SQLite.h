#pragma once

#include <Player.h>
#include <stdio.h>
#include <sqlite3.h> 

class SQLite
{
private:
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called";

public:
	sqlite3* getDB();
	char* getErrMsg();
	int getRc();
	char* getSql();

	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
	void openConnection();
	void execute();
	void insert(Player player);
	void select();

};
