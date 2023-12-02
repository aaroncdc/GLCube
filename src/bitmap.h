#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <windows.h>

#pragma pack(push, 2)
typedef struct dBITMAPHEADER
{
    UINT16    wMagic;
    UINT32    dwSize;
    UINT32    dwReserved;
    UINT32    dwPixOffset;
}BITMAPHEADER;

typedef struct dBITMAPINFOHEADER
{
    UINT32    dwSize;
    INT32     dwWidth;
    INT32     dwHeight;
    UINT16    wPlanes;
    UINT16    wColorDepth;
    UINT32    dwCompression;
    UINT32    dwSizeImage;
    INT32     dwXpixPerMeter;
    INT32     dwYPixPerMeter;
    UINT32    dwPalette;
    UINT32    dwKeyColors;
}DBITMAPINFOHEADER;
#pragma pack(pop)

/*#define BI_RGB              0
#define BI_RLE8             1
#define BI_RLE4             2
#define BI_BITFIELDS        3
#define BI_JPEG             4
#define BI_PNG              5
#define BI_ALPHABITFIELDS   6
#define BI_CMYK             11
#define BI_CMYKRLE8         12
#define BI_CMYKRLE4         13*/

UCHAR *loadbmp();

#endif