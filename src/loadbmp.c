#include "bitmap.h"
#include "dxfacelight.h"
#include <stdio.h>

UCHAR *loadbmp()
{
    UCHAR upright = 1;
    INT pxSz = 0;
    INT sz = 0;
    INT lnSz = 0;
    BITMAPHEADER *bmpHead = (BITMAPHEADER *)dxtexture;
    DBITMAPINFOHEADER *bmpInfo = (DBITMAPINFOHEADER *)((UCHAR *)dxtexture + sizeof(BITMAPHEADER));
    UCHAR *bmpData = (UCHAR *)((UCHAR *)dxtexture + bmpHead->dwPixOffset);
    UCHAR *data;
    UCHAR *dDest;
    UCHAR *lnData = bmpData;

    if(bmpInfo->dwHeight < 0)
    {
        upright = 0;
        bmpInfo->dwHeight = -bmpInfo->dwHeight;
    }

    pxSz = bmpInfo->wColorDepth / 8;
    sz = bmpInfo->dwWidth * bmpInfo->dwHeight * pxSz;
    data = (UCHAR *)calloc(sz,1);
    lnSz = bmpInfo->dwWidth * pxSz;
    lnSz = ((lnSz%4) != 0 ) ? ((lnSz/4)+1)*4 : lnSz;
    //lnData = (UCHAR *)calloc(lnSz, 1);

    for(int h = 0; h < bmpInfo->dwHeight; h++)
    {
        if(upright > 0)
        {
            dDest = data + (bmpInfo->dwHeight - 1 - h) * bmpInfo->dwWidth * pxSz;
        }else{
            dDest = data + h * bmpInfo->dwWidth * pxSz;
        }

        for(int w = 0; w < bmpInfo->dwWidth; w++)
        {
            dDest[w*pxSz] = lnData[w * pxSz + 2];
            dDest[w*pxSz+1] = lnData[w * pxSz + 1];
            dDest[w*pxSz+2] = lnData[w * pxSz];
            if(pxSz == 4)
            {
                dDest[w*pxSz + 3] = lnData[w * pxSz + 3];
            }
        }
        lnData += lnSz;
    }

    printf("Size: %u  Compression: %u \n", bmpHead->dwSize, bmpInfo->dwCompression);
    printf("Width: %i Height: %i \n", bmpInfo->dwWidth, bmpInfo->dwHeight);

    return data;
}