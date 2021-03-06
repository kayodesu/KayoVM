#ifdef _WIN32

#include <ctime>
#include <string>
#include <windows.h>

using namespace std;

int processorNumber()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return sysInfo.dwNumberOfProcessors;
}

int pageSize()
{
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return sysInfo.dwPageSize;
}

const char *osName()
{
	SYSTEM_INFO info;        //用SYSTEM_INFO结构判断64位AMD处理器 
	GetSystemInfo(&info);    //调用GetSystemInfo函数填充结构 
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if (GetVersionEx((OSVERSIONINFO *)&os)) {
		//下面根据版本信息判断操作系统名称 
		switch (os.dwMajorVersion) { //判断主版本号		
		case 4:
			switch (os.dwMinorVersion) { //判断次版本号 
			case 0:
				if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
					return "Microsoft Windows NT 4.0"; //1996年7月发布 
				else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
					return "Microsoft Windows 95";
				break;
			case 10:
				return "Microsoft Windows 98";
			case 90:
				return "Microsoft Windows Me";
			}
			break;
		case 5:
			switch (os.dwMinorVersion) { //再比较dwMinorVersion的值			
			case 0:
				return "Microsoft Windows 2000"; //1999年12月发布
			case 1:
				return "Microsoft Windows XP"; //2001年8月发布
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION
					&& info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) 
					return ("Microsoft Windows XP Professional x64 Edition");
				else if (GetSystemMetrics(SM_SERVERR2) == 0)
					return ("Microsoft Windows Server 2003"); //2003年3月发布 
				else if (GetSystemMetrics(SM_SERVERR2) != 0)
					return "Microsoft Windows Server 2003 R2";
				break;
			}
			break;
		case 6:
			switch (os.dwMinorVersion) {
			case 0:
				if (os.wProductType == VER_NT_WORKSTATION)
					return "Microsoft Windows Vista";
				else
					return "Microsoft Windows Server 2008";//服务器版本 
				break;
			case 1:
				if (os.wProductType == VER_NT_WORKSTATION)
					return "Microsoft Windows 7";
				else
					return "Microsoft Windows Server 2008 R2";
				break;
			case 2:
				if (os.wProductType != VER_NT_WORKSTATION)
					return "Windows Server 2012";
				else
					return "Windows 8";
				break;
			case 3:
				if (os.wProductType == VER_NT_WORKSTATION)
					return "Windows 8.1";
				else
					return "Windows Server 2012 R2";
				break;
			}
			break;
		case 10:
			switch (os.dwMinorVersion) {
			case 0:
				if (os.wProductType == VER_NT_WORKSTATION)
					return "Windows 10";
				else
					return "Windows Server 2016";
				break;
			default:
				break;
			}
			break;
		}
	}

	return "unknown OperatingSystem";
}

const char *osArch()
{
    SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {
		return "INTEL";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_MIPS) {
		return "MIPS";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ALPHA) {
		return "ALPHA";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_PPC) {
		return "PPC";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_SHX) {
		return "SHX";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM) {
		return "ARM";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) {
		return "IA64";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ALPHA64) {
		return "ALPHA64";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_MSIL) {
		return "MSIL";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
		return "AMD64";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA32_ON_WIN64) {
		return "IA32_ON_WIN64";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_NEUTRAL) {
		return "NEUTRAL";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64) {
		return "ARM64";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM32_ON_WIN64) {
		return "ARM32_ON_WIN64";
	} else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA32_ON_ARM64) {
		return "IA32_ON_ARM64";
	} else {
        return "UNKNOWN ARCHITECTURE";
    }
}

const char *getFileSeparator()
{
    return "\\";
}

const char *getPathSeparator()
{
    return ";";
}

const char *getLineSeparator()
{
    return "\r\n";
}

string getTimeZone()
{
    time_t raw_time;
    time (&raw_time);

    struct tm *time_info = localtime(&raw_time);

    char timezone_[64];
    strftime(timezone_, sizeof(timezone_), "%Z", time_info);
    return timezone_;

//    TIME_ZONE_INFORMATION   tzi;
//
//     GetSystemTime(&tzi.StandardDate);
//
//     GetTimeZoneInformation(&tzi);
//
////	size_t len = wcslen(tzi.StandardName) + 1;
////	size_t converted = 0;
////	char *standard_name =(char *) malloc(2 * len * sizeof(char));
////
////	auto cc = wcstombs_s(&converted, standard_name, len, tzi.StandardName, _TRUNCATE);
////
////    auto   strDaylightName   =   tzi.DaylightName;
////
////     auto zone = tzi.Bias/ -60; //时区，如果是中国标准时间则得到8
//
//    wcout << "time zone: " << tzi.DaylightName << endl;
//     return tzi.StandardName;
}

#endif