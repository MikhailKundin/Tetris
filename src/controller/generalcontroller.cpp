#include "generalcontroller.h"

#include <QRandomGenerator>
#include <QTime>

GeneralController::GeneralController(qint8 row, qint8 column) : ROW_COUNT(row), COLUMN_COUNT(column)
{
	IBlock = new QImage(":Images/Blocks/IBlockOriginal.png");
	OBlock = new QImage(":Images/Blocks/OBlockOriginal.png");
	TBlock = new QImage(":Images/Blocks/TBlockOriginal.png");
	LBlock = new QImage(":Images/Blocks/LBlockOriginal.png");
	JBlock = new QImage(":Images/Blocks/JBlockOriginal.png");
	SBlock = new QImage(":Images/Blocks/SBlockOriginal.png");
	ZBlock = new QImage(":Images/Blocks/ZBlockOriginal.png");
	
	random.seed(static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay()));
}

GeneralController::~GeneralController()
{
	delete IBlock;
	delete OBlock;
	delete TBlock;
	delete LBlock;
	delete JBlock;
	delete SBlock;
	delete ZBlock;
}

void GeneralController::moveRight()
{
	if (figure->moveRight())
	{
		emit moveRightSignal();
		emit update();
	}
}

void GeneralController::moveLeft()
{
	if (figure->moveLeft())
	{
		emit moveLeftSignal();
		emit update();
	}
}

void GeneralController::rotate()
{
	if (figure->rotate())
	{
		emit rotateSignal();
		emit update();
	}
}

void GeneralController::moveDown()
{
	if (figure->moveDown())
	{
		emit moveDownSignal();
		emit update();
	}
}

void GeneralController::tick()
{
	
}

void GeneralController::getNextFigure()
{
	qint8 value = random.generate() % 7;
	switch (value)
	{
	case 0:
		nextFigure = new IFigure(ROW_COUNT, COLUMN_COUNT, IBlock);
		break;
	case 1:
		nextFigure = new OFigure(ROW_COUNT, COLUMN_COUNT, OBlock);
		break;
	case 2:
		nextFigure = new TFigure(ROW_COUNT, COLUMN_COUNT, TBlock);
		break;
	case 3:
		nextFigure = new LFigure(ROW_COUNT, COLUMN_COUNT, LBlock);
		break;
	case 4:
		nextFigure = new JFigure(ROW_COUNT, COLUMN_COUNT, JBlock);
		break;
	case 5:
		nextFigure = new SFigure(ROW_COUNT, COLUMN_COUNT, SBlock);
		break;
	case 6:
		nextFigure = new ZFigure(ROW_COUNT, COLUMN_COUNT, ZBlock);
		break;
	}
}
