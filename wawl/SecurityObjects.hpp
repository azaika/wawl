#pragma once
#define ENABLE_WAWL_SECURITYOBJECTS

#include "BaseType.hpp"

namespace wawl {
	namespace fs {

		// security descriptor
		struct SecurityDesc : ::SECURITY_DESCRIPTOR {
			SecurityDesc() {
				::InitializeSecurityDescriptor(
					this,
					SECURITY_DESCRIPTOR_REVISION
				);
			}
			
			SecurityDesc(const SecurityDesc&) = default;
			SecurityDesc& operator = (const SecurityDesc&) = default;
		};

		// security attributes
		struct SecurityAttr : ::SECURITY_ATTRIBUTES {
			SecurityAttr(bool doInteritHandle = false) {
				nLength = sizeof(SecurityAttr);
				bInheritHandle = doInteritHandle;
			}

			SecurityAttr(bool doInheritHandle, SecurityDesc& secDesc) :
				SecurityAttr(doInheritHandle) {
				lpSecurityDescriptor = &secDesc;
			}
		};

	} // ::wawl::fs
} // ::wawl