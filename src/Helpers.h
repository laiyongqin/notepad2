/******************************************************************************
*
*
* Notepad2
*
* Helpers.h
*   Definitions for general helper functions and macros
*
* See Readme.txt for more information about this source code.
* Please send me your comments to this work.
*
* See License.txt for details about distribution and modification.
*
*                                              (c) Florian Balmer 1996-2008
*                                                  florian.balmer@gmail.com
*                                               http://www.flos-freeware.ch
*
*
******************************************************************************/



extern HINSTANCE g_hInstance;


#define COUNTOF(ar) (sizeof(ar)/sizeof(ar[0]))


extern WCHAR szIniFile[MAX_PATH];
#define IniGetString(lpSection,lpName,lpDefault,lpReturnedStr,nSize) \
  GetPrivateProfileString(lpSection,lpName,lpDefault,lpReturnedStr,nSize,szIniFile)
#define IniGetInt(lpSection,lpName,nDefault) \
  GetPrivateProfileInt(lpSection,lpName,nDefault,szIniFile)
#define IniSetString(lpSection,lpName,lpString) \
  WritePrivateProfileString(lpSection,lpName,lpString,szIniFile)
#define IniDeleteSection(lpSection) \
  WritePrivateProfileSection(lpSection,NULL,szIniFile)
__inline BOOL IniSetInt(LPCWSTR lpSection,LPCWSTR lpName,int i) {
  WCHAR tch[32]; wsprintf(tch,L"%i",i); return IniSetString(lpSection,lpName,tch);
}
#define LoadIniSection(lpSection,lpBuf,cchBuf) \
  GetPrivateProfileSection(lpSection,lpBuf,cchBuf,szIniFile);
#define SaveIniSection(lpSection,lpBuf) \
  WritePrivateProfileSection(lpSection,lpBuf,szIniFile)
int IniSectionGetString(LPCWSTR,LPCWSTR,LPCWSTR,LPWSTR,int);
int IniSectionGetInt(LPCWSTR,LPCWSTR,int);
BOOL IniSectionSetString(LPWSTR,LPCWSTR,LPCWSTR);
__inline BOOL IniSectionSetInt(LPWSTR lpCachedIniSection,LPCWSTR lpName,int i) {
  WCHAR tch[32]; wsprintf(tch,L"%i",i); return IniSectionSetString(lpCachedIniSection,lpName,tch);
}


void BeginWaitCursor();
void EndWaitCursor();


//void KeepWindowsAlive();


BOOL Is2k();
//BOOL IsXP();
BOOL IsVista();
BOOL PrivateIsAppThemed();


BOOL SetWindowTitle(HWND,UINT,UINT,LPCWSTR,int,BOOL,UINT,BOOL);
void SetWindowTransparentMode(HWND,BOOL);


void CenterDlgInParent(HWND);
void GetDlgPos(HWND,LPINT,LPINT);
void SetDlgPos(HWND,int,int);
void MakeBitmapButton(HWND,int,HINSTANCE,UINT);
void MakeColorPickButton(HWND,int,HINSTANCE,COLORREF);
void DeleteBitmapButton(HWND,int);


#define StatusSetSimple(hwnd,b) SendMessage(hwnd,SB_SIMPLE,(WPARAM)b,0)
BOOL StatusSetText(HWND,UINT,LPCWSTR);
BOOL StatusSetTextID(HWND,UINT,UINT);
int  StatusCalcPaneWidth(HWND,LPCWSTR);

int Toolbar_GetButtons(HWND,int,LPWSTR,int);
int Toolbar_SetButtons(HWND,int,LPCWSTR,void*,int);

LRESULT SendWMSize(HWND);

#define EnableCmd(hmenu,id,b) EnableMenuItem(hmenu,id,(b)\
                               ?MF_BYCOMMAND|MF_ENABLED:MF_BYCOMMAND|MF_GRAYED)

#define CheckCmd(hmenu,id,b)  CheckMenuItem(hmenu,id,(b)\
                               ?MF_BYCOMMAND|MF_CHECKED:MF_BYCOMMAND|MF_UNCHECKED)

BOOL IsCmdEnabled(HWND, UINT);


#define GetString(id,pb,cb) LoadString(g_hInstance,id,pb,cb)

#define StrEnd(pStart) (pStart + lstrlen(pStart))

int FormatString(LPWSTR,int,UINT,...);
void FormatBytes(LPWSTR,int,DWORD);


BOOL PathIsLnkFile(LPCWSTR);
BOOL PathGetLnkPath(LPCWSTR,LPWSTR,int);
BOOL PathIsLnkToDirectory(LPCWSTR,LPWSTR,int);
BOOL PathCreateDeskLnk(LPCWSTR);
BOOL PathCreateFavLnk(LPCWSTR,LPCWSTR,LPCWSTR);


BOOL TrimString(LPWSTR);
BOOL ExtractFirstArgument(LPCWSTR, LPWSTR, LPWSTR);

void PrepareFilterStr(LPWSTR);

void StrTab2Space(LPWSTR);


void  ExpandEnvironmentStringsEx(LPWSTR,DWORD);
void  PathCanonicalizeEx(LPWSTR);
DWORD GetLongPathNameEx(LPCWSTR,LPWSTR,DWORD);
DWORD_PTR SHGetFileInfo2(LPCWSTR,DWORD,SHFILEINFO*,UINT,UINT);


int  FormatNumberStr(LPWSTR);
BOOL SetDlgItemIntEx(HWND,int,UINT);


#define MBCSToWChar(c,a,w,i) MultiByteToWideChar(c,0,a,-1,w,i)
#define WCharToMBCS(c,w,a,i) WideCharToMultiByte(c,0,w,-1,a,i,NULL,NULL)

UINT    GetDlgItemTextA2W(UINT,HWND,int,LPSTR,int);
UINT    SetDlgItemTextA2W(UINT,HWND,int,LPSTR);
LRESULT ComboBox_AddStringA2W(UINT,HWND,LPCSTR);


UINT CodePageFromCharSet(UINT);


//==== UnSlash Functions ======================================================
void TransformBackslashes(char*,BOOL);


//==== MRU Functions ==========================================================
#define MRU_MAXITEMS 24
#define MRU_NOCASE    1
#define MRU_UTF8      2

typedef struct _mrulist {

  WCHAR  szRegKey[256];
  int   iFlags;
  int   iSize;
  LPWSTR pszItems[MRU_MAXITEMS];

} MRULIST, *PMRULIST, *LPMRULIST;

LPMRULIST MRU_Create(LPCWSTR,int,int);
BOOL      MRU_Destroy(LPMRULIST);
BOOL      MRU_Add(LPMRULIST,LPCWSTR);
BOOL      MRU_Delete(LPMRULIST,int);
BOOL      MRU_Empty(LPMRULIST);
int       MRU_Enum(LPMRULIST,int,LPWSTR,int);
BOOL      MRU_Load(LPMRULIST);
BOOL      MRU_Save(LPMRULIST);


//==== MinimizeToTray Functions - see comments in Helpers.c ===================
VOID MinimizeWndToTray(HWND hWnd);
VOID RestoreWndFromTray(HWND hWnd);



///   End of Helpers.h   \\\
