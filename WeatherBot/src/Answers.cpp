#include "../headers/Answers.hpp"

std::string Answers::start() {
  auto ans =
      "Привет! Я бот Telegram, который может сообщить информацию о погоде. "
      "\n\nОбщие команды:\n /about - расскажем о создателе.\n\nВ сообщении "
      "бот ожидает получить название города";
  return ans;
};

std::string Answers::about() {
  auto ans = "Проект реализовал студент Алексей Жукович БПМ-21-1";
  return ans;
}

std::string Answers::help() {
  auto ans =
      "Привет! Я Telegram-бот, который может сообщить информацию о погоде. "
      "\n\nОбщие команды:\n /about - расскажем о создателе.\n /favorite - "
      "сообщим о погоде в любимом городе. \n /add <Название города> - "
      "добавим город в любимый \n\nВ сообщении "
      "бот ожидает получить название города";
  return unescapeString(ans);
}
std::string Answers::invalidCity() {
  auto ans = "Проверьте, пожалуйста, название города";
  return ans;
}
std::string Answers::favorite() {
  auto ans =
      "Город добавлен в любимый. \n\nВоспользуйтесь командой /favorite и вы "
      "получите полную информацию о вашем любимом городе";
  return ans;
}
std::string Answers::notCity() {
  auto ans = "Проверьте, пожалуйста, написание города";
  return ans;
}
std::string Answers::notFavorite() {
  auto ans =
      "У вас нет любимого города. \n\nЧтобы добавить город в любимый "
      "воспользуйтесь командой /add <Название города>";
  return unescapeString(ans);
}

std::string Answers::info(const std::vector<std::string> &data) {
  std::string ans =
      "Город: {} \n\nПогодные условия: {}\n\nТемпература: "
      "{}°\nОщущается как: {}°\n\nДавление: {} Па\nВлажность: "
      "{}%\n\nСкорость ветра: {} м/с\nНаправление ветра: {}°";
  for (auto i : data) {
    std::string toReplace = "{}";
    std::size_t pos = ans.find(toReplace);
    ans.replace(pos, toReplace.length(), i);
  }
  return ans;
}

std::string trim(const std::string &str) {
  size_t first = str.find_first_not_of(' ');
  if (first == std::string::npos) return "";

  size_t last = str.find_last_not_of(' ');
  return str.substr(first, last - first + 1);
}

std::string unescapeString(const std::string &str) {
  std::string result;
  for (std::size_t i = 0; i < str.length(); ++i) {
    if (str[i] == '\\' && i + 1 < str.length()) {
      switch (str[i + 1]) {
        case 'n':
          result += '\n';
          break;
        default:
          result += str[i];
          break;
      }
      ++i;
    } else {
      result += str[i];
    }
  }
  return result;
}