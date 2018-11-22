/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */
 
#include <elog.h>

#ifdef CONFIG_EASYLOGGER_JLINK_LOG

#include "SEGGER_RTT.h"
#define SEGGER_SYSVIEW_RTT_BUFFER_SIZE      1024                                // Number of bytes that SystemView uses for the buffer.
#define SEGGER_SYSVIEW_RTT_CHANNEL          1                                   // The RTT channel that SystemView will use. 0: Auto selection

static char _UpBuffer  [SEGGER_SYSVIEW_RTT_BUFFER_SIZE];
#if (SEGGER_SYSVIEW_POST_MORTEM_MODE != 1)
static char _DownBuffer[8];  // Small, fixed-size buffer, for back-channel comms
#endif

#endif

#if USE_OSLIB
#include "osMutex.h"
fastembedded::OSMutex *log_mutex;
#endif

/**
 * EasyLogger port initialize
 *
 * @return result
 */
extern "C" ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;

#ifdef CONFIG_EASYLOGGER_JLINK_LOG
    SEGGER_RTT_ConfigUpBuffer   (SEGGER_SYSVIEW_RTT_CHANNEL, "SysView", &_UpBuffer[0],   sizeof(_UpBuffer),   SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    SEGGER_RTT_ConfigDownBuffer (SEGGER_SYSVIEW_RTT_CHANNEL, "SysView", &_DownBuffer[0], sizeof(_DownBuffer), SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    SEGGER_RTT_Init();
#endif
#if USE_OSLIB
    log_mutex = new fastembedded::OSMutex();
    assert(log_mutex);
#endif

    return result;
}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
extern "C" void elog_port_output(const char *log, size_t size) {
#ifdef CONFIG_EASYLOGGER_JLINK_LOG
    SEGGER_RTT_Write(0, log, size);
#endif
}

extern "C" void elog_port_output_lock(void) {
#if USE_OSLIB
	log_mutex->lock();
#endif
}

/**
 * output unlock
 */
extern "C" void elog_port_output_unlock(void) {
#if USE_OSLIB
	log_mutex->unlock();
#endif
}

/**
 * get current time interface
 *
 * @return current time
 */
extern "C" const char *elog_port_get_time(void) {
    return "0:0";
}

/**
 * get current process name interface
 *
 * @return current process name
 */
extern "C" const char *elog_port_get_p_info(void) {
    return "P";
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
extern "C" const char *elog_port_get_t_info(void) {
    return "T";
}
