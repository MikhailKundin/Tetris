#ifndef TESTGRID_H
#define TESTGRID_H

#include <QWidget>
#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QPixmap>

class TestGrid : public QWidget
{
public:
	TestGrid(QWidget* parent = nullptr);
	
private:
	std::unique_ptr<QGridLayout> gBox;
	std::unique_ptr<QPixmap> block;
	std::unique_ptr<QLabel> label;
	std::unique_ptr<QLabel> label2;
};

#endif // TESTGRID_H
