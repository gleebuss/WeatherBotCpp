#include <cpr/cpr.h>

#include <cmath>
#include <json.hpp>
#include <vector>

/// \class Weather_Client
/// \brief Класс, отвечающий за доступ к API.
class Weather_Client {
 private:
  /// API ключ
  ///  \var m_api_key
  std::string m_api_key;
  /// Широта
  ///  \var lat
  std::string lat;
  /// Долгота
  ///  \var lon
  std::string lon;

  Weather_Client() = default;

  ///
  /// \return Функция возвращает json с данными о городе.
  nlohmann::json Current_Weather();
  // nlohmann::json Current_Air(std::string& lat, std::string& lon);

 public:
  /// Создает экземпляр класса Weather_Client и инициализирует необходимые
  /// данные.
  ///  \param m_api_key -  API ключ.
  Weather_Client(const std::string m_api_key);
  /// Функция получает и обрабатывает json с данными о долготе и широте города.
  /// \return Функция возвращает код операции функции.
  bool Geocoding(const std::string country);
  ///
  /// \return Функция возвращает std::vector с данными о городе.
  std::vector<std::string> Data();

  // nlohmann::json Forecast_Air(std::string& lat, std::string& lon);
  // nlohmann::json Forecast_Data(std::string& lat, std::string& lon);
};