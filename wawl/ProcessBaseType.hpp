#pragma once
#define WAWL_PROCESS_BASE_TYPE

#include "BaseType.hpp"
#include "Detail.hpp"

namespace wawl {
	namespace fs {

		// process creation provision
		enum class ProcessCreateProv : std::uint32_t {
			NotInheritJob = CREATE_BREAKAWAY_FROM_JOB,
			NotInheritErrorMode = CREATE_DEFAULT_ERROR_MODE,
			DosMode = CREATE_FORCEDOS,
			CreateNewConsole = CREATE_NEW_CONSOLE,
			CreateNewProcGroup = CREATE_NEW_PROCESS_GROUP,
			NotCreateWindow = CREATE_NO_WINDOW,
			VdmMode = CREATE_SEPARATE_WOW_VDM,
			SharedVdmMode = CREATE_SHARED_WOW_VDM,
			SuspendPrimary = CREATE_SUSPENDED,
			DebugMode = DEBUG_PROCESS,
			NotInheritDebugMode = DEBUG_ONLY_THIS_PROCESS,
			DisallowAccessConsole = DETACHED_PROCESS,

			PriorityLv1 = IDLE_PRIORITY_CLASS,
			PriorityLv2 = BELOW_NORMAL_PRIORITY_CLASS,
			PriorityLv3 = NORMAL_PRIORITY_CLASS,
			PriorityLv4 = ABOVE_NORMAL_PRIORITY_CLASS,
			PriorityLv5 = HIGH_PRIORITY_CLASS,
			MaxPriority = REALTIME_PRIORITY_CLASS
		};

		// process infomation
		using ProcessInfo = ::PROCESS_INFORMATION;

	}

	WAWL_DETAIL_ENABLE_FLAG(fs::ProcessCreateProv)

}