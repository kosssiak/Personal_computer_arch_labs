#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <iostream.h>

int frequencies[] = { 196, 261, 329, 196, 261, 329, 196, 261, 329 };		// Частоты по варианту

int duration[] = { 400, 400, 400, 400, 400, 400, 400, 400, 400 };		// Продолжительность по варианту	

void sound(int frequency, int time) { 						// Звук одной ноты
    int cnt;

    outp(0x43, 0xb6); 								// В порт 43h (управляющий регистр таймера) заносим значение команды 10110110
    										// номер канала - (2)канал, тип операции - 11 ч/з младшего, затем старшего, режим - 3 генератор прямол
    cnt = (int)(1193180L / frequency);						// Делим импульс генератора сигналов на импульс нашей частоты
    outp(0x42, cnt & 0x00ff);							// Вводим в 42 порт((2) канал) значение cnt сначала младшие биты
    outp(0x42, (cnt & 0xff00) >> 8);						// Затем старшие биты

    outp(0x61, inp(0x61) | 3);							// Включаем звук (последние два бита устанавливаем в 1)

    delay(time);								// Задержка на время которое передали

    outp(0x61, inp(0x61) & 0xfc);						//Выключаем звук (два младших бита в ноль)

}


void stateChannel() {
    unsigned int temp, del, dellow, delhigh;
    char* string = new char[9];
    unsigned i;

    outp(0x43, 0xe2);								// В порт 43 заносим команда 11100010 (11, 1 - не фиксировать счётчик, 0 - получить состояние канала, 
										// 001 - значение (0)канала, 0)
    temp = inp(0x40); 								// Получение слова состояния (0) канала из его порта 40h
    itoa(temp, string, 2);							// Перевод числа temp в двоичную и запись в string
    cout << "0 channel state word: " << string << endl;

    outp(0x43, 0x06);								// Фиксация (блокировка)
    outp(0x43, 0x36);								// 00 - канал, 11 - чтение и запись, 011 3 режим, 0 двоичный
    dellow = inp(0x40);								// Чтение младшего СЕ
    delhigh = inp(0x40);							// Старшего
    del = delhigh * 256 + dellow;
    itoa(del, string, 16);							// Перевод в 16-ичную
    cout << "delim 0:   " << string << endl;
	

    outp(0x43, 0xe4);								// 11100100

    temp = inp(0x41);
    itoa(temp, string, 2);
    cout << "1 channel state word: " << string << endl;


    outp(0x43, 0x46);
    outp(0x43, 0x76);
    dellow = inp(0x41);
    delhigh = inp(0x41);
    del = delhigh * 256 + dellow;
    itoa(del, string, 16);
    cout << "delim 1:  " << string << endl;


    outp(0x43, 0xe8);								//11101000

    temp = inp(0x42);
    itoa(temp, string, 2);
    cout << "2 channel state word: " << string << endl;

    outp(0x43, 0x86);
    outp(0x43, 0xb6);
    dellow = inp(0x42);
    delhigh = inp(0x42);
    del = delhigh * 256 + dellow;
    itoa(del, string, 16);
    cout << "delim 2:   " << string << endl;

    free(string);
}

int main() {
    for (int i = 0; i < 9; i++)
    {
        sound(frequencies[i], duration[i]);
    }
    stateChannel();								// Вывод слова состояния каждого канала в двоичной форме и вывод значения
    return 0;
}
