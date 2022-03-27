/*
 * lcd.h
 *
 *  Author: Rümeysa Yavuz
 */ 


#ifndef LCD_H_
#define LCD_H_

void lcd_init(void);
void lcd_display_text(char *str);
void lcd_set_cursor(int position);

#endif /* LCD_H_ */