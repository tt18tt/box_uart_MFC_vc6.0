// uart_testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "uart_test.h"
#include "uart_testDlg.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUart_testDlg dialog

CUart_testDlg::CUart_testDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUart_testDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUart_testDlg)
	m_EDITTX = _T("");
	m_RX = _T("");
	m_ID = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUart_testDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUart_testDlg)
	DDX_Control(pDX, IDC_BUTsend, m_BUTsend);
	DDX_Control(pDX, IDC_BUTON, m_BUTON);
	DDX_Text(pDX, IDC_EDITTX, m_EDITTX);
	DDX_Control(pDX, IDC_MSCOMM1, m_COMM1);
	DDX_Text(pDX, IDC_RX, m_RX);
	DDX_Text(pDX, IDC_ID, m_ID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUart_testDlg, CDialog)
	//{{AFX_MSG_MAP(CUart_testDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTON, OnButon)
	ON_BN_CLICKED(IDC_BUTsend, OnBUTsend)
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnEditchangeCombo1)
	ON_BN_CLICKED(IDC_clearRX, OnclearRX)
	ON_BN_CLICKED(IDC_BUTTON1, OnReadId)
	ON_BN_CLICKED(IDC_BUTTON2, OnWriteID)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUart_testDlg message handlers

BOOL CUart_testDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnEditchangeCombo1();//自动寻找串口
	SetDlgItemText(IDC_COMBO2,"9600");
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUart_testDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUart_testDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUart_testDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CUart_testDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CUart_testDlg)
	ON_EVENT(CUart_testDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CUart_testDlg::OnButon() 
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	CString str1; 
	int num;
	if(m_COMM1.GetPortOpen())
		m_COMM1.SetPortOpen(FALSE);
	//选择端口号
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(strTemp); //将获取的值存放到CString类型变量strTemp中。
	str1=strTemp.Mid(3,2); //取出第3位后2位
	num =  atoi(str1);
	printf("com%d\n",num);//端口号
	m_COMM1.SetCommPort(num); 

	//设置IO缓存区
	m_COMM1.SetInBufferSize(1024); //设置输入缓冲区的大小，Bytes
	m_COMM1.SetOutBufferSize(1024); //设置输入缓冲区的大小，Bytes//

	//设置波特率 默认无校验	
	strTemp.Empty();
	((CComboBox*)GetDlgItem(IDC_COMBO2))->GetWindowText(strTemp); //将获取的值存放到CString类型变量strTemp中。
	str1 = strTemp;//波特率
	str1+=",n,8,1";
	m_COMM1.SetSettings(str1); 
	
	//设置其他参数
	m_COMM1.SetInputMode(1); //1：表示以二进制方式检取数据
	m_COMM1.SetRThreshold(1); //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
	m_COMM1.SetInputLen(0); //设置当前接收区数据长度为0
	if(!m_COMM1.GetPortOpen())
	{
		m_COMM1.SetPortOpen(TRUE);//打开串口
		AfxMessageBox("打开成功");
	}
	else
		AfxMessageBox("cannot open serial port");
	m_COMM1.GetInput();//先预读缓冲区以清除残留数据
	UpdateData(false);
	
}
using namespace std;

/**************************************************************************** 
函数名称: str_to_hex 
函数功能: 字符串转换为十六进制 
输入参数: string 字符串  len 字符串的长度。 
输出参数: cbuf 十六进制
*****************************************************************************/   
static int str_to_hex(unsigned char *string, unsigned char *cbuf, int len)  
{  
    BYTE high, low;  
    int idx, ii=0;  
    for (idx=0; idx<len; idx+=2)   
    {  
        high = string[idx];  
        low = string[idx+1];  
          
        if(high>='0' && high<='9')  
            high = high-'0';  
        else if(high>='A' && high<='F')  
            high = high - 'A' + 10;  
        else if(high>='a' && high<='f')  
            high = high - 'a' + 10;  
        else  
            return -1;  
          
        if(low>='0' && low<='9')  
            low = low-'0';  
        else if(low>='A' && low<='F')  
            low = low - 'A' + 10;  
        else if(low>='a' && low<='f')  
            low = low - 'a' + 10;  
        else  
            return -1;  
          
        cbuf[ii++] = high<<4 | low;  
    }  
    return 0;  
} 

