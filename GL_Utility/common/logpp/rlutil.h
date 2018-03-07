#pragma once


/// Define: RLUTIL_USE_ANSI
/// Define this to use ANSI escape sequences also on Windows
/// (defaults to using WinAPI instead).
#if 0
#define RLUTIL_USE_ANSI
#endif

/// Define: RLUTIL_STRING_T
/// Define/typedef this to your preference to override rlutil's string type.
///
/// Defaults to std::string with C++ and char* with C.
#if 0
#define RLUTIL_STRING_T char*
#endif

#ifndef RLUTIL_INLINE
	#ifdef _MSC_VER
		#define RLUTIL_INLINE __inline
	#else
		#define RLUTIL_INLINE static __inline__
	#endif
#endif

#ifdef __cplusplus
	/// Common C++ headers
	#include <iostream>
	#include <string>

#else
	#include <stdio.h> // for getch() / printf()
	#include <string.h> // for strlen()
#endif // __cplusplus

#ifdef _WIN32
	#include <windows.h>  // for WinAPI and Sleep()
	#define _NO_OLDNAMES  // for MinGW compatibility
	#define getch _getch
	#define kbhit _kbhit
#else


#endif // _WIN32


#ifdef __cplusplus
/// Namespace: rlutil
/// In C++ all functions except <getch>, <kbhit> and <gotoxy> are arranged
/// under namespace rlutil. That is because some platforms have them defined
/// outside of rlutil.
namespace rlutil {
#endif

/**
 * Defs: Internal typedefs and macros
 * RLUTIL_STRING_T - String type depending on which one of C or C++ is used
 * RLUTIL_PRINT(str) - Printing macro independent of C/C++
 */

#ifdef __cplusplus
	#ifndef RLUTIL_STRING_T
		typedef std::string RLUTIL_STRING_T;
	#endif // RLUTIL_STRING_T

	#define RLUTIL_PRINT(st) do { std::cout << st; } while(false)
#else // __cplusplus
	#ifndef RLUTIL_STRING_T
		typedef const char* RLUTIL_STRING_T;
	#endif // RLUTIL_STRING_T

