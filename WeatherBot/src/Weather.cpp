#include "../headers/Weather.hpp"

Weather_Client::Weather_Client(const std::string m_api_key) {
  this->m_api_key = m_api_key;
};
bool Weather_Client::Geocoding(const std::string country) {
  cpr::Response r =
      cpr::Get(cpr::Url{"http://api.openweathermap.org/geo/1.0/direct"},
               cpr::Parameters{{"q", country}, {"appid", this->m_api_key}});
  nlohmann::json json = nlohmann::json::parse(r.text);
  bool flag = false;
  if (json.size() != 0) {
    this->lat = std::to_string(json[0]["lat"].get<double>());
    this->lon = std::to_string(json[0]["lon"].get<double>());
    flag = true;
  }
  return flag;
};

nlohmann::json Weather_Client::Current_Weather() {
  cpr::Response r =
      cpr::Get(cpr::Url{"https://api.openweathermap.org/data/2.5/weather"},
               cpr::Parameters{{"lat", this->lat},
                               {"lon", this->lon},
                               {"appid", this->m_api_key},
                               {"units", "metric"},
                               {"lang", "ru"}});
  nlohmann::json json = nlohmann::json::parse(r.text);
  return json;
};

std::vector<std::string> Weather_Client::Data() {
  auto json = this->Current_Weather();
  std::vector<std::string> data;
  if (!json.empty()) {
    data.push_back(json["name"]);
    data.push_back(json["weather"][0]["description"]);
    data.push_back(std::to_string((int)std::round(json["main"]["temp"].get<float>())));
    data.push_back(std::to_string((int)std::round(json["main"]["feels_like"].get<float>())));
    data.push_back(std::to_string(json["main"]["pressure"].get<int>()));
    data.push_back(std::to_string(json["main"]["humidity"].get<int>()));
    data.push_back(std::to_string(json["wind"]["speed"].get<int>()));
    data.push_back(std::to_string(json["wind"]["deg"].get<int>()));
  }
  return data;
}

// nlohmann::json Weather_Client::Current_Air(std::string& lat, std::string&
// lon) {
//   cpr::Response r = cpr::Get(
//       cpr::Url{"http://api.openweathermap.org/data/2.5/air_pollution"},
//       cpr::Parameters{{"lat", lat}, {"lon", lon}, {"appid",
//       this->m_api_key}});
//   if (r.status_code == 200) {
//     nlohmann::json json = nlohmann::json::parse(r.text);
//     return json;
//   }
// };

// nlohmann::json Weather_Client::Forecast_Air(std::string& lat,
//                                             std::string& lon) {
//   cpr::Response r = cpr::Get(
//       cpr::Url{"http://api.openweathermap.org/data/2.5/air_pollution/forecast"},
//       cpr::Parameters{{"lat", lat}, {"lon", lon}, {"appid",
//       this->m_api_key}});
//   if (r.status_code == 200) {
//     nlohmann::json json = nlohmann::json::parse(r.text);
//     return json;
//   }
// };

// nlohmann::json Weather_Client::Forecast_Data(std::string& lat,
//                                              std::string& lon) {
//   cpr::Response r = cpr::Get(
//       cpr::Url{"http://api.openweathermap.org/data/2.5/forecast"},
//       cpr::Parameters{{"lat", lat}, {"lon", lon}, {"appid",
//       this->m_api_key}});
//   if (r.status_code == 200) {
//     nlohmann::json json = nlohmann::json::parse(r.text);
//     return json;
//   }
// };
