#include "log++.h"



namespace logpp
{
	/*Implementation for class: Console*/
	/*Template functions will be implemented in the header*/

	Console::Color Console::defaultColor = Color::WHITE;
	bool Console::debuggingEnabled = true;


	void Console::enableDebug()
	{
		debuggingEnabled = true;
	}

	void Console::disableDebug()
	{
		debuggingEnabled = false;
	}
	

	void Console::setDefaultColor(Color clr)
	{
		defaultColor = clr;
	}





	/*Implementation for class: TextFile::Exception*/

	TextFile::Exception::Exception(std::string msg) : error(msg)
	{

	}

	std::string TextFile::Exception::what()
	{
		return error;
	}





	/*Implementation for class: TextFile*/

	TextFile::TextFile()
	{

	}

	TextFile::~TextFile()
	{
		/*Test for file.is_open(), so we don't throw an exception in the destructor when close is called before destroying*/
		if (isOpen())
			close();
	}

	TextFile::TextFile(std::string path, bool allow_create)
	{
		if (allow_create)
			create(path);
		else
			open(path);
	}

	void TextFile::open(std::string path)
	{
		/*Open the file. std::fstream::in flag is there not because we want input, but because it forces the file to exist already.
		To be able to create a file, the user must call TextFile::create()*/
		file.open(path, std::fstream::out | std::fstream::in);
		if (!isOpen())
			throw TextFile::Exception("Failed to open file at path " + path);
	}

	void TextFile::create(std::string path)
	{
		/*Open the file without std::fstream::in flag, because we want to allow creation of a new file*/
		file.open(path, std::fstream::out);
		if (!isOpen())
			throw TextFile::Exception("Failed to create file at path " + path);
	}

	void TextFile::close()
	{
		/*Test if a file is currently open*/
		if (!isOpen())
			throw TextFile::Exception("Unable to close file. Reason: No file is currently open");
		/*Now we are sure we can close the file, do so*/
		file.close();
	}

	void TextFile::write(std::string text)
	{
		/*Check if the file is currently open, and throw an exception if this isn't the case*/
		if (!isOpen())
			throw TextFile::Exception("Unable to write to file. Reason: No file is currently open");
		file << text;
	}

	void TextFile::moveCursor(long pos)
	{
		if (!isOpen())
			throw TextFile::Exception("Unable to move cursor in file. Reason: No file is currently open");
		file.seekp(pos);
	}

	auto TextFile::getCursor()
	{
		if (!isOpen())
			throw TextFile::Exception("Unable to get cursor position in file. Reason: No file is currently open");
		return file.tellp();
	}

	bool TextFile::isOpen()
	{
		return file.is_open();
	}




	/*Implementation for class: FileLog::Exception*/

	FileLog::Exception::Exception(std::string msg) : error(msg)
	{

	}

	std::string FileLog::Exception::what()
	{
		return error;
	}





	/*Implementation for class: FileLog*/

	FileLog::FileLog()
	{

	}

	FileLog::FileLog(std::string fileName, bool timestamp)
	{
		try
		{
			open(fileName);
		}
		catch (TextFile::Exception e)
		{
			/*Rethrow any eventual exceptions*/
			throw FileLog::Exception(e.what());
		}
	}

	FileLog::~FileLog()
	{
		/*Close the file if it is open*/
		if (isOpen())
			file.close();
	}

	bool FileLog::isOpen()
	{
		/*Return if the file is open*/
		return file.isOpen();
	}

	std::string FileLog::generateTimeStamp()
	{
		auto time = std::time(nullptr);
		struct tm timeinfo;
		localtime_s(&timeinfo, &time);

		std::ostringstream stream;
		stream << std::put_time(&timeinfo, "%d-%m-%y %Hh%Mm%Ss");

		std::string stamp = stream.str();
		stamp = "[" + stamp + "] ";

		return stamp;
	}

	void FileLog::open(std::string fileName, bool timestamp)
	{
		/*Try creating a file for logging, and rethrow the exception if something happens*/
		try
		{
			if (timestamp)
			{
				std::string stamp = generateTimeStamp();

				fileName = stamp + fileName;
			}
			file.create(fileName);
		}
		catch (TextFile::Exception error)
		{
			/*Throws a new instance of FileLog::Exception instead of TextFile::Exception. This is because the user doesn't have to
			*expect to be dealing with TextFile when using FileLog*/
			throw FileLog::Exception(error.what());
		}
	}

	void FileLog::close()
	{
		try
		{
			file.close();
		}
		catch (TextFile::Exception error)
		{
			/*Throw a new instance of FileLog::Exception, see also FileLog::open()*/
			throw FileLog::Exception(error.what());
		}
	}


	void FileLog::write(std::string text, bool timestamp)
	{
		try
		{
			/*If timestamp is enabled, write that timestamp to the file*/
			if (timestamp)
			{
				std::string stamp = generateTimeStamp();

				/*Write timestamp to file*/
				file.write(stamp);
			}
			/*Format message (add "[LOG]" and a newline)*/
			text = "[LOG]: " + text;

			/*Write message, with the eventual timestamp already in front*/
			file.write(text);
		}
		catch (TextFile::Exception e)
		{
			/*Rethrow exception with different exception type, see also FileLog::close() and FileLog::open()*/
			throw FileLog::Exception(e.what());
		}
		catch (...)
		{
			throw FileLog::Exception("An unknown exception occurred\n");
		}

	}

};
