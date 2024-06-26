#ifndef SEGY_H_INCLUDED
#define SEGY_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cstring>
#include <string.h>

#include <vector>

#include "util.h"
#include "caches/caches.h"
#include "map_file.h"

const int TEXTUAL_HEADER_SIZE = 3200;
const int VOLUME_HEADER_SIZE = 400;

const int TRACE_HEADER_SIZE = 240;

using namespace std;

struct POINTF
{
    double x;
    double y;
};


//SEGY rev1,IEEE FLOATING POINT，400
struct VOLUMEHEADER
{
    int jobid;	/* 3201-3204        */
    int lino;	 	//*3205-3208
    int reno;		//*209-3212
    short ntrpr;	//* 3213-3214
    short nart;		//*3215-3216
    unsigned short hdt; 	//*3217-3218
    unsigned short dto; /* 3219-3220  */
    unsigned short hns; //*3221-3222
    unsigned short nso; /* */
    short format;//*1=4 IBM； 2=4； 3=2； 4=4）
    //	5=4IEEE
    //	6=
    //	7=
    //	8=1
    short fold;		//*CDP3227-3228
    short tsort;

    short vscode;	//3231-3232
    short hsfs;	/* 3233-3234	*/
    short hsfe;	/* 3235-3236    */
    short hslen;	/* 3237-3238*/
    short hstyp; //3239-3240
    short schn;	/* 3241-3242	*/
    short hstas; //3243-3244
    short hstae; //3245-3246
    short htatyp; //3247-3248
    short hcorr; //3249-3250
    short bgrcv; //3251-3252
    short rcvm;	 //3253-3254
    short mfeet; // 3255-3256
    short polyt; //3257-3258
    short vpol;	//3259-3260
    short hunass1[120];	/* 3261-3500 unassigned */
    short rev; //3501-3502 SEGY， SEGY Rev12002
    short hunass2[49];	/* 3261-3500 unassigned */



};


//SEGY rev1,IEEE FLOATING POINT，240
struct TRACEHEADER
{
    int iSLNum;	//1-4
    int iTSTNum; //5-8
    int iOriNum;		// 9-12 **
    int iTraNum;  //13-16
    int iSorceNum;	 //17-20
    int iCdpNum;	/* 21-24	*/
    int iCdpTra;    //25-28	CDP
    short nTraId;	   //29-30

    short nVsTra;	   // 31-32
    short nHsTra;	  //33-34
    short nDuse;	  //35-36
    int iOffset;  //37-40
    int gelev; //41-44
    int selev;	//45-48
    int sdepth;	/* 49-52	 */
    int gdel;	/* 53-56	*/
    int sdel;	/* 57-60   */
    int swdep;	/* 61-64	*/
    int gwdep;	/* 65-68	*/
    short scalel;//69-70
    short scalco;//1-72
    int  iSourseX;	/* 73-76	*/
    int  iSourseY;	/* 77-80	 */
    int  iGroupX;	/* 81-81	*/
    int  iGroupY;	/* 85-88	*/
    short counit; //89-90
    short wevel;	/* 91-92	*/
    short swevel;	/* 93-94	*/
    short sut;	/* 95-96	*/
    short gut;	/*97-98	*/
    short sstat;	/* 99-100	*/
    short gstat;	/* 101-102	*/
    short tstat; //103-104
    short laga; //105-106
    short lagb;	//107-108
    short delrt; //109-110
    short muts;	/* 111-112	*/
    short mute;	/* 113-114	*/
    unsigned short uNs; //**
    unsigned short uRate;//**
    short gain;	/* 119-120	*/
    short igc;	/* 121-122	*/
    short igi;	/* 123-124	*/
    short corr;	/* 125-126	*/
    short sfs;	/* 127-128	*/
    short sfe;	/* 129-130	*/
    short slen;	/* 131-132	*/
    short styp;	/* 133-134	*/
    short stas;	/* 135-136	*/
    short stae;	/* 137-138	 */
    short tatyp;	/* 139-140	 */
    short afilf;	/* 141-142	 */
    short afils;	/* 143-144	 */
    short nofilf;	/* 145-146	 */
    short nofils;	/* 147-148 */
    short lcf;	/*149-150	*/
    short hcf;	/* 151-152	 */
    short lcs;	/* 153-154	*/
    short hcs;	/* 155-156	*/
    short year;	//157-158
    short day;	//159-160
    short hour;	//161-162
    short minute;	// 163-164
    short sec;	// 165-166
    short timbas;	/*167-168*/
    short trwf;	/* 169-170*/
    short grnors;	/* 171-172	*/
    short grnofr;	/* 173-174	*/
    short grnlof;	/* 175-176	*/
    short gaps;	/* 177-178	 */
    short otrav; //179-180
    int cdpX; //181-184
    int cdpY;//185-188
    int Inline3D;//189-192
    int CrossLine3D;//193-196
    int ShotPoint;//197-200
    short ShotPointScalar;//201-202 ，197-200
    short TraceValueMeasurementUnit;
    /*
     203-204
     -1 = （DataSampleMeasurementUnits Stanza）
     0 = default
     1 = Pascal(Pa)
     2 = Volts(V)
     3 = Millivolts(mV)
     4 = Amperes(A)
     5 = Meters(m)
     6 = Meters per second(m/s)
     7 = Meters per second squared(m/s2)
     8 = Newton(N)
     9 = Watt(W)
     */

