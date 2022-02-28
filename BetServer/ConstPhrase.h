#ifndef CONSTPHRASE_H
#define CONSTPHRASE_H

#include <string>


// Инициализация данных до запуска websockets
const std::string     ERROR_CLIENTS =     "Error loading a server client database.";
const std::string     ERROR_TENNIS =      "Error loading a database of tennis games.";


// Протокольные команды
namespace Cmd
{
	const std::string COMMAND =           "command";
	const std::string USER_ID =           "user_id";
	const std::string USER_FROM =         "user_from";
	const std::string MESSAGE =           "message";
	// Идентификатор игры
	const std::string SET_TENNIS =        "set_tennis";
	const std::string TENNIS_ID =         "tennis_id";
	// Устанавливаем сет
	const std::string SET_SET =           "set_set";
	const std::string SET_NUM =           "set_num";
	const std::string SIDE_PLAY =         "side_play";
	// Отмена сета
	const std::string CANCEL_SET =        "cancel_set";
	const std::string CANCEL_MESSAGE =    "cancel_message";
	// Фиксация времени розыгрышей
	const std::string BY_POINT =          "by_point";
	// Счётчик розыгрышей
	const std::string SET_POINT =         "set_point";
	const std::string TYPE_POINT =        "type_point";
	// Отмена времени последнего розыгрыша
	const std::string CANCEL_POINT =      "cancel_point";
	// Двойная ошибка
	const std::string DOUBLE_FAULT =      "double_fault";
	const std::string TYPE_FAULT =        "type_fault";
	// Конец гейма
	const std::string END_GAMES =         "end_games";
	const std::string GAMES_WIN =         "games_win";
	// Конец сета
	const std::string END_SET =           "end_set";
	const std::string END_MESSAGE =       "end_message";
	// Выход из игры
	const std::string END_TENNIS =        "end_tennis";
	const std::string TYPE_END =          "type_end";

}


// Командны верификации
namespace AuthPhrase
{
	// Верификация пользователя
	const std::string AUTH =              "auth";
	const std::string LOGIN =             "login";
	const std::string PASS =              "pass";
	// Сообщения для логирования и отправки пользователю об успешности авторизации
	const std::string AUTH_CMD =          " authorization status is ";
	const std::string AUTH_TRUE =         "АВТОРИЗОВАН:: :: :: :: :: ::НЕАКТИВНО::НЕАКТИВНО::НЕАКТИВНО:: :: ::-1::-1";
	const std::string AUTH_FALSE =        "-1:: :: :: :: :: ::НЕАКТИВНО::НЕАКТИВНО::НЕАКТИВНО:: :: ::-1::Пара логин пароль указана неверно";
	const std::string NOT_AUTH_CMD =      " has not been verified, but is taking action. ";
	const std::string NOT_AUTH =          "-1:: :: :: :: :: ::НЕАКТИВНО::НЕАКТИВНО::НЕАКТИВНО:: :: ::-1::Вначале необходимо авторизоваться";
	// Для проверки AUTH после авторизации
	const std::string AUTH_EARLIER_CMD =  " tries to log in again.";
	const std::string AUTH_EARLIER =      "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Вы уже авторизовались";
	const std::string COM_UNKNOWN_CMD =   " entered an unknown command.";
	const std::string COM_UNKNOWN =       "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Упс!\nЧто-то пошло не так";
}


// Фразы для раздела Теннис
namespace TennisPhrase
{
	// Сообщения для функций проверок типа - "exam":
	// examGameID
	const std::string TENNIS_NOT_CMD =    " has not yet selected a game.";
	const std::string TENNIS_NOT_CHOOSE = "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Вы не выбрали игру";
	// examActivSet
	const std::string SET_NOT_CMD =       " has not yet selected a set.";
	const std::string SET_NOT_CHOOSE =    "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Вы не выбрали сет";
	// examActivGames
	const std::string GAMES_NOT_CMD =     " has not yet selected a game.";
	const std::string GAMES_NOT_CHOOSE =  "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Вы не выбрали гейм";
	// examInactivPress
	const std::string STOP_BYPOINT_CMD =  " has started BY_POINT and is trying to perform more actions.";
	const std::string STOP_BYPOINT =      "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Вначале нажмите на СТОП";

