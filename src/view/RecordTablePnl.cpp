#include "RecordTablePnl.h"

#include <QSqlDatabase>
#include <QApplication>
#include <QScreen>
#include <QGridLayout>
#include <QLabel>

#include <QDebug>

RecordTablePnl::RecordTablePnl(quint16 height, qreal mult, QWidget *parent) : QWidget(parent)
{
	gBox = std::make_unique<QGridLayout>(this);
	setLayout(gBox.get());
	
	topSpaceLbl = std::make_unique<QLabel>(this);
	topSpaceLbl->setMinimumHeight(static_cast<qint32>(TOP_SPACE*mult));
	gBox->addWidget(topSpaceLbl.get(), 0, 0);
	gBox->setContentsMargins(static_cast<qint32>(MARIGN*mult), 0, 0, 0);
	
	qint8 i;
	for (i = 1; i < 12; i++)
	{
		QLabel *name = new QLabel;
		QLabel *point = new QLabel;
		
		names.append(name);
		points.append(point);
		
		name->setAlignment(Qt::AlignRight);
		point->setAlignment(Qt::AlignLeft);
		
		name->setText("0123456789:");
		point->setText("012345");
		
		QPalette palette;
		palette.setColor(QPalette::WindowText, Qt::yellow);
		name->setPalette(palette);
		point->setPalette(palette);
		
		QFont font = name->font();
		font.setPixelSize(static_cast<qint32>(BASE_FONT_SIZE*mult));
		name->setFont(font);
		point->setFont(font);
		
		gBox->addWidget(name, i, 0);
		gBox->addWidget(point, i, 1);
		
		gBox->setRowMinimumHeight(i, static_cast<qint32>(ROW_HEIGHT*mult));
	}
	
	bottomSpaceLbl = std::make_unique<QLabel>(this);
	bottomSpaceLbl->setMinimumHeight(static_cast<qint32>(BOTTOM_SPACE*mult));
	gBox->addWidget(bottomSpaceLbl.get(), i, 0);
	
	resize(static_cast<qint32>(WIDTH*mult), height);
	//qDebug() << WIDTH*mult;
	
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
}
