/* 
 * Copyright (c) 2002 Light Weight Java Game Library Project
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are 
 * met:
 * 
 * * Redistributions of source code must retain the above copyright 
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of 'Light Weight Java Game Library' nor the names of 
 *   its contributors may be used to endorse or promote products derived 
 *   from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * $Id$
 *
 * @author elias_naur <elias_naur@users.sourceforge.net>
 * @version $Revision$
 */

#ifndef _COMMON_TOOLS_H
#define _COMMON_TOOLS_H

#include <jni.h>
#include "org_lwjgl_Sys.h"

extern bool debug;

// Must be x * max_event_size + 1
#define EVENT_BUFFER_SIZE (25 * 4 + 1)
#define ISDEBUGENABLED() (debug)

typedef struct {
	unsigned char input_event_buffer[EVENT_BUFFER_SIZE];
	unsigned char output_event_buffer[EVENT_BUFFER_SIZE];

	int list_start;
	int list_end;
} event_queue_t;

extern void initEventQueue(event_queue_t *event_queue);
extern int copyEvents(event_queue_t *event_queue, int event_size);
extern void putEventElement(event_queue_t *queue, unsigned char byte);
extern unsigned char *getOutputList(event_queue_t *queue);
extern int getEventBufferSize(event_queue_t *event_queue);
extern void throwException(JNIEnv *env, const char *msg);
extern void throwOpenALException(JNIEnv * env, const char * err);
extern void setDebugEnabled(bool enable);
extern void printfDebug(const char *format, ...);

static inline void * safeGetBufferAddress(JNIEnv *env, jobject buffer, int offset) {
	if (buffer == NULL)
		return NULL;
	else
		return (void *)((char *)env->GetDirectBufferAddress(buffer) + offset);
}

static inline jobject safeNewBuffer(JNIEnv *env, void *p, int size) {
	if (p == NULL)
		return NULL;
	else
		return env->NewDirectByteBuffer(p, size);
}

static inline const void *offsetToPointer(jint offset) {
	return (const char *)NULL + offset;
}

typedef void *(* ExtGetProcAddressPROC) (const char *func_name);
typedef struct {
	char *method_name;
	char *signature;
	void *method_pointer;

	char *ext_function_name;
	void **ext_function_pointer;
} JavaMethodAndExtFunction;

#define NUMFUNCTIONS(x) (sizeof(x)/sizeof(JavaMethodAndExtFunction));

extern void doExtension(JNIEnv *env, jobject ext_set, const char *method_name, const char *ext);
extern jclass ext_ResetClass(JNIEnv *env, const char *class_name);
extern bool ext_InitializeClass(JNIEnv *env, jclass clazz, jobject ext_set, const char *ext_name, ExtGetProcAddressPROC gpa, int num_functions, JavaMethodAndExtFunction *functions);

#endif
