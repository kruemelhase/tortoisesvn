// TortoiseSVN - a Windows shell extension for easy version control

// Copyright (C) 2003 - Tim Kemp and Stefan Kueng

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#pragma once
#include "globals.h"
#include <tchar.h>
#include <string>
#include "registry.h"

#define REGISTRYTIMEOUT 2000
class ShellCache
{
public:
	ShellCache()
	{
		showrecursive = CRegStdWORD(_T("Software\\TortoiseSVN\\RecursiveOverlay"));
		driveremote = CRegStdWORD(_T("Software\\TortoiseSVN\\DriveMaskRemote"));
		drivefixed = CRegStdWORD(_T("Software\\TortoiseSVN\\DriveMaskFixed"));
		drivecdrom = CRegStdWORD(_T("Software\\TortoiseSVN\\DriveMaskCDROM"));
		driveremove = CRegStdWORD(_T("Software\\TortoiseSVN\\DriveMaskRemovable"));
		recursiveticker = GetTickCount();
		driveticker = recursiveticker;
		langticker = recursiveticker;
		menulayout = CRegStdWORD(_T("Software\\TortoiseSVN\\ContextMenuEntries"), MENUCHECKOUT | MENUUPDATE | MENUCOMMIT);
		langid = CRegStdWORD(_T("Software\\TortoiseSVN\\LanguageID"), 1033);
	}
	DWORD GetMenuLayout()
	{
		if ((GetTickCount() - REGISTRYTIMEOUT) > layoutticker)
		{
			layoutticker = GetTickCount();
			menulayout.read();
		} // if ((GetTickCount() - REGISTRYTIMEOUT) > layoutticker)
		return (menulayout);
	}
	BOOL IsRecursive()
	{
		if ((GetTickCount() - REGISTRYTIMEOUT)>recursiveticker)
		{
			recursiveticker = GetTickCount();
			showrecursive.read();
		} // if ((GetTickCount() - REGISTRYTIMEOUT)>recursiveticker)
		return (showrecursive);
	}
	BOOL IsRemote()
	{
		DriveValid();
		return (driveremote);
	}
	BOOL IsFixed()
	{
		DriveValid();
		return (drivefixed);
	}
	BOOL IsCDRom()
	{
		DriveValid();
		return (drivecdrom);
	}
	BOOL IsRemovable()
	{
		DriveValid();
		return (driveremove);
	}
	BOOL IsPathAllowed(LPCTSTR path)
	{
		TCHAR pathbuf[MAX_PATH+4];
		_tcscpy(pathbuf, path);
		PathRemoveFileSpec(pathbuf);
		PathAddBackslash(pathbuf);
		UINT drivetype = GetDriveType(pathbuf);
		if ((drivetype == DRIVE_REMOVABLE)&&(!IsRemovable()))
			return FALSE;
		if ((drivetype == DRIVE_FIXED)&&(!IsFixed()))
			return FALSE;
		if ((drivetype == DRIVE_REMOTE)&&(!IsRemote()))
			return FALSE;
		if ((drivetype == DRIVE_CDROM)&&(!IsCDRom()))
			return FALSE;
		return TRUE;
	}
	DWORD GetLangID()
	{
		if ((GetTickCount() - REGISTRYTIMEOUT) > langticker)
		{
			langticker = GetTickCount();
			langid.read();
		} // if ((GetTickCount() - REGISTRYTIMEOUT) > layoutticker)
		return (langid);
	}

private:
	void DriveValid()
	{
		if ((GetTickCount() - REGISTRYTIMEOUT)>driveticker)
		{
			driveticker = GetTickCount();
			driveremote.read();
			drivefixed.read();
			drivecdrom.read();
			driveremove.read();
		}
	}
	CRegStdWORD langid;
	CRegStdWORD showrecursive;
	CRegStdWORD driveremote;
	CRegStdWORD drivefixed;
	CRegStdWORD drivecdrom;
	CRegStdWORD driveremove;
	CRegStdWORD menulayout;
	DWORD recursiveticker;
	DWORD driveticker;
	DWORD layoutticker;
	DWORD langticker;
};