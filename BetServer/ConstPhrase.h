#ifndef CONSTPHRASE_H
#define CONSTPHRASE_H

#include <string>


// ������������� ������ �� ������� websockets
const std::string     ERROR_CLIENTS =     "Error loading a server client database.";
const std::string     ERROR_TENNIS =      "Error loading a database of tennis games.";


// ������������ �������
namespace Cmd
{
	const std::string COMMAND =           "command";
	const std::string USER_ID =           "user_id";
	const std::string USER_FROM =         "user_from";
	const std::string MESSAGE =           "message";
	// ������������� ����
	const std::string SET_TENNIS =        "set_tennis";
	const std::string TENNIS_ID =         "tennis_id";
	// ������������� ���
	const std::string SET_SET =           "set_set";
	const std::string SET_NUM =           "set_num";
	const std::string SIDE_PLAY =         "side_play";
	// ������ ����
	const std::string CANCEL_SET =        "cancel_set";
	const std::string CANCEL_MESSAGE =    "cancel_message";
	// �������� ������� ����������
	const std::string BY_POINT =          "by_point";
	// ������� ����������
	const std::string SET_POINT =         "set_point";
	const std::string TYPE_POINT =        "type_point";
	// ������ ������� ���������� ���������
	const std::string CANCEL_POINT =      "cancel_point";
	// ������� ������
	const std::string DOUBLE_FAULT =      "double_fault";
	const std::string TYPE_FAULT =        "type_fault";
	// ����� �����
	const std::string END_GAMES =         "end_games";
	const std::string GAMES_WIN =         "games_win";
	// ����� ����
	const std::string END_SET =           "end_set";
	const std::string END_MESSAGE =       "end_message";
	// ����� �� ����
	const std::string END_TENNIS =        "end_tennis";
	const std::string TYPE_END =          "type_end";

}


// �������� �����������
namespace AuthPhrase
{
	// ����������� ������������
	const std::string AUTH =              "auth";
	const std::string LOGIN =             "login";
	const std::string PASS =              "pass";
	// ��������� ��� ����������� � �������� ������������ �� ���������� �����������
	const std::string AUTH_CMD =          " authorization status is ";
	const std::string AUTH_TRUE =         "�����������:: :: :: :: :: ::���������::���������::���������:: :: ::-1::-1";
	const std::string AUTH_FALSE =        "-1:: :: :: :: :: ::���������::���������::���������:: :: ::-1::���� ����� ������ ������� �������";
	const std::string NOT_AUTH_CMD =      " has not been verified, but is taking action. ";
	const std::string NOT_AUTH =          "-1:: :: :: :: :: ::���������::���������::���������:: :: ::-1::������� ���������� ��������������";
	// ��� �������� AUTH ����� �����������
	const std::string AUTH_EARLIER_CMD =  " tries to log in again.";
	const std::string AUTH_EARLIER =      "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::�� ��� ��������������";
	const std::string COM_UNKNOWN_CMD =   " entered an unknown command.";
	const std::string COM_UNKNOWN =       "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::���!\n���-�� ����� �� ���";
}


// ����� ��� ������� ������
namespace TennisPhrase
{
	// ��������� ��� ������� �������� ���� - "exam":
	// examGameID
	const std::string TENNIS_NOT_CMD =    " has not yet selected a game.";
	const std::string TENNIS_NOT_CHOOSE = "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::�� �� ������� ����";
	// examActivSet
	const std::string SET_NOT_CMD =       " has not yet selected a set.";
	const std::string SET_NOT_CHOOSE =    "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::�� �� ������� ���";
	// examActivGames
	const std::string GAMES_NOT_CMD =     " has not yet selected a game.";
	const std::string GAMES_NOT_CHOOSE =  "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::�� �� ������� ����";
	// examInactivPress
	const std::string STOP_BYPOINT_CMD =  " has started BY_POINT and is trying to perform more actions.";
	const std::string STOP_BYPOINT =      "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::������� ������� �� ����";

