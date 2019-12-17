#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QFile>
#include <QString>

#include <iostream>

using namespace std;

#define PORT "COM6"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QSerialPort serial (PORT);

  // Настраиваем порт
  serial.setBaudRate (250000); // Скорость
  serial.setDataBits (QSerialPort::Data8); // Длина посылки в битах
  serial.setStopBits (QSerialPort::OneStop); // Количество стоп-бит
  serial.setPortName (PORT); // Номер ком-порта
  serial.setReadBufferSize(0); // Размер буфера чтения

  if (!serial.open(QSerialPort::ReadWrite)) {
    cout << "Port not opened";
    return 0;
  } else {
    cout << "Port opened!";
  }

  // Открываем файл
  QFile file ("sound.wav");
  if (file.open(QFile::ReadWrite))
      cout << "File opened" << endl;
  else {
      cout << "File d'not opened" << endl;
      return a.exec();
  }

  // Считываем файл в ОЗУ
  QByteArray data = file.readAll (), buf, data_in;

  cout << "Size file "  << data.size () << " Bytes" << endl;

  for (int i = 0; i < data.size (); ++i) {
    buf.append (data.at (i));

    // Формируем пакеты по 3000 сэмплов и загружаем их в буфер отправки
    if (buf.size () == 3000) {
        serial.write (buf);
        // Ожидаем завершения отправки данных
        serial.waitForBytesWritten ();
        buf.clear ();
    }
  }

  serial.close ();

  cout << "Writed" << endl;

  return a.exec();
}