    int TransductionConstantMantissa; //205-208
    short TransductionConstantPower;//209-210
    short TransductionUnit; //211-212
    /*
     -1 = （DataSampleMeasurementUnits Stanza）
     0 = default
     1 = Pascal(Pa)
     2 = Volts(V)
     3 = Millivolts(mV)
     4 = Amperes(A)
     5 = Meters(m)
     6 = Meters per second(m/s)
     7 = Meters per second squared(m/s2)
     8 = Newton(N)
     9 = Watt(W)
     */
    short TraceIdentifier;//213-214
    short ScalarTraceHeader; //215-216
    short SourceType;//217-218

    int SourceEnergyDirectionMantissa;//219-222
    short SourceEnergyDirectionExponent;//223-225
    int SourceMeasurementMantissa;//225-228
    short SourceMeasurementExponent;//229-230
    short SourceMeasurementUnit; //2031-232
    /*
     -1 = （ataSampleMeasurementUnits Stanza）
     0 =
     1 = Joule(J)
     2 = Kilowatt(kW)
     3 = Pascal(Pa)
     4 = Bar(Bar)
     4 = Bar-meter(Bar-m)
     5 = Newton(N)
     6 = Kilograms(kg)
     */

    int UnassignedInt1;
    int UnassignedInt2;
};





class CSegyRead
{

public:
    CSegyRead();
    ~CSegyRead();
    CSegyRead(char * csSgyParth);

    bool m_bHasTextualHeader;
        bool m_bIsEDBCode;
        bool m_bIsBigEndian;

        enum DataFormat
        {
            IBMFLOAT,
            IEEEFLOAT,
            IEEEINT32,
            IEEEINT16,
            IEEEINT8
        };

        void SwapVolumeHead(VOLUMEHEADER &);
        void SwapTraceHead(TRACEHEADER &);

        bool OpenFile(const char *, bool);


        const unsigned char *ReadTextualHeader();  //3200 bytes
        const VOLUMEHEADER &ReadVolumeHeader(); //400 bytes
        const TRACEHEADER &ReadTraceHeader(int nIndex);  //240 bytes
        float * ReadTraceData(int nIndex);

        float * GetTraceData(){return m_pData;}


        const unsigned char* GetEbcdic() const { return m_szTextInfo;}
        void SetHasTextualHeader() { m_bHasTextualHeader =false;}
        VOLUMEHEADER GetVolumeHeader(){ return m_volHead;}
        TRACEHEADER GetTraceHeader() { return m_traHead;}
        float* GetTraceData(int nIndex );

        const char* GetTraceHeadAsBytes() { return m_szTraceHead;}

        //short getTraId() const;
        int getSamplesNumber() const;
        int getSamplesInterval() const;
        short getFormat() const;
        int getTotalTraceNumber() const;
        int getSegyRev() const; //SEGY rev1 or rev0

        float GetSampleValue(int idx);
        //float GetTrace(long long n);


        void closeFile();
        void SetNewTextualHeader ();
        void WriteSegy(const char *csReadFile, const char *csWriteFile);



        //char m_csFilepath[300];
    public:
        char *m_szNewHeader;
        CacheDirecta cache;



    private:

        char * csReadFile;
        DataFormat m_fmt;
        TRACEHEADER m_traHead;
        VOLUMEHEADER m_volHead;
        unsigned long long m_lFileLenth;

        unsigned  m_nTraNumPerInLine;
        int m_nTraceTolNum;
        int m_nInLineNum;
        int m_nXLineNum;
        //int m_nCurrentTraceNum;
        int m_nSmpNum;

        long lStartPosition;

        unsigned char m_szTextInfo[TEXTUAL_HEADER_SIZE]; //3200 bytes en EBCDIC
        char m_szVolumeHead[VOLUME_HEADER_SIZE];//400
        char m_szTraceHead[TRACE_HEADER_SIZE]; //240

        short m_nFormatCode;
        short m_nSegyRev;//SEGY

        int m_nSampleInterval;
        int m_nSampleNum;
        int m_nDataLenth;
        int m_nStrtInLine;
        int m_nStopInLine;
        int m_nStrtXLine;
        int m_nStopXline;
        int m_nStrtTime;
        int m_nStopTime;
        int m_nScaleoSet;

