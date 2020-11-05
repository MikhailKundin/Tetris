#ifndef TETRISINFO_H
#define TETRISINFO_H

#include <QObject>

class TetrisInfo
{
public:
	static QPair<qint8, qint8> getCoord(qint16 cell);
	static qint16 getCell(QPair<qint8, qint8> coord);
	
	enum  Figures : quint8 {I, O, T, L, J, S, Z};
	
	static const quint8 ROW_COUNT = 20;
	static const quint8 COLUMN_COUNT = 10;
};

#endif // TETRISINFO_H
