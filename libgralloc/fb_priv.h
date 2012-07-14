/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FB_PRIV_H
#define FB_PRIV_H
#include <linux/fb.h>

#define NUM_FRAMEBUFFERS_MIN  2
//XXX: Enable triple framebuffers
#define NUM_FRAMEBUFFERS_MAX  2

#define NO_SURFACEFLINGER_SWAPINTERVAL
#define COLOR_FORMAT(x) (x & 0xFFF) // Max range for colorFormats is 0 - FFF

enum hdmi_mirroring_state {
    HDMI_NO_MIRRORING,
    HDMI_UI_MIRRORING,
};

struct private_handle_t;

enum {
    // flag to indicate we'll post this buffer
    PRIV_USAGE_LOCKED_FOR_POST = 0x80000000,
    PRIV_MIN_SWAP_INTERVAL = 0,
    PRIV_MAX_SWAP_INTERVAL = 1,
};

struct private_module_t {
    gralloc_module_t base;
    struct private_handle_t* framebuffer;
    uint32_t fbFormat;
    uint32_t flags;
    uint32_t numBuffers;
    uint32_t bufferMask;
    pthread_mutex_t lock;
    buffer_handle_t currentBuffer;
    struct fb_var_screeninfo info;
    struct fb_fix_screeninfo finfo;
    float xdpi;
    float ydpi;
    float fps;
    uint32_t swapInterval;
#if defined(__cplusplus) && defined(HDMI_DUAL_DISPLAY)
    int orientation;
    int videoOverlay; // VIDEO_OVERLAY - 2D or 3D
    int secureVideoOverlay; // VideoOverlay is secure
    uint32_t currentOffset;
    int enableHDMIOutput; // holds the type of external display
    bool trueMirrorSupport;
    bool exitHDMIUILoop;
    float actionsafeWidthRatio;
    float actionsafeHeightRatio;
    bool hdmiStateChanged;
    hdmi_mirroring_state hdmiMirroringState;
    pthread_mutex_t overlayLock;
    pthread_cond_t overlayPost;
#endif
};



#endif /* FB_PRIV_H */