        int m_nXCoordLenth;
        int m_nYCoordLenth;
        int m_nXCoordSet;
        int m_nYCoordSet;
        int m_nInlineSet;
        int m_nXlineSet;
        int m_nInlineLenth;
        int m_nXLineLenth;
        int m_nTotalTraceNum;


        float m_fXInterval;
        float m_fYInterval;
        float m_fTraceInterval;
        float m_fLineInterval;

        bool bDataOrdination;
        bool m_bDataWS;
        bool m_bDataIBMFmt;
        bool m_bCoordUserSet;
        bool m_bLineSet;
        bool m_bCoordSet;
        bool segyRegular;
        bool m_bEBText;
        bool m_bOpen;


        short m_nTraId;

        float smp;
        float* m_pData; //
        char* m_pszData;
        vector <double> m_vData;


        POINTF P1,P2,P3,P4;

    public:

        void SetInfo();
        void ScanData();
        void Scan3DData();

        int nAciertos=0;



        POINTF ScanPerTrace(int num);

        FILE *m_fpr;
        FILE *m_fprWrite;
        char* mmap_pointer;
        bool use_mmap;

        #if defined(__WIN32) || defined(_WIN64)
        HANDLE hFile, hMap;

        #elif
        struct stat statbf;
        #endif


};



CSegyRead::CSegyRead()
{
    cache = CacheDirecta(128, 16); // Aqui se inicializa la cache de composicion directa de 128 lineas y 16 palabras por linea
    mmap_pointer = NULL;
    this->use_mmap=false;
    #if defined(__WIN32) || defined(_WIN64)
    this->hFile = NULL;
    this->hMap = NULL;

    #endif
    m_bDataIBMFmt = true;
    m_bDataWS = true;
    m_bEBText = true;
    m_nDataLenth = 4;
    m_nXCoordLenth = 4;
    m_nXCoordSet = 73;
    m_nYCoordSet = 77;
    m_nInlineSet = 9; //inline
    m_nXlineSet = 21; //xl
    m_nInlineLenth = 4;
    m_nXLineLenth = 4;
    m_nXCoordLenth = 4; //X
    m_nYCoordLenth = 4; //Y
    m_nSampleInterval = 0;
    m_nSampleNum = 0;
    m_fmt = IBMFLOAT;
    bDataOrdination = false;
    m_nStrtTime = 0;
    m_nStrtXLine = 0;
    m_nStrtInLine = 0;
    m_nStopXline = 0;
    m_nStopTime = 0;
    m_nStopInLine = 0;
    m_nScaleoSet = 71;

    m_fXInterval = 0.f;
    m_fLineInterval = 0.f;

    m_bIsEDBCode = true;
    m_bIsBigEndian = true;
    m_bHasTextualHeader = true;
    m_bOpen = false;

    m_bLineSet = true;
    m_bCoordSet = true;
    segyRegular = false;

    m_pData = 0;
    m_pszData = 0;

    m_fpr = NULL;
}

CSegyRead::~CSegyRead()
{
    fclose(m_fpr);
    if (m_pData)
        delete []m_pData;
    if (m_pszData)
        delete []m_pszData;
}

CSegyRead::CSegyRead(char *csSgyParth)
{

}

const unsigned char *CSegyRead::ReadTextualHeader()
{
    if(!this->use_mmap)
    {
        fseek(m_fpr,0,0);
        if (m_bHasTextualHeader)
        {

            fread(m_szTextInfo,sizeof(unsigned char),TEXTUAL_HEADER_SIZE,m_fpr);

        }
        else
        {

            char* temTextInfo  = new char[3200];
            temTextInfo = "This SEG-Y file has no 3200-byte EBCDIC textual header!";
            memcpy(m_szTextInfo, temTextInfo,3200);
        }

        return m_szTextInfo;
    }
    else // Aqui se usa mmap
    {
        if (m_bHasTextualHeader)
        {

            memcpy((char*)&m_szTextInfo, this->mmap_pointer, TEXTUAL_HEADER_SIZE); // Se copia directamente del archivo los primeros 3200 bytes

        }
        else
        {

            char* temTextInfo  = new char[3200];
            temTextInfo = "Este archivo SEG-Y no tiene cabecera textual.";
            memcpy(m_szTextInfo, temTextInfo,3200);
        }

        return m_szTextInfo;
    }

}


