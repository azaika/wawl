#pragma once
#define ENABLER_WAWL_FILESYSTEM

#include "BaseType.hpp"
#include "Error.hpp"
#include "SecurityObjects.hpp"
#include "Console.hpp"

namespace wawl {
	namespace fs {

		using FileHandle = Handle;

		// startup option of application
		enum class StartupOption : Uint32 {
			Fullscreen = STARTF_RUNFULLSCREEN,
			ForceChangeCursor = STARTF_FORCEONFEEDBACK,
			ForceImmutCursor = STARTF_FORCEOFFFEEDBACK,
			NoPinningTaskbar = STARTF_PREVENTPINNING || STARTF_TITLEISAPPID,
			RelateTitleWithAppID = STARTF_TITLEISAPPID,
			RelateTitleWithLnk = STARTF_TITLEISLINKNAME
		};

		// file access descriptor
		enum class AccessDesc : Uint32 {
			None = NULL,
			All = GENERIC_ALL,
			Execute = GENERIC_EXECUTE,
			Read = GENERIC_READ,
			Write = GENERIC_WRITE,
			Delete = DELETE,
			ReadSecurityCtrl = READ_CONTROL,
			EnableSync = SYNCHRONIZE,
			WriteDAC = WRITE_DAC,
			ChangeOwner = WRITE_OWNER,
			RightAll = STANDARD_RIGHTS_ALL,
			RightNormal = STANDARD_RIGHTS_REQUIRED,
			AccessSysSecurity = ACCESS_SYSTEM_SECURITY,
			AllowMaximum = MAXIMUM_ALLOWED,
			RightAllSpecificDesc = SPECIFIC_RIGHTS_ALL
		};

		// file share permission
		enum class FileSharePermit : Uint32 {
			None = NULL,
			Delete = FILE_SHARE_DELETE,
			Read = FILE_SHARE_READ,
			Write = FILE_SHARE_WRITE
		};

		// file creation provision
		enum class FileCreateProv : Uint32 {
			New = CREATE_NEW,
			AlwaysNew = CREATE_ALWAYS,
			OpenExisting = OPEN_EXISTING,
			AlwaysOpen = OPEN_ALWAYS,
			ClearExisting = TRUNCATE_EXISTING
		};

		// file attribute
		enum class FileAttr : Uint32 {
			Archive = FILE_ATTRIBUTE_ARCHIVE,
			Encrypt = FILE_ATTRIBUTE_ENCRYPTED,
			Hide = FILE_ATTRIBUTE_HIDDEN,
			Normal = FILE_ATTRIBUTE_NORMAL,
			NotIndexed = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
			Offline = FILE_ATTRIBUTE_OFFLINE,
			ReadOnly = FILE_ATTRIBUTE_READONLY,
			System = FILE_ATTRIBUTE_SYSTEM,
			Temporary = FILE_ATTRIBUTE_TEMPORARY,

			NoCaching = FILE_FLAG_WRITE_THROUGH,
			Overlapp = FILE_FLAG_OVERLAPPED,
			NoBuffering = FILE_FLAG_NO_BUFFERING,
			RandomAccess = FILE_FLAG_RANDOM_ACCESS,
			SequentialAccess = FILE_FLAG_SEQUENTIAL_SCAN,
			CloseToDelete = FILE_FLAG_DELETE_ON_CLOSE,
			Buckup = FILE_FLAG_BACKUP_SEMANTICS,
			UsePosixSemantics = FILE_FLAG_POSIX_SEMANTICS,
			NoReparsing = FILE_FLAG_OPEN_REPARSE_POINT,
			NoRecall = FILE_FLAG_OPEN_NO_RECALL,

			Anonymous = SECURITY_ANONYMOUS,
			Identification = SECURITY_IDENTIFICATION,
			Impersonation = SECURITY_IMPERSONATION,
			Delegation = SECURITY_IMPERSONATION,
			DynamicTracking = SECURITY_CONTEXT_TRACKING,
			EffectiveOnly = SECURITY_EFFECTIVE_ONLY,
			EnableSecurityCamouflage = SECURITY_SQOS_PRESENT
		};

		// init file handle
		FileHandle createFile(
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
		FileHandle createFile(
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
		FileHandle createFile(
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
		FileHandle createFile(
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
		FileHandle createFile(
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
		FileHandle createFile(
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
		FileHandle createFile(
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
		

	} // ::wawl::fs
} // ::wawl