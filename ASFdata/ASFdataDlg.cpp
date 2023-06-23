
// ASFdataDlg.cpp: 구현 파일
//
#pragma warning(disable:4996) // C4996 에러를 무시
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "pch.h"
#include "framework.h"
#include "ASFdata.h"
#include "ASFdataDlg.h"
#include "afxdialogex.h"
#include <locale.h> // 글자 깨짐 방지
#include <Windows.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <atlstr.h> //MFC 사용할수있게 해주는 헤더

#include <iostream>
#include <regex>
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


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

	m_tpMData = new MAP_TData;
	m_tpBMData = new MAP_TBData;
	m_tpSTRData = new MAP_TStr;
	
	ASF_vInitdata();
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
	InItStruct(&m_MapInfo);
	IniLoad();

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

void CASFdataDlg::OnSplit(CString value, CString phraser, CStringArray& strs)
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
			strs.Add(tempStr);
			length = 0;
		}
	}
}


CString CASFdataDlg::TextInCoderCheck()
{
	enum encoding { ANSI, UTF8, UTF8_BOM, UTF16_LE, UTF16_BE };
	encoding enc = ANSI;
	CString sContent;
	enc;
	CFile hFile;
	if (hFile.Open(m_Path, CFile::modeRead)) // m_Path 파일경로
	{
		int nLen = (int)hFile.GetLength();
		TCHAR* pData = new TCHAR[nLen + 2];
		memset(pData, 0, (nLen + 2));

		LONG nReadSize = hFile.Read(pData, nLen);
		if (nReadSize == nLen)
		{
			// 인코딩 검사
			char* szBOM = new char[3];
			memset(szBOM, 0, 3);
			memmove(szBOM, (char*)pData, 3);

			unsigned char littleEndianBOM[] = { 0xFF, 0xFE };
			unsigned char bigEndianBOM[] = { 0xFE, 0xFF };
			unsigned char utf8BOM[] = { 0xEF, 0xBB, 0xBF };

			unsigned char* lpHeader = (unsigned char*)szBOM;

			if (lpHeader[0] == littleEndianBOM[0] && lpHeader[1] == littleEndianBOM[1])
				enc = encoding::UTF16_LE;
			else if (lpHeader[0] == bigEndianBOM[0] && lpHeader[1] == bigEndianBOM[1])
				enc = encoding::UTF16_BE;
			else if (lpHeader[0] == utf8BOM[0] && lpHeader[1] == utf8BOM[1] && lpHeader[2] == utf8BOM[2])
				enc = encoding::UTF8_BOM;
			else
			{
				// 위 3가지 경우가 아닐 경우 파일 내용을 분석해 UTF8과 Ansi를 구분함
				if (IsUTF8((const void*)pData, nLen))
					enc = encoding::UTF8;
			}

			// 인코딩 처리
			WCHAR* pBuffer = new WCHAR[nLen + 2];
			memset(pBuffer, 0, nLen + 2);

			switch (enc)
			{
			case ANSI:
			{
				int nLength = MultiByteToWideChar(CP_ACP, 0, (char*)pData, nLen, NULL, NULL);
				memset(pBuffer, 0, sizeof(WCHAR) * (nLength + 1));
				MultiByteToWideChar(CP_ACP, 0, (char*)pData, nLen, pBuffer, nLength);
				break;
			}
			case UTF8:
			{
				int nLength = MultiByteToWideChar(CP_UTF8, 0, (char*)pData, nLen, NULL, NULL);
				memset(pBuffer, 0, sizeof(WCHAR) * (nLength + 1));
				MultiByteToWideChar(CP_UTF8, 0, (char*)pData, nLen, pBuffer, nLength);
				break;
			}
			case UTF8_BOM:
			{
				int nLength = MultiByteToWideChar(CP_UTF8, 0, (char*)pData + 3, nLen - 3, NULL, NULL);
				memset(pBuffer, 0, sizeof(WCHAR) * (nLength + 1));
				MultiByteToWideChar(CP_UTF8, 0, (char*)pData + 3, nLen - 3, pBuffer, nLength);
				break;
			}
			case UTF16_LE:
			{
				wcscpy(pBuffer, (WCHAR*)pData + 1);
				break;
			}
			case UTF16_BE:
			{
				wcscpy_s(pBuffer, nLen + 2, (WCHAR*)pData + 1);

				// Swap Byte
				WCHAR ch;
				WCHAR* tmpBuf = new WCHAR[nLen + 2];
				memset(tmpBuf, 0, nLen + 2);
				memmove(tmpBuf, pBuffer, nLen);

				int nPos = 0;
				while (nPos <= nLen)
				{
					ch = pBuffer[nPos];
					if (ch == 0x00)
					{
						memcpy(pBuffer, tmpBuf, nLen);
						break;
					}

					tmpBuf[nPos++] = MAKEWORD(HIBYTE(ch), LOBYTE(ch));
				}
				delete[] tmpBuf;
				break;
			}
			default:
				break;
			}

			sContent = (CString)pBuffer;

			delete[] szBOM;
			delete[] pData;
			delete[] pBuffer;
		}
	}
	hFile.Close();
	return sContent;
}
void CASFdataDlg::SectionLoad(CStringArray  *Sections)
{
	CString section = TextInCoderCheck();
	CStringArray arr_split;
	OnSplit(section, "\n", arr_split);
	for (int i = 0; i < arr_split.GetSize(); i++)
	{
		CString temp = arr_split.GetAt(i);
		if (temp.Left(1) == "[")
		{
			int varLen = _tcslen("[");
			temp = temp.Mid(varLen);
			temp.Replace(_T("]\r"), _T(""));
			Sections->Add(temp);
		}
		else { continue; }
	}
}
void CASFdataDlg::GetKoreanData(MapInfo *info, CString title)
{
	CString txt = TextInCoderCheck();
	txt = txt.Mid(txt.Find(title));
	txt = txt.Left(txt.Find("\r\n\r\n["));
	CStringArray tempArr;
	OnSplit(txt, "\r\n", tempArr);
	if (tempArr.GetSize() < 5)
	{
		for (int i = 0; i < 6 - tempArr.GetSize(); i++)
		{
			tempArr.Add("NULL");
		}
	}
	for (int i = 1; i < tempArr.GetSize() ; i++)
	{
		CStringArray tempArr_Key;
		CString temp = tempArr.GetAt(i);
		OnSplit(temp,"=",tempArr_Key);
		temp = tempArr_Key.GetAt(0);

		if (info->format == "")
		{
			temp == "Type" ? info->format = tempArr_Key.GetAt(1) : info->format = "";
		}
		if (info->name == -1)
		{
			temp == "Code" ? info->name = getMapName(tempArr_Key.GetAt(1)) : info->name = -1;
		}
		if (info->ch == -1)
		{
			temp == "Ch" ? info->ch = _ttoi(tempArr_Key.GetAt(1)) : info->ch = -1;
		}
		if (info->addr == -1)
		{
			temp == "Idx" ? info->addr = _ttoi(tempArr_Key.GetAt(1)) : info->addr = -1;
		}
		if (info->bit == -1)
		{
			temp == "Bit" ? info->bit = _ttoi(tempArr_Key.GetAt(1)) : info->bit = -1;

		}
	}
	info->text = title;
}

