// ConnectInfo.cpp: implementation of the CConnectInfo class.
//
//////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include "ConnectInfo.h"
#include <string>
#include <iostream>
#include <cassert>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define WSTRING_from_STRING 0
#define string_2_wstring 0

STDMETHODIMP CConnectInfo::PushInfo1W(/*[in]*/ICONNECTINFO_MSGTYPE msg_type, 
									  /*[in]*/WSTRING msg1, 
									  /*[in]*/ULONG resource_no, 
									  /*[in]*/ULONG connection_no )
{
// 	// ObjectLock lock(this);
// 	std::wstring msg = wstring_from_WSTRING(msg1);
// 	std::wstring::size_type last_pos = 0;
// 	std::wstring::size_type pos = msg.find( L"\n", last_pos );
// 	while( pos != std::wstring::npos )
// 	{
// 		std::wstring line( msg, last_pos, pos-last_pos );
// 		if( line.length() > 0 && line[line.length()-1] == L'\r' )
// 			line.erase( line.length()-1, 1 );
// 		if( line != L"" )
// 		{
// 			push_backW(resource_no, connection_no, msg_type, line);
// 		}
// 		last_pos = pos+1;
// 		pos = msg.find( L"\n", last_pos );
// 	}
// 	std::wstring end_line( msg, last_pos, msg.length()-last_pos);
// 	if( end_line != L"" )
// 	{
// 		push_backW(resource_no, connection_no, msg_type, end_line);
// 	}
	connect_info_item2 item;
	item.resource_no = resource_no;
	item.connection_no = connection_no;
	item.msg_type = msg_type;
	item.msg_id = 0;
	item.param_type = E_CONNECT_INFO_STRING;
	item.param.resize(4 + msg1.len * sizeof(WCHAR));
	char* buffer = &item.param[0];
	memcpy(buffer, &msg1.len, 4), buffer += 4;
	memcpy(buffer, msg1.str, msg1.len * sizeof(WCHAR));
	push_back2(item);
	return S_OK;
}

STDMETHODIMP CConnectInfo::PushInfo2W(/*[in]*/ICONNECTINFO_MSGTYPE msg_type, 
									  /*[in]*/ULONG msg_id, 
									  /*[in]*/ULONG resource_no, 
									  /*[in]*/ULONG connection_no )
{
// 	// ObjectLock lock(this);
// 	msg_pool* ptr = msg_pool::get_instance();
// 	PushInfo1W( msg_type, WSTRING_EX(ptr->get_msg_from_id(msg_id)), resource_no, connection_no );
	connect_info_item2 item;
	item.resource_no = resource_no;
	item.connection_no = connection_no;
	item.msg_type = msg_type;
	item.msg_id = msg_id;
	item.param_type = E_CONNECT_INFO_NULL;
	push_back2(item);

	return S_OK;
}

STDMETHODIMP CConnectInfo::PushFormatInfo1W(/*[in]*/ICONNECTINFO_MSGTYPE msg_type, 
										   /*[in]*/ULONG msg_id, 
										   /*[in]*/ULONG num, 
										   /*[in]*/ULONG resource_no, 
										   /*[in]*/ULONG connection_no )
{
// 	// ObjectLock lock(this);
// 	msg_pool* ptr = msg_pool::get_instance();
// 	std::wstring format_str = ptr->get_msg_from_id( msg_id );
// 	std::wstring num_str( utility::long2str(num, std::wstring()) );
// 	std::wstring::size_type pos = format_str.find( L"$1" );
// 	if( pos == std::wstring::npos )
// 	{
// 		PushInfo1W( ICI_ERROR_MSG, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
// 	else
// 	{
// 		format_str.replace( pos, 2, num_str );
// 		PushInfo1W( msg_type, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
	connect_info_item2 item;
	item.resource_no = resource_no;
	item.connection_no = connection_no;
	item.msg_type = msg_type;
	item.msg_id = msg_id;
	item.param_type = E_CONNECT_INFO_LONG;
	item.param.resize( sizeof(num));
	memcpy(&item.param[0], &num, item.param.length());
	push_back2(item);
	return S_OK;
}

