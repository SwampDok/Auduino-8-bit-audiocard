# -*- coding: utf-8 -*-
"""
Created on Tue Dec 17 18:07:46 2019

@author: Swamp_Dok
"""

import wave
import struct
import numpy as np

types = {
    1: np.uint8,
    2: np.int16,
    4: np.int32
}

in_file = "sharm_22050hz.wav"

# Выбираем файл для воспроизведения
wav = wave.open("sharm_22050hz.wav", mode="r")

#число каналов, число байт на сэмпл, число фреймов в секунду (частота дискретизации), общее число фреймов, тип сжатия, имя типа сжатия
(nchannels, sampwidth, framerate, nframes, comptype, compname) = wav.getparams()

print ('Параметры файла ' + str(in_file))
print ('Частота дискретизации:' + str(framerate))
print ('Число каналов:' + str(nchannels))
print ('Количество фреймов :' + str(nframes))
print ('Число байт на сэмпл' + str(sampwidth))


# Считаем все фреймы 
# Фрейм включает семплы левого и правого канала
content = wav.readframes(nframes)

# Закрываем открытый для чтения файл
wav.close()

# формуирует массив сэмплов из непрерывного файла по размеру сэмпла
samples = np.fromstring(content, dtype=types[sampwidth])

# Выделяем один канал из общего числа сэмплов
# Сэмплы каналов идут через один
if sampwidth != 1:
    for n in range(nchannels):
        channel = samples[n+1::nchannels]
else:
    channel = samples
    

# Создаем файл с одним каналов из базового файла
obj = wave.open('sound.wav','wb')

obj.setnchannels(1) # mono
obj.setsampwidth(1) # 8бит сэмпл
obj.setframerate(framerate) # Задаем частоту дискретизации

#Выделяем память для хранения преобразованого файла
a_out = np.zeros(nframes, dtype = np.uint8)

# Определение максимального значения сэмпла по разрядности
max_value = (2**(sampwidth*8) - 1)
print ('Максимальное значение сэмпла при выбранной разрядности' + str(max_value))


# 8-битные сэпмплы беззнаковые, а все прочие знаковые
# Это нужно иметь в виду
for i in range(nframes - 1):
    # нормализация и перевод к виду 8 бит без знака
    #Для фосьмибитных файлов
    if sampwidth == 1:
        a_out[i] =  (channel[i]/max_value) * 255
    #Для прочих разрядностей
    else:
        a_out[i] =  ((channel[i]+ max_value/2 )/max_value) * 255


print ("Минимальное значение сэмпла выходного файла" + str(a_out.min()))
print ("Максимальный значение сэмпла выходного файла" + str(a_out.max()))

for i in range(nframes):
    # Формируем фрейм
   data = struct.pack('<B', a_out[i])
   # Записываем фрейм
   obj.writeframesraw( data )

# Закрываем итоговый файл
obj.close()
