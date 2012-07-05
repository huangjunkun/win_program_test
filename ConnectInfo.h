// ConnectInfo.h: interface for the CConnectInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTINFO_H__F4E104B7_F39A_4718_8EA8_BA70115F8D13__INCLUDED_)
#define AFX_CONNECTINFO_H__F4E104B7_F39A_4718_8EA8_BA70115F8D13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <string>
#include <deque>
#include <cassert>


#define STDMETHODCALLTYPE       
#define STDMETHOD(method)       virtual HRESULT STDMETHODCALLTYPE method
    
#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE

typedef struct tagSTRING
{
	size_t len;
	char* str;
} STRING;

typedef struct tagWSTRING
{
	size_t len;
	wchar_t* str;
} WSTRING;

struct connect_info_item
{
    int resource_no;
    int connection_no;
    int msg_type;
    std::string msg;
};

struct connect_info_itemW
{
	int resource_no;
	int connection_no;
	int msg_type;
	std::wstring msg;
};

typedef 
enum tagICONNECTINFO_MSGTYPE
{	ICI_SEND_MSG	= 0,
ICI_RECV_MSG	= 1,
ICI_NOTIFY_MSG	= 2,
ICI_ERROR_MSG	= 3,
ICI_WARN_MSG	= 4
} 	ICONNECTINFO_MSGTYPE;

// 连接信息的“参数类型”定义如下：
enum e_connect_info{
	E_CONNECT_INFO_NULL = 0,
	E_CONNECT_INFO_LONG,
	E_CONNECT_INFO_LONGLONG,
	E_CONNECT_INFO_LONG_LONG,
	E_CONNECT_INFO_STRING,
	E_CONNECT_INFO_STRING_STRING,
	E_CONNECT_INFO_LONG_STRING,
	E_CONNECT_INFO_STRING_LONG,
};

struct connect_info_item2
{
	int				resource_no;		//资源标识
	int				connection_no; 		//连接标识
	int				msg_type; 			//信息类型
	int				msg_id; 			//信息id
	e_connect_info	param_type; 		//参数类型标识
	std::string		param;				//存储参数缓冲区，根据不同类型做不同编解码。
};


typedef BYTE*	BUFFER_PTR;

typedef ULONG BUFFER_SIZE;

class CConnectInfo 
{
public:

	/*************************************************/
	/*	IConnectInfoU					
	/*************************************************/
	STDMETHOD(PushInfo1W)(/*[in]*/ICONNECTINFO_MSGTYPE msg_type, /*[in]*/WSTRING msg, /*[in]*/ULONG resource_no, /*[in]*/ULONG connection_no );
	STDMETHOD(PushInfo2W)(/*[in]*/ICONNECTINFO_MSGTYPE msg_type, /*[in]*/ULONG msg_id, /*[in]*/ULONG resource_no, /*[in]*/ULONG connection_no );    
	STDMETHOD(PushFormatInfo1W)(/*[in]*/ICONNECTINFO_MSGTYPE lMsgType, /*[in]*/ULONG lMsgID, /*[in]*/ULONG lNum, /*[in]*/ULONG resource_no, /*[in]*/ULONG connection_no );
	STDMETHOD(PushFormatInfo2W)(/*[in]*/ICONNECTINFO_MSGTYPE lMsgType, /*[in]*/ULONG lMsgID, /*[in]*/ULONGLONG lNum, /*[in]*/ULONG resource_no, /*[in]*/ULONG connection_no ) ;
	STDMETHOD(PushFormatInfo3W)(/*[in]*/ICONNECTINFO_MSGTYPE lMsgType, /*[in]*/ULONG lMsgID, /*[in]*/ULONG lNum1, /*[in]*/ULONG lNum2, /*[in]*/ULONG resource_no, /*[in]*/ULONG connection_no ) ;
	STDMETHOD(PushFormatInfo4W)(/*[in]*/ICONNECTINFO_MSGTYPE lMsgType, /*[in]*/ULONG lMsgID, /*[in]*/WSTRING str, /*[in]*/ULONG resource_no, /*[in]*/ULONG connection_no ) ;
	STDMETHOD(PushFormatInfo5W)(/*[in]*/ICONNECTINFO_MSGTYPE lMsgType, /*[in]*/ULONG lMsgID, /*[in]*/WSTRING str1, /*[in]*/WSTRING str2, /*[in]*/ULONG resource_no, /*[in]*/ULONG connection_no ) ;
	STDMETHOD(PushFormatInfo6W)(/*[in]*/ICONNECTINFO_MSGTYPE lMsgType, /*[in]*/ULONG lMsgID, /*[in]*/ULONG lNum, /*[in]*/WSTRING str, /*[in]*/ULONG resource_no, /*[in]*/ULONG connection_no ) ;
	STDMETHOD(PushFormatInfo7W)(/*[in]*/ICONNECTINFO_MSGTYPE lMsgType, /*[in]*/ULONG lMsgID, /*[in]*/WSTRING str, /*[in]*/ULONG lNum, /*[in]*/ULONG resource_no, /*[in]*/ULONG connection_no ) ;
	STDMETHOD(GetNewConnectInfoW)( /*[in]*/BUFFER_PTR buffer, /*[in]*/BUFFER_SIZE bufLen, /*[out]*/ULONG *pResultSize, LONG *pResult );

	STDMETHOD(LoadConnectInfoW)( /*[in]*/BUFFER_PTR buffer, /*[in]*/BUFFER_SIZE bufLen, /*[out]*/LONG *pResult );
	STDMETHOD(ConnectInfoCount)( /*[out]*/ULONG *pResult );

	const connect_info_item2& operator[] (size_t index) const
	{
		assert (index < _items2.size());
		return _items2[index];
	}
	connect_info_item2& operator[] (size_t index)
	{
		assert (index < _items2.size());
		return _items2[index];
	}
protected:
 
	// 20120620
	bool fetch_one_item2( connect_info_item2& result );
	void push_front2( connect_info_item2& item );
	void push_back2( int resource_no, int connection_no, ICONNECTINFO_MSGTYPE msg_type, e_connect_info param_type,
		const std::string& param );
	void push_back2(connect_info_item2& item);
	void get_new_conncet_info2( /*[in]*/BUFFER_PTR buffer, /*[in]*/BUFFER_SIZE bufLen, /*[out]*/ULONG *pResultSize, LONG *pResult );
	void load_connect_info2( /*[in]*/BUFFER_PTR buffer, /*[in]*/BUFFER_SIZE bufLen, /*[out]*/LONG *pResult);

private:
	static unsigned read_info_param(BUFFER_PTR buffer, e_connect_info param_type, std::string& param);

private:
	std::deque<connect_info_item2> _items2;

};

int test_CConnectInfo();

#endif // !defined(AFX_CONNECTINFO_H__F4E104B7_F39A_4718_8EA8_BA70115F8D13__INCLUDED_)
