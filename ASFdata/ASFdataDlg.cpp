
// ASFdataDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ASFdata.h"
#include "ASFdataDlg.h"
#include "afxdialogex.h"
#include <locale.h> // 글자 깨짐 방지
#include <Windows.h>
#include <iostream>
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CASFdataDlg 대화 상자

CASFdataDlg::CASFdataDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ASFDATA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_IsRun = FALSE;
	m_IsShow = FALSE;
	m_SaveMode = 0;
	m_Ip = "";
	m_Port = 0;
	m_Interval = 0;
	m_Dir ="";
	m_TryCnt = 0;
	m_Path = "./info/info.ini";
}

void CASFdataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CASFdataDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INILOAD_BTN, &CASFdataDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CASFdataDlg 메시지 처리기

BOOL CASFdataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_tpMData = new MAP_TData;
	m_tpBMData = new MAP_TBData;

	ASF_vInitdata();



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CASFdataDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CASFdataDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CASFdataDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CASFdataDlg::OnBnClickedButton1()
{
	IniLoad();
}


void CASFdataDlg::IniLoad()
{
	TCHAR buffer[250]; // 섹션 이름을 저장할 버퍼
	std::vector<CString> sections; // 섹션 이름을 저장할 벡터

	// INI 파일로부터 섹션 이름들을 가져옴
	DWORD size = GetPrivateProfileSectionNames(buffer, sizeof(buffer), m_Path);
	if (size > 0)
	{
		// 섹션 이름들을 파싱하여 벡터에 저장
		LPTSTR pSection = buffer;
		while (*pSection)
		{
			sections.push_back(pSection);
			pSection += _tcslen(pSection) + 1;
		}
		// 각 섹션에 대해 키와 값을 읽음
		for (const CString& section : sections)
		{
			MapInfo info;
			TCHAR keyBuffer[255]; // 키 이름을 저장할 버퍼
			// 섹션에 속한 키들을 가져옴
			DWORD keySize;
			keySize = GetPrivateProfileString(section, nullptr, _T(""), keyBuffer, sizeof(keyBuffer), m_Path);
			if (keySize > 0)
			{
				// 키와 값을 출력
				LPTSTR pKey = keyBuffer;
				while (*pKey)
				{
					TCHAR valueBuffer[250]; // 값을 저장할 버퍼
					// 키에 해당하는 값을 가져옴
					GetPrivateProfileString(section, pKey, _T(""), valueBuffer, sizeof(valueBuffer), m_Path);
					// 키와 값을 출력
					CString key(pKey);
					CString value(valueBuffer);

					if (section == "Init") { InitSave(key, value); }
					else {
						getDataItem(section, key, value, &info);
					}
					printf(("Section: %S\nKey: %S\nValue: %S\n"), section, key, value);
					pKey += _tcslen(pKey) + 1;
				}
			}
		}
	}
}

void CASFdataDlg::getDataItem(CString section, CString key, CString value, MapInfo*info)
{
	CStringArray dataArray;
	int valueCnt = ASF_vSplit(value, _T(","), dataArray);
	int ch = 0;
	if (valueCnt > 1)
	{
		if (dataArray.GetAt(0).Find(L"[") != -1 )
		{
			CString temp = dataArray.GetAt(0).Right(2);
			ch = _ttoi(temp.Left(1));
		}
	}
	info->ch = ch;
	if (valueCnt == 2)
	{
		info->text = section;
		info->name = getMapName(dataArray.GetAt(0));
		info->addr = _ttoi(dataArray.GetAt(1));
		mList[TYPE_3264].AddTail(*info);
	}
	else if (valueCnt == 3)
	{
		info->text = section;
		info->name = getMapName(dataArray.GetAt(0));
		info->addr = _ttoi(dataArray.GetAt(1));
		info->bit = _ttoi(dataArray.GetAt(2));
		mList[TYPE_BIT].AddTail(*info);
	}
	else { 
		info->format = value; 
	}
}

void CASFdataDlg::InitSave(CString key, CString value)
{
	if (key == "AutoRun") 
	{ 
		if (value.Compare(_T("yes"))==0) 
		{ 
			m_IsRun = true; 
		} 
		else { m_IsRun = false; }
	}
	else if (key == "SHOW")
	{
		if (value == "yes") { m_IsShow = true; }
		else { m_IsShow = false; }
	}
	else if (key == "SaveMode") { m_SaveMode = _ttoi(value); }
	else if (key == "IP") { m_Ip = value; }
	else if (key == "PORT") { m_Port = _ttoi(value); }
	else if (key == "Interval") { m_Interval = _ttoi(value); }
	else if (key == "Try Count") { m_TryCnt = _ttoi(value); }
	else if (key == "Dir") { m_Dir = value; }
}
// 
// battery backup map data structure