STDMETHODIMP CConnectInfo::PushFormatInfo2W(/*[in]*/ICONNECTINFO_MSGTYPE msg_type, 
											/*[in]*/ULONG msg_id, 
											/*[in]*/ULONGLONG num, 
											/*[in]*/ULONG resource_no, 
											/*[in]*/ULONG connection_no )
{
// 	// ObjectLock lock(this);
// 	msg_pool* ptr = msg_pool::get_instance();
// 	std::wstring format_str = ptr->get_msg_from_id( msg_id );
// 	std::wstring num_str( utility::ulonglong2str(num, std::wstring()) );
// 	std::wstring::size_type pos = format_str.find( L"$1" );
// 	if( pos == std::wstring::npos )
// 	{
// 		PushInfo1W( ICI_ERROR_MSG, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
// 	else
// 	{
// 		format_str.replace( pos, 2, num_str );
// 		PushInfo1W( msg_type, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
	connect_info_item2 item;
	item.resource_no = resource_no;
	item.connection_no = connection_no;
	item.msg_type = msg_type;
	item.msg_id = msg_id;
	item.param_type = E_CONNECT_INFO_LONGLONG;
	item.param.resize( sizeof(num));
	memcpy(&item.param[0], &num, item.param.length());
	push_back2(item);
	return S_OK;
}

STDMETHODIMP CConnectInfo::PushFormatInfo3W(/*[in]*/ICONNECTINFO_MSGTYPE msg_type, 
											/*[in]*/ULONG msg_id, 
											/*[in]*/ULONG num1, 
											/*[in]*/ULONG num2, 
											/*[in]*/ULONG resource_no, 
											/*[in]*/ULONG connection_no )
{
// 	// ObjectLock lock(this);
// 	msg_pool* ptr = msg_pool::get_instance();
// 	std::wstring format_str = ptr->get_msg_from_id( msg_id );
// 	std::wstring num_str1( utility::long2str(num1, std::wstring()) );
// 	std::wstring num_str2( utility::long2str(num2, std::wstring()) );
// 	std::wstring::size_type pos = format_str.find( L"$1" );
// 	if( pos != std::wstring::npos )
// 	{
// 		format_str.replace( pos, 2, num_str1 );
// 	}
// 	pos = format_str.find( L"$2" );
// 	if( pos == std::wstring::npos )
// 	{
// 		PushInfo1W( ICI_ERROR_MSG, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
// 	else
// 	{
// 		format_str.replace( pos, 2, num_str2 );
// 		PushInfo1W( msg_type, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
	connect_info_item2 item;
	item.resource_no = resource_no;
	item.connection_no = connection_no;
	item.msg_type = msg_type;
	item.msg_id = msg_id;
	item.param_type = E_CONNECT_INFO_LONG_LONG;
	item.param.resize( sizeof(num2) + sizeof(num1));
	char* buffer = &item.param[0];
	memcpy(buffer, &num1, sizeof(num1)), buffer += sizeof(num1);
	memcpy(buffer, &num2, item.param.length());
	push_back2(item);
	return S_OK;
}


STDMETHODIMP CConnectInfo::PushFormatInfo4W(/*[in]*/ICONNECTINFO_MSGTYPE msg_type, 
											/*[in]*/ULONG msg_id, 
											/*[in]*/WSTRING str, 
											/*[in]*/ULONG resource_no, 
											/*[in]*/ULONG connection_no )
{
// 	// ObjectLock lock(this);
// 	msg_pool* ptr = msg_pool::get_instance();
// 	std::wstring format_str = ptr->get_msg_from_id( msg_id );
// 	std::wstring::size_type pos = format_str.find( L"$1" );
// 	if( pos == std::wstring::npos )
// 	{
// 		PushInfo1W( ICI_ERROR_MSG, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
// 	else
// 	{
// 		format_str.replace( pos, 2, str.str, str.len );
// 		PushInfo1W( msg_type, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
	connect_info_item2 item;
	item.resource_no = resource_no;
	item.connection_no = connection_no;
	item.msg_type = msg_type;
	item.msg_id = msg_id;
	item.param_type = E_CONNECT_INFO_STRING;
	item.param.resize(4 + str.len * sizeof(WCHAR));
	char* buffer = &item.param[0];
	memcpy(buffer, &str.len, 4), buffer += 4;
	//memcpy(buffer, &str.len, sizeof(str.len)), buffer += sizeof(str.len);
	memcpy(buffer, str.str, str.len * sizeof(WCHAR));
	push_back2(item);
	return S_OK;
}

