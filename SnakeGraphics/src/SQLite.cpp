# include "SQLite.h"


sqlite3* SQLite::getDB()
{
	return db;
}

char* SQLite::getErrMsg()
{
	return zErrMsg;
}

int SQLite::getRc()
{
	return rc;
}

char* SQLite::getSql()
{
	return sql;
}

int SQLite::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for (i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

//void SQLite::openConnection()
//{
//	rc = sqlite3_open("snake.db", &db);
//	if (rc)
//		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//	else
//		fprintf(stderr, "Opened database successfully\n");
//}
//
//void SQLite::insert(Player player)
//{
//	std::string name = player.getPlayerName();
//	int score = player.getScore();
//	sql = "INSERT INTO players (ID,NAME,SCORE) "
//		"VALUES (name, score); ";
//
//	/* Execute SQL statement */
//	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	if (rc != SQLITE_OK)
//	{
//		fprintf(stderr, "SQL error: %s\n", zErrMsg);
//		sqlite3_free(zErrMsg);
//	}
//	else
//		fprintf(stdout, "Records created successfully\n");
//
//	sqlite3_close(db);
//}