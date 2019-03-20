// CP210xSerialTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, TCHAR *argv[], TCHAR *envp[])
{
    HANDLE hMaster, hSlave;
	bool transferSuccess = true;

    _tprintf(_T("CP210x BBasic Serial Communication Test\n\n"));

	TCHAR masterPort, slavePort;

	_tprintf(_T("Enter Master COM Port (1-9): "));
	_tscanf(_T("%d"), &masterPort);

	_tprintf(_T("Enter Slave COM Port (1-9) [for loopback use the same COM port as the Master]: "));
	_tscanf(_T("%d"), &slavePort);

	TCHAR masterString[6], slaveString[6];

	memset(masterString, 0, 6);
	memset(slaveString, 0, 6);

	_tcscpy(masterString, _T("COM0:"));
	masterString[3] = masterPort + 0x30;
	
	_tcscpy(slaveString, _T("COM0:"));
	slaveString[3] = slavePort + 0x30;

	hMaster	= CreateFile(masterString, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

	if (masterPort == slavePort)
	{
		hSlave = hMaster;
	}
	else
	{
		hSlave	= CreateFile(slaveString, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);
	}

	if (hMaster != INVALID_HANDLE_VALUE)
	{
		if (hSlave != INVALID_HANDLE_VALUE)
		{
			if (PurgeComm(hMaster, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR))
			{
				if (PurgeComm(hSlave, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR))
				{
					DCB dcbMasterInitState, dcbSlaveInitState;

					if (GetCommState(hMaster, &dcbMasterInitState))
					{
						if (GetCommState(hSlave, &dcbSlaveInitState))
						{
							DCB dcbMaster = dcbMasterInitState;
							DCB dcbSlave = dcbSlaveInitState;

							dcbMaster.BaudRate= 57600;
							dcbMaster.Parity= NOPARITY;
							dcbMaster.ByteSize= 8;
							dcbMaster.StopBits= ONESTOPBIT;

							dcbSlave.BaudRate= 57600;
							dcbSlave.Parity= NOPARITY;
							dcbSlave.ByteSize= 8;
							dcbSlave.StopBits= ONESTOPBIT;

							COMMTIMEOUTS ctM, ctS;

							GetCommTimeouts(hMaster, &ctM);
							GetCommTimeouts(hSlave, &ctS);

							ctM.ReadTotalTimeoutConstant = 10000;
							ctS.ReadTotalTimeoutConstant = 10000;

							SetCommTimeouts(hMaster, &ctM);
							SetCommTimeouts(hSlave, &ctS);

							if (SetCommState(hMaster, &dcbMaster))
							{
								Sleep(60);

								if (SetCommState(hSlave, &dcbSlave))
								{
									Sleep(60);

									DWORD bytesWritten = 0, bytesRead = 0;

									BYTE sampleMasterData[64];
									BYTE sampleSlaveData[64];

									for (int i = 0; i < 64; i++)
									{
										sampleMasterData[i] = i;
										sampleSlaveData[i] = 0;
									}

									if (WriteFile(hMaster, sampleMasterData, 64, &bytesWritten, NULL))
									{
										if (ReadFile(hSlave, sampleSlaveData, 64, &bytesRead, NULL))
										{
											transferSuccess = true;

											for (int i = 0; i < 64; i++)
												if (sampleMasterData[i] != sampleSlaveData[i]) transferSuccess = false;

											if (transferSuccess)
											{
												for (int i = 0; i < 64; i++)
												{
													sampleMasterData[i] = 0;
													sampleSlaveData[i] = i;
												}

												if (WriteFile(hMaster, sampleMasterData, 64, &bytesWritten, NULL))
												{
													if (ReadFile(hSlave, sampleSlaveData, 64, &bytesRead, NULL))
													{
														transferSuccess = true;

														for (int i = 0; i < 64; i++)
															if (sampleMasterData[i] != sampleSlaveData[i]) transferSuccess = false;

														if (transferSuccess)
															_tprintf(_T("Test Successful!"));
														else
															_tprintf(_T("Error in data on Slave to Master transfer"));
													}
													else
														_tprintf(_T("Error reading data from Master COM port"));
												}
												else
													_tprintf(_T("Error writing data to Slave COM port"));
											}
											else
												_tprintf(_T("Error in data on Master to Slave transfer"));
										}
										else
											_tprintf(_T("Error reading data from Slave COM port"));
									}
									else
										_tprintf(_T("Error writing data to Master COM port"));

									SetCommState(hSlave, &dcbSlaveInitState);
								}
								else
									_tprintf(_T("Error setting Slave COM port state"));
							
								SetCommState(hMaster, &dcbMasterInitState);
							}
							else
								_tprintf(_T("Error setting Master COM port state"));
						}
						else
							_tprintf(_T("Error getting Slave COM port state"));
					}
					else
						_tprintf(_T("Error getting Master COM port state"));
				}
				else
					_tprintf(_T("Error purging Slave COM port"));
			}
			else
				_tprintf(_T("Error purging Master COM port"));
			
			CloseHandle(hSlave);
			hSlave = INVALID_HANDLE_VALUE;
		}
		else
			_tprintf(_T("Error opening Slave COM port"));

		CloseHandle(hMaster);
		hMaster = INVALID_HANDLE_VALUE;
	}
	else
		_tprintf(_T("Error opening Master COM port"));

	Sleep(4000);

    return 0;
}

