#include <dbmanager.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}


bool DbManager::addBook(BookRecord rec)
        //const QString& Title, const QString& Author, const QString& Lang, const QString& Price, const QString& Year)
{
    bool success = false;

        QSqlQuery queryAdd;

        queryAdd.prepare("INSERT INTO kursovaya (Title, Author, Lang, Price, Year, FAV) VALUES (:title, :author, :lang, :price, :year, 0)");

        queryAdd.bindValue(":title", rec.Title);
        queryAdd.bindValue(":author", rec.Author);
        queryAdd.bindValue(":lang", rec.Lang);
        queryAdd.bindValue(":price", rec.Price);
        queryAdd.bindValue(":year", rec.Year);

        if(queryAdd.exec() == true)
        {
            success = true;
        }
        else
        {
            qDebug() << "add person failed: " << queryAdd.lastError();
        }


    return success;
}

bool DbManager::removeBook(const QString& id)
{
    bool success = false;

    if (bookExists(id) == true)
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM kursovaya WHERE ID = (:ID)");
        queryDelete.bindValue(":ID", id);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove book failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove book failed: book doesnt exist";
    }

    return success;
}


bool DbManager::bookExists(const QString& id) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT ID FROM kursovaya WHERE ID = (:ID)");
    checkQuery.bindValue(":ID", id);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "book exists failed: " << checkQuery.lastError();
    }

    return exists;
}


vector<BookRecord> DbManager::bookSearch(BookRecord rec){

    vector<BookRecord> recs;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM kursovaya WHERE Title LIKE :title AND Author LIKE :author AND Lang LIKE :lang AND Price LIKE :price AND Year LIKE :year AND Fav LIKE :fav");
    checkQuery.bindValue(":title", rec.Title);
    checkQuery.bindValue(":author", rec.Author);
    checkQuery.bindValue(":lang", rec.Lang);
    checkQuery.bindValue(":price", rec.Price);
    checkQuery.bindValue(":year", rec.Year);
    checkQuery.bindValue(":fav", rec.Fav);



    checkQuery.exec();


        while(checkQuery.next()){
            QString id = checkQuery.value(0).toString();
            QString title = checkQuery.value(1).toString();
            QString author = checkQuery.value(2).toString();
            QString lang = checkQuery.value(3).toString();
            QString price = checkQuery.value(4).toString();
            QString year = checkQuery.value(5).toString();
            QString fav = checkQuery.value(6).toString();




            BookRecord rec(id, title, author, lang, price, year, fav);

            recs.push_back(rec);
        }


    return recs;
}

void DbManager::setFav(QString id){

    bool success = false;

    if (bookExists(id) == true)
    {
        QSqlQuery query;
        query.prepare("UPDATE kursovaya SET FAV = 1 WHERE ID = :ID");
        query.bindValue(":ID", id);
         success = query.exec();

         if(!success)
             qDebug() << "setfav book failed: " << query.lastError();

    } else qDebug() << "setfav book failed: book doesnt exist";




}
void DbManager::unsetFav(QString id){

     bool success = false;

    if (bookExists(id) == true)
    {
        QSqlQuery query;
        query.prepare("UPDATE kursovaya SET FAV = 0 WHERE ID = :ID");
        query.bindValue(":ID", id);
         success = query.exec();

         if(!success)
             qDebug() << "unsetfav book failed: " << query.lastError();

    } else qDebug() << "unsetfav book failed: book doesnt exist";



}


