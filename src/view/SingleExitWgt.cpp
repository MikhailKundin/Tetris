#include "SingleExitWgt.h"
#include "ui_SingleExitWgt.h"

#include "PushLabel.h"

SingleExitWgt::SingleExitWgt(QPair<QPixmap *, QPixmap *> buttonImg, qreal mult, QWidget *parent) :
	QWidget(parent), ui(new Ui::SingleExitWgt), MULT(mult)
{
	ui->setupUi(this);
	
	setVisible(false);
	setLayout(ui->gridLayout);
	ui->verticalLayout->setSpacing((static_cast<qint32>(BASE_HEIGHT*MULT) - ELEMENT_HEIGHT*2) / 2);
	
	ELEMENT_HEIGHT = static_cast<quint16>(BASE_ELEMENT_HEIGHT*MULT);
	ELEMENT_WIDTH = static_cast<quint16>(BASE_ELEMENT_WIDTH*MULT);
	BORDER = static_cast<quint16>(BASE_BORDER*MULT);
	
	restartBtn = std::make_unique<PushLabel>("Перезапустить", this);
	exitBtn = std::make_unique<PushLabel>("В главное меню", this);
	
	restartBtn->loadPixmaps(buttonImg.first, buttonImg.second);
	exitBtn->loadPixmaps(buttonImg.first, buttonImg.second);
	
	restartBtn->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	exitBtn->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	
	ui->verticalLayout->setMargin(BORDER);
	ui->verticalLayout->addWidget(restartBtn.get());
	ui->verticalLayout->addWidget(exitBtn.get());
	
	QFont font = restartBtn->font();
	font.setPixelSize(static_cast<quint8>(BASE_FONT*MULT));
	restartBtn->setFont(font);
	exitBtn->setFont(font);
	
	QPalette btnPal;
	btnPal.setColor(QPalette::WindowText, Qt::yellow);
	restartBtn->setPalette(btnPal);
	exitBtn->setPalette(btnPal);
	
	ui->gridLayout->addWidget(ui->back, 1, 1);
	ui->back->resize(static_cast<qint32>(BASE_WEIGHT*MULT), static_cast<qint32>(BASE_HEIGHT*MULT));
	QPixmap img(":/Images/Backgrounds/200x200PanelBackground.png");
	ui->back->setPixmap(img.scaled(ui->back->size()));
	
	QPalette pal(palette());
	QColor col;
	col.setRgb(0, 0, 0, 200);
	pal.setColor(QPalette::Background, col);
	setAutoFillBackground(true);
	setPalette(pal);
	
	connect(restartBtn.get(), &PushLabel::clicked, this, &SingleExitWgt::restartBtnPush);
	connect(exitBtn.get(), &PushLabel::clicked, this, &SingleExitWgt::exitBtnPush);
}

SingleExitWgt::~SingleExitWgt()
{
	delete ui;
}

void SingleExitWgt::activate(bool state)
{
	setVisible(state);
}

void SingleExitWgt::restartBtnPush()
{
	setVisible(false);
	emit restartSignal();
}

void SingleExitWgt::exitBtnPush()
{
	setVisible(false);
	emit exitSignal();
}
