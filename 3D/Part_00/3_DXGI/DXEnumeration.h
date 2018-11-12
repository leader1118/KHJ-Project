#pragma once
#include "DXDefine.h"

class DEnumOutput
{
public:
	~DEnumOutput();
	void			Set(UINT iIndex, IDXGIOutput* pAdapter);
	UINT			m_Output;
	IDXGIOutput*	m_pOutput;
	DXGI_OUTPUT_DESC m_Desc;
	vector<DXGI_MODE_DESC> m_DisplayModeList;
};

class DEnumDevice
{
public:
public:
	~DEnumDevice();
	UINT					m_AdapterOrdinal;
	vector<DEnumOutput*>	m_OutputInfoList;
	D3D_DRIVER_TYPE			DeviceType;
};
class DEnumAdapter
{
public:
	~DEnumAdapter();
	void				Set(UINT iIndex, IDXGIAdapter* pAdapter);
	UINT				m_AdapterOrdinal;
	DXGI_ADAPTER_DESC	m_AdapterDesc;
	IDXGIAdapter*		m_pAdapter;
	vector<DEnumOutput*> m_OutputInfoList;
	vector<DEnumOutput*> m_DeviceInfoList;
};
class DXEnumeration
{
public:
	vector<DEnumAdapter*> m_AdapterInfoList;
public:
	HRESULT Enumerate(IDXGIFactory* pFactory);
	HRESULT EnumerateDevices(DEnumAdapter* pAdapterInfo);
	HRESULT EnumerateDisplayModes(DEnumOutput);
	HRESULT EnumerateOutputs(DEnumAdapter* pAdaperInfo);
	void	ClearAdapterInfoList();
public:
	DXEnumeration(void);
	virtual ~DXEnumeration(void);
};

