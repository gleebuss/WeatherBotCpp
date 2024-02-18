#include "../headers/Listeners.hpp"

TgBot::ReplyKeyboardMarkup::Ptr CreateKeyboard(std::vector<std::string> arr) {
  TgBot::ReplyKeyboardMarkup::Ptr keyboard(new TgBot::ReplyKeyboardMarkup);
  keyboard->resizeKeyboard = true;

  std::vector<TgBot::KeyboardButton::Ptr> buttonsRow;
  for (auto i : arr) {
    TgBot::KeyboardButton::Ptr button(new TgBot::KeyboardButton);
    button->text = i;
    buttonsRow.push_back(button);
  }

  keyboard->keyboard.push_back(buttonsRow);
  return keyboard;
};

void Listeners(TgBot::Bot &bot) {
  bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
    if (Connector::getInstance().IsEmpty(message->chat->username))
      Connector::getInstance().Setup(message->chat->username);
    std::vector<std::string> arr = {"/about", "/favorite", "/help"};
    auto keyboard = CreateKeyboard(arr);
    bot.getApi().sendMessage(message->chat->id, Answers::help(), false, 0,
                             keyboard);
  });

  bot.getEvents().onCommand("about", [&bot](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, Answers::about());
  });

  bot.getEvents().onCommand("help", [&bot](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, Answers::help());
  });

  bot.getEvents().onCommand("add", [&bot](TgBot::Message::Ptr message) {
    bool flag = false;
    auto client = Weather_Client(dotenv::getenv("API"));
    auto city = trim(message->text.erase(0, 4));
    if (city.size() > 0 && client.Geocoding(city)) {
      flag = true;
      Connector::getInstance().Update(city, message->chat->username);
    }
    flag ? bot.getApi().sendMessage(message->chat->id, Answers::favorite())
         : bot.getApi().sendMessage(message->chat->id, Answers::notCity());
  });

  bot.getEvents().onCommand("favorite", [&bot](TgBot::Message::Ptr message) {
    auto city = Connector::getInstance().getCity(message->chat->username);
    if (city != "") {
      auto client = Weather_Client(dotenv::getenv("API"));
      client.Geocoding(city);
      bot.getApi().sendMessage(message->chat->id, Answers::info(client.Data()));
    } else
      bot.getApi().sendMessage(message->chat->id, Answers::notFavorite());
  });

  bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
    if (StringTools::startsWith(message->text, "/"))
      return;
    else {
      auto client = Weather_Client(dotenv::getenv("API"));
      bool flag = client.Geocoding(message->text);
      if (flag) {
        auto data = client.Data();
        bot.getApi().sendMessage(message->chat->id, Answers::info(data));
      } else
        bot.getApi().sendMessage(message->chat->id, Answers::invalidCity());
    }
  });
}