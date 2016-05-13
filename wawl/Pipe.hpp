#pragma once
#define ENABLE_WAWL_PIPE

#include <utility>

#include "WawlBase.hpp"
#include "FileBaseType.hpp"
#include "SecurityObjects.hpp"

namespace wawl {
	namespace fs {
		namespace pipe {

			inline std::pair<Handle, Handle> createUnnamedPipe() {
				std::pair<Handle, Handle> ret;

				::CreatePipe(
					&ret.first,
					&ret.second,
					nullptr,
					0
					);

				return ret;
			}
			inline std::pair<Handle, Handle> createUnnamedPipe(
				SecurityAttr secAttr,
				Uint32 bufferSize
				) {
				std::pair<Handle, Handle> ret;

				::CreatePipe(
					&ret.first,
					&ret.second,
					&secAttr,
					bufferSize
					);

				return ret;
			}

			enum class AccessMode {
				Duplex = PIPE_ACCESS_DUPLEX,
				Inbound = PIPE_ACCESS_INBOUND,
				Outbound = PIPE_ACCESS_OUTBOUND
			};

			enum class PipeType {
				Byte = PIPE_TYPE_BYTE,
				Message = PIPE_TYPE_MESSAGE,
				MessageStream = PIPE_READMODE_MESSAGE,
			};

			SimpleAccessDesc toAccessDesc(AccessMode mode) {
				switch (mode) {
				case AccessMode::Duplex:
					return SimpleAccessDesc::All;
				case AccessMode::Inbound:
					return SimpleAccessDesc::Write;
				case AccessMode::Outbound:
					return SimpleAccessDesc::Read;
				}
			}
			AccessMode toAccessMode(SimpleAccessDesc desc) {
				switch (desc){
				case SimpleAccessDesc::Write:
					return AccessMode::Outbound;
				case SimpleAccessDesc::Read:
					return AccessMode::Inbound;
				case SimpleAccessDesc::All:
					return AccessMode::Duplex;
				}
			}

			constexpr Uint32 UnlimitedInstances = PIPE_UNLIMITED_INSTANCES;

			inline FileHandle createNamedPipe(
				const Tstring& pipeName,
				AccessMode* accessMode,
				PipeType* pipeType,
				Uint32* instanceLimits,
				Uint32* outBufferSize,
				Uint32* inBufferSize,
				Uint32* timeOut,
				const SecurityAttr* secAttr
				) {
				SecurityAttr sa = (secAttr ? *secAttr : SecurityAttr());

				return
					::CreateNamedPipe(
						pipeName.c_str(),
						(accessMode ? unpackEnum(*accessMode) : PIPE_ACCESS_DUPLEX),
						(pipeType ? unpackEnum(*pipeType) : PIPE_TYPE_BYTE),
						(instanceLimits ? *instanceLimits : UnlimitedInstances),
						(outBufferSize ? *outBufferSize : 256),
						(inBufferSize ? *inBufferSize : 256),
						(timeOut ? *timeOut : 1000),
						&sa
						);
			}
			inline FileHandle createNamedPipe(
				const Tstring& pipeName
				) {
				return
					createNamedPipe(
						pipeName,
						nullptr,
						nullptr,
						nullptr,
						nullptr,
						nullptr,
						nullptr,
						nullptr
						);
			}
			inline FileHandle createNamedPipe(
				const Tstring& pipeName,
				AccessMode accessMode,
				PipeType pipeType
				) {
				return
					createNamedPipe(
						pipeName,
						&accessMode,
						&pipeType,
						nullptr,
						nullptr,
						nullptr,
						nullptr,
						nullptr
						);
			}
			inline FileHandle createNamedPipe(
				const Tstring& pipeName,
				AccessMode accessMode,
				PipeType pipeType,
				Uint32 outBufferSize,
				Uint32 inBufferSize
				) {
				return
					createNamedPipe(
						pipeName,
						&accessMode,
						&pipeType,
						nullptr,
						&outBufferSize,
						&inBufferSize,
						nullptr,
						nullptr
						);
			}
			inline FileHandle createNamedPipe(
				const Tstring& pipeName,
				AccessMode accessMode,
				PipeType pipeType,
				Uint32 outBufferSize,
				Uint32 inBufferSize,
				Uint32 instanceLimits,
				Uint32 timeOut,
				const SecurityAttr& secAttr
				) {
				return
					createNamedPipe(
						pipeName,
						&accessMode,
						&pipeType,
						&instanceLimits,
						&outBufferSize,
						&inBufferSize,
						&timeOut,
						&secAttr
						);
			}

			// open named pipe
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

		} //::wawl::fs::pipe
	} // wawl::fs
} // ::wawl