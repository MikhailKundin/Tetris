#include "RecordTablePnl.h"

#include <QGridLayout>
#include <QLabel>

RecordTablePnl::RecordTablePnl(quint16 height, qreal mult, QWidget *parent) : QWidget(parent), MULT(mult)
{
	gBox = std::make_unique<QGridLayout>(this);
	setLayout(gBox.get());
	
	topSpaceLbl = std::make_unique<QLabel>(this);
	topSpaceLbl->setMinimumHeight(static_cast<qint32>(TOP_SPACE*mult));
	gBox->addWidget(topSpaceLbl.get(), 0, 0);
	gBox->setContentsMargins(static_cast<qint32>(MARIGN*mult), 0, 0, 0);
	
	db = new Database(DB_NAME);
	
	QList<QPair<QString, quint32> > records = db->getRecords();
	for (quint8 i = 1; i < 12; i++)
	{
		QLabel *name = new QLabel;
		QLabel *point = new QLabel;
		
		names.append(name);
		points.append(point);
		
		name->setAlignment(Qt::AlignRight);
		point->setAlignment(Qt::AlignLeft);
		
		if (i <= records.length())
		{
			name->setText(records.at(i-1).first);
			point->setText(QString::number(records.at(i-1).second));
		}
		
		QPalette palette;
		if (i > records.length())
		{
			palette.setColor(QPalette::WindowText, Qt::red);
		}
		else
		{
			palette.setColor(QPalette::WindowText, Qt::yellow);
		}
		name->setPalette(palette);
		point->setPalette(palette);
		
		QFont font("Segoe Print", -1, QFont::Bold);
		font.setPixelSize(static_cast<qint32>(BASE_FONT_SIZE*MULT));
		name->setFont(font);
		point->setFont(font);
		
		gBox->addWidget(name, i, 0);
		gBox->addWidget(point, i, 1);
		
		gBox->setRowMinimumHeight(i, static_cast<qint32>(ROW_HEIGHT*MULT));
	}
	
	names.at(place)->setText("Вы");
	points.at(place)->setText("0");
	
	bottomSpaceLbl = std::make_unique<QLabel>(this);
	bottomSpaceLbl->setMinimumHeight(static_cast<qint32>(BOTTOM_SPACE*mult));
	gBox->addWidget(bottomSpaceLbl.get(), 12, 0);
	
	resize(static_cast<qint32>(WIDTH*mult), height);

	
	backLbl = std::make_unique<QLabel>(this);
	backLbl->move(0, 0);
	backLbl->resize(size());
	QPixmap border(":Images/Backgrounds/RecordTableBackground.png");
	backLbl->setPixmap(border.scaled(backLbl->size()));
}

RecordTablePnl::~RecordTablePnl()
{
	foreach(QLabel *name, names)
	{
		delete name;
	}
	foreach(QLabel *point, points)
	{
		delete point;
	}
	
	delete db;
	QSqlDatabase::removeDatabase(DB_NAME);
}

void RecordTablePnl::updateRecordTable(quint32 newPoints)
{
	points.at(place)->setText(QString::number(newPoints));
	if (place > 0)
	{
		while (newPoints > points.at(place-1)->text().toUInt())
		{
			QString name = names.at(place-1)->text();
			QString point = points.at(place-1)->text();
			
			names.at(place-1)->setText(names.at(place)->text());
			points.at(place-1)->setText(points.at(place)->text());
			names.at(place)->setText(name);
			points.at(place)->setText(point);
			
			QPalette palette;
			palette.setColor(QPalette::WindowText, Qt::red);
			names.at(place-1)->setPalette(palette);
			points.at(place-1)->setPalette(palette);
			
			palette.setColor(QPalette::WindowText, Qt::yellow);
			names.at(place)->setPalette(palette);
			points.at(place)->setPalette(palette);
			
			place--;
			if (place <= 0)
			{
				break;
			}
		}
	}
}

void RecordTablePnl::saveResult(const QString &name)
{
	db->setRecord(name, points.at(place)->text().toUInt());
}

quint8 RecordTablePnl::getPlace() const
{
	return place;
}

void RecordTablePnl::restart()
{
	place = 10;
	QList<QPair<QString, quint32> > records = db->getRecords();
	for (quint8 i = 0; i < 10; i++)
	{
		QLabel *name = names.at(i);
		QLabel *point = points.at(i);
		name->setText(records.at(i).first);
		point->setText(QString::number(records.at(i).second));
		QPalette palette;
		palette.setColor(QPalette::WindowText, Qt::yellow);
		name->setPalette(palette);
		point->setPalette(palette);
	}
	QLabel *name = names.at(10);
	QLabel *point = points.at(10);
	name->setText("Вы");
	point->setText("0");
	QPalette palette;
	palette.setColor(QPalette::WindowText, Qt::red);
	name->setPalette(palette);
	point->setPalette(palette);
}