STDMETHODIMP CConnectInfo::PushFormatInfo5W(/*[in]*/ICONNECTINFO_MSGTYPE msg_type, 
											/*[in]*/ULONG msg_id, 
											/*[in]*/WSTRING str1, 
											/*[in]*/WSTRING str2, 
											/*[in]*/ULONG resource_no, 
											/*[in]*/ULONG connection_no )
{
// 	// ObjectLock lock(this);
// 	msg_pool* ptr = msg_pool::get_instance();
// 	std::wstring format_str = ptr->get_msg_from_id( msg_id );
// 	std::wstring::size_type pos = format_str.find( L"$1" );
// 	if( pos != std::wstring::npos )
// 	{
// 		format_str.replace( pos, 2, str1.str, str1.len );
// 	}
// 	pos = format_str.find( L"$2" );
// 	if( pos == std::wstring::npos )
// 	{
// 		PushInfo1W( ICI_ERROR_MSG, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
// 	else
// 	{
// 		format_str.replace( pos, 2, str2.str, str2.len );
// 		PushInfo1W( msg_type, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
	connect_info_item2 item;
	item.resource_no = resource_no;
	item.connection_no = connection_no;
	item.msg_type = msg_type;
	item.msg_id = msg_id;
	item.param_type = E_CONNECT_INFO_STRING_STRING;
	item.param.resize(8  + (str1.len+str2.len) * sizeof(WCHAR));
	char* buffer = &item.param[0];
	memcpy(buffer, &str1.len, 4), buffer += 4;
	memcpy(buffer, str1.str, str1.len * sizeof(WCHAR)), buffer += str1.len * sizeof(WCHAR);
	memcpy(buffer, &str2.len, 4), buffer += 4;
	memcpy(buffer, str2.str, str2.len * sizeof(WCHAR)); // buffer += str1.len * sizeof(WCHAR);
	push_back2(item);
	
	return S_OK;
}

STDMETHODIMP CConnectInfo::PushFormatInfo6W(/*[in]*/ICONNECTINFO_MSGTYPE msg_type, 
											/*[in]*/ULONG msg_id, 
											/*[in]*/ULONG num, 
											/*[in]*/WSTRING str, 
											/*[in]*/ULONG resource_no, 
											/*[in]*/ULONG connection_no )
{
// 	// ObjectLock lock(this);
// 	msg_pool* ptr = msg_pool::get_instance();
// 	std::wstring format_str = ptr->get_msg_from_id( msg_id );
// 	std::wstring num_str( utility::long2str(num, std::wstring()) );
// 	std::wstring::size_type pos = format_str.find( L"$1" );
// 	if( pos != std::wstring::npos )
// 	{
// 		format_str.replace( pos, 2, num_str );
// 	}
// 	pos = format_str.find( L"$2" );
// 	if( pos == std::wstring::npos )
// 	{
// 		PushInfo1W( ICI_ERROR_MSG, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
// 	else
// 	{
// 		format_str.replace( pos, 2, str.str, str.len );
// 		PushInfo1W( msg_type, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
	connect_info_item2 item;
	item.resource_no = resource_no;
	item.connection_no = connection_no;
	item.msg_type = msg_type;
	item.msg_id = msg_id;
	item.param_type = E_CONNECT_INFO_LONG_STRING;
	item.param.resize(8  + str.len * sizeof(WCHAR));
	char* buffer = &item.param[0];
	memcpy(buffer, &num, 4), buffer += 4;
	memcpy(buffer, &str.len, 4), buffer += 4;
	memcpy(buffer, str.str, str.len * sizeof(WCHAR));
	push_back2(item);
	return S_OK;
}

STDMETHODIMP CConnectInfo::PushFormatInfo7W(/*[in]*/ICONNECTINFO_MSGTYPE msg_type, 
											/*[in]*/ULONG msg_id, 
											/*[in]*/WSTRING str, 
											/*[in]*/ULONG num, 
											/*[in]*/ULONG resource_no, 
											/*[in]*/ULONG connection_no )
{
// 	// ObjectLock lock(this);
// 	msg_pool* ptr = msg_pool::get_instance();
// 	std::wstring format_str = ptr->get_msg_from_id( msg_id );
// 	std::wstring num_str( utility::long2str(num, std::wstring()) );
// 	std::wstring::size_type pos = format_str.find( L"$1" );
// 	if( pos != std::wstring::npos )
// 	{
// 		format_str.replace( pos, 2, str.str, str.len );
// 	}
// 	pos = format_str.find( L"$2" );
// 	if( pos == std::wstring::npos )
// 	{
// 		PushInfo1W( ICI_ERROR_MSG, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
// 	else
// 	{
// 		format_str.replace( pos, 2, num_str );
// 		PushInfo1W( msg_type, WSTRING_EX(format_str), resource_no, connection_no );
// 	}
	connect_info_item2 item;
	item.resource_no = resource_no;
	item.connection_no = connection_no;
	item.msg_type = msg_type;
	item.msg_id = msg_id;
	item.param_type = E_CONNECT_INFO_STRING_LONG;
	item.param.resize(8  + str.len * sizeof(WCHAR));
	char* buffer = &item.param[0];
	memcpy(buffer, &str.len, 4), buffer += 4;
	memcpy(buffer, str.str, str.len * sizeof(WCHAR)), buffer += str.len * sizeof(WCHAR); 
	memcpy(buffer, &num, 4), buffer += 4;
	push_back2(item);

	return S_OK;
}
STDMETHODIMP CConnectInfo::GetNewConnectInfoW( /*[in]*/BUFFER_PTR buffer, /*[in]*/BUFFER_SIZE bufLen, /*[out]*/ULONG *pResultSize, LONG *pResult )
{
	get_new_conncet_info2(buffer, bufLen, pResultSize, pResult);
	return S_OK;
}