char Cc_Check_new(unsigned char *buf,int len)
{
	int Sum_check=0;
	int F_sum=0;
	int Cc=0;
	int i;
	Cc = buf[0];
	for (i=1;i<len;i++)
	{	    
		Cc = Cc^buf[i];
	}
   	   	    	
	return Cc;	   	    	
}

int Cc_Check_old(unsigned char *buf,int len)
{
	int Sum_check=0;
	int F_sum=0;
	int Cc=0;
	int i;
	
	for (i=0;i<len;i++)
	    {
	    	Sum_check+=buf[i];	    	
	    	}
	   	    	F_sum=~Sum_check;   	    	
	   	    	Cc=F_sum+1;	 	   	    	
	   	    	return Cc;	   	    	
}

void CUart_testDlg::OnBUTsend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); //读取编辑框内容
	unsigned char send_commd[256];
	unsigned char resp[1000];
	unsigned char device_ID[30];
	CByteArray arry; 
	CString str1;
	char num_str[2];
	int i,len,lens;
	int test;
	memset(send_commd,0,256);
	memset(resp,0,100);
	memset(num_str,0,2);
	memset(device_ID,0,30);
	memcpy(resp,m_EDITTX.GetBuffer(0),(unsigned char)m_EDITTX.GetLength());
	len = (unsigned int)m_EDITTX.GetLength();//得到指令长度
	memcpy(device_ID,m_ID.GetBuffer(0),(unsigned char)m_ID.GetLength());
	lens = (unsigned int)m_ID.GetLength();//得到ID长度

	printf("len == %d\n",len);
	send_commd[0] = 0xf0;
	send_commd[1] = 7+(len/2)+2;
	send_commd[2] = 0x05;

	str_to_hex(device_ID,send_commd+3,lens);
	//memcpy(send_commd+3,device_ID,4);

	str_to_hex(resp,send_commd+7,len);
	
	send_commd[7+len/2] = Cc_Check_new(send_commd + 1, 6+len/2);
	send_commd[7+len/2+1] = 0xf1;
	

	printf("test == %x\n",test);
	for(i = 0;i<7+len/2+2;i++)
	{
		printf(" %02x",send_commd[i]);
		arry.Add(send_commd[i]);//将16进制加入到arry数据中
	}
	printf("\n");

	m_COMM1.SetOutput(COleVariant(arry));//发送数据
}

void CUart_testDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
VARIANT variant_inp;
    COleSafeArray safearray_inp;
    LONG len,k;
    BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integerthat is not signed.
	char result[100];
    CString strtemp;
	memset(rxdata,0,2048);
	
    if(m_COMM1.GetCommEvent()==2) //事件值为2表示接收缓冲区内有字符
    {             ////////以下你可以根据自己的通信协议加入处理代码
		Sleep(200);
		printf("now type == %d\n",m_COMM1.GetCommEvent());
        variant_inp=m_COMM1.GetInput(); //读缓冲区
        safearray_inp=variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
        len=safearray_inp.GetOneDimSize(); //得到有效数据长度
        for(k=0;k<len;k++)
            safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
        for(k=0;k<len;k++) //将数组转换为Cstring型变量
        {	
            BYTE bt=*(char*)(rxdata+k); //字符型 方便存入缓存区
            strtemp.Format("%02x ",bt); //16进制转字符串存入
            m_RX+=strtemp; //加入接收编辑框对应字符串 
        }
		printf("len_k == %d\n",len);

		for(k=0;k<len;k++) //将数组转换为Cstring型变量
        {	
			printf(" %02x",rxdata[k]);
        }
		printf("\n");
		if(rxdata[2]== 0x02)//关于设备号的指令
		{
			memset(result,0,100);
			if(rxdata[3] == 0x11)
			{
				sprintf(result,"设备号为:0x%x 0x%x 0x%x 0x%x",rxdata[4],rxdata[5],rxdata[6],rxdata[7]);	
			}
			else
			{
				if(rxdata[4] == 0x01)
				{
					sprintf(result,"设置设备ID成功");
				}
				if(rxdata[4] == 0x00)
				{
					sprintf(result,"设置设备ID失败");
				}
			}
			MessageBox(result);
			return ;
		}
		
    }
	m_RX+="\r\n";//加个换行符
	SetDlgItemText(IDC_RX,m_RX);//不使用UpdateData(FALSE);的原因是该函数会
	//刷新整个对话框的数据，而SetDlgItemText() 只更新接收编辑框的数据。
}