const VOLUMEHEADER &CSegyRead::ReadVolumeHeader() // Aqui se lee la cabecera de volumen o binaria
{
    unsigned long long lenth;

    if(!this->use_mmap)
    {
        fseek(m_fpr,0,0);

        if (m_bHasTextualHeader)
        {
            fseek(m_fpr,TEXTUAL_HEADER_SIZE,0);
            lenth = m_lFileLenth;

        }
        else lenth = m_lFileLenth-TEXTUAL_HEADER_SIZE;


        fread(&m_volHead,sizeof(VOLUMEHEADER),1,m_fpr);


        if (m_bDataWS)
            SwapVolumeHead(m_volHead);

        if (m_nSampleNum != 0 && m_nXLineNum != 0)
            m_nInLineNum = lenth/(m_nSampleNum*m_nXLineNum*m_nDataLenth);
        if (m_nInLineNum < 0)
            m_nInLineNum = 0;

        return m_volHead;
    }
    else // Aqui se usa a mmap
    {
        char *bf=this->mmap_pointer;
        if (m_bHasTextualHeader) // Si
        {
            bf = this->mmap_pointer+TEXTUAL_HEADER_SIZE;

            lenth = m_lFileLenth;

        }
        else lenth = m_lFileLenth-TEXTUAL_HEADER_SIZE;


        memcpy((char*)&m_volHead,bf, sizeof(VOLUMEHEADER));


        if (m_bDataWS)
            SwapVolumeHead(m_volHead);

        if (m_nSampleNum != 0 && m_nXLineNum != 0)
            m_nInLineNum = lenth/(m_nSampleNum*m_nXLineNum*m_nDataLenth);
        if (m_nInLineNum < 0)
            m_nInLineNum = 0;

        return m_volHead;
    }

}

const TRACEHEADER &CSegyRead::ReadTraceHeader(int nIndex/*=0*/) // Aqui se le la N-esima cabecera de traza
{
    if(!this->use_mmap)
    {

        long long lOffset = TEXTUAL_HEADER_SIZE+VOLUME_HEADER_SIZE;
        if (!m_bHasTextualHeader)
            lOffset = VOLUME_HEADER_SIZE;
        lOffset += (TRACE_HEADER_SIZE+m_nSampleNum*m_nDataLenth)*(nIndex-1);
        fseek(m_fpr,lOffset,SEEK_SET);
        fread(m_szTraceHead,sizeof(char),TRACE_HEADER_SIZE,m_fpr);
        memcpy((char*)&m_traHead,m_szTraceHead,sizeof(char)*TRACE_HEADER_SIZE);

        if (m_bDataWS)
            SwapTraceHead(m_traHead);

        return m_traHead;
    }
    else //Aqui se usa a mmap
    {
        long long lOffset = TEXTUAL_HEADER_SIZE+VOLUME_HEADER_SIZE;
        if (!m_bHasTextualHeader)
            lOffset = VOLUME_HEADER_SIZE;
        lOffset += (TRACE_HEADER_SIZE+m_nSampleNum*m_nDataLenth)*(nIndex-1);

        char* bf = this->mmap_pointer+lOffset;
        memcpy((char*)&m_szTraceHead, bf, TRACE_HEADER_SIZE);
        memcpy((char*)&m_traHead,m_szTraceHead,sizeof(char)*TRACE_HEADER_SIZE);

        if (m_bDataWS)
            SwapTraceHead(m_traHead);

        return m_traHead;
    }
}

float* CSegyRead::ReadTraceData(int nIndex)
{
    //if (nIndex < 0)
    //    nIndex = m_nCurrentTraceNum;
    long long lOffset = TEXTUAL_HEADER_SIZE+VOLUME_HEADER_SIZE;
    if (!m_bHasTextualHeader)
        lOffset = VOLUME_HEADER_SIZE;
    lOffset += (nIndex-1)*(TRACE_HEADER_SIZE+m_nSampleNum*m_nDataLenth)+TRACE_HEADER_SIZE;
    fseek(m_fpr,lOffset,0);

    if (m_pData != 0)
        delete []m_pData;
    if (m_pszData != 0)
        delete []m_pszData;

    m_pszData = new char[m_nSampleNum*m_nDataLenth];
    m_pData = new float[m_nSampleNum];


    if(!this->use_mmap)
    {
        fread(m_pszData,sizeof(char),m_nSampleNum*m_nDataLenth,m_fpr);
    }
    else // Se usa mmap
    {
        memcpy(m_pszData, this->mmap_pointer+lOffset, m_nSampleNum*m_nDataLenth);
    }



    for (int i=0;i<m_nSampleNum;i++)
    {
        memcpy((char*)m_pData+i*sizeof(float),m_pszData+i*m_nDataLenth,m_nDataLenth);
        if (m_bDataIBMFmt)
            ibm2ieee(&m_pData[i],m_bDataWS);

    }



    return m_pData;


}

float *formatTransform(const char *szBuff,int len,int format)
{

    float *pData = new float[len];
    switch (format)
    {
    case 1:
    {
        for (int i=0;i<len;i++)
        {

            uint32 x;
            //memcpy((char*)&x,szBuff+i*4,4);

            float z = (float)x;
            ibm2ieee(&z,1);

            pData[i] = x;
        }
    }
        break;
    case 2:
    {
        for (int i=0;i<len;i++)
        {
            int x;
            memcpy((char*)&x,szBuff+i*4,4);
            pData[i] = swapi4(x);
        }
    }
        break;
    case 3:
    {
        for (int i=0;i<len;i++)
        {
            int x;
            memcpy((char*)&x,szBuff+i*2,2);
            pData[i] = swapi2(x);
        }
    }


        break;
    case 5:
    {
        for (int i=0;i<len;i++)
        {
            int x;
            memcpy((char*)&x,szBuff+i*4,4);
            pData[i] = swapi4(x);
        }
    }
        break;
    }

    return pData;
}

