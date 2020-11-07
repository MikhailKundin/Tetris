#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

class Database
{
public:
	Database(const QString &connectionName);
	QList<QPair<QString, quint32> > getRecords() const;
	void setRecord(const QString &name, const quint32 points) const;
	
private:
	QSqlDatabase m_db;
};

#endif // DATABASE_H