void CUart_testDlg::OnEditchangeCombo1() 
{
	//程序启动时获取全部可用串口
	HANDLE hCom;
	int i,num,k;
	CString str;
	BOOL flag;
	((CComboBox *)GetDlgItem(IDC_COMBO1))->ResetContent();
	 flag = FALSE;
	 num = 0;
	 for (i = 1;i <= 16;i++)
	 {//支持16个串口
		 str.Format("\\\\.\\COM%d",i);//用creatfile打开串口 这种方法才支持10以上的
		 hCom = CreateFile(str, 0, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);//打开串口
		 if(INVALID_HANDLE_VALUE != hCom )
		 {//能打开该串口，则添加该串口
			 CloseHandle(hCom);
			 str = str.Mid(4);
			 ((CComboBox *)GetDlgItem(IDC_COMBO1))->AddString(str);
			 if (flag == FALSE)
			 {
				 flag = TRUE;
				 num = i;
			 }
		 }
	 }
	 i = ((CComboBox *)GetDlgItem(IDC_COMBO1))->GetCount();
	 if (i == 0)
	 {//若找不到可用串口则禁用“打开串口”功能
		((CComboBox *)GetDlgItem(IDC_COMBO1))->EnableWindow(FALSE);
	 }
	 else
	 {
		 k = ((CComboBox *)GetDlgItem((IDC_COMBO1)))->GetCount();
		 ((CComboBox *)GetDlgItem(IDC_COMBO1))->SetCurSel(k - 1);
		 //mCom.BindCommPort(num);
	 }
}

void CUart_testDlg::OnclearRX() 
{
	// TODO: Add your control notification handler code here
	m_RX.Empty();
	SetDlgItemText(IDC_RX,m_RX);//不使用UpdateData(FALSE);的原因是该函数会
}

void CUart_testDlg::OnReadId() 
{
	// TODO: Add your control notification handler code here
	unsigned char send_commd[256];
	int i;
	CByteArray arry; 
	UpdateData(TRUE); //读取编辑框内容
	memset(send_commd,0,256);
	send_commd[0] = 0x23;
	send_commd[1] = 0x04;
	send_commd[2] = 0x02;
	send_commd[3] = 0x11;
	send_commd[4] = Cc_Check_old(send_commd+2,12);
	send_commd[5] = 0x24;

	for(i = 0;i<6;i++)
	{
		printf(" %02x",send_commd[i]);
		arry.Add(send_commd[i]);//将16进制加入到arry数据中
	}
	printf("\n");

	m_COMM1.SetOutput(COleVariant(arry));//发送数据
}

void CUart_testDlg::OnWriteID() 
{
	// TODO: Add your control notification handler code here
	unsigned char send_commd[256];
	unsigned char resp[1000];
	unsigned char device_ID[30];
	int i,lens;
	CByteArray arry; 
	UpdateData(TRUE); //读取编辑框内容
	memset(send_commd,0,256);
	memset(resp,0,100);
	memset(device_ID,0,30);

	memcpy(device_ID,m_ID.GetBuffer(0),(unsigned char)m_ID.GetLength());
	lens = (unsigned int)m_ID.GetLength();//得到ID长度

	send_commd[0] = 0x23;
	send_commd[1] = 0x08;
	send_commd[2] = 0x02;
	send_commd[3] = 0x01;
	str_to_hex(device_ID,send_commd+4,lens);
	send_commd[8] = Cc_Check_old(send_commd+2,12);
	send_commd[9] = 0x24;

	for(i = 0;i<10;i++)
	{
		printf(" %02x",send_commd[i]);
		arry.Add(send_commd[i]);//将16进制加入到arry数据中
	}
	printf("\n");
	m_COMM1.SetOutput(COleVariant(arry));//发送数据
}
