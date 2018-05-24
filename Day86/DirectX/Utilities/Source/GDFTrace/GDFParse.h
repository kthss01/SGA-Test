//--------------------------------------------------------------------------------------
// File: GDFParse.h
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once

#include "d3dx10.h"

#pragma pack( push )
#pragma pack( 2 )

typedef struct
{
   BITMAPINFOHEADER   icHeader;      // DIB header
   RGBQUAD         icColors[1];   // Color table
   BYTE            icXOR[1];      // DIB bits for XOR mask
   BYTE            icAND[1];      // DIB bits for AND mask
} ICONIMAGE, *LPICONIMAGE;


typedef struct
{
    BYTE    bWidth;               // Width of the image
    BYTE    bHeight;              // Height of the image (times 2)
    BYTE    bColorCount;          // Number of colors in image (0 if >=8bpp)
    BYTE    bReserved;            // Reserved
    WORD    wPlanes;              // Color Planes
    WORD    wBitCount;            // Bits per pixel
    DWORD    dwBytesInRes;         // how many bytes in this resource?
    WORD    nID;                  // the ID
} MEMICONDIRENTRY, *LPMEMICONDIRENTRY;

typedef struct 
{
    WORD            idReserved;   // Reserved
    WORD            idType;       // resource type (1 for icons)
    WORD            idCount;      // how many images?
    MEMICONDIRENTRY   idEntries[1]; // the entries for each image
} MEMICONDIR, *LPMEMICONDIR;
#pragma pack( pop )

static unsigned int   iconResolution[] = {16, 32, 48, 256};

class CGDFParse
{
public:
    CGDFParse();
    ~CGDFParse();

    HRESULT LoadXML( WCHAR* strGDFPath );

    HRESULT ExtractXML( WCHAR* strGDFBinPath, WORD wLanguage = LANG_NEUTRAL );

    HRESULT ValidateGDF( WCHAR* strGDFPath, WCHAR* strReason, int cchReason );

    HRESULT ValidateXML( WCHAR* strGDFBinPath, WORD wLanguage, WCHAR* strReason, int cchReason );

    HRESULT EnumLangs( WCHAR* strGDFBinPath );
    int GetNumLangs() const { return m_LanguageCount; }
    WORD GetLang( int iIndex ) const { return m_Languages[iIndex]; } 

    // To use these, call ExtractXML() first
    HRESULT GetName( WCHAR* strDest, int cchDest );
    HRESULT GetDescription( WCHAR* strDest, int cchDest );
    HRESULT GetReleaseDate( WCHAR* strDest, int cchDest );
    HRESULT GetGenre( WCHAR* strDest, int cchDest );
    HRESULT GetDeveloper( WCHAR* strDest, int cchDest );
    HRESULT GetDeveloperLink( WCHAR* strDest, int cchDest );
    HRESULT GetPublisher( WCHAR* strDest, int cchDest );
    HRESULT GetPublisherLink( WCHAR* strDest, int cchDest );
    HRESULT GetVersion( WCHAR* strDest, int cchDest );
    HRESULT GetWinSPR( float* pnMin, float* pnRecommended );
    HRESULT GetGameID( WCHAR* strDest, int cchDest );
    HRESULT GetRatingSystem( int iRating, WCHAR* strRatingSystem, int cchRatingSystem );
    HRESULT GetRatingID( int iRating, WCHAR* strRatingID, int cchRatingID );
    HRESULT GetRatingDescriptor( int iRating, int iDescriptor, WCHAR* strDescriptor, int cchDescriptor );
    HRESULT GetGameExe( int iGameExe, WCHAR* strEXE, int cchEXE );
    HRESULT GetSavedGameFolder( WCHAR* strDest, int cchDest );
    HRESULT GetType( WCHAR* strDest, int cchDest );
    HRESULT GetRSS( WCHAR* strDest, int cchDest );
    HRESULT ExtractGDFThumbnail( WCHAR* strGDFBinPath, D3DX10_IMAGE_INFO* info, WORD wLanguage = LANG_NEUTRAL );
    HRESULT OutputGDFIconInfo( WCHAR* strGDFBinPath, BOOL* bIconEightBits,BOOL* bIconThirtyTwoBits, WORD wLanguage = LANG_NEUTRAL );
    BOOL IsIconPresent( WCHAR* strGDFBinPath );
    HRESULT IsV2GDF(BOOL* pfV2GDF);

protected:
    HRESULT LoadXMLinMemory( WCHAR* strGDFBinPath, WORD wLanguage, HGLOBAL* phResourceCopy );
    bool ValidateUsingSchema( VOID* pDoc, WCHAR* strReason, int cchReason );
    HRESULT GetXMLValue( WCHAR* strXPath, WCHAR* strValue, int cchValue );
    HRESULT GetXMLAttrib( WCHAR* strXPath, WCHAR* strAttribName, WCHAR* strValue, int cchValue );
    HRESULT GetAttribFromNode( IXMLDOMNode* pNode, WCHAR* strAttrib, WCHAR* strDest, int cchDest );
    HRESULT ConvertGuidToFolderName( WCHAR* strFolderGuid, WCHAR* strFolderName );
    static BOOL CALLBACK StaticEnumResLangProc( HMODULE hModule, LPCWSTR lpType, LPCWSTR lpName, WORD wLanguage, LONG_PTR lParam );
    BOOL EnumResLangProc( HMODULE hModule, LPCWSTR lpType, LPCWSTR lpName, WORD wLanguage );

    IXMLDOMNode* m_pRootNode;
    bool m_bCleanupCOM;

    WORD m_Languages[256];
    int m_LanguageCount;
};
