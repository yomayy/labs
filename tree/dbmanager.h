#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <vector>
#include "bookrecord.h"

using namespace std;

class DbManager
{
public:

    DbManager(const QString& path);
    ~DbManager();

    bool isOpen() const;
    bool addBook(BookRecord rec);
    bool removeBook(const QString& id);
    bool bookExists(const QString& id) const;//existBook

    void setFav(QString id);

    void unsetFav(QString id);
    vector<BookRecord> bookSearch(BookRecord rec);
    //searchBook
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
