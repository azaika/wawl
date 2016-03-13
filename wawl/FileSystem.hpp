#pragma once
#define ENABLER_WAWL_FILESYSTEM

#include "WawlBase.hpp"
#include "FileBaseType.hpp"
#include "SecurityObjects.hpp"
#include "Console.hpp"

namespace wawl {
	namespace fs {

		// init file handle
		inline FileHandle createFile(
			const Tstring fileName,
			FileCreateProv* createProv,
			AccessDesc* accessDesc,
			FileSharePermit* shareMode,
			SecurityAttr* secAttr,
			FileAttr* fileAttr,
			FileHandle baseFile
			) {
			SecurityAttr sa = (secAttr ? *secAttr : SecurityAttr());

			return ::CreateFile(
				fileName.c_str(),
				(accessDesc ? unpackEnum(*accessDesc) : GENERIC_ALL),
				(shareMode ? unpackEnum(*shareMode) : 0),
				&sa,
				(createProv ? unpackEnum(*createProv) : CREATE_ALWAYS),
				(fileAttr ? unpackEnum(*fileAttr) : FILE_ATTRIBUTE_NORMAL),
				baseFile
				);
		}
		inline FileHandle createFile(
			const Tstring fileName
			) {
			return createFile(
				fileName,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr
				);
		}
		inline FileHandle createFile(
			const Tstring fileName,
			FileCreateProv createProv
			) {
			return createFile(
				fileName,
				&createProv,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				nullptr
				);
		}
		inline FileHandle createFile(
			const Tstring fileName,
			FileCreateProv createProv,
			FileHandle baseFile
			) {
			return createFile(
				fileName,
				&createProv,
				nullptr,
				nullptr,
				nullptr,
				nullptr,
				baseFile
				);
		}
		inline FileHandle createFile(
			const Tstring fileName,
			FileCreateProv createProv,
			AccessDesc accessDesc,
			FileSharePermit shareMode
			) {
			return createFile(
				fileName,
				&createProv,
				&accessDesc,
				&shareMode,
				nullptr,
				nullptr,
				nullptr
				);
		}
		inline FileHandle createFile(
			const Tstring fileName,
			FileCreateProv createProv,
			AccessDesc accessDesc,
			FileSharePermit shareMode,
			SecurityAttr secAttr,
			FileAttr fileAttr
			) {
			return createFile(
				fileName,
				&createProv,
				&accessDesc,
				&shareMode,
				&secAttr,
				&fileAttr,
				nullptr
				);
		}
		inline FileHandle createFile(
			const Tstring fileName,
			FileCreateProv createProv,
			AccessDesc accessDesc,
			FileSharePermit shareMode,
			SecurityAttr secAttr,
			FileAttr fileAttr,
			FileHandle baseFile
			) {
			return createFile(
				fileName,
				&createProv,
				&accessDesc,
				&shareMode,
				&secAttr,
				&fileAttr,
				baseFile
				);
		}

		inline FileHandle openNamedPipe(
			const Tstring& pipeName,
			SimpleAccessDesc accessMode
			) {
			return ::CreateFile(
				pipeName.c_str(),
				unpackEnum(accessMode),
				0,
				nullptr,
				OPEN_EXISTING,
				0,
				0
				);
		}

		inline std::int64_t getFileSize(FileHandle file) {
			::LARGE_INTEGER li;
			if (::GetFileSizeEx(file, &li))
				throw static_cast<Error>(::GetLastError());

			return static_cast<std::int64_t>(li.QuadPart);
		}

		inline bool readFile(
			FileHandle file,
			Tstring& buf,
			std::size_t n
			) {
			Uint32 readSize;

			buf.resize(n + 1);

			bool isSuccess =
				::ReadFile(
					file,
					&buf[0],
					n,
					&readSize,
					nullptr
					) != 0;

			buf.resize(readSize);

			return isSuccess;
		}

		inline bool writeFile(FileHandle file, const Tstring& str) {
			Uint32 writtenSize;

			return
				::WriteFile(
					file,
					str.c_str(),
					str.size() + 1,
					&writtenSize,
					nullptr
					) != 0;
		}

	} // ::wawl::fs
} // ::wawl