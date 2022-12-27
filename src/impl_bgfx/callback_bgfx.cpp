#include "crpch.hpp"

#include <bx/file.h>
#include <filesystem>
#include <bimg/bimg.h>

#include "impl_bgfx/bgfx_callback.hpp"
#include "impl_bgfx/avi_writer.hpp"
#include "debug/logger.hpp"

BgfxCallback::BgfxCallback()
{
	Core::Logger::LogInfo("Constructing BGFX Callbacks");
}

BgfxCallback::~BgfxCallback()
{
}

void BgfxCallback::fatal(const char* _filePath, uint16_t _line, bgfx::Fatal::Enum _code, const char* _str) 
{
	// Something unexpected happened, inform user and bail out
	bx::debugPrintf("Fatal error: 0x%08x: %s", _code, _str);

	// Must terminate, continuing will cause crash anyway
	abort();
}

void BgfxCallback::traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) 
{
	// Filter out all trace logs we don't want to see
	if (_format[0] != '!')
	{
		return;
	}

	// Construct final message to log
	char temp[8192];
	char* out = temp;
	int32_t len = vsnprintf(out, sizeof(temp), _format, _argList);
	if ((int32_t)sizeof(temp) < len)
	{
		out = (char*)alloca(len + 1);
		len = vsnprintf(out, len, _format, _argList);
	}
	out[len - 1] = '\0';

	// Remove first character from the const char array since that will be a '!' and we don't want to log that
	std::string outString = out;
	outString.erase(0, 1);
	
	// Log BGFX message to the console window
	Core::Logger::LogInfo(outString.c_str());
}

void BgfxCallback::profilerBegin(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) 
{
}

void BgfxCallback::profilerBeginLiteral(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) 
{
}

void BgfxCallback::profilerEnd() 
{
}

uint32_t BgfxCallback::cacheReadSize(uint64_t _id) 
{
	return 0;
}

bool BgfxCallback::cacheRead(uint64_t _id, void* _data, uint32_t _size) 
{
	return false;
}

void BgfxCallback::cacheWrite(uint64_t _id, const void* _data, uint32_t _size) 
{
}

void BgfxCallback::screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t /*_size*/, bool _yflip) 
{
	char temp[1024];

	// Save screen shot as PNG.
	bx::snprintf(temp, BX_COUNTOF(temp), "%s.png", _filePath);
	bx::FileWriter writer;
	bx::Error err;
	if (bx::open(&writer, temp, false, &err))
	{
		bimg::imageWritePng(&writer, _width, _height, _pitch, _data, bimg::TextureFormat::RGBA8, _yflip, &err);
		bx::close(&writer);
	}
}

void BgfxCallback::captureBegin(uint32_t _width, uint32_t _height, uint32_t /*_pitch*/, bgfx::TextureFormat::Enum /*_format*/, bool _yflip) 
{
	Core::Logger::LogWarn("Recording video capture...");

	std::string capturePath = "../debug/captures/";

	auto dirIter = std::filesystem::directory_iterator(capturePath);
	int fileCount = 0;
	for (auto& entry : dirIter)
	{
		if (entry.is_regular_file())
		{
			fileCount++;
		}
	}

	std::string captureTitle = std::string("capture_") + std::string(std::to_string(fileCount) + ".avi");

	fileWriter = new bx::FileWriter();
	aviWriter = new AviWriter(fileWriter);

	if (!aviWriter->open((std::string(capturePath) + captureTitle).c_str(), _width, _height, 30, _yflip))
	{
		delete aviWriter;
		aviWriter = nullptr;

		delete fileWriter;
		fileWriter = nullptr;
	}
}

void BgfxCallback::captureEnd() 
{
	Core::Logger::LogWarn("Video capture saved to debug/captures/*.avi");

	if (aviWriter != nullptr)
	{
		aviWriter->close();

		delete aviWriter;
		aviWriter = nullptr;

		delete fileWriter;
		fileWriter = nullptr;
	}
}

void BgfxCallback::captureFrame(const void* _data, uint32_t /*_size*/) 
{
	//Core::Logger::LogWarn("Using capture without callback (a.k.a. pointless) [frame]");

	if (aviWriter != nullptr)
	{
		aviWriter->frame(_data);
	}
}