
// ASFdataDlg.h: 헤더 파일
//

#pragma once
#include "ASFtype.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") // 콘솔창 출력

// CASFdataDlg 대화 상자

enum TYPE_MAP
{
	TYPE_3264 = 0
	, TYPE_BIT
	, TYPE_STRING
	, TYPE_MAX
};

typedef struct MAP_TStr
{
	TCHAR caSysPath[MAX_PATH_SIZE];             // system execution file path
	TCHAR caPLCFile[MAX_PATH_SIZE];             // PLC file name
	TCHAR caMAPFile[MAX_PATH_SIZE];             // MAP file name
	TCHAR caAxis[MAP_MAX_AXIS][MAX_AXIS_SIZE];  // Axis string
	TCHAR caMachine[MAX_MACHINE];               // machine name

	TCHAR caNCPath[MAP_MAX_CH][MAX_PATH_SIZE];      // NC program file path
	TCHAR caErrProg[MAP_MAX_CH][MAX_FILE_SIZE];     // error program name
	TCHAR caMainProg[MAP_MAX_CH][MAX_FILE_SIZE];    // main program name
	TCHAR caSubProg[MAP_MAX_CH][MAX_FILE_SIZE];     // sub program name
	TCHAR caMDIProg[MAP_MAX_CH][MAX_FILE_SIZE];     // MDI mode program name
	TCHAR caSeqProg[MAP_MAX_CH][MAP_MAX_PROG][MAX_FILE_SIZE]; // for restart

	TCHAR caDataPath[MAX_PATH_SIZE];				// Data file path
	TCHAR caLanguage[10];							// Selected Language 

	//added by pch [2008.06.09] API에서 알람 처리 가능하도록 하기 위해 추가함 
	TCHAR caCurAlarmMsg[MAX_PATH_SIZE];          // 현재 발생되는 시스템 알람 메시지  
	TCHAR caCurOpMsg[MAX_PATH_SIZE];             // 현재 발생되는 경고 메시지
	TCHAR	caPntProg[MAX_PATH_SIZE];				// 프로파일 Pnt전체 경로
	TCHAR	ca2DProg[MAX_PATH_SIZE];				// 선택한 2D NC Data전체 경로

} stMAP_TStr;

typedef struct MAP_TBStr
{
	TCHAR caTemp1[MAP_MAX_CH][MAX_PATH_SIZE];
	TCHAR caTemp2[MAP_MAX_CH][MAX_FILE_SIZE];
	TCHAR caTemp3[MAP_MAX_CH][MAX_FILE_SIZE];   //  [6/12/2014 choijh] - 개발자 정의 EventLog로 사용하겠음
	TCHAR caTemp4[MAP_MAX_CH][MAX_FILE_SIZE];
	TCHAR caTemp5[MAP_MAX_CH][MAX_FILE_SIZE];
	TCHAR caTemp6[MAP_MAX_CH][MAP_MAX_PROG][MAX_FILE_SIZE];
} stMAP_TBStr;

