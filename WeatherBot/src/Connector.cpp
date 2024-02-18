#include "../headers/Connector.hpp"

Connector& Connector::getInstance() {
  static Connector instance;
  return instance;
}

bool Connector::IsEmpty(std::string username) {
  int count;
  try {
    db.get()->operator<<("select count(*) from favorite where username = ?;")
            << username >>
        count;
  } catch (std::exception& e) {
    std::cerr << e.what();
  };
  return count == 0 ? true : false;
}

std::string Connector::getCity(std::string username) {
  std::string city;
  try {
    db.get()->operator<<("select city from favorite where username = ?;")
            << username >> city;
  } catch (std::exception& e) {
    std::cerr << e.what();
  };
  return city;
}
void Connector::Setup(std::string username) {
  try {
    db.get()->operator<<("insert into favorite (username,city) values (?,?);")
        << username << "";
  } catch (std::exception& e) {
    std::cerr << e.what();
  };
}

void Connector::Update(std::string city, std::string username) {
  try {
    db.get()->operator<<("update favorite set city = ? where username = ?;")
        << city << username;
  } catch (std::exception& e) {
    std::cerr << e.what();
  };
}

Connector::Connector() {
  sqlite::database tmp("dbfile.db");
  tmp << "create table if not exists favorite ("
         "   _id integer primary key autoincrement not null,"
         "   username text unique not null,"
         "   city text"
         ");";
  db = std::make_shared<sqlite::database>(tmp);
};