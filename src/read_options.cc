#include "read_options.h"

#ifdef READ_OPTIONS_H_

#include <glog/logging.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

ReadOptions::ReadOptions(const char *fileName)
{
	// if(!google::IsGoogleLoggingInitialized())
		// google::InitGoogleLogging("./log");
	m_pFile = NULL;
	m_pFileName = NULL;
	m_pString = NULL;
	m_pOption = NULL;
	m_pVal = NULL;
	m_Length = 256;
	m_Line = 0;
	m_SepIndex = 0;
	m_bPermitted = false;
	
	FILE *pFile = fopen(fileName, "rb");
	m_pFile = (void*)pFile;
	m_pFileName = const_cast<char*>(fileName);
	if(NULL == m_pFile)
	{
		m_bPermitted = false;
		return;
	}
	else
		m_bPermitted = true;
	
	m_pString = new char[m_Length];
	m_pOption = new char[m_Length];
	m_pVal = new char[m_Length];
	if((NULL == m_pString || NULL == m_pOption) || (NULL == m_pVal))
	{
		LOG(ERROR) << "Error: no enough memory to allocate for params\n";
		m_bPermitted = false;
		return;
	}
	else
		m_bPermitted = true;
	
	memset(m_pString, 0, m_Length*sizeof(char));
	memset(m_pOption, 0, m_Length*sizeof(char));
	memset(m_pVal, 0, m_Length*sizeof(char));
	
}

ReadOptions::~ReadOptions(void)
{
	if(m_bPermitted)
		fclose((FILE*)m_pFile);
	if(NULL != m_pString)
	{
		delete m_pString;
		m_pString = NULL;
	}
	if(NULL != m_pOption)
	{
		delete m_pOption;
		m_pOption = NULL;
	}
	if(NULL != m_pVal)
	{
		delete m_pVal;
		m_pVal = NULL;
	}
	// google::ShutdownGoogleLogging();
}

bool ReadOptions::readPermitted(void)
{
	if(!m_bPermitted)
		LOG(ERROR) << "Error: open file <" << m_pFileName << "> failed, permission denied or file not exsits\n";
	return m_bPermitted;
}

char *ReadOptions::read(const char *option)
{
	FILE *pFile = fopen(m_pFileName, "rb");
	if(NULL == m_pFile)
	{
		m_bPermitted = false;
		return m_pVal;
	}
	
	while(!feof(pFile))
	{
	NEXT_LINE:
		// get a line
		fgets(m_pString, m_Length-1, pFile);
		// LOG(INFO) << "str-> " << str;
		// LOG(INFO) << ++m_Line;
		for(int i=0;i<strlen(m_pString);++i)
		{
			// skip if space in the front so that get option
			if(m_pString[i] == ' ')
				continue;
			memset(m_pOption, 0, m_Length*sizeof(char));
			memcpy(m_pOption, &m_pString[i], strlen(option)*sizeof(char));
			// LOG(INFO) << "m_pOption-> " << m_pOption;
			if(strcmp(m_pOption, option))
			{
				// LOG(INFO) << "Not match";
				goto NEXT_LINE;
			}
			// skip if space in the front so that get value
			m_SepIndex = i+1+strlen(option);
			for(i=m_SepIndex;i<strlen(m_pString);++i)
			{
				if(m_pString[i] == ' ' || m_pString[i] == '=')
					continue;
				memset(m_pVal, 0, m_Length*sizeof(char));
				memcpy(m_pVal, &m_pString[i], m_Length);
				// LOG(INFO) << "m_pVal-> " << m_pVal;
				goto END_OF_FILE;
			}
		}
		
		// LOG(INFO) << "m_pOption: " << m_pOption << ",  m_pVal: " << m_pVal;
		goto END_OF_FILE;;
	}
END_OF_FILE:
	fclose(pFile);
	return m_pVal;
}

bool *ReadOptions::getNext(void)
{

}

char *ReadOptions::readOption(void)
{

}

char *ReadOptions::readVal(void)
{
	
}

#endif // READ_OPTIONS_H_