void CConnectInfo::get_new_conncet_info2( /*[in]*/BUFFER_PTR buffer, /*[in]*/BUFFER_SIZE bufLen, /*[out]*/ULONG *pResultSize, LONG *pResult )
{
	unsigned sum_length = 4;
	unsigned msg_num=0;
	connect_info_item2 one_item;
	bool has_info = fetch_one_item2( one_item );
	while( has_info )
	{
		size_t length = one_item.param.length();
		if( (sum_length + length + 20) > bufLen )
		{
			push_front2( one_item );
			break;
		}
		std::cout << " fetch_one_item2 this item's length: " << (sum_length + length + 20) << "\n";

		::memcpy( (char*)buffer+sum_length, &(one_item.resource_no), 4 ), sum_length += 4;
		::memcpy( (char*)buffer+sum_length, &(one_item.connection_no), 4 ), sum_length += 4;
		::memcpy( (char*)buffer+sum_length, &(one_item.msg_type), 4 ), sum_length += 4;
		::memcpy( (char*)buffer+sum_length, &(one_item.msg_id), 4 ), sum_length += 4;
		::memcpy( (char*)buffer+sum_length, &(one_item.param_type), 4 ), sum_length += 4;

		::memcpy( (char*)buffer+sum_length, &length, 4 ), sum_length += 4;
		::memcpy( (char*)buffer+sum_length, one_item.param.c_str(), length ) ,sum_length += length;
		++msg_num;
		has_info = fetch_one_item2( one_item );
	}
	int ret;
	if( msg_num == 0 )
	{
		if( has_info )
			ret =  1;
		else
		{
			::memcpy( buffer, &msg_num,4 );
			*pResultSize = 4;
			ret = 0;
		}
	}
	else
	{
		::memcpy( buffer, &msg_num,4 );
		*pResultSize = sum_length;
		if( has_info )
			ret = 2;
		else
			ret = 0;
	}
	*pResult = ret;
}

bool CConnectInfo::fetch_one_item2( connect_info_item2& result )
{

	if (!_items2.empty())
	{
		result = _items2.front();
		_items2.pop_front();
		return true;
	}
	else
		return false;

}

void CConnectInfo::push_front2( connect_info_item2& item )
{
	_items2.push_front(item);
}

void CConnectInfo::push_back2( connect_info_item2& item )
{
	_items2.push_back(item);
}

void CConnectInfo::push_back2( int resource_no, int connection_no, ICONNECTINFO_MSGTYPE msg_type, e_connect_info param_type,
							  const std::string& param )
{
	_items2.push_back( connect_info_item2() );
	connect_info_item2& back = _items2.back();
	back.resource_no = resource_no;
	back.connection_no = connection_no;
	back.msg_type = (int)msg_type;
	back.param_type = param_type;	
	back.param = param;
}


STDMETHODIMP CConnectInfo::LoadConnectInfoW( /*[in]*/BUFFER_PTR buffer, /*[in]*/BUFFER_SIZE bufLen, /*[out]*/LONG *pResult)
{
	load_connect_info2(buffer, bufLen, pResult);
	return S_OK;
}

STDMETHODIMP CConnectInfo::ConnectInfoCount( /*[out]*/ULONG *pResult )
{
	*pResult = _items2.size();
	return S_OK;
}

