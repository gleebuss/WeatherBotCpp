#include <string>
#include <vector>

///
/// \param str - строка в которой есть лишние пробелы в начале и в конце.
/// \return Функция возвращает строку без лишних пробелов.
std::string trim(const std::string &str);

///
/// \param str - строка в которой есть '\\n', которые не преобразуются в перенос
/// строки. \return Функуця возвращает строку с переносами строки.
std::string unescapeString(const std::string &str);

/// \class Answers
/// \brief Класс, отвечающий за тип ответа клиенту.
///
/// Данный класс предоставляет различные ответы клиенту.
struct Answers {
  ///
  /// \return Функция возвращает ответ бота при команде  /start.
  static std::string start();
  ///
  /// \return Функция возвращает ответ бота при команде  /about.
  static std::string about();
  ///
  /// \return Функция возвращает ответ бота при команде  /help.
  static std::string help();
  ///
  /// \return Функция возвращает ответ бота, если пользователь ошибся с названием
  /// города.
  static std::string invalidCity();
  ///
  /// \return Функция возвращает ответ бота при команде  /favorite.
  static std::string favorite();
  ///
  /// \return Функция возвращает ответ бота, если пользователь ошибся с названием
  /// города.
  static std::string notCity();
  ///
  /// \return Функция возвращает ответ бота, если у пользователя нет любимого города.
  static std::string notFavorite();
  ///
  /// \param data - вектор, который хранит данные о городе.
  /// \return Функция возвращает ответ бота при команде  /info.
  static std::string info(const std::vector<std::string> &data);
};