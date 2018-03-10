#ifndef LOG_PLUS_PLUS_H
#define LOG_PLUS_PLUS_H

#include "rlutil.h"
#include <iostream> //for logging to the Console
#include <string> //for std::string general usage
#include <fstream> //for TextFile class
#include <iomanip> //for timestamps
#include <ctime> //for timestamps
#include <sstream> //for timestamps

namespace logpp
{
	/*Class for writing colored and formatted output to the console. This class never throws exceptions*/
	class Console final
	{
	public:
		/*Color enum*/
		enum Color
		{
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


		/*Static logging functions*/

		/*prints error message when condition parameter is false*/
		template<typename T>
		inline static void log_assert(bool condition, T data, Color clr = Color::LIGHTRED)
		{
			if (!condition)
				error(data);
		}
		/*Prints a light red error message*/
		template<typename T>
		inline static void error(T data, Color clr = Color::LIGHTRED)
		{
			rlutil::setColor(static_cast<int>(clr));
			std::cout << "[ERROR]: " << data << "\n";
			rlutil::setColor(static_cast<int>(defaultColor));
		}
		/*Prints a light green debug message.*/
		template<typename T>
		inline static void debug(T data, Color clr = Color::LIGHTGREEN)
		{
			rlutil::setColor(static_cast<int>(clr));
			std::cout << "[DEBUG]: " << data << "\n";
			rlutil::setColor(static_cast<int>(defaultColor));
		}
		/*Prints a yellow warning message*/
		template<typename T>
		inline static void warning(T data, Color clr = Color::YELLOW)
		{
			/*Check if debugging is disabled*/
			if (!debuggingEnabled)
				return;
			rlutil::setColor(static_cast<int>(clr));
			std::cout << "[WARNING]: " << data << "\n";
			rlutil::setColor(static_cast<int>(defaultColor));
		}
		/*Prints a white log message*/
		template<typename T>
		inline static void log(T data, Color clr = defaultColor)
		{
			rlutil::setColor(static_cast<int>(clr));
			std::cout << "[LOG]: " << data << "\n";
			rlutil::setColor(static_cast<int>(defaultColor));
		}

		/*Sets default color for log and debug messages*/
		static void setDefaultColor(Color clr);

		/*Disables debugging output*/
		static void disableDebug();

		/*Enables debug*/
		static void enableDebug();

	private:
		/*Prevent instantiation*/
		Console();

		static Color defaultColor;
		static bool debuggingEnabled;

	};

	class TextFile final
	{
	public:
		//Create empty text file
		TextFile();
		//Automatically closes the file if it is open, doesn't throw exceptions
		~TextFile();

		/*<param name="path">The path of the file to open</param>
		  <param name="allow_create">If true, create() will be called to open the file, thus allowing a new file to be created. Defaults to false</param>
		  <exception cref="TextFile::Exception">Thrown when fstream::open fails</exception>*/
		explicit TextFile(std::string path, bool allow_create = false);

		//Opens a file, this function requires the file to exist, and wil throw an exception of type TextFile::Exception if the file doesn't exist
		void open(std::string path);
		//Creates and opens a new file at specified path. Throws an exception of type TextFile::Exception when creation fails
		void create(std::string path);

		//Closes the file. If no file is currently open, this function will throw an exception of type TextFile::Exception
		void close();

		//Writes data to current position in the textfile. Throws an exception of type TextFile::Exception when no file is opened
		void write(std::string text);

		//Moves the cursor to specified location. 0 for start. Throws an exception of type TextFile::Exception when no file is opened
		void moveCursor(long pos);

		//Gets the current cursor position. Throws an exception of type TextFile::Exception when no file is opened
		auto getCursor();

		//Returns true if a file is currently opened
		bool isOpen();

		///Exceptions thrown by TextFile class will be of this type
		class Exception final
		{
		private:
			std::string error;
		public:
			explicit Exception(std::string msg);

			///<returns>Returns an std::string describing the error</returns>
			std::string what();
		};

	private:
		std::fstream file;
	};

	class FileLog final
	{
	public:
		/*Creates an empty log, doesn't open a file for writing*/
		FileLog();

		/*Opens a log at path fileName*/
		explicit FileLog(std::string fileName, bool timestamp = true);

		/*Closes the logging file*/
		~FileLog();

		/*Opens a log at path fileName*/
		void open(std::string fileName, bool timestamp = true);

		/*Closes current logging file*/
		void close();

		/*Writes text to current logging file. Throws an instance of FileLog::Exception when there is currently no log open.
		 *Automatically adds a newline*/
		void write(std::string text, bool timestamp = true);

		/*Returns true if there is currently a file open for logging*/
		bool isOpen();

		/*Class used for exceptions in FileLog*/
		class Exception final
		{
		public:
			explicit Exception(std::string msg);

			///<returns>An std::string describing the error</returns>
			std::string what();
		private:
			std::string error; 
		};

	private:
		TextFile file;
		std::string generateTimeStamp();
	};
}
#endif