	#define RLUTIL_PRINT(st) printf("%s", st)
#endif // __cplusplus

/**
 * Enums: Color codes
 *
 * BLACK - Black
 * BLUE - Blue
 * GREEN - Green
 * CYAN - Cyan
 * RED - Red
 * MAGENTA - Magenta / purple
 * BROWN - Brown / dark yellow
 * GREY - Grey / dark white
 * DARKGREY - Dark grey / light black
 * LIGHTBLUE - Light blue
 * LIGHTGREEN - Light green
 * LIGHTCYAN - Light cyan
 * LIGHTRED - Light red
 * LIGHTMAGENTA - Light magenta / light purple
 * YELLOW - Yellow (bright)
 * WHITE - White (bright)
 */
enum {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	GREY,
	DARKGREY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};

/**
 * Consts: ANSI escape strings
 *
 * ANSI_CLS                - Clears screen
 * ANSI_CONSOLE_TITLE_PRE  - Prefix for changing the window title, print the window title in between
 * ANSI_CONSOLE_TITLE_POST - Suffix for changing the window title, print the window title in between
 * ANSI_ATTRIBUTE_RESET    - Resets all attributes
 * ANSI_CURSOR_HIDE        - Hides the cursor
 * ANSI_CURSOR_SHOW        - Shows the cursor
 * ANSI_CURSOR_HOME        - Moves the cursor home (0,0)
 * ANSI_BLACK              - Black
 * ANSI_RED                - Red
 * ANSI_GREEN              - Green
 * ANSI_BROWN              - Brown / dark yellow
 * ANSI_BLUE               - Blue
 * ANSI_MAGENTA            - Magenta / purple
 * ANSI_CYAN               - Cyan
 * ANSI_GREY               - Grey / dark white
 * ANSI_DARKGREY           - Dark grey / light black
 * ANSI_LIGHTRED           - Light red
 * ANSI_LIGHTGREEN         - Light green
 * ANSI_YELLOW             - Yellow (bright)
 * ANSI_LIGHTBLUE          - Light blue
 * ANSI_LIGHTMAGENTA       - Light magenta / light purple
 * ANSI_LIGHTCYAN          - Light cyan
 * ANSI_WHITE              - White (bright)
 * ANSI_BACKGROUND_BLACK   - Black background
 * ANSI_BACKGROUND_RED     - Red background
 * ANSI_BACKGROUND_GREEN   - Green background
 * ANSI_BACKGROUND_YELLOW  - Yellow background
 * ANSI_BACKGROUND_BLUE    - Blue background
 * ANSI_BACKGROUND_MAGENTA - Magenta / purple background
 * ANSI_BACKGROUND_CYAN    - Cyan background
 * ANSI_BACKGROUND_WHITE   - White background
 */
const RLUTIL_STRING_T ANSI_CLS                = "\033[2J\033[3J";
const RLUTIL_STRING_T ANSI_CONSOLE_TITLE_PRE  = "\033]0;";
const RLUTIL_STRING_T ANSI_CONSOLE_TITLE_POST = "\007";
const RLUTIL_STRING_T ANSI_ATTRIBUTE_RESET    = "\033[0m";
const RLUTIL_STRING_T ANSI_CURSOR_HIDE        = "\033[?25l";
const RLUTIL_STRING_T ANSI_CURSOR_SHOW        = "\033[?25h";
const RLUTIL_STRING_T ANSI_CURSOR_HOME        = "\033[H";
const RLUTIL_STRING_T ANSI_BLACK              = "\033[22;30m";
const RLUTIL_STRING_T ANSI_RED                = "\033[22;31m";
const RLUTIL_STRING_T ANSI_GREEN              = "\033[22;32m";
const RLUTIL_STRING_T ANSI_BROWN              = "\033[22;33m";
const RLUTIL_STRING_T ANSI_BLUE               = "\033[22;34m";
const RLUTIL_STRING_T ANSI_MAGENTA            = "\033[22;35m";
const RLUTIL_STRING_T ANSI_CYAN               = "\033[22;36m";
const RLUTIL_STRING_T ANSI_GREY               = "\033[22;37m";
const RLUTIL_STRING_T ANSI_DARKGREY           = "\033[01;30m";
const RLUTIL_STRING_T ANSI_LIGHTRED           = "\033[01;31m";
const RLUTIL_STRING_T ANSI_LIGHTGREEN         = "\033[01;32m";
const RLUTIL_STRING_T ANSI_YELLOW             = "\033[01;33m";
const RLUTIL_STRING_T ANSI_LIGHTBLUE          = "\033[01;34m";
const RLUTIL_STRING_T ANSI_LIGHTMAGENTA       = "\033[01;35m";
const RLUTIL_STRING_T ANSI_LIGHTCYAN          = "\033[01;36m";
const RLUTIL_STRING_T ANSI_WHITE              = "\033[01;37m";
const RLUTIL_STRING_T ANSI_BACKGROUND_BLACK   = "\033[40m";
const RLUTIL_STRING_T ANSI_BACKGROUND_RED     = "\033[41m";
const RLUTIL_STRING_T ANSI_BACKGROUND_GREEN   = "\033[42m";
const RLUTIL_STRING_T ANSI_BACKGROUND_YELLOW  = "\033[43m";
const RLUTIL_STRING_T ANSI_BACKGROUND_BLUE    = "\033[44m";
const RLUTIL_STRING_T ANSI_BACKGROUND_MAGENTA = "\033[45m";
const RLUTIL_STRING_T ANSI_BACKGROUND_CYAN    = "\033[46m";
const RLUTIL_STRING_T ANSI_BACKGROUND_WHITE   = "\033[47m";
// Remaining colors not supported as background colors



/// Function: getANSIColor
/// Return ANSI color escape sequence for specified number 0-15.
///
/// See <Color Codes>
RLUTIL_INLINE RLUTIL_STRING_T getANSIColor(const int c) {
	switch (c) {
		case BLACK       : return ANSI_BLACK;
		case BLUE        : return ANSI_BLUE; // non-ANSI
		case GREEN       : return ANSI_GREEN;
		case CYAN        : return ANSI_CYAN; // non-ANSI
		case RED         : return ANSI_RED; // non-ANSI
		case MAGENTA     : return ANSI_MAGENTA;
		case BROWN       : return ANSI_BROWN;
		case GREY        : return ANSI_GREY;
		case DARKGREY    : return ANSI_DARKGREY;
		case LIGHTBLUE   : return ANSI_LIGHTBLUE; // non-ANSI
		case LIGHTGREEN  : return ANSI_LIGHTGREEN;
		case LIGHTCYAN   : return ANSI_LIGHTCYAN; // non-ANSI;
		case LIGHTRED    : return ANSI_LIGHTRED; // non-ANSI;
		case LIGHTMAGENTA: return ANSI_LIGHTMAGENTA;
		case YELLOW      : return ANSI_YELLOW; // non-ANSI
		case WHITE       : return ANSI_WHITE;
		default: return "";
	}
}

/// Function: getANSIBackgroundColor
/// Return ANSI background color escape sequence for specified number 0-15.
///
/// See <Color Codes>
RLUTIL_INLINE RLUTIL_STRING_T getANSIBackgroundColor(const int c) {
	switch (c) {
		case BLACK  : return ANSI_BACKGROUND_BLACK;
		case BLUE   : return ANSI_BACKGROUND_BLUE;
		case GREEN  : return ANSI_BACKGROUND_GREEN;
		case CYAN   : return ANSI_BACKGROUND_CYAN;
		case RED    : return ANSI_BACKGROUND_RED;
		case MAGENTA: return ANSI_BACKGROUND_MAGENTA;
		case BROWN  : return ANSI_BACKGROUND_YELLOW;
		case GREY   : return ANSI_BACKGROUND_WHITE;
		default: return "";
	}
}

/// Function: setColor
/// Change color specified by number (Windows / QBasic colors).
/// Don't change the background color
///
/// See <Color Codes>
RLUTIL_INLINE void setColor(int c) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFFF0) | (WORD)c); // Foreground colors take up the least significant byte
#else
	RLUTIL_PRINT(getANSIColor(c));