bool CASFdataDlg::IsUTF8(const void* pBuffer, long size)
{
	bool bUTF8 = true;
	unsigned char* start = (unsigned char*)pBuffer;
	unsigned char* end = (unsigned char*)pBuffer + size;
	while (start < end)
	{
		if (*start < 0x80) // (10000000)[output][/output]
		{
			start++;
		}
		else if (*start < (0xC0)) // (11000000)
		{
			bUTF8 = false;
			break;
		}
		else if (*start < (0xE0)) // (11100000)
		{
			if (start >= end - 1)
				break;
			if ((start[1] & (0xC0)) != 0x80)
			{
				bUTF8 = false;
				break;
			}
			start += 2;
		}
		else if (*start < (0xF0)) // (11110000)
		{
			if (start >= end - 2)
				break;
			if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)
			{
				bUTF8 = false;
				break;
			}
			start += 3;
		}
		else
		{
			bUTF8 = false;
			break;
		}
	}
	return bUTF8;
}



void CASFdataDlg::IniLoad()
{
	CStringArray sections;
	// INI 파일로부터 섹션 이름들을 가져옴
	SectionLoad(&sections);

	// 각 섹션에 대해 키와 값을 읽음
	for (int i=0; i<sections.GetCount(); i++)
	{
		CString section = sections.GetAt(i);
		printf("%s\n", section);
		MapInfo info = m_MapInfo;
		TCHAR keyBuffer[255]; // 키 이름을 저장할 버퍼
		// 섹션에 속한 키들을 가져옴
		DWORD keySize;
		keySize = GetPrivateProfileString(section, nullptr, _T(""), keyBuffer, sizeof(keyBuffer), m_Path);



		if (keySize == 0) {
			GetKoreanData(&info, section);
			AddDataItem(&info);
			continue;

		}
		// 키와 값을 출력
		LPTSTR pKey = keyBuffer;
		while (*pKey)
		{
			if (section == "Init")
			{
				// 키에 해당하는 값을 가져옴
				CString key(pKey);
				TCHAR valueBuffer[60];
				GetPrivateProfileString(section, pKey, _T(""), valueBuffer, sizeof(valueBuffer), m_Path);
				CString value(valueBuffer);

				pKey += _tcslen(pKey) + 1;
				InitSave(key, value);
			}
			else { break; }
		}
		if (section != "Init")
		{
			TCHAR typeBuffer[40]; // 값을 저장할 버퍼
			TCHAR codeBuffer[30];
			TCHAR idxBuffer[4];
			TCHAR chBuffer[4];
			TCHAR bitBuffer[4];

			GetPrivateProfileString(section, _T("Type"), _T(""), typeBuffer, sizeof(typeBuffer), m_Path);
			GetPrivateProfileString(section, _T("Code"), _T(""), codeBuffer, sizeof(codeBuffer), m_Path);
			GetPrivateProfileString(section, _T("Idx"), _T("0"), idxBuffer, sizeof(idxBuffer), m_Path);
			GetPrivateProfileString(section, _T("Ch"), _T("-1"), chBuffer, sizeof(chBuffer), m_Path);
			GetPrivateProfileString(section, _T("Bit"), _T("-1"), bitBuffer, sizeof(bitBuffer), m_Path);

			// 키와 값을 출력
			CString iniType(typeBuffer);
			CString iniCode(codeBuffer);
			CString iniIdx(idxBuffer);
			CString iniCh(chBuffer);
			CString iniBit(bitBuffer);

			if (iniType == "" || iniCode == "") { 
				printf("섹션 : %c\n 값이 확인되지 않습니다\n", section);
				continue; 
			}
			info.text = section;
			info.name = getMapName(iniCode);
			info.ch = _ttoi(iniCh);
			info.addr = _ttoi(iniIdx);
			info.bit = _ttoi(iniBit);
			info.format = iniType;

			AddDataItem(&info);
		}
	}
	SaveData();
}

