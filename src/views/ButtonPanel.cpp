#include "ButtonPanel.h"
#include "ui_ButtonPanel.h"

#include <QLabel>
#include <QSpacerItem>
#include <QSoundEffect>

#include "PushLabel.h"

ButtonPanel::ButtonPanel(QString info, QList<QString> buttons, 
						 QPair<QHash<QString, QPixmap *>, QHash<QString, QSoundEffect *> > media, 
						 qreal mult, QWidget *parent) :
	QWidget(parent), ui(new Ui::ButtonPanel), MULT(mult)
{
	ui->setupUi(this);
	
	infoLbl = std::make_unique<QLabel>(info, this);
	
	QFont font("Segoe Print", -1, QFont::Bold);
	font.setPixelSize(static_cast<quint8>(BASE_FONT*MULT));
	infoLbl->setFont(font);
	
	QPalette btnPal;
	btnPal.setColor(QPalette::WindowText, Qt::yellow);
	infoLbl->setPalette(btnPal);
	
	infoLbl->setAlignment(Qt::AlignCenter);
	infoLbl->setWordWrap(true);
	infoLbl->setFixedWidth(static_cast<qint32>(BASE_ELEMENT_WIDTH*MULT));
	ui->verticalLayout->addWidget(infoLbl.get());
	
	spacer = std::make_unique<QSpacerItem>(1, static_cast<qint32>(BASE_SPACE*MULT));
	ui->verticalLayout->addSpacerItem(spacer.get());
	
	buildPanel(buttons, media.first, media.second);
}

ButtonPanel::ButtonPanel(QList<QString> buttons, 
						 QPair<QHash<QString, QPixmap *>, QHash<QString, QSoundEffect *> > media, 
						 qreal mult, QWidget *parent) :
	QWidget(parent), ui(new Ui::ButtonPanel), MULT(mult)
{
	ui->setupUi(this);
	
	buildPanel(buttons, media.first, media.second);
}

ButtonPanel::~ButtonPanel()
{
	ui->verticalLayout->removeItem(spacer.get());
	foreach (PushLabel *button, m_buttons)
	{
		button->deleteLater();
	}
	delete ui;
}

void ButtonPanel::buildPanel(QList<QString> buttons, QHash<QString, QPixmap *> pixmaps,
							 QHash<QString, QSoundEffect *> sounds)
{
	ELEMENT_HEIGHT = static_cast<quint16>(BASE_ELEMENT_HEIGHT*MULT);
	ELEMENT_WIDTH = static_cast<quint16>(BASE_ELEMENT_WIDTH*MULT);
	BORDER = static_cast<quint16>(BASE_BORDER*MULT);
	
	setLayout(ui->gridLayout);
	ui->verticalLayout->setContentsMargins(BORDER, BORDER, BORDER, BORDER*2);
	
	QPalette pal(palette());
	QColor col;
	col.setRgb(0, 0, 0, 200);
	pal.setColor(QPalette::Window, col);
	setAutoFillBackground(true);
	setPalette(pal);
	
	foreach (QString button, buttons)
	{
		PushLabel *pushLabel = new PushLabel(button, this);
		pushLabel->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
		pushLabel->loadPixmaps(pixmaps["enter"], pixmaps["leave"]);
		pushLabel->loadSounds(sounds["enterSound"]);
		
		QFont font("Segoe Print", -1, QFont::Bold);
		font.setPixelSize(static_cast<quint8>(BASE_FONT*MULT));
		pushLabel->setFont(font);
		pushLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
		
		QPalette pal;
		pal.setColor(QPalette::WindowText, Qt::yellow);
		pushLabel->setPalette(pal);
		
		ui->verticalLayout->addWidget(pushLabel, 0, Qt::AlignCenter);
		
		connect(pushLabel, &PushLabel::clicked, this, &ButtonPanel::buttonClicked);
		m_buttons.append(pushLabel);
	}
	
	ui->back->setFixedSize(ui->verticalLayout->totalMinimumSize());
	ui->back->setPixmap((*pixmaps["back"]).scaled(ui->back->size()));
	ui->gridLayout->addWidget(ui->back, 1, 1);
}

void ButtonPanel::buttonClicked()
{
	emit clicked(qobject_cast<PushLabel *>(sender())->objectName());
}
