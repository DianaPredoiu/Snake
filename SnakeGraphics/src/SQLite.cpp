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

void SQLite::openConnection()
{
	std::string p = FOO;
	p.append("/utility/SQL/");
	std::string path = p.append("snake.db");
	rc = sqlite3_open(path.c_str(), &db);
	if (rc)
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	else
		fprintf(stderr, "Opened database successfully\n");
}

void SQLite::insert(Player player)
{
	openConnection();
	std::string name = player.getPlayerName();
	int score = player.getScore();
	std::string sscore = std::to_string(score);
	std::string insert = "INSERT INTO players (NAME,SCORE) VALUES ('"+name+"'," + sscore + "); ";
	sql = new char[insert.length() + 1];
	strcpy(sql, insert.c_str());

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
		fprintf(stdout, "Records created successfully\n");

	sqlite3_close(db);
}