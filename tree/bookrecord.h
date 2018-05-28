#ifndef BOOKRECORD_H
#define BOOKRECORD_H
#include <QString>
#include <QDebug>

class BookRecord
{
public:
    BookRecord(
            QString Id,
            QString Title,
            QString Author,
            QString Lang,
            QString Price,
            QString Year,
            QString Fav
            );

    BookRecord();

    QString Title;
    QString Author;
    QString Lang;
    QString Price;
    QString Year;
    QString Fav;
    QString Id;

    void print(){
        qDebug() << "Title: " << Title << "\n";
        qDebug() << "Author: " << Author << "\n";
        qDebug() << "Lang: " << Lang << "\n";
        qDebug() << "Price: " << Price << "\n";
        qDebug() << "Year: " << Year << "\n";
        qDebug() << "Fav: " << Fav << "\n";
        qDebug() << "Id: " << Id << "\n";
        qDebug() << "";


    }
};

#endif // BOOKRECORD_H
