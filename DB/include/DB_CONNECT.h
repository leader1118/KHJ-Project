#pragma once
#include "ODBCSTD.h"
class DB_CONNECT
{
public:
	SQLHENV		m_hENV; // 환경핸들
	SQLHDBC		m_hDBC;	// 연결핸들
	SQLHSTMT	m_hSTMT; // 명령핸들
public:
	void		DBConnect(); // 접속 및 버전
	void		DBDisConnect(); // 해제
public:
	DB_CONNECT();
	virtual ~DB_CONNECT();
};


