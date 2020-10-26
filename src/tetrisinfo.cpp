#include "TetrisInfo.h"

QPair<qint8, qint8> TetrisInfo::getCoord(qint16 cell)
{
	qint8 x = cell % COLUMN_COUNT;
	qint8 y = static_cast<qint8>(cell / COLUMN_COUNT);
	
	return {x, y};
}

qint16 TetrisInfo::getCell(QPair<qint8, qint8> coord)
{
	qint16 x = coord.first;
	qint16 y = coord.second;
	
	return y*COLUMN_COUNT + x;
}
