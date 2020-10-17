#include "testgrid.h"

#include <QDebug>
#include <QFile>

#include "testpaint.h"

TestGrid::TestGrid(QWidget *parent) : QWidget(parent)
{
	gBox = std::make_unique<QGridLayout>(this);
	setLayout(gBox.get());
	
	block = std::make_unique<QPixmap>("..\\..\\etc\\Images\\Blocks\\Original\\LBlockOriginal.png");
	label = std::make_unique<QLabel>(this);
	//label->setPixmap(*block.get());
	//label->resize(block->size());
	
	label2 = std::make_unique<QLabel>(this);
	//label2->setPixmap(*block.get());
	//label2->resize(block->size());
	
	//gBox->addWidget(label.get(), 0, 1);
	//gBox->addWidget(label2.get(), 0, 2);
	gBox->addWidget(new TestPaint(this), 0, 1);
	gBox->addWidget(new TestPaint(this), 0, 2);
	
	gBox->setColumnStretch(0, 1);
	gBox->setColumnStretch(3, 1);
}