void CConnectInfo::load_connect_info2( /*[in]*/BUFFER_PTR buffer, /*[in]*/BUFFER_SIZE bufLen, /*[out]*/LONG *pResult )
{
	if (bufLen < 4)
		return;

	_items2.clear();
	BUFFER_PTR read_buf = buffer;
	size_t item_count = 0;
	memcpy(&item_count, read_buf, 4), read_buf += 4;
	_items2.resize(item_count);
	//std::cout << " item_count:" << item_count << "\n";
	size_t item_i = 0;
	for (; item_i < _items2.size(); ++item_i)
	{
		if ((read_buf + 20) > buffer + bufLen)
			break;

		connect_info_item2& one_item = _items2[item_i];
		::memcpy(&(one_item.resource_no), read_buf, 4 ), read_buf += 4;
		::memcpy(&(one_item.connection_no), read_buf, 4 ), read_buf += 4;
		::memcpy(&(one_item.msg_type), read_buf, 4 ), read_buf += 4;
		::memcpy(&(one_item.msg_id), read_buf, 4 ), read_buf += 4;
		::memcpy(&(one_item.param_type), read_buf, 4 ), read_buf += 4;
// 		std::cout << " msg_id:" << one_item.msg_id << "\n";
// 		std::cout << " param_type:" << one_item.param_type << "\n";
		read_buf += read_info_param(read_buf, one_item.param_type, one_item.param);
// 		switch(one_item.param_type)
// 		{
// 		case E_CONNECT_INFO_NULL:
// 			break;
// 		case E_CONNECT_INFO_LONG:
// 			one_item.param.resize(4);
// 			memcpy(&one_item.param[0], read_buf, 4), read_buf += 4;
// 			break;
// 		case E_CONNECT_INFO_LONGLONG:
// 			one_item.param.resize(8);
// 			memcpy(&one_item.param[0], read_buf, 8), read_buf += 8;
// 			break;
// 		case E_CONNECT_INFO_LONG_LONG:
// 			one_item.param.resize(8);
// 			memcpy(&one_item.param[0], read_buf, 8), read_buf += 8;
// 			break;
// 		case E_CONNECT_INFO_STRING:
// 			{
// 				size_t str_size = 0;
// 				memcpy(&str_size, read_buf, 4);
// 				one_item.param.resize(str_size * sizeof(WCHAR) + 4);
// 				memcpy(&one_item.param[0], read_buf, one_item.param.size()), read_buf += one_item.param.size();
// 			}
// 			break;
// 		case E_CONNECT_INFO_STRING_STRING:
// 			{
// 				size_t str_size = 0;
// 				memcpy(&str_size, read_buf, 4);
// 				std::string param1;
// 				param1.resize(str_size * sizeof(WCHAR) + 4);
// 				memcpy(&param1[0], read_buf, param1.size()), read_buf += param1.size();
// 				str_size = 0;
// 				memcpy(&str_size, read_buf, 4);
// 				std::string param2;
// 				param2.resize(str_size * sizeof(WCHAR) + 4);
// 				memcpy(&param2[0], read_buf, param2.size()), read_buf += param2.size();
// 				one_item.param = param1 + param2;
// 			}
// 			break;
// 		case E_CONNECT_INFO_STRING_LONG:
// 			{
// 				size_t str_size = 0;
// 				memcpy(&str_size, read_buf, 4);
// 				one_item.param.resize(str_size * sizeof(WCHAR) + 8);
// 				memcpy(&one_item.param[0], read_buf, one_item.param.size()), read_buf += one_item.param.size();
// 			}
// 			break;
// 		case E_CONNECT_INFO_LONG_STRING:
// 			{
// 				size_t str_size = 0;
// 				memcpy(&str_size, read_buf+4, 4);
// 				one_item.param.resize(str_size * sizeof(WCHAR) + 8);
// 				memcpy(&one_item.param[0], read_buf, one_item.param.size()), read_buf += one_item.param.size();
// 			}
// 			break;
// 		default:
// 			assert(!"Unkown enum type.");
// 		}
 	}
	_items2.resize(item_i);
}