typedef struct MAP_TData
{
	U32 X[MAP_MAX_X];                      // X map
	U32 Y[MAP_MAX_Y];                      // Y map
	U32 G[MAP_MAX_CH + 1][MAP_MAX_G];        // G map
	U32 F[MAP_MAX_CH + 1][MAP_MAX_F];        // F map
	U32 R[MAP_MAX_SR];                     // system memory R map

	F64 PA[MAP_MAX_CH][MAP_MAX_PA];        // always replace P map
	F64 PI[MAP_MAX_CH][MAP_MAX_PI];        // idle replace P map
	F64 PM[MAP_MAX_CH][MAP_MAX_PM];        // motion stop replace P map
	F64 PP[MAP_MAX_CH][MAP_MAX_PP];        // power on replace P map
	F64 PU[MAP_MAX_CH][MAP_MAX_PU];        // user P map
	F64 PS[MAP_MAX_AXIS][MAP_MAX_PS];      // motion stop replace P map
	F64 SV[MAP_MAX_CH][MAP_MAX_SV];        // status volitile
	F64 ML[MAP_MAX_CH][MAP_MAX_PROG][MAP_MAX_ML];    // local macro
	F64 MGV[MAP_MAX_CH][MAP_MAX_MGV];      // global macro volitile
	F64 B[MAP_MAX_B];                      // B map

	//TCHAR MSTR[MAX_STRMAP_STR][MAX_STRMAP_STR_SIZE];					//문자열 맵 추가. 22.11.17 hyunwoo.

	TCHAR cExitIPR, cExitPOS, cExitIPO, cExitPLC;           // exit flag  
	TCHAR cBootIPR, cBootPOS, cBootIPO, cBootPLC;           // boot flag  

	TCHAR cSYSReady;                                        // boot interlock
	//U32 ulTimerAdr, ulSercosAdr, ulSramAdr, ulCanAdr;    // base address
	int ulTimerAdr, ulSercosAdr, ulSramAdr, ulCanAdr;    // base address
	U08 ucInterrupt;                                     // base address

	MAP_TStr STR;                           // string map
	// 20040805 
	TCHAR cSYSPowerFail;					// Power fail -> sys off 
	// 20040903
	//TCHAR cRestartMode;						// Restart Mode ON

	// 20051011
	//BOOL bLicensed;
	int g_nLicenseNo;

	U32		ulMEndFlag;								// 0:ing, 1:end
	U32		ulMSave_Num;
	F64		daMSave_XPos[2000];						// Profile Measure X Position Save
	F64		daMSave_ZPos[2000];						// Profile Measure Z Position Save

} stMAP_TData;


typedef struct MAP_TBData
{
	S32 T[MAP_MAX_T];                      // T map
	S32 C[MAP_MAX_C];                      // C map
	S32 D[MAP_MAX_D];                      // D map
	U32 R[MAP_MAX_BR];                     // battery backup memory R map

	F64 SN[MAP_MAX_CH][MAP_MAX_SN];        // status non-volitile
	F64 MGN[MAP_MAX_CH][MAP_MAX_MGN];      // global macro non-volitile
	MAP_TBStr STR;                          // string map
	TCHAR caStart[10];                      // start flag for init data
} MAP_TBData;



typedef struct MapInfo
{
	CString text;
	int ch;
	int name;
	int addr;
	int bit;
	CString format;
}MapInfo;
class CASFdataDlg : public CDialogEx
{
// 생성입니다.
public:
	CASFdataDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASFDATA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private:
	MAP_TData* m_tpMData;
	MAP_TBData* m_tpBMData;
	MAP_TStr* m_tpSTRData;
	void ASF_vCreate();
	void ASF_vDestroy();
	void ASF_vShow();
	void ASF_vHide();
	void ASF_vRefresh();
	void ASF_vPaint();
	void ASF_vSize();
	S32 ASF_nWndProc();
	void ASF_vKeyData();

	int getBit32(int data, int bit);
	void ASF_vInitdata();
	CString time(int value);
	void InItStruct(MapInfo* info);
	
	MapInfo m_MapInfo;
	
	void IniLoad();
	void InitSave(CString key, CString value);
	CList<MapInfo, MapInfo&>  mList[TYPE_MAX];
	int getMapName(CString value);
	void AddDataItem(MapInfo *info);
	CString GetMapData(int type, MapInfo* info);
	void SaveFile(CString data);
	char* ToChar(CString value);
	void SaveData();
	CString CheckBitType(MapInfo info);
	double Check3264Type(MapInfo info);
	CString CheckSTRType(MapInfo);
	TCHAR *ToTChar(CString value);
	CString GetPullBit(U32 num);
	int setBit32(int data, int bit, int onoff);
	

	bool m_IsRun;
	bool m_IsShow;
	int m_SaveMode;
	CString m_Ip;
	int m_Port;
	int m_Interval;
	int m_TryCnt;
	CString m_Dir;
	CString m_Path;
};
