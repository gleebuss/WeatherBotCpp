#include <memory>
#include <sqlite_modern_cpp.h>

/// \class Connector
/// \brief Класс, отвечающий за соеднинение с бд.
class Connector {
 public:
  static Connector &getInstance();
  /// Функция проверяет есть ли пользователь в бд.
  ///  \param username -  id пользователя в телеграмме.
  /// \return Функия возвращает true если да.
  bool IsEmpty(std::string username);

  /// Функция добавляет пользователя в бд.
  ///  \param username -  id пользователя в телеграмме.
  void Setup(std::string username);

  /// Функция обновляет любимый город у пользователя.
  ///  \param username -  id пользователя в телеграмме.
  ///  \param city -  название города.
  void Update(std::string city, std::string username);

  ///  \param username -  id пользователя в телеграмме.
  /// \return Функция возвращает строку с любимым городом пользователя.
  std::string getCity(std::string username);

  Connector(const Connector &) = delete;
  Connector &operator=(const Connector &) = delete;
  Connector(Connector &&) = delete;
  Connector &operator=(Connector &&) = delete;

 private:
  /// Указатель на бд.
  ///  \var db
  std::shared_ptr<sqlite::database> db;
  Connector();
};