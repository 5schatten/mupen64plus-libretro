/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-core - api/vidext.c                                       *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2009 Richard Goedeken                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       * 
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
                       
/* This file contains the Core video extension functions which will be exported
 * outside of the core library.
 */

#include <stdlib.h>
#include <string.h>

#define M64P_CORE_PROTOTYPES 1
#include "../osd/osd.h"
#include "callbacks.h"
#include "m64p_types.h"
#include "m64p_vidext.h"
#include "vidext.h"
#include <glsm/glsmsym.h>

/* local variables */
static m64p_video_extension_functions l_ExternalVideoFuncTable = {11, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
static int l_VideoExtensionActive = 0;
static int l_VideoOutputActive = 0;
static int l_Fullscreen = 0;

/* global function for use by frontend.c */
m64p_error OverrideVideoFunctions(m64p_video_extension_functions *VideoFunctionStruct)
{
    /* check input data */
    if (VideoFunctionStruct == NULL)
        return M64ERR_INPUT_ASSERT;
    if (VideoFunctionStruct->Functions < 11)
        return M64ERR_INPUT_INVALID;

    /* disable video extension if any of the function pointers are NULL */
    if (VideoFunctionStruct->VidExtFuncInit == NULL ||
        VideoFunctionStruct->VidExtFuncQuit == NULL ||
        VideoFunctionStruct->VidExtFuncListModes == NULL ||
        VideoFunctionStruct->VidExtFuncSetMode == NULL ||
        VideoFunctionStruct->VidExtFuncGLGetProc == NULL ||
        VideoFunctionStruct->VidExtFuncGLSetAttr == NULL ||
        VideoFunctionStruct->VidExtFuncGLGetAttr == NULL ||
        VideoFunctionStruct->VidExtFuncGLSwapBuf == NULL ||
        VideoFunctionStruct->VidExtFuncSetCaption == NULL ||
        VideoFunctionStruct->VidExtFuncToggleFS == NULL ||
        VideoFunctionStruct->VidExtFuncResizeWindow == NULL)
    {
        l_ExternalVideoFuncTable.Functions = 11;
        memset(&l_ExternalVideoFuncTable.VidExtFuncInit, 0, 11 * sizeof(void *));
        l_VideoExtensionActive = 0;
        return M64ERR_SUCCESS;
    }

    /* otherwise copy in the override function pointers */
    memcpy(&l_ExternalVideoFuncTable, VideoFunctionStruct, sizeof(m64p_video_extension_functions));
    l_VideoExtensionActive = 1;
    return M64ERR_SUCCESS;
}

int VidExt_InFullscreenMode(void)
{
    return l_Fullscreen;
}

int VidExt_VideoRunning(void)
{
    return l_VideoOutputActive;
}

/* video extension functions to be called by the video plugin */
EXPORT m64p_error CALL VidExt_Init(void)
{
    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_Quit(void)
{
    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_ListFullscreenModes(m64p_2d_size *SizeArray, int *NumSizes)
{
    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_SetVideoMode(int Width, int Height, int BitsPerPixel, m64p_video_mode ScreenMode, m64p_video_flags Flags)
{
    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_ResizeWindow(int Width, int Height)
{
    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_SetCaption(const char *Title)
{
    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_ToggleFullScreen(void)
{
    return M64ERR_SUCCESS;
}

EXPORT void * CALL VidExt_GL_GetProcAddress(const char* Proc)
{
    glsm_ctx_proc_address_t proc_info;
    proc_info.addr = NULL;
    if (!glsm_ctl(GLSM_CTL_PROC_ADDRESS_GET, NULL))
        return NULL;
    return proc_info.addr(Proc);
}

EXPORT m64p_error CALL VidExt_GL_SetAttribute(m64p_GLattr Attr, int Value)
{
    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_GL_GetAttribute(m64p_GLattr Attr, int *pValue)
{
    return M64ERR_SUCCESS;
}

EXPORT m64p_error CALL VidExt_GL_SwapBuffers(void)
{
    //retro_return(true);
    return M64ERR_SUCCESS;
}


