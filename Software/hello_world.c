/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "altera_up_avalon_character_lcd.h"
#include "timer.h"
#include "vga.h"
#include "io.h"
#include "Excercises/excercise2.h"

#define switches (volatile char *) 0x1001060
#define leds (char *) 0x1001070

int main()
{
	alt_up_character_lcd_dev * char_lcd_dev;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");//("/dev/Char_LCD_16x2");
	if ( char_lcd_dev == NULL)
		printf ("Error: could not open character LCD device\n");
	else
		printf ("Opened character LCD device\n");
	/* Initialize the character display */
	alt_up_character_lcd_init (char_lcd_dev);
	/* Write "Welcome to" in the first row */
	alt_up_character_lcd_string(char_lcd_dev, "Welcome to");
	/* Write "the DE2 board" in the second row */
	char second_row[] = "the DE2 board\0";
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, second_row);

	printf("hello, world!\n");
	alt_up_pixel_buffer_dma_dev* pixel_buffer = setUp();
	clearScreen(pixel_buffer);
	drawLine(pixel_buffer, 64, 0, 64, 240, 0xFFFF);
	drawLine(pixel_buffer, 64, 0, 320, 240, 0xFFFF);
	drawLine(pixel_buffer, 64, 240, 320, 0, 0xFFFF);
	drawBox(pixel_buffer, 10, 90, 54, 150, 0xFFFF);
	printLine();

	char keys;
	setHardwareTimerPeriod(5 * CLOCK_FREQ);
	startHardwareTimer();

	while (1)
	{
		if (hasHardwareTimerExpired() == 1)
		{
			printf("Timer has expired\n");
		}
	}

	while (1)
	{
		keys = IORD_8DIRECT(0x1001080, 0);
		IOWR_8DIRECT(0x1001070, 0, keys);
	}

	timer_test();
	timeMatrixMultiply();

	return 0;
}
