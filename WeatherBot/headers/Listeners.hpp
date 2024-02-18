#include <tgbot/tgbot.h>

#include "../dependencies/dotenv.h"
#include "Answers.hpp"
#include "Connector.hpp"
#include "Weather.hpp"

TgBot::ReplyKeyboardMarkup::Ptr CreateKeyboard(std::vector<std::string> arr);

void Listeners(TgBot::Bot &bot);