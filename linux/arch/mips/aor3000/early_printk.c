/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2014 Aleksander Osman
 */

void prom_putchar(char c)
{
        volatile char *console_ptr = (volatile char *)0xBFFFFFFF;
        (*console_ptr) = c;
}
