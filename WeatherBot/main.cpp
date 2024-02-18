#include <tgbot/tgbot.h>

#include <iostream>

#include "dependencies/dotenv.h"
#include "headers/Listeners.hpp"

/// @mainpage Описание
/// Телеграм-бот, который позволяет узнать погоду в различных городах.


///
/// @brief Функция main, запускающая бота и обрабатывающая команды.
/// @return Код возврата программы.
///
/// Данная функция является точкой входа в программу. Она инициализирует бота,
/// устанавливает соединение с необходимыми сервисами и запускает бесконечный цикл
/// для обработки команд от пользователей.
///
int main() {
  dotenv::init(".env");

  TgBot::Bot bot(dotenv::getenv("TOKEN"));

  Listeners(bot);

  try {
    TgBot::TgLongPoll longPoll(bot);
    while (true) {
      bot.getApi().getUpdates();
      longPoll.start();
    }
  } catch (const TgBot::TgException &e) {
    std::cerr << "Ошибка в работе: " << e.what() << std::endl;
  }

  return 0;
}