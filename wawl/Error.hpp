﻿#pragma once
#define WAWL_ERROR_HPP

#include "BaseType.hpp"
#include "BaseUtility.hpp"

namespace wawl {

	// WinAPI errors
	// need more
	enum class Error : std::uint32_t {
		Success = ERROR_SUCCESS,
		InvalidFunction = ERROR_INVALID_FUNCTION,
		FileNotFound = ERROR_FILE_NOT_FOUND,
		PathNotFound = ERROR_PATH_NOT_FOUND,
		CannotOpenFiles = ERROR_TOO_MANY_OPEN_FILES,
		AccessDenied = ERROR_ACCESS_DENIED,
		InvalidHandle = ERROR_INVALID_HANDLE,
		StorageTrashed = ERROR_ARENA_TRASHED,
		NotEnoughMemory = ERROR_NOT_ENOUGH_MEMORY,
		InvalidStorageBlock = ERROR_INVALID_BLOCK,
		BadEnvironment = ERROR_BAD_ENVIRONMENT,
		BadFormat = ERROR_BAD_FORMAT,
		InvalidAccess = ERROR_INVALID_ACCESS,
		InvalidData = ERROR_INVALID_DATA,
		OutOfMemory = ERROR_OUTOFMEMORY,
		DriveNotFound = ERROR_INVALID_DRIVE,
		CannotDeleteDirectory = ERROR_CURRENT_DIRECTORY,
		DifferentDevice = ERROR_NOT_SAME_DEVICE,
		NoMoreFiles = ERROR_NO_MORE_FILES,
		MediaAccessProtected = ERROR_WRITE_PROTECT,
		BadUnit = ERROR_BAD_UNIT,
		DeviceNotReady = ERROR_NOT_READY,
		BadCommand = ERROR_BAD_COMMAND,
		CRC = ERROR_CRC,
		BadLengthCommand = ERROR_BAD_LENGTH,
		CannotSeek = ERROR_SEEK,
		NotDOSDisk = ERROR_NOT_DOS_DISK,
		SectorNotFound = ERROR_SECTOR_NOT_FOUND,
		NoPaper = ERROR_OUT_OF_PAPER,
		CannotWrite = ERROR_WRITE_FAULT,
		CannotRead = ERROR_READ_FAULT,
		DeviceNotWork = ERROR_GEN_FAILURE,
		FileSharingViolation = ERROR_SHARING_VIOLATION,
		FileLockViolation = ERROR_LOCK_VIOLATION,
		WrongDisk = ERROR_WRONG_DISK,
		SharingBufferExceeded = ERROR_SHARING_BUFFER_EXCEEDED,
		FileEOF = ERROR_HANDLE_EOF,
		DiskHandlerFull = ERROR_HANDLE_DISK_FULL,
		NotSupported = ERROR_NOT_SUPPORTED,
		NetworkPathNotFound = ERROR_REM_NOT_LIST,
		DuplicateName = ERROR_DUP_NAME,
		BadNetworkPath = ERROR_BAD_NETPATH,
		NetworkBusy = ERROR_NETWORK_BUSY,
		DeviceNotExist = ERROR_DEV_NOT_EXIST,
		TooManyCommands = ERROR_TOO_MANY_CMDS,
		AdaptorHardwareError = ERROR_ADAP_HDW_ERR,
		BadNetworkResponse = ERROR_BAD_NET_RESP,
		UnexpectedNetworkError = ERROR_UNEXP_NET_ERR,
		BadRemoteAdaptor = ERROR_BAD_REM_ADAP,
		PrintQueueFull = ERROR_PRINTQ_FULL,
		NoSpoolSpace = ERROR_NO_SPOOL_SPACE,
		PrintCancelled = ERROR_PRINT_CANCELLED,
		NetNameDeleted = ERROR_NETNAME_DELETED,
		NetworkAccessDenied = ERROR_NETWORK_ACCESS_DENIED,
		BadNetworkDeviceType = ERROR_BAD_DEV_TYPE,
		BadNetworkName = ERROR_BAD_NET_NAME,
		TooManyNames = ERROR_TOO_MANY_NAMES,
		TooManySessions = ERROR_TOO_MANY_SESS,
		ServerPaused = ERROR_SHARING_PAUSED,
		ReqestUnaccepted = ERROR_REQ_NOT_ACCEP,
		DevicePaused = ERROR_REDIR_PAUSED,
		FileExists = ERROR_FILE_EXISTS,
		CannotMakeFile = ERROR_CANNOT_MAKE,
		I24Failed = ERROR_FAIL_I24,
		OutOfStorage = ERROR_OUT_OF_STRUCTURES,
		DeviceNameAlreadyAssigned = ERROR_ALREADY_ASSIGNED,
		InvalidPassword = ERROR_INVALID_PASSWORD,
		InvalidParam = ERROR_INVALID_PARAMETER,
		NetWriteFault = ERROR_NET_WRITE_FAULT,
		NoProcSlots = ERROR_NO_PROC_SLOTS,
		TooManySemaphores = ERROR_TOO_MANY_SEMAPHORES,
		ExclusiveSemaphoreAlreadyOwned = ERROR_EXCL_SEM_ALREADY_OWNED,
		SemaphoreSetted = ERROR_SEM_IS_SET,
		TooManySemaphoreRequests = ERROR_TOO_MANY_SEM_REQUESTS,
		InvalidAtInterruptTime = ERROR_INVALID_AT_INTERRUPT_TIME,
		SemaphoresOwnerDied = ERROR_SEM_OWNER_DIED,
		SemaphoreUserLimit = ERROR_SEM_USER_LIMIT,
		DiskNotChanged = ERROR_DISK_CHANGE,
		DriveLocked = ERROR_DRIVE_LOCKED,
		PipeBroke = ERROR_BROKEN_PIPE,
		OpenFailed = ERROR_OPEN_FAILED,
		BufferOverflow = ERROR_BUFFER_OVERFLOW,
		DiskFull = ERROR_DISK_FULL,
		NoMoreSearchHandles = ERROR_NO_MORE_SEARCH_HANDLES,
		InvalidTargetHandle = ERROR_INVALID_TARGET_HANDLE,
		InvalidCategory = ERROR_INVALID_CATEGORY,
		InvalidVarifySwitch = ERROR_INVALID_VERIFY_SWITCH,
		BadDriverLevel = ERROR_BAD_DRIVER_LEVEL,
		NotImplemented = ERROR_CALL_NOT_IMPLEMENTED,
		SemaphoreTimeout = ERROR_SEM_TIMEOUT,
		NotEnoughBuffer = ERROR_INSUFFICIENT_BUFFER,
		InvalidName = ERROR_INVALID_NAME,
		InvalidLabel = ERROR_INVALID_LABEL,
		NoVolumeLabel = ERROR_NO_VOLUME_LABEL,
		ModuleNotFound = ERROR_MOD_NOT_FOUND,
		ProcNotFound = ERROR_PROC_NOT_FOUND,
		UnnecessaryWaitingForChildren = ERROR_WAIT_NO_CHILDREN,
		DirectAccessHandle = ERROR_DIRECT_ACCESS_HANDLE,
		NegativeSeek = ERROR_NEGATIVE_SEEK,
		DeviceSeekFailed = ERROR_SEEK_ON_DEVICE,
		InvalidJoinTargetUse = ERROR_IS_JOIN_TARGET,
		DriveJoined = ERROR_IS_JOINED,
		DriveSubsted = ERROR_IS_SUBSTED,
		NotJoinedDrive = ERROR_NOT_JOINED,
		NotSebstedDrive = ERROR_NOT_SUBSTED,
		JoinedDriveJoin = ERROR_JOIN_TO_JOIN,
		SubstedDriveSubst = ERROR_SUBST_TO_SUBST,
		JoinedDriveSubst = ERROR_JOIN_TO_SUBST,
		SubstedDriveJoin = ERROR_SUBST_TO_JOIN,
		DriveBusy = ERROR_BUSY_DRIVE,
		SameDrive = ERROR_SAME_DRIVE,
		NotRootDir = ERROR_DIR_NOT_ROOT,
		NotEmptyDir = ERROR_DIR_NOT_EMPTY,
		SubstedPath = ERROR_IS_SUBST_PATH,
		JoinedPath = ERROR_IS_JOIN_PATH,
		BusyPath = ERROR_PATH_BUSY,
		SubstedTarget = ERROR_IS_SUBST_TARGET,
		SystemTraceNotAllowed = ERROR_SYSTEM_TRACE,
		InvalidEventCount = ERROR_INVALID_EVENT_COUNT,
		TooManyMuxwaiters = ERROR_TOO_MANY_MUXWAITERS,
		InvalidListFormat = ERROR_INVALID_LIST_FORMAT,
		TooLongLabel = ERROR_LABEL_TOO_LONG,
		TooManyTCBS = ERROR_TOO_MANY_TCBS,
		SignalRefused = ERROR_SIGNAL_REFUSED,
		SegmentDiscarded = ERROR_DISCARDED,
		SegmentUnlocked = ERROR_NOT_LOCKED,
		BadThreadIDAddres = ERROR_BAD_THREADID_ADDR,
		BadArguments = ERROR_BAD_ARGUMENTS,
		InvalidPath = ERROR_BAD_PATHNAME,
		SignalPending = ERROR_SIGNAL_PENDING,
		MaxThreadsReached = ERROR_MAX_THRDS_REACHED,
		FileLockFailed = ERROR_LOCK_FAILED,
		ResourceBusy = ERROR_BUSY,
		CancelViolation = ERROR_CANCEL_VIOLATION,
		AtomicLockNotSupported = ERROR_ATOMIC_LOCKS_NOT_SUPPORTED,
		InvalidSegmentNumber = ERROR_INVALID_SEGMENT_NUMBER,
		InvalidArgsOrd = ERROR_INVALID_ORDINAL,
		FileAlreadyExists = ERROR_ALREADY_EXISTS,
		InvalidFlagNumber = ERROR_INVALID_FLAG_NUMBER,
		SemaphoreNotFound = ERROR_SEM_NOT_FOUND,
		InvalidStartingCodeSegment = ERROR_INVALID_STARTING_CODESEG,
		InvalidStackSegment = ERROR_INVALID_STACKSEG,
		InvalidModuleType = ERROR_INVALID_MODULETYPE,
		InvalidExeSignature = ERROR_INVALID_EXE_SIGNATURE,
		ExeMarkedInvailed = ERROR_EXE_MARKED_INVALID,
		BadExeFormat = ERROR_BAD_EXE_FORMAT,
		IteratedDataExceeds64K = ERROR_ITERATED_DATA_EXCEEDS_64k,
		InvalidMinAllocSize = ERROR_INVALID_MINALLOCSIZE,
		InvalidDynamicLink = ERROR_DYNLINK_FROM_INVALID_RING,
		IOPLDisabled = ERROR_IOPL_NOT_ENABLED,
		InvalidSegDPL = ERROR_INVALID_SEGDPL,
		AutoDataSegExceeds64K = ERROR_AUTODATASEG_EXCEEDS_64k,
		Ring2SegNotMovable = ERROR_RING2SEG_MUST_BE_MOVABLE,
		RelocChainExceedsSegLimit = ERROR_RELOC_CHAIN_XEEDS_SEGLIM,
		RelocChainInfLoop = ERROR_INFLOOP_IN_RELOC_CHAIN,
		EnvVarNotFound = ERROR_ENVVAR_NOT_FOUND,
		SentSignalNotFound = ERROR_NO_SIGNAL_SENT,
		TooLongFilename = ERROR_FILENAME_EXCED_RANGE,
		Ring2StackInUse = ERROR_RING2_STACK_IN_USE,
		TooLongPathMetaExpansion = ERROR_META_EXPANSION_TOO_LONG,
		InvalidSignalNumber = ERROR_INVALID_SIGNAL_NUMBER,
		Thread1Inactive = ERROR_THREAD_1_INACTIVE,
		SegmentLocked = ERROR_LOCKED,
		TooManyModules = ERROR_TOO_MANY_MODULES,
		LoadModuleNested = ERROR_NESTING_NOT_ALLOWED,
		ExeMachineTypeMismatch = ERROR_EXE_MACHINE_TYPE_MISMATCH,
		ModifyExeSignedBinaryFailed = ERROR_EXE_CANNOT_MODIFY_SIGNED_BINARY,
		ModifyExeStrongSignedBinaryFailed = ERROR_EXE_CANNOT_MODIFY_STRONG_SIGNED_BINARY,
		BadPipe = ERROR_BAD_PIPE,
		PipeBusy = ERROR_PIPE_BUSY,
		PipeNoData = ERROR_NO_DATA,
		PipeNotConnected = ERROR_PIPE_NOT_CONNECTED,
		MoreDataExists = ERROR_MORE_DATA,
		SessionCanceled = ERROR_VC_DISCONNECTED,
		InvalidExtAttrName = ERROR_INVALID_EA_NAME,
		InconsistentEstAttr = ERROR_EA_LIST_INCONSISTENT,

		// and more...
	};

	inline Error getLastError() {
		return static_cast<Error>(::GetLastError());
	}

	inline void setLastError(Error error) {
		::SetLastError(unpackEnum(error));
	}

	inline std::uint32_t errorToStr(Tstring& buf, Error error) {
		buf.resize(512);
		std::uint32_t writtenSize =
			::FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM,
				nullptr,
				unpackEnum(error),
				0,
				&buf[0],
				static_cast<std::uint32_t>(buf.size() + 1),
				nullptr
			);
		buf.resize(writtenSize);

		return writtenSize;
	}

} // ::wawl