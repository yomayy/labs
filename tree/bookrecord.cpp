#include "bookrecord.h"

BookRecord::BookRecord(){

}

BookRecord::BookRecord(
        QString Id,
        QString Title,
        QString Author,
        QString Lang,
        QString Price,
        QString Year,
        QString Fav
      )
{
    this-> Title = Title;
    this-> Author= Author;
    this-> Lang= Lang;
    this-> Price= Price;
    this-> Year= Year;
    this-> Fav= Fav;
    this-> Id= Id;

}

