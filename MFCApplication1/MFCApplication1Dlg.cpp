
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent),
	m_select_brush(RGB(0, 200, 255)),
	m_unselect_brush(RGB(0, 80, 200)),
	m_select_pen(PS_SOLID, 1, RGB(0, 255, 255)),
	m_unselect_pen(PS_SOLID, 1, RGB(0, 0, 128))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	/*
	m_select_brush.CreateSolidBrush(RGB(0, 200, 255));
	m_unselect_brush.CreateSolidBrush(RGB(0, 80, 200));
	m_select_pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	m_unselect_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	*/
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{

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
		CBrush * p_old_brush = dc.SelectObject(&m_unselect_brush);
		CPen * p_old_pen = dc.SelectObject(&m_unselect_pen);

		int x, y;

		for (y = 0; y < 3; y++) {
			for (x = 0; x < 6; x++) {
				dc.Rectangle(50 + x * 100, 50 + y* 100, 151 + x * 100, 151 + y*100);
			}
		}

		if (m_index != -1) {
			x = m_index % 7;
			y = m_index / 7;

			dc.SelectObject(&m_select_brush);
			dc.SelectObject(&m_select_pen);

			dc.Ellipse(x * 100, y * 100, 101 + x * 100, 101 + y * 100);
		}
		
		dc.SelectObject(p_old_brush);
		dc.SelectObject(p_old_pen);

		// CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//if (point.y < 100) {
		/*
		m_index_x = -1;

		for (int i = 0; i < 6; i++) {
			if (point.x < 100 + i * 100) {
				m_index_x = i;
				break;
			}
		}
		*/

		/*
		// 코드를 간단히
		m_index_x = point.x / 100;
		m_index_y = point.y / 100;
		if (m_index_x >= 6 || m_index_y >= 3) m_index_x = -1;
		*/
		
	point.x = point.x / 100;		// 0 ~ 5
	point.y = point.y / 100;		// 0 ~ 2

	if (point.x >= 7 || point.y >= 4) m_index = -1;
	m_index = point.y * 7 + point.x;

	Invalidate(TRUE);
	//}

	CDialogEx::OnLButtonDown(nFlags, point);
}
