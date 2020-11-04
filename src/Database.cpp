#include "Database.h"

#include <QSqlQuery>

#include <QDebug>

Database::Database()
{
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName("Tetris.sqlite");
	m_db.open();
}

QList<QPair<QString, quint32> > Database::getRecords() const
{
	QSqlQuery query(m_db);
	query.prepare("SELECT Name, Points "
				  "FROM RecordTable "
				  "WHERE Name != '' "
				  "ORDER BY Points DESC "
				  "LIMIT 10");
	query.exec();
	
	QList<QPair<QString, quint32> > records;
	while (query.next())
	{
		QString name = query.value(0).toString();
		quint32 points = query.value(1).toUInt();
		records.append({name, points});
	}
	
	return records;
}

void Database::setRecord(const QString &name, const quint32 points) const
{
	QSqlQuery query(m_db);
	query.prepare("INSERT INTO RecordTable (Name, Points, Date) "
				  "VALUES (:name, :points, datetime('now'))");
	query.bindValue(":name", name);
	query.bindValue(":points", points);
	query.exec();
}