float* CSegyRead::GetTraceData(int nIndex )
{
    int bufLen = m_nSampleNum*m_nDataLenth;

    m_pData = new float[m_nSampleNum];

    char *szBuff = new char[bufLen];

    unsigned long long lOffset = TEXTUAL_HEADER_SIZE+VOLUME_HEADER_SIZE;

    if (!m_bHasTextualHeader)
        lOffset =VOLUME_HEADER_SIZE;
    lOffset +=(nIndex-1)*(TRACE_HEADER_SIZE+bufLen)+TRACE_HEADER_SIZE;

    if(!this->use_mmap)
    {
        fseek(m_fpr,lOffset,0);

        fread(szBuff,sizeof(char),bufLen,m_fpr);
    }
    else //Usando mmap
    {
        char* szBuff = this->mmap_pointer+lOffset;
    }



    int len = m_nSampleNum;
    float *m_pData = new float[len];
    memset((char*)m_pData,0,len*sizeof(float));

    switch (m_nFormatCode)
    {
    case 1:
    {
        for (int i=0;i<len;i++)
        {
            float x;
            //memcpy((char*)&x,szBuff+i*4,4);

            cache.prefetch(i+1, szBuff);

            if(cache.acceso(i, (uint32&)x, szBuff)) // Aqui se hace el acceso a la cache
            {
                nAciertos++;
            }

            ibm2ieee(&x,1);
            m_pData[i] = x;
        }
    }
        break;
    case 2:
    {
        for (int i=0;i<len;i++)
        {
            int x;
            memcpy((char*)&x,szBuff+i*4,4);
            m_pData[i] = swapi4(x);
        }
    }
        break;
    case 3:
    {
        for (int i=0;i<len;i++)
        {
            int x;
            memcpy((char*)&x,szBuff+i*2,2);
            m_pData[i] = swapi2(x);
        }
    }


        break;
    case 5:
    {
        for (int i=0;i<len;i++)
        {
            float x;
            memcpy((char*)&x,szBuff+i*4,4);
            m_pData[i] = swapf4(x);

        }
    }
        break;

    }



    delete []szBuff;
    return (float*)m_pData;
}





float CSegyRead::GetSampleValue(int idx)
{

    m_pszData = new char[m_nSampleNum*m_nDataLenth];
    m_pData = new float[m_nSampleNum];
    int*    xmp = (int*)&smp;
    float*  dat = (float*)(m_pszData+240);

    short*       int2ptr = (short*)       dat;
    int*         int4ptr = (int*)         dat;
    signed char* int1ptr = (signed char*) dat;

    if(m_nFormatCode==1)
    {
        smp =  dat[idx];
        ibm2ieee(&smp,1);
    }
    else if(m_nFormatCode==2)
    {
        smp = swapi4(int4ptr[idx]);
    }
    else if(m_nFormatCode==3)
    {
        smp = swapi2(int2ptr[idx]);
    }
    else if(m_nFormatCode==4)
    {
        smp = dat[idx];
    }
    else if(m_nFormatCode==5)
    {
        *xmp = swapi4(int4ptr[idx]);
    }
    else if(m_nFormatCode==6)
    {
        smp = int1ptr[idx];
    }
    else
        smp = 0;

    return smp;
}

/*
float CSegyRead::GetTrace(long long n)
{
    long long l;
    int trl = 240+m_nTotalTraceNum*m_nDataLenth;

    //if(_F == NULL) return false;

    if(n == 0) return false;

    if(n < 1 || n > m_nTotalTraceNum)
    {
        printf("Bad Trace Number");
        return false;
    }

    fseek(m_fpr, 3600+(n-1)*trl, SEEK_SET);
    l = fread(_INPTRC, 1, _TRL, _F );

    _CurrentTrace = n;

    for(n=0; n < _TotalSamples; n++)
        m_pData[n] =  GetSampleValue(n);

    return m_pData;
}
*/


bool CSegyRead::OpenFile(const char *csReadFile, bool use_mmap=false)
{

    closeFile();

    this->use_mmap = use_mmap;

    if(!this->use_mmap)
    {
        m_fpr = fopen(csReadFile,"rb");

        if (m_fpr == NULL)
        {
            printf("No se pudo abrir el SEG-Y");
            return false ;
        }

        //strcpy(m_csFilepath,csReadFile);
        fseek(m_fpr,0,2);

        m_lFileLenth = ftell(m_fpr);

        fseek(m_fpr,0,0);


        ReadTextualHeader();
        ReadVolumeHeader();
        ReadTraceHeader(1);
        SetInfo();

        //ReadTraceData(20);
        //ScanData();

        return true;
    }
    else
    {
        #if defined(__WIN32) || defined(_WIN64)
        this->mmap_pointer = getMmapPtr(csReadFile, &this->hFile, &this->hMap);
        #else
        this->mmap_pointer = getMmapPtr(csReadFile, &this->statbf);
        #endif
    }

}