void CASFdataDlg::AddDataItem(MapInfo*info)
{
	if (info->bit != -1){
		mList[TYPE_BIT].AddTail(*info);
	}
	else if (info->format == "%S") {
		mList[TYPE_STRING].AddTail(*info);
	}
	else
	{
		mList[TYPE_3264].AddTail(*info);
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

CString CASFdataDlg::CheckSTRType(MapInfo info)
{
	CString data;
	switch (info.name)
	{
	case HX_STR_NCPATH:
		data = m_tpSTRData->caNCPath[info.ch];
		break;
	case HX_STR_PLCFILE:
		data = m_tpSTRData->caPLCFile;
		break;
	case HX_STR_MAPFILE:
		data = m_tpSTRData->caMAPFile;
		break;
	case HX_STR_MAINPROG:
		data = m_tpSTRData->caMainProg[info.ch];
		break;
	case HX_STR_SUBPROG:
		data = m_tpSTRData->caSubProg[info.ch];
		break;
	case HX_STR_ALARMMSG:
		data = m_tpSTRData->caCurAlarmMsg;
		break;
	case HX_STR_OPMSG:
		data = m_tpSTRData->caCurOpMsg;
		break;
	default:
		printf("section : %s\nCheckSTRType 함수 값이 들어가지 않았습니다.\n", info.text);
		data = "잘못된 데이터 입니다.";
	}
	return data;
}

double CASFdataDlg::Check3264Type(MapInfo info)
{
	double data;
	switch (info.name)
	{
	case HX_PA:
		data= m_tpMData->PA[info.ch][info.addr];
		break;
	case HX_PI:
		data = m_tpMData->PI[info.ch][info.addr];
		break;
	case HX_PM:
		data = m_tpMData->PM[info.ch][info.addr];
		break;
	case HX_PP:
		data = m_tpMData->PP[info.ch][info.addr];
		break;
	case HX_PU:
		data = m_tpMData->PU[info.ch][info.addr];
		break;
	case HX_PS:
		data = m_tpMData->PS[info.ch][info.addr];
		break;
	case HX_SV:
		data = m_tpMData->SV[info.ch][info.addr];
		break;
	case HX_ML:
		data = m_tpMData->ML[info.ch][info.addr][info.bit];
		break;
	case HX_MGV:
		data = m_tpMData->MGV[info.ch][info.addr];
		break;
	case HX_B:
		data = m_tpMData->B[info.addr];
		break;
	case HX_SN:
		data = m_tpBMData->SN[info.ch][info.addr];
		break;
	default:
		printf("section : %s\nCheck3264Type 함수 값이 들어가지 않았습니다.\n", info.text);
		data = -1;
	}
	return data;
}

CString CASFdataDlg::CheckBitType(MapInfo info)
{
	CString data =_T("");
	switch (info.name)
	{
	case HX_X:
		if (info.bit == 0)
		{
			data.Format(_T("%d"), m_tpMData->X[info.addr]);
		}
		else {
			data.Format(_T("%d"),getBit32(m_tpMData->X[info.addr], info.bit));
		}
		break;
	case HX_Y:
		if (info.bit == 0)
		{
			data.Format(_T("%d"), m_tpMData->Y[info.addr]);
		}
		else {
			data.Format(_T("%d"), getBit32(m_tpMData->Y[info.addr], info.bit));
		}
		break;
	case HX_G:
		if (info.bit == 0)
		{
			data.Format(_T("%d"), m_tpMData->G[info.ch][info.addr]);
		}
		else {
			data.Format(_T("%d"), getBit32(m_tpMData->G[info.ch][info.addr], info.bit));
		}
		break;
	case HX_F:
		if (info.bit == 0)
		{
			data.Format(_T("%d"), m_tpMData->F[info.ch][info.addr]);
		}
		else {
			data.Format(_T("%d"), getBit32(m_tpMData->F[info.ch][info.addr], info.bit));
		}
		break;
	case HX_T:
		data.Format(_T("%d"), getBit32(m_tpBMData->T[info.addr], info.bit));
		break;
	case HX_C:
		data.Format(_T("%d"), getBit32(m_tpBMData->C[info.addr], info.bit));
		break;
	case HX_D:
		data.Format(_T("%d"), getBit32(m_tpBMData->D[info.addr], info.bit));
		break;

	case HX_R:
		if (info.addr > 1024)
		{
			if (info.bit == 0)
			{
				data.Format(_T("%d"), m_tpMData->R[info.addr - 1024]);
			}
			else {
				data.Format(_T("%d"),getBit32(m_tpMData->R[info.addr - 1024], info.bit));
			}
		}
		else
		{
			if (info.bit == 0)
			{
				data.Format(_T("%d"), m_tpMData->R[info.addr]);
			}
			else {
				data.Format(_T("%d"), getBit32(m_tpMData->R[info.addr], info.bit));
			}
		}
		break;
	default:
		printf("section : %s\nCheckBitType 함수 값이 들어가지 않았습니다.\n", info.text);
		data = "";
	}
	return data;
}


CString CASFdataDlg::GetPullBit(U32 num)
{
	CString bit2=_T("");
	for (int i = 31; i >= 0; --i) { //8자리 숫자까지 나타냄
		int result = num >> i & 1;
		bit2.AppendFormat(_T("%d"),result);
	}
	return bit2;
}

int CASFdataDlg::getMapName(CString value)
{
	int name = -1;
	if (value.Find(L'[') != -1)
	{
		value = value.Left(value.GetLength() - 3);
	}
	value.MakeUpper();
	if (value == "X") {
		name = HX_X;
	}
	else if (value == "Y") {
		name = HX_Y;
	}
	else if (value == "G") {
		name = HX_G;
	}
	else if (value == "F") {
		name = HX_F;
	}
	else if (value == "R") {
		name = HX_R;
	}
	else if (value == "PA") {
		name = HX_PA;
	}
	else if (value == "PI") {
		name = HX_PI;
	}
	else if (value == "PM") {
		name = HX_PM;
	}
	else if (value == "PP") {
		name = HX_PP;
	}
	else if (value == "PU") {
		name = HX_PU;
	}
	else if (value == "PS") {
		name = HX_PS;
	}
	else if (value == "SV") {
		name = HX_SV;
	}
	else if (value == "ML") {
		name = HX_ML;
	}
	else if (value == "MGV") {
		name = HX_MGV;
	}
	else if (value == "B") {
		name = HX_B;
	}
	else if (value == "T") {
		name = HX_T;
	}
	else if (value == "C") {
		name = HX_C;
	}
	else if (value == "D") {
		name = HX_D;
	}
	else if (value == "SN") {
		name = HX_SN;
	}
	else if (value == "MGN") {
		name = HX_MGN;
	}
	else if (value == "STR_NCPATH") {
		name = HX_STR_NCPATH;
	}
	else if (value == "STR_PLC") {
		name = HX_STR_PLCFILE;
	}
	else if (value == "STR_MAP") {
		name = HX_STR_MAPFILE;
	}
	else if (value == "STR_MAINNC") {
		name = HX_STR_MAINPROG;
	}
	else if (value == "STR_SUBNC") {
		name = HX_STR_SUBPROG;
	}
	else if (value == "STR_CURALM") {
		name = HX_STR_ALARMMSG;
	}
	else if (value == "STR_CUROPMSG") {
		name = HX_STR_OPMSG;
	}

	return name;
}


int CASFdataDlg::getBit32(int data, int bit)
{
	return ((data >> bit) & 0x01) ? 1 : 0;
}


void CASFdataDlg::ASF_vInitdata()
{
	m_tpBMData->SN[0][2] = (double)2457851;
	m_tpBMData->SN[0][0] = (double)5548752;
	m_tpBMData->SN[0][1] = (double)4523441;
	m_tpMData->PS[0][31] = 1.2348;
	m_tpMData->PS[1][31] = 4.6548;
	m_tpMData->Y[160] = 0xF;
	m_tpMData->X[200] = (unsigned int)0101;// 65 가 나온 이유는? = 숫자앞에 0이 들어가면 8진수로 인식이 됩니다
	_tcscpy_s(m_tpSTRData->caNCPath[2], _countof(m_tpSTRData->caNCPath[2]), "NC 주소입니다.");
	_tcscpy_s(m_tpSTRData->caPLCFile, _countof(m_tpSTRData->caPLCFile), "PLC 파일 이름입니다.");
	_tcscpy_s(m_tpSTRData->caMAPFile, _countof(m_tpSTRData->caMAPFile), "MAP 파일 이름입니다.");
	_tcscpy_s(m_tpSTRData->caMainProg[2], _countof(m_tpSTRData->caMainProg[2]), "MAIN 프로그램");
	_tcscpy_s(m_tpSTRData->caSubProg[0], _countof(m_tpSTRData->caSubProg[0]), "SUB 프로그램");
	_tcscpy_s(m_tpSTRData->caCurAlarmMsg, _countof(m_tpSTRData->caCurAlarmMsg), "알람 메시지 입니다.");
	_tcscpy_s(m_tpSTRData->caCurOpMsg, _countof(m_tpSTRData->caPLCFile), "오피 메시지 입니다.");
}


CString CASFdataDlg::GetMapData(int type, MapInfo* info)
{
	CString data=_T("");
	double bit =0;
	if (type != TYPE_STRING && info->ch == -1) { info->ch = 0; }
	switch (type) {
	case TYPE_3264:
		bit = Check3264Type(*info);
		break;
	case TYPE_BIT:
		data += CheckBitType(*info);
		break;
	case TYPE_STRING:
		if (CheckSTRType(*info) == "")
		{
			data = "";
		}
		else { data = CheckSTRType(*info); }
		break;
	}

	if (info->format.Compare(_T("time"))==0)
	{
		if (bit > 0)
		{
			CString currentDate = time((int)bit);
			data += currentDate;
		}
		else { data = ""; }
	}

	else if(info->format.Find(_T("f")) !=-1) {
		if (bit > 0)
		{
			data.Format(_T("%.3f"), bit);
		}
		else { data = ""; }
	}
	return data;
}

void CASFdataDlg::SaveData()
{
	CString data = "";
	for (int k = 0; k < TYPE_MAX; k++) {
		for (int i = 0; i < mList[k].GetCount(); i++) {

			CString check_data;
			check_data += mList[k].GetAt(mList[k].FindIndex(i)).text;
			check_data += "=";
			check_data += GetMapData(k, &mList[k].GetAt(mList[k].FindIndex(i)));
			check_data += "\n";
			if (GetMapData(k, &mList[k].GetAt(mList[k].FindIndex(i))) == ""|| GetMapData(k, &mList[k].GetAt(mList[k].FindIndex(i))).GetLength() >40)
			{
				check_data = "";
			}
			data += check_data;
		}
	}
	SaveFile(data);
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

void CASFdataDlg::SaveFile(CString value)
{
	
	if (m_SaveMode == 0)
	{
		FILE* pFile;
		fopen_s(&pFile,"data.txt", "w,ccs=UTF-8");
		//FILE* pFile = fopen("data.txt", "w"); // ANSI txt파일로 저장
		//char* chdata = ToChar(value);
		CStringW strw(value);
		wchar_t* chdata = (wchar_t*)(const wchar_t*)strw;
		fwprintf(pFile,chdata);
		fclose(pFile);
	}
	else
	{
		CString currentDate;
		CTime data = CTime::GetCurrentTime();
		currentDate.Format(_T("%d%d%d%d%d%d.txt"), data.GetYear(), data.GetMonth(), data.GetDay(), data.GetHour(), data.GetMinute(), data.GetSecond());
		char* chtime = ToChar(currentDate);
		char* chdata = ToChar(value);
		FILE* pFile = fopen("data_"+*chtime, "wt");
		fprintf(pFile, chdata);
		fclose(pFile);

	}


}

char* CASFdataDlg::ToChar(CString value)
{
	char buffer[4096] = { 0 };
	memset(buffer, 0, 4096);
	strcpy(buffer, CT2A(value));
	return buffer;
}
TCHAR* CASFdataDlg::ToTChar(CString value)
{
	TCHAR* des = new TCHAR[value.GetLength() + 1]; // 1은 NULL을 위한 여유공간
	_tcscpy(des, value.GetBuffer(0));
	return des;
}

void CASFdataDlg::InItStruct(MapInfo* info)
{
	info->addr = -1;
	info->bit = -1;
	info->ch = -1;
	info->format = "";
	info->name = -1;
	info->text = "";
}


// 창 만들기
void CASFdataDlg::ASF_vCreate()
{
	IniLoad();
}

// 윈도우 삭제
void CASFdataDlg::ASF_vDestroy()
{
	delete []m_tpMData;
	delete[] m_tpBMData;
	delete[] m_tpSTRData;
}

//윈도우 출력
void CASFdataDlg::ASF_vShow() {}

// 윈도우 숨김
void CASFdataDlg::ASF_vHide() {}

// 타이머 함수가 일정간격으로 호출하는 함수
void CASFdataDlg::ASF_vRefresh() {}

// 화면 다시그릴 필요가 있을때
void CASFdataDlg::ASF_vPaint() {}

// 윈도우사이즈
void CASFdataDlg::ASF_vSize() {}

//
S32 CASFdataDlg::ASF_nWndProc()
{
	S32 s32_bit = 0;
	return s32_bit;
}

// 입력받은 키
void CASFdataDlg::ASF_vKeyData() {}
