# include "SQLite.h"
#include <Player.h>
#include <iostream>
#include <vector>

std::vector<Player> players;

SQLite::SQLite()
{

}

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

std::vector<Player> SQLite:: getPlayers()
{
	return players;
}

int SQLite::callback(void *data, int argc, char **argv, char **azColName)
{
	Player player;
	player.setPlayerName(argv[1]);
	player.setPlayerScore(std::stoi(argv[2]));
	player.setLevel(argv[3]);
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
	std::string level = player.getLevel();
	std::string insert = "INSERT INTO players (NAME,SCORE,LEVEL) VALUES ('" + name + "'," + sscore +", '"+ level + "'); ";
	sql = new char[insert.length() + 1];
	strcpy(sql, insert.c_str());
	execute();
}

void SQLite::select(std::string level)
{
	openConnection();
	players.clear();
	std::string select = "SELECT * FROM players where LEVEL= '" + level + "' order by score desc limit 5;";
	sql = new char[select.length() + 1];
	strcpy(sql, select.c_str());
	execute();
}

SQLite::~SQLite()
{

}