	// ��������� ������� ��� ��������� �������:
	// ������������� ����
	const std::string GAME_SET_CMD =       " has initialized the Tennis-game: ID: ";
	const std::string GAME_IS_SET_1 =      "-1::";                                         // ������ ���� ������
	const std::string GAME_IS_SET_2 =      ":: :: :: ::���������::���������::���������::"; // ������ ���� ������
	const std::string GAME_IS_SET_3 =      "::�������� ���� ID ";
	const std::string GAME_IS_SET_4 =      "\n";
	const std::string GAME_IS_SET_5 =      "::-1";
	const std::string INCORRECT_GAME_CMD = " entered incorrect game ID.";
	const std::string INCORRECT_GAME_ID =  "-1:: :: :: :: :: ::���������::���������::���������:: :: ::-1::�� ������� �������� ID ����";
	const std::string CLOSE_TENNIS_CMD =   " opens a new game without closing the old one.";
	const std::string CLOSE_TENNIS =       "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::������� ��������� ��� �������� ����";
	// ������������� ���
	const std::string INVALID_SET_CMD =    " specified an invalid set number.";
	const std::string INVALID_SET =        "-1::-1::-1:: :: :: ::���������::���������::���������::-1::-1::-1::�� �� ������� ����� ����";
	const std::string COMPL_SET_CMD =      " selected a completed set Num: ";
	const std::string COMPLET_SET =        "-1::-1::-1:: :: :: ::���������::���������::���������::-1::-1::-1::���� ��� ��� ������";
	const std::string CHOSEN_SET_CMD =     " has selected set Num: ";
	const std::string CHOOSE_PLAYER_CMD =  " and selected player: ";
	const std::string CHOOSE_PLAYER_HOME = "-1::-1::-1::<:: ::0-0::����::0::0::-1::-1::������ ��� � ";
	const std::string CHOOSE_PLAYER_AWAY = "-1::-1::-1:: ::<::0-0::����::0::0::-1::-1::������ ��� � ";
	const std::string CHOOSE_PLAYER_END =  ".\n::-1";
	const std::string ALREADY_SET_CMD =    " has selected a set, but a different set has already been assigned to him.";
	const std::string ALREADY_SET =        "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::������� ��������� ��� N ";
	const std::string NOT_VALID_CMD =      " sent an invalid value to the server.";
	const std::string NOT_VALID =          "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::�� �� ������� ��� ������������ ��������";
	// ������ ����
	const std::string SIGNAL_SET_CMD =     " tried to cancel the signaling or archival set N: ";
	const std::string SIGNAL_SET =         "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::������ �������� ���������� ��� �������� ���";
	const std::string CANC_SET_CMD =       " has canceled set Num: ";
	const std::string CANCELED_SET =       "-1::-1::-1:: :: :: ::���������::���������::���������::-1::-1::��� � ";
	const std::string CANCELED_SET_END =   " �������.\n::-1";
	const std::string CANC_SET_BASE =      "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::��� � ";
	const std::string CANC_SET_BASE_END =  " �������.\n::-1";
	const std::string UNPLAY_SET_CMD =     " selected an unplayed set Num: ";
	const std::string UNPLAYED_SET =       "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::���� ��� ��� �� ������. ��� � ";
	// �������� ������� ����������
	const std::string PRESS_BUT_CMD =      " pressed the button, position ";
	const std::string PRESSED_BUTTON_OFF = "-1::-1::-1::-1::-1::-1::����::-1::-1::-1::-1::-1::-1";
	const std::string PRESSED_BUTTON_ON =  "-1::-1::-1::-1::-1::-1::����::-1::-1::-1::-1::-1::-1";
	// ������� ����������
	const std::string UP_POINT_CMD =       " has increased the value of the points. Points: ";
	const std::string DOWN_POINT_CMD =     " has decremented the value of the points. Points: ";
	const std::string POINT_COUNT_PREV =   "-1::-1::-1::-1::-1::-1::-1::";
	const std::string POINT_COUNT_END =    "::-1::-1::-1::-1::-1";
	// ������ ������� ���������� ���������
	const std::string CANC_POINT_CMD =     " canceled the time of last point.";
	const std::string CANCELED_POINT =     "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::��������� �������� ��� �������";
	// ������� ������
	const std::string INCR_CMD =           " has increased the double fault. Double fault: ";
	const std::string DECR_CMD =           " has decremented the double fault. Double fault: ";
	const std::string DOUBLE_VALUE_PREV =  "-1::-1::-1::-1::-1::-1::-1::";
	const std::string DOUBLE_VALUE_END =   "::-1::-1::-1::-1";
	// ����� �����
	const std::string WIN_NOT_VALID =      "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::�� �� ������� ����������";
	const std::string FINISH_GAME_CMD =    " has completed the game, the score in the set is ";
	const std::string WINNER_CMD =         " The winner is ";
	const std::string FINISH_GAME_1 =      "-1::-1::-1";
	const std::string GAME_HOME =          "::<:: ::";
	const std::string GAME_AWAY =          ":: ::<::";
	const std::string FINISH_GAME_2 =      "::����::0::0::-1::-1::� ����� ������� ";
	const std::string FINISH_GAME_3 =      ".\n::-1";
	const std::string AUTO_CLOSE =         "Automatic closing.";
	const std::string PREV_SIGN_CMD =      " sent a PREV-signal: ";
	// ����� ����
	const std::string CANC_GAMES =         " canceled the current game.";
	const std::string NONE_SIGNAL_CMD =    " has closed the game and set. None signal in set N: ";
	const std::string HAVE_SIGNAL =        " received the signal: ";
	const std::string END_SET_PREV =       "-1::-1::-1:: :: :: ::���������::���������::���������::-1::-1::��� � ";
	const std::string END_SET_END =        " ������.\n::-1";
	// ����� �� ����
	const std::string FINISH_SET_CMD =     " tries to close the game when the set is open.";
	const std::string FINISH_SET =         "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::�� �� ������� ������� ���";
	const std::string NOT_VALID_SAVE =     "-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::-1::�� �� ������� ��� ���������� ����";
	const std::string CANS_REP_CMD =       "Canceled sets report was saved successfully.";
	const std::string CANS_REP =           "���������� ���� ��������� �������.";
	const std::string CANS_REP_FAIL_CMD =  "Canceled sets report saved failed.";
	const std::string CANS_REP_FAIL =      "�� ������� ��������� ����� ���������� �����.";
	const std::string SUCCESS = "success.";
	const std::string SUCCESS_USER =       "�������.";
	const std::string FAIL =               "fail.";
	const std::string FAIL_USER =          "� �������.";
	const std::string SAVE_RESULT_CMD =    " saved the game. Save result: ";
	const std::string SAVE_RESULT_PREV =   "-1:: :: :: :: :: ::���������::���������::���������:: :: ::���� ��������� ";
	const std::string SAVE_RESULT_END =    "\n::-1";
}

#endif // !CONSTPHRASE_H