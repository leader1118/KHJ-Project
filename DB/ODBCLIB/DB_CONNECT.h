#pragma once
#include "ODBCSTD.h"
class DB_CONNECT
{
public:
	SQLHENV		m_hENV; // ȯ���ڵ�
	SQLHDBC		m_hDBC;	// �����ڵ�
	SQLHSTMT	m_hSTMT; // ����ڵ�
public:
	void		DBConnect(); // ���� �� ����
	void		DBDisConnect(); // ����
public:
	DB_CONNECT();
	virtual ~DB_CONNECT();
};


