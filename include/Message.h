#pragma once

#include "Math.h"

//0xfd is new line
//0xff is end of text
/*0xfe is special
	Next byte is length of structure
	Next comes where to branch
	if 0:
		Next halfword ???
		if 0:
			Next byte is what to do
			Last byte (L)
			if 0:
				str = L - numStars
*/

struct Message
{
	// static wchar_t chars = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
	// 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	// 'W', 'X', 'Y', 'Z', '「', '」', '?', '!', '~', ',', '“', '”', '•', 'a', 'b', 'c',
	// 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
	// 't', 'u', 'v', 'w', 'x', 'y', 'z', '-', '.','\'', ':', ';', '&', ' ', '/', ' ',
	// '€', ' ', '‚', 'ƒ', '„', '…', '†', '‡', '^', '‰', 'Š', '<', 'Œ', ' ', 'Ž', ' ',
	// ' ', '‘', '’', ' ', ' ', '•', '–', '—', '˜', '™', 'š', '>', 'œ', ' ', 'ž', 'Ÿ',
	// ' ', '¡', '¢', '£', '¤', '¥', '¦', '§', '¨', '©', 'ª', '«', '¬', '­', '®', '¯',
	// '°', '±', '²', '³', '´', 'µ', '¶', '•', '¸', '¹', 'º', '»', '¼', '½', '¾', '¿',
	// 'À', 'Á', 'Â', 'Ã', 'Ä', 'Å', 'Æ', 'Ç', 'È', 'É', 'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï',
	// 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', '×', 'Ø', 'Ù', 'Ú', 'Û', 'Ü', 'Ý', 'Þ', 'ß'};

	u32 textOffset;
	s16 textBoxWidth;
	s16 textBoxHeight; // in lines

	static void LoadTextVS();
	static void SetTextGlobalsVS();

	static void PrepareTalk();
	static void EndTalk();

	static void AddChar(char charInFontEncoding);
	static void Display(u32 msgID); // calls DisplayText
	static void DisplayText(u16 msgID);

	static void DisplaySaving(u16 savingMessageID);

	// for menus
	static void DisplaySaveStatusText(u16 msgID);
	static void DisplayLevelClearText(u16 firstButtonMsgID, s8 clearedLevelID);
	static void DisplayVsExitText(u16 vsMsgID);
	static void DisplayPauseText(u16 firstButtonMsgID, u8 levelID);
	static void DisplayPauseTextVS(u16 vsMsgID);
	static void DisplayControllerModeText(u16 firstButtonMsgID);
	static void DisplayOptionsMenuText(u16 firstButtonMsgID);
	static void DisplaySaveMenuText(u16 firstButtonMsgID);
	static void DisplayDontSaveText(u16 firstButtonMsgID);

	static void DisplayCourseNameForStarSelect(u32 courseID);
	static void DisplayStarNameForStarSelect(u32 starID);

	static bool UpdateWindow();
	static void Update();

	static void ResetAllGlobals();
};

struct MESG_File;

struct MsgIDCharEntry
{
	u16 perCharID;
	u16 msgID;
};

extern u8 MSG_BOX_CURR_LEFT_X;
extern u8 MSG_BOX_CURR_TOP_Y;
extern u8 MSG_BOX_MIN_LEFT_X;
extern u8 MSG_BOX_MIN_TOP_Y;
extern u8 MSG_BOX_CENTER_X;
extern u8 MSG_BOX_CENTER_Y;

extern s32 MSG_LINE_HEIGHT;
extern s32 CURR_MSG_ID;
extern Message* CURR_MSG_PTR;
extern char* CURR_MSG_TEXT_CHAR;
extern Message* MSG_ARR_PTR;
extern MESG_File* MSG_FILE_PTR;
extern MESG_File* VS_MSG_FILE_PTR;
extern MsgIDCharEntry MSG_ID_CHAR_MAP[0x62];
extern u16 UTF16_TO_FONT_TABLE[0x100];
extern u8 TALK_FONT_CHAR_WIDTHS[0x100];

extern u8 MESSAGE_RESULT;
extern bool BOUNCING_MSG_ARROWS_VISIBLE;
extern bool IS_SAVING_MESSAGE_DISPLAYED;
extern u8 SAVE_MESSAGE_TIMER;
extern bool IS_MESSAGE_DISAPPEARING;

using MsgGenTextFunc = void(*)();
