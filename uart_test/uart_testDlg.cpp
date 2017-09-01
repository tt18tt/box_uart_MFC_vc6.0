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
	OnEditchangeCombo1();//�Զ�Ѱ�Ҵ���
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
	//ѡ��˿ں�
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(strTemp); //����ȡ��ֵ��ŵ�CString���ͱ���strTemp�С�
	str1=strTemp.Mid(3,2); //ȡ����3λ��2λ
	num =  atoi(str1);
	printf("com%d\n",num);//�˿ں�
	m_COMM1.SetCommPort(num); 

	//����IO������
	m_COMM1.SetInBufferSize(1024); //�������뻺�����Ĵ�С��Bytes
	m_COMM1.SetOutBufferSize(1024); //�������뻺�����Ĵ�С��Bytes//

	//���ò����� Ĭ����У��	
	strTemp.Empty();
	((CComboBox*)GetDlgItem(IDC_COMBO2))->GetWindowText(strTemp); //����ȡ��ֵ��ŵ�CString���ͱ���strTemp�С�
	str1 = strTemp;//������
	str1+=",n,8,1";
	m_COMM1.SetSettings(str1); 
	
	//������������
	m_COMM1.SetInputMode(1); //1����ʾ�Զ����Ʒ�ʽ��ȡ����
	m_COMM1.SetRThreshold(1); //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�
	m_COMM1.SetInputLen(0); //���õ�ǰ���������ݳ���Ϊ0
	if(!m_COMM1.GetPortOpen())
	{
		m_COMM1.SetPortOpen(TRUE);//�򿪴���
		AfxMessageBox("�򿪳ɹ�");
	}
	else
		AfxMessageBox("cannot open serial port");
	m_COMM1.GetInput();//��Ԥ���������������������
	UpdateData(false);
	
}
using namespace std;

/**************************************************************************** 
��������: str_to_hex 
��������: �ַ���ת��Ϊʮ������ 
�������: string �ַ���  len �ַ����ĳ��ȡ� 
�������: cbuf ʮ������
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
	UpdateData(TRUE); //��ȡ�༭������
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
	len = (unsigned int)m_EDITTX.GetLength();//�õ�ָ���
	memcpy(device_ID,m_ID.GetBuffer(0),(unsigned char)m_ID.GetLength());
	lens = (unsigned int)m_ID.GetLength();//�õ�ID����

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
		arry.Add(send_commd[i]);//��16���Ƽ��뵽arry������
	}
	printf("\n");

	m_COMM1.SetOutput(COleVariant(arry));//��������
}

void CUart_testDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
VARIANT variant_inp;
    COleSafeArray safearray_inp;
    LONG len,k;
    BYTE rxdata[2048]; //����BYTE���� An 8-bit integerthat is not signed.
	char result[100];
    CString strtemp;
	memset(rxdata,0,2048);
	
    if(m_COMM1.GetCommEvent()==2) //�¼�ֵΪ2��ʾ���ջ����������ַ�
    {             ////////��������Ը����Լ���ͨ��Э����봦�����
		Sleep(200);
		printf("now type == %d\n",m_COMM1.GetCommEvent());
        variant_inp=m_COMM1.GetInput(); //��������
        safearray_inp=variant_inp; //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
        len=safearray_inp.GetOneDimSize(); //�õ���Ч���ݳ���
        for(k=0;k<len;k++)
            safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE������
        for(k=0;k<len;k++) //������ת��ΪCstring�ͱ���
        {	
            BYTE bt=*(char*)(rxdata+k); //�ַ��� ������뻺����
            strtemp.Format("%02x ",bt); //16����ת�ַ�������
            m_RX+=strtemp; //������ձ༭���Ӧ�ַ��� 
        }
		printf("len_k == %d\n",len);

		for(k=0;k<len;k++) //������ת��ΪCstring�ͱ���
        {	
			printf(" %02x",rxdata[k]);
        }
		printf("\n");
		if(rxdata[2]== 0x02)//�����豸�ŵ�ָ��
		{
			memset(result,0,100);
			if(rxdata[3] == 0x11)
			{
				sprintf(result,"�豸��Ϊ:0x%x 0x%x 0x%x 0x%x",rxdata[4],rxdata[5],rxdata[6],rxdata[7]);	
			}
			else
			{
				if(rxdata[4] == 0x01)
				{
					sprintf(result,"�����豸ID�ɹ�");
				}
				if(rxdata[4] == 0x00)
				{
					sprintf(result,"�����豸IDʧ��");
				}
			}
			MessageBox(result);
			return ;
		}
		
    }
	m_RX+="\r\n";//�Ӹ����з�
	SetDlgItemText(IDC_RX,m_RX);//��ʹ��UpdateData(FALSE);��ԭ���Ǹú�����
	//ˢ�������Ի�������ݣ���SetDlgItemText() ֻ���½��ձ༭������ݡ�
}



void CUart_testDlg::OnEditchangeCombo1() 
{
	//��������ʱ��ȡȫ�����ô���
	HANDLE hCom;
	int i,num,k;
	CString str;
	BOOL flag;
	((CComboBox *)GetDlgItem(IDC_COMBO1))->ResetContent();
	 flag = FALSE;
	 num = 0;
	 for (i = 1;i <= 16;i++)
	 {//֧��16������
		 str.Format("\\\\.\\COM%d",i);//��creatfile�򿪴��� ���ַ�����֧��10���ϵ�
		 hCom = CreateFile(str, 0, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);//�򿪴���
		 if(INVALID_HANDLE_VALUE != hCom )
		 {//�ܴ򿪸ô��ڣ�����Ӹô���
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
	 {//���Ҳ������ô�������á��򿪴��ڡ�����
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
	SetDlgItemText(IDC_RX,m_RX);//��ʹ��UpdateData(FALSE);��ԭ���Ǹú�����
}

void CUart_testDlg::OnReadId() 
{
	// TODO: Add your control notification handler code here
	unsigned char send_commd[256];
	int i;
	CByteArray arry; 
	UpdateData(TRUE); //��ȡ�༭������
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
		arry.Add(send_commd[i]);//��16���Ƽ��뵽arry������
	}
	printf("\n");

	m_COMM1.SetOutput(COleVariant(arry));//��������
}

void CUart_testDlg::OnWriteID() 
{
	// TODO: Add your control notification handler code here
	unsigned char send_commd[256];
	unsigned char resp[1000];
	unsigned char device_ID[30];
	int i,lens;
	CByteArray arry; 
	UpdateData(TRUE); //��ȡ�༭������
	memset(send_commd,0,256);
	memset(resp,0,100);
	memset(device_ID,0,30);

	memcpy(device_ID,m_ID.GetBuffer(0),(unsigned char)m_ID.GetLength());
	lens = (unsigned int)m_ID.GetLength();//�õ�ID����

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
		arry.Add(send_commd[i]);//��16���Ƽ��뵽arry������
	}
	printf("\n");
	m_COMM1.SetOutput(COleVariant(arry));//��������
}
