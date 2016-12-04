/* Copyright (c) 2002, Marek Michalkiewicz <marekm@amelek.gda.pl>
   Copyright (c) 2007, 2008 Eric B. Weddington
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. */

/* $Id$ */

#if (__GNUC__ < 3) || (__GNUC__ == 3 && __GNUC_MINOR__ < 3)
#error "GCC version >= 3.3 required"
#endif

#include <avr/io.h>
#include "ctoasm.inc"
#include "atmega328p.S"

	.section .init0,"ax",@progbits
	.weak	__init
;	.func	__init
__init:

#ifndef __AVR_ASM_ONLY__
	.weak	__stack

	/* By default, malloc() uses the current value of the stack pointer
	   minus __malloc_margin as the highest available address.

	   In some applications with external SRAM, the stack can be below
	   the data section (in the internal SRAM - faster), and __heap_end
	   should be set to the highest address available for malloc().  */
	.weak	__heap_end
	.set	__heap_end, 0

	.section .init2,"ax",@progbits
	clr	__zero_reg__
	out	AVR_STATUS_ADDR, __zero_reg__
	ldi	r28,lo8(__stack)
	ldi	r29,hi8(__stack)
	out	AVR_STACK_POINTER_HI_ADDR, r29
	out	AVR_STACK_POINTER_LO_ADDR, r28

	.set	__stack, RAMEND
#endif /* !__AVR_ASM_ONLY__ */

	.section .init9,"ax",@progbits
#ifdef __AVR_ASM_ONLY__
	JMP	main
#else	/* !__AVR_ASM_ONLY__ */
	CALL	main
	JMP	exit
#endif	/* __AVR_ASM_ONLY__ */
;	.endfunc

    .section .note.gnu.avr.deviceinfo, "", @note
#define NOTE_NAME "AVR"
#ifdef __AVR_DEVICE_NAME__
    #define DEVICE_NAME STR(__AVR_DEVICE_NAME__)
#else
    #define DEVICE_NAME ""
#endif

    .long .L__note_name_end - .L__note_name_start
    .long .L__desc_end - .L__desc_start
    .long 1 ; Type 1 - this is the only known note type for AVR.
.L__note_name_start:
    .asciz NOTE_NAME
    .balign 4
.L__note_name_end:
.L__desc_start:
#ifdef FLASHSTART
    .long FLASHSTART
#else
    .long 0
#endif
#ifdef PROGMEM_SIZE
    .long PROGMEM_SIZE
#elif FLASHEND > 0
    .long FLASHEND + 1
#else
    .long FLASHEND
#endif
    .long RAMSTART
#ifdef RAMSIZE
    .long RAMSIZE
#elif RAMEND > 0
    .long RAMEND - RAMSTART + 1
#else
    .long RAMEND
#endif
#ifdef E2START
    .long E2START
#else
    .long 0
#endif
#ifdef EEPROM_SIZE
    .long EEPROM_SIZE
#elif E2END > 0
    .long E2END + 1
#else
    .long E2END
#endif
    /* String offsets table.
    Index 0 - Size of offset table in bytes
    Index 1 - Device name byte offset
    */
.L__stroffsettab_start:
.long .L__stroffsettab_end - .L__stroffsettab_start /* Size of index table in bytes */
.long .L__device_name_start - .L__strtab_start /* Byte offset of device name */
.L__stroffsettab_end:
    /* String table for storing arbitrary strings.
    Offsets are stored in the string offset table above */
.L__strtab_start:
    .byte 0
.L__device_name_start:
    .byte 0
.L__device_name_end:
    .byte 0
.L__strtab_end:
.L__desc_end:
    .balign 4