	// Сообщения сервера для обработки событий:
	// Идентификатор игры
	const std::string GAME_SET_CMD =       " has initialized the Tennis-game: ID: ";
	const std::string GAME_IS_SET_1 =      "-1::";                                         // дальше блок ироков
	const std::string GAME_IS_SET_2 =      ":: :: :: ::НЕАКТИВНО::НЕАКТИВНО::НЕАКТИВНО::"; // дальше блок ироков
	const std::string GAME_IS_SET_3 =      "::Запущена игра ID ";
	const std::string GAME_IS_SET_4 =      "\n";
	const std::string GAME_IS_SET_5 =      "::-1";
	const std::string INCORRECT_GAME_CMD = " entered incorrect game ID.";
	const std::string INCORRECT_GAME_ID =  "-1:: :: :: :: :: ::НЕАКТИВНО::НЕАКТИВНО::НЕАКТИВНО:: :: ::-1::Вы указали неверный ID игры";
	const std::string CLOSE_TENNIS_CMD =   " opens a new game without closing the old one.";
	const std::string CLOSE_TENNIS =       "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Вначале сохраните уже открытую игру";
	// Устанавливаем сет
	const std::string INVALID_SET_CMD =    " specified an invalid set number.";
	const std::string INVALID_SET =        "-1::-1::-1:: :: :: ::НЕАКТИВНО::НЕАКТИВНО::НЕАКТИВНО::-1::-1::-1::Вы не выбрали номер сета";
	const std::string COMPL_SET_CMD =      " selected a completed set Num: ";
	const std::string COMPLET_SET =        "-1::-1::-1:: :: :: ::НЕАКТИВНО::НЕАКТИВНО::НЕАКТИВНО::-1::-1::-1::Этот сет уже сыгран";
	const std::string CHOSEN_SET_CMD =     " has selected set Num: ";
	const std::string CHOOSE_PLAYER_CMD =  " and selected player: ";
	const std::string CHOOSE_PLAYER_HOME = "-1::-1::-1::<:: ::0-0::ПУСК::0::0::-1::-1::Открыт сет № ";
	const std::string CHOOSE_PLAYER_AWAY = "-1::-1::-1:: ::<::0-0::ПУСК::0::0::-1::-1::Открыт сет № ";
	const std::string CHOOSE_PLAYER_END =  ".\n::-1";
	const std::string ALREADY_SET_CMD =    " has selected a set, but a different set has already been assigned to him.";
	const std::string ALREADY_SET =        "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Сначала завершите сет N ";
	const std::string NOT_VALID_CMD =      " sent an invalid value to the server.";
	const std::string NOT_VALID =          "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Вы не указали все обязательные значения";
	// Отмена сета
	const std::string SIGNAL_SET_CMD =     " tried to cancel the signaling or archival set N: ";
	const std::string SIGNAL_SET =         "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Нельзя отменить сигнальный или архивный сет";
	const std::string CANC_SET_CMD =       " has canceled set Num: ";
	const std::string CANCELED_SET =       "-1::-1::-1:: :: :: ::НЕАКТИВНО::НЕАКТИВНО::НЕАКТИВНО::-1::-1::Сет № ";
	const std::string CANCELED_SET_END =   " отменен.\n::-1";
	const std::string CANC_SET_BASE =      "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Сет № ";
	const std::string CANC_SET_BASE_END =  " отменен.\n::-1";
	const std::string UNPLAY_SET_CMD =     " selected an unplayed set Num: ";
	const std::string UNPLAYED_SET =       "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Этот сет еще не сыгран. Сет № ";
	// Фиксация времени розыгрышей
	const std::string PRESS_BUT_CMD =      " pressed the button, position ";
	const std::string PRESSED_BUTTON_OFF = "-1::-1::-1::-1::-1::-1::СТОП::-1::-1::-1::-1::-1::-1";
	const std::string PRESSED_BUTTON_ON =  "-1::-1::-1::-1::-1::-1::ПУСК::-1::-1::-1::-1::-1::-1";
	// Счётчик розыгрышей
	const std::string UP_POINT_CMD =       " has increased the value of the points. Points: ";
	const std::string DOWN_POINT_CMD =     " has decremented the value of the points. Points: ";
	const std::string POINT_COUNT_PREV =   "-1::-1::-1::-1::-1::-1::-1::";
	const std::string POINT_COUNT_END =    "::-1::-1::-1::-1::-1";
	// Отмена времени последнего розыгрыша
	const std::string CANC_POINT_CMD =     " canceled the time of last point.";
	const std::string CANCELED_POINT =     "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Последний активный мяч отменен";
	// Двойная ошибка
	const std::string INCR_CMD =           " has increased the double fault. Double fault: ";
	const std::string DECR_CMD =           " has decremented the double fault. Double fault: ";
	const std::string DOUBLE_VALUE_PREV =  "-1::-1::-1::-1::-1::-1::-1::";
	const std::string DOUBLE_VALUE_END =   "::-1::-1::-1::-1";
	// Конец гейма
	const std::string WIN_NOT_VALID =      "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Вы не указали победителя";
	const std::string FINISH_GAME_CMD =    " has completed the game, the score in the set is ";
	const std::string WINNER_CMD =         " The winner is ";
	const std::string FINISH_GAME_1 =      "-1::-1::-1";
	const std::string GAME_HOME =          "::<:: ::";
	const std::string GAME_AWAY =          ":: ::<::";
	const std::string FINISH_GAME_2 =      "::ПУСК::0::0::-1::-1::В гейме победил ";
	const std::string FINISH_GAME_3 =      ".\n::-1";
	const std::string AUTO_CLOSE =         "Automatic closing.";
	const std::string PREV_SIGN_CMD =      " sent a PREV-signal: ";
	// Конец сета
	const std::string CANC_GAMES =         " canceled the current game.";
	const std::string NONE_SIGNAL_CMD =    " has closed the game and set. None signal in set N: ";
	const std::string HAVE_SIGNAL =        " received the signal: ";
	const std::string END_SET_PREV =       "-1::-1::-1:: :: :: ::НЕАКТИВНО::НЕАКТИВНО::НЕАКТИВНО::-1::-1::Сет № ";
	const std::string END_SET_END =        " закрыт.\n::-1";
	// Выход из игры
	const std::string FINISH_SET_CMD =     " tries to close the game when the set is open.";
	const std::string FINISH_SET =         "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Вы не закрыли текущий сет";
	const std::string NOT_VALID_SAVE =     "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::Вы не указали тип сохранения игры";
	const std::string CANS_REP_CMD =       "Canceled sets report was saved successfully.";
	const std::string CANS_REP =           "Отмененные сеты сохранены успешно.";
	const std::string CANS_REP_FAIL_CMD =  "Canceled sets report saved failed.";
	const std::string CANS_REP_FAIL =      "Не удалось сохранить отчет отмененных сетов.";
	const std::string SUCCESS = "success.";
	const std::string SUCCESS_USER =       "успешно.";
	const std::string FAIL =               "fail.";
	const std::string FAIL_USER =          "с ошибкой.";
	const std::string SAVE_RESULT_CMD =    " saved the game. Save result: ";
	const std::string SAVE_RESULT_PREV =   "-1:: :: :: :: :: ::НЕАКТИВНО::НЕАКТИВНО::НЕАКТИВНО:: :: ::Игра сохранена ";
	const std::string SAVE_RESULT_END =    "\n::-1";
}

#endif // !CONSTPHRASE_H