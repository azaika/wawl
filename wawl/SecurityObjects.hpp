#pragma once
#define ENABLE_WAWL_SECURITYOBJECTS

#include "BaseType.hpp"

namespace wawl {
	namespace fs {

		// security descriptor
		using SecurityDesc = ::SECURITY_DESCRIPTOR;
		// make initialized security descriptor
		SecurityDesc createSecurityDesc() {
			SecurityDesc sd;
			::InitializeSecurityDescriptor(
				&sd,
				SECURITY_DESCRIPTOR_REVISION
				);

			return sd;
		}

		// security attributes
		using SecurityAttr = ::SECURITY_ATTRIBUTES;
		// make initialized security descriptor
		SecurityAttr createSecurityAttr(bool doInheritHandle) {
			SecurityAttr sa;

			sa.nLength = sizeof(SecurityAttr);
			sa.bInheritHandle = doInheritHandle;
			sa.lpSecurityDescriptor = nullptr;
		}
		SecurityAttr createSecurityAttr(bool doInheritHandle, SecurityDesc& secDesc) {
			SecurityAttr sa;

			sa.nLength = sizeof(SecurityAttr);
			sa.bInheritHandle = doInheritHandle;
			sa.lpSecurityDescriptor = &secDesc;
		}

	} // ::wawl::fs
} // ::wawl