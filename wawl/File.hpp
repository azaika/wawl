#pragma once
#define ENABLE_WAWL_FILE

#include "WawlBase.hpp"
#include "FileBaseType.hpp"
#include "SecurityObjects.hpp"

namespace wawl {
	namespace fs {

		// init file handle
		inline FileHandle createFile(
			const Tstring fileName,
			FileCreateProv* createProv,
			UnifyEnum<AccessDesc>* accessDescs,
			FileSharePermit* shareMode,
			SecurityAttr* secAttr,
			UnifyEnum<FileAttr>* fileAttrs,
			FileHandle baseFile
			) {
			SecurityAttr sa = (secAttr ? *secAttr : SecurityAttr());

			return ::CreateFile(
				fileName.c_str(),
				(accessDescs ? accessDescs->get() : GENERIC_ALL),
				(shareMode ? unpackEnum(*shareMode) : 0),
				&sa,
				(createProv ? unpackEnum(*createProv) : CREATE_ALWAYS),
				(fileAttrs ? fileAttrs->get() : FILE_ATTRIBUTE_NORMAL),
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
			UnifyEnum<AccessDesc> accessDescs,
			FileSharePermit shareMode
			) {
			return createFile(
				fileName,
				&createProv,
				&accessDescs,
				&shareMode,
				nullptr,
				nullptr,
				nullptr
				);
		}
		inline FileHandle createFile(
			const Tstring fileName,
			FileCreateProv createProv,
			UnifyEnum<AccessDesc> accessDescs,
			FileSharePermit shareMode,
			SecurityAttr secAttr,
			UnifyEnum<FileAttr> fileAttrs
			) {
			return createFile(
				fileName,
				&createProv,
				&accessDescs,
				&shareMode,
				&secAttr,
				&fileAttrs,
				nullptr
				);
		}
		inline FileHandle createFile(
			const Tstring fileName,
			FileCreateProv createProv,
			UnifyEnum<AccessDesc> accessDescs,
			FileSharePermit shareMode,
			SecurityAttr secAttr,
			UnifyEnum<FileAttr> fileAttrs,
			FileHandle baseFile
			) {
			return createFile(
				fileName,
				&createProv,
				&accessDescs,
				&shareMode,
				&secAttr,
				&fileAttrs,
				baseFile
				);
		}


		// get file size in byte 
		inline std::int64_t getFileSize(FileHandle file) {
			::LARGE_INTEGER li;

			if (::GetFileSizeEx(file, &li))
				throw static_cast<Error>(::GetLastError());

			return static_cast<std::int64_t>(li.QuadPart);
		}

		// read text from file and write it buffer
		inline bool readFile(
			FileHandle file,
			Tstring& buf,
			std::uint32_t n
			) {
			::DWORD readSize;

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

		// write text to file
		inline bool writeFile(FileHandle file, const Tstring& str) {
			::DWORD writtenSize;

			return
				::WriteFile(
					file,
					str.c_str(),
					static_cast<std::uint32_t>(str.size() + 1),
					&writtenSize,
					nullptr
					) != 0;
		}

		// copy a file (not an async function)
		inline bool copyFile(
			const Tstring& baseFileName,
			const Tstring& newFileName,
			bool isOverwrite = true
			) {
			return ::CopyFile(
				baseFileName.c_str(),
				newFileName.c_str(),
				isOverwrite
				) != 0;
		}

		inline bool deleteFile(const Tstring& fileName) {
			return ::DeleteFile(fileName.c_str()) != 0;
		}

		inline FileType getFileType(FileHandle file) {
			return static_cast<FileType>(::GetFileType(file));
		}

		inline UnifyEnum<FileAttr> getFileAttrs(const Tstring& fileName) {
			return UnifyEnum<FileAttr>(::GetFileAttributes(fileName.c_str()));
		}

		// get full filepath of specified filepath
		inline Tstring getFileFullPath(const Tstring& fileName) {
			std::uint32_t needSize =
				::GetFullPathName(
					fileName.c_str(), 0, nullptr, nullptr
					);

			Tstring ret;
			ret.resize(needSize);

			::GetFullPathName(
				fileName.c_str(),
				needSize + 1,
				&ret[0],
				nullptr
				);

			return ret;
		}

	} // ::wawl::fs
} // ::wawl