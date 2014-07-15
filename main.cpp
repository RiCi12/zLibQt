#include <QCoreApplication>
#include <zlib.h>
#include <QFile>
#include <QDir>
#include <QByteArray>

void zip(QString filename, QString zipfilename);
void unzip(QString zipfilename, QString filename);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    zip("file1", "zipdestinationfile");
    unzip("zipsourcefile", "unzipdestinationfile");

    return a.exec();
}

void zip(QString filename, QString zipfilename) {



    QFile input1(filename);
    QFile input2(zipfilename);
    QFile output(zipfilename);
    input1.open(QFile::ReadOnly);
    input2.open(QFile::ReadOnly);
    output.open(QFile::WriteOnly);
    QByteArray uncompresed(input1.readAll());
    uncompresed.append("§");
    uncompresed.append(input2.readAll());
    QByteArray compressed = qCompress(uncompresed);
    output.write(compressed);
    input1.close();
    input2.close();
    output.close();
}

void unzip(QString zipfilename, QString filename) {
    QFile input(zipfilename);
    QFile output1(zipfilename);
    QFile output2(filename);
    input.open(QFile::ReadOnly);
    output1.open(QFile::WriteOnly);
    output2.open(QFile::WriteOnly);
    QByteArray compresed(input.readAll());
    QByteArray uncompresed = qUncompress(compresed);
    char* sep = "§";
    QList<QByteArray> uncompresedList = uncompresed.split(*sep);
    output1.write(uncompresedList.at(0));
    output2.write(uncompresedList.at(1));
    input.close();
    output1.close();
    output2.close();
}
