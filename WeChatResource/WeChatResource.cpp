// WeChatResource.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "util.h"

//#define WECHATRESOURCE TEXT("WeChatResource.dll.1")

const SuppWxCfg g_Supported_wx_Version[] = {
	{ TEXT("2.6.5.38"), 0x247EF1 ,{3, {0x8A, 0x45, 0xF3}, 3, {0x33, 0xc0, 0x90}}},
	{ TEXT("2.6.6.25"), 0x24BA81 ,{3, {0x8A, 0x45, 0xF3}, 3, {0x33, 0xc0, 0x90}}},
	{ TEXT("2.6.6.28"), 0x24B451 ,{3, {0x8A, 0x45, 0xF3}, 3, {0x33, 0xc0, 0x90}}},
    { TEXT("2.6.6.44"), 0x24B821 ,{3, {0x8A, 0x45, 0xF3}, 3, {0x33, 0xc0, 0x90}}},
    { TEXT("2.6.7.32"), 0x252DB1 ,{3, {0x8A, 0x45, 0xF3}, 3, {0x33, 0xc0, 0x90}}},
};

/* //2.6.5.38
text:10247EF1 8A 45 F3                                      mov     al, [ebp+var_D]
*/

bool FakeRevokeMsg()
{
	DWORD offset = 0x247EF1;
	//33 C0                xor eax,eax 
	BYTE code[] = { 0x33, 0xc0, 0x90 };
	DWORD code_count = 3;

	if (!IsSupportedWxVersion(
        g_Supported_wx_Version,
        ARRAYSIZE(g_Supported_wx_Version),
        &offset,
        NULL,
        NULL,
        code,
        &code_count)) {
		return false;
	}
	
	HMODULE hMod = GetModuleHandle(WECHATWINDLL);
	if (!hMod) {
		return false;
	}

	PVOID addr = (BYTE*)hMod + offset;
	Patch(addr, code_count, code);

	return true;
}

void RestoreRevokeMsg()
{
	DWORD offset = 0x247EF1;
	BYTE code[] = { 0x8A, 0x45, 0xF3 };
	DWORD code_count = 3;

	if (!IsSupportedWxVersion(
        g_Supported_wx_Version,
        ARRAYSIZE(g_Supported_wx_Version), 
        &offset,
        code,
        &code_count)) {
		return;
	}
	
	HMODULE hMod = GetModuleHandle(WECHATWINDLL);
	if (!hMod) {
		return;
	}

	PVOID addr = (BYTE*)hMod + offset;
	Patch(addr, code_count, code);
}