void CSegyRead::closeFile()
{
    this->nAciertos = 0;

    #if defined(__WIN32) || defined(_WIN64)
    if(hFile != NULL)
    {
        CloseHandle(hFile);
        hFile = NULL;
    }
    if(hMap != NULL)
    {
        CloseHandle(hMap);
        hMap = NULL;
    }

    #else
    munmap(this->mmap_pointer, this->statbf.st_size);
    #endif
    if (m_fpr != NULL)
    {

        fclose(m_fpr);
        m_fpr == NULL;
    }
}

void CSegyRead::SetNewTextualHeader()
{
    m_szNewHeader = "This is a SEG-Y file containing microseismic event signals"; //3200
}

void CSegyRead::WriteSegy(const char *csReadFile, const char *csWriteFile)
{
    m_fpr = fopen(csReadFile,"rb");
    m_fprWrite = fopen(csWriteFile,"wb");

    if (m_fpr == NULL)
    {
        printf("no se pudo leer el SEG-Y.");
        return ;
    }

    fseek(m_fprWrite,0,0);
    for (int i=0; i<3200; i++)
    {
        fputc(m_szNewHeader[i], m_fprWrite);
    }


    char ch;
    fseek(m_fpr,3200,0);
    fseek(m_fprWrite,3200,0);
    while(!feof(m_fpr))
    {
        ch = fgetc(m_fpr);
        fputc(ch, m_fprWrite);

    }

    fclose(m_fprWrite);
}

void CSegyRead::SetInfo()
{
    m_nFormatCode = m_volHead.format;
    m_nSegyRev = m_volHead.rev;

    m_nSampleNum = m_volHead.hns;
    m_nSampleInterval = m_volHead.hdt;

    //m_fmt = m_volHead.format == 1?IBMFLOAT:IEEEFLOAT;
    m_nStrtTime = m_traHead.delrt;
    m_nStopTime = m_traHead.delrt + m_nSampleInterval*m_nSampleNum / 1000;
    m_nXLineNum = m_volHead.ntrpr;

    //m_nTraId=m_traHead.nTraId;

    switch(m_nFormatCode)
    {
    case 1:
    {
        m_nDataLenth = 4;
        break;
    }

    case 2:
    {
        m_nDataLenth = 4;
        break;
    }
    case 3:
    {
        m_nDataLenth = 2;
        break;
    }
    case 5:
    {
        m_nDataLenth = 4;
        break;
    }
    case 8:
    {
        m_nDataLenth = 1;
        break;
    }
    }



    unsigned long long len = m_lFileLenth;
    if (m_bHasTextualHeader)
    {
        len = len-TEXTUAL_HEADER_SIZE-VOLUME_HEADER_SIZE;
    }
    else
    {
        len = len -VOLUME_HEADER_SIZE;
    }

    m_nTotalTraceNum = len/(TRACE_HEADER_SIZE+m_nSampleNum*m_nDataLenth);
}

void CSegyRead::ScanData()
{
    Scan3DData();
}

void CSegyRead::Scan3DData()
{
    m_nInLineNum = 0;
    m_nXLineNum = 0;

    unsigned long long len = m_lFileLenth;
    if (m_bHasTextualHeader)
        len = len-TEXTUAL_HEADER_SIZE-VOLUME_HEADER_SIZE;
    m_nTotalTraceNum = len/(TRACE_HEADER_SIZE+m_nSampleNum*m_nDataLenth);

    m_nInLineNum  = 1;

    P1 = ScanPerTrace(0);
    m_nStrtInLine = m_traHead.iTSTNum;
    m_nStrtXLine = m_traHead.iCdpNum;
    m_nStrtTime = m_traHead.delrt;
    m_nStopTime = m_nStrtTime + m_nSampleNum*m_nSampleInterval/1000;

    int flag = m_traHead.iOriNum;
    for (int i=1;i<m_nTotalTraceNum;i++)
    {
        POINTF pt = ScanPerTrace(i);
        if (flag != m_traHead.iOriNum)
        {
            m_nXLineNum = i;
            break;
        }
    }
    m_nInLineNum = m_nTotalTraceNum / m_nXLineNum;
    m_nStopInLine = m_nStrtInLine + m_nInLineNum;
    P2 = ScanPerTrace(m_nXLineNum-1);
    m_nStopXline = m_traHead.iCdpNum;
    P3 = ScanPerTrace(m_nTotalTraceNum-1);
    P4 = ScanPerTrace(m_nTotalTraceNum-m_nXLineNum);
}

