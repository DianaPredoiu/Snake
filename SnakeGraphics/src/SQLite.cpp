# include "SQLite.h"
#include <Player.h>
#include <iostream>
#include <vector>

std::vector<Player> players;

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

int SQLite::callback(void *data, int argc, char **argv, char **azColName)
{
	Player player;
	player.setPlayerName(argv[1]);
	player.setPlayerScore(std::stoi(argv[2]));
	players.push_back(player);

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

void SQLite::execute()
{
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		fprintf(stdout, "Records created successfully\n");

	}

	sqlite3_close(db);
}

void SQLite::insert(Player player)
{
	openConnection();
	std::string name = player.getPlayerName();
	int score = player.getScore();
	std::string sscore = std::to_string(score);
	std::string insert = "INSERT INTO players (NAME,SCORE) VALUES ('" + name + "'," + sscore + "); ";
	sql = new char[insert.length() + 1];
	strcpy(sql, insert.c_str());
	execute();
}

void SQLite::select()
{
	openConnection();
	sql = "SELECT * FROM players order by score desc limit 5;";
	execute();
}