#endif
}

/// Function: setBackgroundColor
/// Change background color specified by number (Windows / QBasic colors).
/// Don't change the foreground color
///
/// See <Color Codes>
RLUTIL_INLINE void setBackgroundColor(int c) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFF0F) | (((WORD)c) << 4)); // Background colors take up the second-least significant byte
#else
	RLUTIL_PRINT(getANSIBackgroundColor(c));
#endif
}

/// Function: saveDefaultColor
/// Call once to preserve colors for use in resetColor()
/// on Windows without ANSI, no-op otherwise
///
/// See <Color Codes>
/// See <resetColor>
RLUTIL_INLINE int saveDefaultColor(void) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	static char initialized = 0; // bool
	static WORD attributes;

	if (!initialized) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		attributes = csbi.wAttributes;
		initialized = 1;
	}
	return (int)attributes;
#else
	return -1;
#endif
}

/// Function: resetColor
/// Reset color to default
/// Requires a call to saveDefaultColor() to set the defaults
///
/// See <Color Codes>
/// See <setColor>
/// See <saveDefaultColor>
RLUTIL_INLINE void resetColor(void) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)saveDefaultColor());
#else
	RLUTIL_PRINT(ANSI_ATTRIBUTE_RESET);
#endif
}

#ifdef __cplusplus
}; // namespace rlutil
#endif