POINTF CSegyRead::ScanPerTrace(int num)
{
    unsigned long long lOffset = TEXTUAL_HEADER_SIZE+VOLUME_HEADER_SIZE;
    if (!m_bHasTextualHeader)
        lOffset = 0;
    lOffset += (TRACE_HEADER_SIZE+m_nSampleNum*m_nDataLenth)*(unsigned long long)num;

    char sz[TRACE_HEADER_SIZE];
    int nLineFlag = -1;
    int scale;

    fseek(m_fpr,lOffset,0);
    fread(sz,TRACE_HEADER_SIZE,1,m_fpr);
    memcpy((char*)&m_traHead,sz,TRACE_HEADER_SIZE);

    memcpy((char*)&m_traHead.iTSTNum,sz+m_nInlineSet-1,m_nInlineLenth);
    memcpy((char*)&m_traHead.iCdpNum,sz+m_nXlineSet-1,m_nXLineLenth);
    memcpy((char*)&scale,sz+m_nScaleoSet-1,sizeof(short));
    memcpy((char*)&m_traHead.iGroupX,sz+m_nXCoordSet-1,m_nXCoordLenth);
    memcpy((char*)&m_traHead.iGroupY,sz+m_nYCoordSet-1,m_nYCoordLenth);

    if (m_bDataWS)
    {
        SwapTraceHead(m_traHead);
        scale = swapi2(scale);
    }

    scale = abs(scale);
    if (scale==0)
        scale = 1;

    POINTF pt;
    pt.x = (double)m_traHead.iGroupX/(double)scale;
    pt.y = (double)m_traHead.iGroupY/(double)scale;

    return pt;
}

int CSegyRead::getSamplesNumber() const
{
    return m_nSampleNum;
}

int CSegyRead::getSamplesInterval() const
{
    return m_nSampleInterval;
}

short CSegyRead::getFormat() const
{
    return m_nFormatCode;
}



int CSegyRead::getTotalTraceNumber() const
{
    return m_nTotalTraceNum;
}

int CSegyRead::getSegyRev() const
{
    return m_nSegyRev;
}



/*
const unsigned char *CSegyRead::GetEbcdicTextualHeader() const
{
    fseek(m_fpr,0,0);
    if (m_bHasTextualHeader)
    {
        fread(m_szTextInfo,sizeof(unsigned char),TEXTUAL_HEADER_SIZE,m_fpr);
        if (m_bIsEDBCode)
        {
            for (int i=0;i<TEXTUAL_HEADER_SIZE;i++)
                m_szTextInfo[i] = EbcdicToAscii(m_szTextInfo[i]);
        }
    }

    return m_szTextInfo;
}
*/


void CSegyRead::SwapVolumeHead(VOLUMEHEADER &m_volHead)
{
    m_volHead.jobid   = swapi4(m_volHead.jobid);
    m_volHead.lino    = swapi4(m_volHead.lino);
    m_volHead.reno    = swapi4(m_volHead.reno);
    m_volHead.ntrpr   = swapi2(m_volHead.ntrpr);
    m_volHead.nart    = swapi2(m_volHead.nart);
    m_volHead.hdt     = swapi2(m_volHead.hdt);
    m_volHead.hns     = swapi2(m_volHead.hns);
    m_volHead.nso     = swapi2(m_volHead.nso);
    m_volHead.format  = swapi2(m_volHead.format);
    m_volHead.fold    = swapi2(m_volHead.fold);
    m_volHead.tsort   = swapi2(m_volHead.tsort);
    m_volHead.vscode  = swapi2(m_volHead.vscode);
    m_volHead.hsfs    = swapi2(m_volHead.hsfs);
    m_volHead.hsfe    = swapi2(m_volHead.hsfe);
    m_volHead.hslen   = swapi2(m_volHead.hslen);
    m_volHead.hstyp   = swapi2(m_volHead.hstyp);
    m_volHead.schn    = swapi2(m_volHead.schn);
    m_volHead.hstas   = swapi2(m_volHead.hstas);
    m_volHead.hstae   = swapi2(m_volHead.hstae);
    m_volHead.htatyp  = swapi2(m_volHead.htatyp);
    m_volHead.hcorr   = swapi2(m_volHead.hcorr);
    m_volHead.bgrcv   = swapi2(m_volHead.bgrcv);
    m_volHead.rcvm    = swapi2(m_volHead.rcvm);
    m_volHead.mfeet   = swapi2(m_volHead.mfeet);
    m_volHead.polyt   = swapi2(m_volHead.polyt);
    m_volHead.vpol    = swapi2(m_volHead.vpol);
}

