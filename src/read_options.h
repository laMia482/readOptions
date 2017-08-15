#ifndef READ_OPTIONS_H_
#define READ_OPTIONS_H_

class ReadOptions
{
public:
	ReadOptions(const char *);
	~ReadOptions(void);
	bool readPermitted(void);
	char *read(const char *);
	char *getNext(void);
	char *readOption(void);
	char *readVal(void);
	
private:
	void *m_pFile;
	char *m_pFileName;
	char *m_pOption;
	char *m_pVal;
	int m_Lenth;
	int m_Line;
	bool m_bPermitted;
};

#endif // READ_OPTIONS_H_