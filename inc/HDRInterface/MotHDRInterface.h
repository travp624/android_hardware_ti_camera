#ifndef MOT_HDRINTERFACE_H

#define MOT_HDRINTERFACE_H

#include <utils/threads.h>
#if 0
#include "ammem.h"
#include "amcomdef.h"
#endif
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#if 0
#include "amkernel.h"
#include "merror.h"
#include "amstream.h"
#include "arcsoft_multiexposure.h"
#include "arcsoft_jpgcodec.h"
#endif

#include "CameraHal.h"


namespace android {

typedef bool MBool;
typedef unsigned char MByte;

class MotHDRInterface {
public:
    MotHDRInterface(CameraAdapter *omxCamAdap);
    MBool HDRInterfaceProcess();
    int setDataBuffers(MByte* pBuf, unsigned int filledLen, unsigned int offset);
    void setImageSize(int width, int height);
    //void provideResultantBuffToCamHAL(ASVLOFFSCREEN* exposureImgOut);
    void provideResultantBuffToCamHAL(void* exposureImgOut);

    void stop();
    bool init();

    virtual ~MotHDRInterface();

private:
    MBool HDRProcess(MByte* pUnderExposure, MByte* pNormalExposure, MByte* mOverExposure,
                 MByte* pHdrResultData, int image_pitch, int image_width, int image_height);

    class Worker;

    Worker *mWorker;

    int mImageWidth;
    int mImageHeight;
    int mImagePitch;
    int mImageLength;
    MByte* mHdrResultData;

    CameraAdapter *mOmxCamAdapter;
    unsigned char *mJpegDataBuff;

    Mutex mMutex;
    Condition mCondition;

    sp<MemoryHeapBase> RAWPictureHeapForUnderExp;
    sp<MemoryBase> RAWPictureMemBaseForUnderExp;
    sp<MemoryHeapBase> RAWPictureHeapForNormalExp;
    sp<MemoryBase> RAWPictureMemBaseForNormalExp;
    sp<MemoryHeapBase> RAWPictureHeapForOverExp;
    sp<MemoryBase> RAWPictureMemBaseForOverExp;
};

} // namespace android

#endif  // MOT_HDRINTERFACE_H_