void CSegyRead::SwapTraceHead(TRACEHEADER &m_traHead)
{
    m_traHead.iSLNum    = swapi4(m_traHead.iSLNum);
    m_traHead.iTSTNum   = swapi4(m_traHead.iTSTNum);
    m_traHead.iOriNum   = swapi4(m_traHead.iOriNum);
    m_traHead.iTraNum   = swapi4(m_traHead.iTraNum);
    m_traHead.iSorceNum = swapi4(m_traHead.iSorceNum);
    m_traHead.iCdpNum   = swapi4(m_traHead.iCdpNum);
    m_traHead.iCdpTra   = swapi4(m_traHead.iCdpTra);
    m_traHead.nTraId    = swapi2(m_traHead.nTraId);
    m_traHead.nVsTra    = swapi2(m_traHead.nVsTra);
    m_traHead.nHsTra    = swapi2(m_traHead.nHsTra);
    m_traHead.nDuse     = swapi2(m_traHead.nDuse);
    m_traHead.iOffset   = swapi4(m_traHead.iOffset);
    m_traHead.gelev     = swapi4(m_traHead.gelev);
    m_traHead.selev     = swapi4(m_traHead.selev);
    m_traHead.sdepth    = swapi4(m_traHead.sdepth);
    m_traHead.gdel      = swapi4(m_traHead.gdel);
    m_traHead.sdel      = swapi4(m_traHead.sdel);
    m_traHead.swdep     = swapi4(m_traHead.swdep);
    m_traHead.gwdep     = swapi4(m_traHead.gwdep);
    m_traHead.scalel    = swapi2(m_traHead.scalel);
    m_traHead.scalco    = swapi2(m_traHead.scalco);
    m_traHead.iSourseX  = swapi4(m_traHead.iSourseX);
    m_traHead.iSourseY  = swapi4(m_traHead.iSourseY);
    m_traHead.iGroupX   = swapi4(m_traHead.iGroupX);
    m_traHead.iGroupY   = swapi4(m_traHead.iGroupY);
    m_traHead.counit    = swapi2(m_traHead.counit);
    m_traHead.wevel     = swapi2(m_traHead.wevel);
    m_traHead.swevel    = swapi2(m_traHead.swevel);
    m_traHead.sut       = swapi2(m_traHead.sut);
    m_traHead.gut       = swapi2(m_traHead.gut);
    m_traHead.sstat     = swapi2(m_traHead.sstat);
    m_traHead.gstat     = swapi2(m_traHead.gstat);
    m_traHead.tstat     = swapi2(m_traHead.tstat);
    m_traHead.laga      = swapi2(m_traHead.laga);
    m_traHead.lagb      = swapi2(m_traHead.lagb);
    m_traHead.delrt     = swapi2(m_traHead.delrt);
    m_traHead.muts      = swapi2(m_traHead.muts);
    m_traHead.mute      = swapi2(m_traHead.mute);
    m_traHead.uNs       = swapi2(m_traHead.uNs);
    m_traHead.uRate     = swapi2(m_traHead.uRate);
    m_traHead.gain      = swapi2(m_traHead.gain);
    m_traHead.igc       = swapi2(m_traHead.igc);
    m_traHead.igi       = swapi2(m_traHead.igi);
    m_traHead.corr      = swapi2(m_traHead.corr);
    m_traHead.sfs       = swapi2(m_traHead.sfs);
    m_traHead.sfe       = swapi2(m_traHead.sfe);
    m_traHead.slen      = swapi2(m_traHead.slen);
    m_traHead.styp      = swapi2(m_traHead.styp);
    m_traHead.stas      = swapi2(m_traHead.stas);
    m_traHead.stae      = swapi2(m_traHead.stae);
    m_traHead.tatyp     = swapi2(m_traHead.tatyp);
    m_traHead.afilf     = swapi2(m_traHead.afilf);
    m_traHead.nofilf    = swapi2(m_traHead.nofilf);
    m_traHead.nofils    = swapi2(m_traHead.nofils);
    m_traHead.lcf       = swapi2(m_traHead.lcf);
    m_traHead.hcf       = swapi2(m_traHead.hcf);
    m_traHead.lcs       = swapi2(m_traHead.lcs);
    m_traHead.hcs       = swapi2(m_traHead.hcs);
    m_traHead.year      = swapi2(m_traHead.year);
    m_traHead.day       = swapi2(m_traHead.day);
    m_traHead.hour      = swapi2(m_traHead.hour);
    m_traHead.minute    = swapi2(m_traHead.minute);
    m_traHead.sec       = swapi2(m_traHead.sec);
    m_traHead.timbas    = swapi2(m_traHead.timbas);
    m_traHead.trwf      = swapi2(m_traHead.trwf);
    m_traHead.grnors    = swapi2(m_traHead.grnors);
    m_traHead.grnofr    = swapi2(m_traHead.grnofr);
    m_traHead.grnlof    = swapi2(m_traHead.grnlof);
    m_traHead.gaps      = swapi2(m_traHead.gaps);
    m_traHead.otrav     = swapi2(m_traHead.otrav);
}


#endif // SEGY_H_INCLUDED
