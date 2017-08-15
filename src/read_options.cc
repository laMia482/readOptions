#include "read_options.h"

#ifdef READ_OPTIONS_H_

#include <glog/logging.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

ReadOptions::ReadOptions(const char *fileName)
{
	::google::InitGoogleLogging("/dev/nell");
	m_pFile = NULL;
	m_pFileName = NULL;
	m_pOption = NULL;
	m_pVal = NULL;
	m_Lenth = 256;
	m_bPermitted = false;
	
	FILE *pFile = (FILE*)m_pFile;
	pFile = fopen(fileName, "rb");
	m_pFileName = const_cast<char*>(fileName);
	if(NULL == m_pFile)
	{
		m_bPermitted = false;
		return;
	}
	else
		m_bPermitted = true;
	
	m_pOption = new char[m_Lenth];
	m_pVal = new char[m_Lenth];
	if((NULL == m_pOption) || (NULL == m_pVal))
	{
		LOG(ERROR) << "Error: no enough memory to allocate for params\n";
		m_bPermitted = false;
		return;
	}
	else
		m_bPermitted = true;
	
	memset(m_pOption, 0, m_Lenth*sizeof(char));
	memset(m_pVal, 0, m_Lenth*sizeof(char));
	
}

ReadOptions::~ReadOptions(void)
{
	if(m_bPermitted)
		fclose((FILE*)m_pFile);
	if(NULL == m_pOption)
		delete m_pOption;
	if(NULL == m_pVal)
		delete m_pVal;
}

bool ReadOptions::readPermitted(void)
{
	if(!m_bPermitted)
		LOG(ERROR) << "Error: open file <" << m_pFileName << "> failed, permission denied or file not exsits\n";
	return m_bPermitted;
}

char *ReadOptions::read(const char *option)
{
	
}

char *ReadOptions::getNext(void)
{
	
}

char *ReadOptions::readOption(void)
{
	
}

char *ReadOptions::readVal(void)
{
	
}

#endif // READ_OPTIONS_H_