unsigned CConnectInfo::read_info_param( BUFFER_PTR buffer, e_connect_info param_type, std::string& param)
{
	BUFFER_PTR read_buf = buffer;
	unsigned param_len = 0;
	memcpy(&param_len, read_buf, 4), read_buf += 4;
	std::cout << " param_len:" << param_len << "\n";
	switch(param_type)
	{
	case E_CONNECT_INFO_NULL:
		break;
	case E_CONNECT_INFO_LONG:
		param.resize(4);
		memcpy(&param[0], read_buf, 4), read_buf += 4;
		break;
	case E_CONNECT_INFO_LONGLONG:
		param.resize(8);
		memcpy(&param[0], read_buf, 8), read_buf += 8;
		break;
	case E_CONNECT_INFO_LONG_LONG:
		param.resize(8);
		memcpy(&param[0], read_buf, 8), read_buf += 8;
		break;
	case E_CONNECT_INFO_STRING:
		{
			size_t str_size = 0;
			memcpy(&str_size, read_buf, 4);
			param.resize(str_size * sizeof(WCHAR) + 4);
			memcpy(&param[0], read_buf, param.size()), read_buf += param.size();
		}
		break;
	case E_CONNECT_INFO_STRING_STRING:
		{
			size_t str_size = 0;
			memcpy(&str_size, read_buf, 4);
			std::string param1;
			param1.resize(str_size * sizeof(WCHAR) + 4);
			memcpy(&param1[0], read_buf, param1.size()), read_buf += param1.size();
			str_size = 0;
			memcpy(&str_size, read_buf, 4);
			std::string param2;
			param2.resize(str_size * sizeof(WCHAR) + 4);
			memcpy(&param2[0], read_buf, param2.size()), read_buf += param2.size();
			param = param1 + param2;
		}
		break;
	case E_CONNECT_INFO_STRING_LONG:
		{
			size_t str_size = 0;
			memcpy(&str_size, read_buf, 4);
			param.resize(str_size * sizeof(WCHAR) + 8);
			memcpy(&param[0], read_buf, param.size()), read_buf += param.size();
		}
		break;
	case E_CONNECT_INFO_LONG_STRING:
		{
			size_t str_size = 0;
			memcpy(&str_size, read_buf+4, 4);
			param.resize(str_size * sizeof(WCHAR) + 8);
			memcpy(&param[0], read_buf, param.size()), read_buf += param.size();
		}
		break;
	default:
		assert(!"Unkown enum type.");
	}
	assert (param_len == param.size());
	return (read_buf - buffer);
}

int test_CConnectInfo()
{
	CConnectInfo connect_info;
	WSTRING MSG[] = { {5, L"55555"}, {6, L"666666"}};
	connect_info.PushInfo1W(ICI_NOTIFY_MSG, MSG[0], 0, 0 );
	connect_info.PushInfo2W(ICI_NOTIFY_MSG, 1, 0, 0);
	connect_info.PushFormatInfo1W(ICI_NOTIFY_MSG, 2, static_cast<ULONG>(-1), 0, 0);
	connect_info.PushFormatInfo2W(ICI_NOTIFY_MSG, 3, static_cast<ULONGLONG>(-1), 0, 0);
	connect_info.PushFormatInfo3W(ICI_NOTIFY_MSG, 4, static_cast<ULONG>(-1), static_cast<ULONG>(-1), 0, 0);
	connect_info.PushFormatInfo4W(ICI_NOTIFY_MSG, 5, MSG[0], 0, 0);
	connect_info.PushFormatInfo5W(ICI_NOTIFY_MSG, 6, MSG[0], MSG[1], 0, 0);
	connect_info.PushFormatInfo6W(ICI_NOTIFY_MSG, 7, static_cast<ULONG>(-1), MSG[0], 0, 0);
	connect_info.PushFormatInfo7W(ICI_NOTIFY_MSG, 8, MSG[0], static_cast<ULONG>(-1), 0, 0);

	const unsigned MAX_BUFFER_SIZE = 1024 * 64;
	char buffer[MAX_BUFFER_SIZE];
	ULONG result_size = 0;
	LONG result = 0;
	connect_info.GetNewConnectInfoW((BUFFER_PTR)buffer, MAX_BUFFER_SIZE, &result_size, &result );
	std::cout << " ** result_size:" << result_size << " result:" << result << "\n";

	result_size = 0, result = 0;
	CConnectInfo info_bak;
	info_bak.LoadConnectInfoW((BUFFER_PTR)buffer, MAX_BUFFER_SIZE, &result);
	ULONG info_count = 0;
	info_bak.ConnectInfoCount(&info_count);
	std::cout << " info_count:" << info_count << "\n";
	std::cout << " ** result_size:" << result_size << " result:" << result << "\n";
	for (size_t i = 0; i < info_count; ++i )
	{
		connect_info_item2& item = info_bak[i];
		std::cout << " msg_id:" << item.msg_id << "\n";
		std::cout << " param_type:" << item.param_type << "\n";
		std::cout << " param:" << item.param << "\n";
	}

	return 0;
}