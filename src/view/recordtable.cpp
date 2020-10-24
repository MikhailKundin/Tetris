#include "recordtable.h"

#include <QDebug>

RecordTable::RecordTable(QSize s, QWidget *parent) : QWidget(parent)
{	
	gBox = std::make_unique<QGridLayout>(this);
	setLayout(gBox.get());
	
	topSpaceLbl = std::make_unique<QLabel>(this);
	topSpaceLbl->setMinimumHeight(TOP_SPACE);
	gBox->addWidget(topSpaceLbl.get(), 0, 0);
	
	qint8 i;
	for (i = 1; i < 12; i++)
	{
		QLabel *name = new QLabel;
		QLabel *point = new QLabel;
		
		names.append(name);
		points.append(point);
		
		gBox->addWidget(name, i, 0);
		gBox->addWidget(point, i, 1);
		
		name->setAlignment(Qt::AlignRight);
		point->setAlignment(Qt::AlignLeft);
		
		name->setText("Test" + QString::number(i) + ":");
		point->setText("00000");
		
		QPalette palette;
		palette.setColor(QPalette::WindowText, Qt::yellow);
		name->setPalette(palette);
		point->setPalette(palette);
		
		QFont font = name->font();
		font.setPixelSize(14);
		name->setFont(font);
		point->setFont(font);
		
		gBox->setRowMinimumHeight(i, CELL_HEIGHT);
	}
	
	bottomSpaceLbl = std::make_unique<QLabel>(this);
	bottomSpaceLbl->setMinimumHeight(BOTTOM_SPACE);
	gBox->addWidget(bottomSpaceLbl.get(), i, 0);
	
	resize(s);
	
	backLbl = std::make_unique<QLabel>(this);
	backLbl->move(0, 0);
	backLbl->resize(s.width(), height());
	QPixmap border(":Images/Backgrounds/RecordTableBackground.png");
	backLbl->setPixmap(border.scaled(backLbl->size()));
}

RecordTable::~RecordTable()
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