//
//int CASFdataDlg::hxMapType(int nMapName)
//{
//	//    int nMapType = 0;
//	switch (nMapName)
//	{
//	case HX_X:
//	case HX_Y:
//	case HX_G:
//	case HX_F:
//	case HX_SR:
//	case HX_T:
//	case HX_C:
//	case HX_D:
//	case HX_BR:
//	case HX_DEVICE:
//	case HX_R:
//		//case HX_SYSREADY:
//		//	//        nMapType = MAP32;
//		//	return MAP32;
//		//	break;
//	case HX_PA:
//	case HX_PI:
//	case HX_PM:
//	case HX_PP:
//	case HX_PU:
//	case HX_PS:
//	case HX_SV:
//	case HX_ML:
//	case HX_MGV:
//	case HX_B:
//	case HX_SN:
//		//case HX_MGN:
//		//	//        nMapType = MAP64;
//		//	return MAP64;
//		//	break;
//		//}
//	}
//}


int CASFdataDlg::getMapName(CString value)
{
	int name = -1;
	if (value.Find(L"[") != -1)
	{
		value = value.Left(value.GetLength() - 3);
	}

	if (value.MakeUpper() == "X") {
		name = HX_X;
	}
	else if (value.MakeUpper() == "Y")  {
		name = HX_Y;
	}
	else if (value.MakeUpper() == "G") {
		name = HX_G;
	}
	else if (value.MakeUpper() == "F") {
		name = HX_F;
	}
	else if (value.MakeUpper() == "R") {
		name = HX_R;
	}
	else if (value.MakeUpper() == "PA") {
		name = HX_PA;
	}
	else if (value.MakeUpper() == "PI") {
		name = HX_PI;
	}
	else if (value.MakeUpper() == "PM") {
		name = HX_PM;
	}
	else if (value.MakeUpper() == "PP") {
		name = HX_PP;
	}
	else if (value.MakeUpper() == "PU") {
		name = HX_PU;
	}
	else if (value.MakeUpper() == "PS") {
		name = HX_PS;
	}
	else if (value.MakeUpper() == "SV") {
		name = HX_SV;
	}
	else if (value.MakeUpper() == "ML") {
		name = HX_ML;
	}
	else if (value.MakeUpper() == "MGV")  {
		name = HX_MGV;
	}
	else if (value.MakeUpper() == "B") {
		name = HX_B;
	}
	else if (value.MakeUpper() == "T") {
		name = HX_T;
	}
	else if (value.MakeUpper() == "C") {
		name = HX_C;
	}
	else if (value.MakeUpper() == "D") {
		name = HX_D;
	}
	else if (value.MakeUpper() == "SN") {
		name = HX_SN;
	}
	else if (value.MakeUpper() == "MGN") {
		name = HX_MGN;
	}

	return name;
}



int CASFdataDlg::getBit32(int data, int bit)
{
	return ((data >> bit) & 0x01) ? 1 : 0;
}

int CASFdataDlg::setBit32(int data, int bit, int onoff)
{
	onoff = onoff ? 1 : 0;

	long temp = (0x1 << bit);
	if (onoff) {
		data |= temp;
	}
	else {
		data &= (~temp);
	}
	return data;
}

// 구조체 만들기 함수
void CASFdataDlg::ASF_vCreate() 
{

}

// ini파일의 데이터가 형식에 맞지 않을때 삭제
void CASFdataDlg::ASF_vDestroy() 
{}

void CASFdataDlg::ASF_vShow() {}

void CASFdataDlg::ASF_vHide() {}

// 새로고침
void CASFdataDlg::ASF_vRefresh() {}
void CASFdataDlg::ASF_vPaint() {}
void CASFdataDlg::ASF_vSize() {}
S32 CASFdataDlg::ASF_nWndProc() 
{
	S32 s32_bit =0;
	return s32_bit;
}
void CASFdataDlg::ASF_vKeyData() {}

int CASFdataDlg::ASF_vSplit(CString value, CString phraser, CStringArray& strs)
{
	int count = 0;

	CString tempStr = value;

	int length = value.GetLength();

	while (length)
	{
		int find = tempStr.Find(phraser);
		if (find != -1)
		{
			CString temp = tempStr.Left(find);
			int varLen = _tcslen(phraser);
			strs.Add(tempStr.Left(find));
			tempStr = tempStr.Mid(find + varLen);
			count++;
		}
		else
		{
			length = 0;
			strs.Add(tempStr);
			count++;
		}
	}
	return count;
}


void CASFdataDlg::ASF_vInitdata()
{
	m_tpBMData->SN[0][2] = 2244567851;
	m_tpBMData->SN[0][0] = 5485648752;
	m_tpBMData->SN[0][1] = 2341523441;
	m_tpMData->PS[0][31] = 1.2348;
	m_tpMData->PS[1][31] = 4.6548;
	m_tpMData->X[200] = 0101;
}


CString CASFdataDlg::time(int value)
{
	CString data;
	int h = value / 3600;
	int m = value - h * 3600.;
	m /= 60;
	int s = value - h * 3600. - m * 60;
	data.Format(_T("%02d:%02d:%02d"), h, m, s);

	return data;
}

void CASFdataDlg::GetMapData()
{
	CString data;

}

void CASFdataDlg::SaveData()
{
	if (m_SaveMode == 0);
}