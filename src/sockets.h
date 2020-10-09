#ifndef SOCKETS_H
#define SOCKETS_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTcpSocket>

class Sockets : public QWidget
{
	Q_OBJECT
	
public:
	Sockets(QWidget* parent = nullptr);
	
private slots:
	void setServerBtnPush();
	void setClientBtnPush();
	void connectBtnPush();
	void sendMessageBtnPush();
	
	void readMessage();
	
	void socketStateChanged();
	
private:
	void consoleAdd(const QString& str) const;
	
	std::unique_ptr<QHBoxLayout> hBox;
	std::unique_ptr<QVBoxLayout> vBox;
	
	std::unique_ptr<QPushButton> setServerBtn;
	std::unique_ptr<QPushButton> setClientBtn;
	std::unique_ptr<QPushButton> connectBtn;
	std::unique_ptr<QPushButton> sendMessageBtn;
	
	std::unique_ptr<QTextEdit> console;
	
	std::unique_ptr<QTcpSocket> socket;
};

#endif // SOCKETS_H
