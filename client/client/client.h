#ifndef CLIENT_H
#define CLIENT_H

#include <QtGui/QDialog>
#include <QTcpSocket>
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QMessageBox>
#include <QString>
#include <QTextCodec>
#include "ui_client.h"

class Client : public QDialog
{
	Q_OBJECT

public:
	Client(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Client();

public slots:
	void start();
	void startTransfer();
	void updataProgress(qint64 num_bytes);
	void displayError(QAbstractSocket::SocketError socketError);
	void openFile();

private:
	Ui::ClientClass ui;

	QTcpSocket tcp_socket;
	quint64 total_btyes,
		bytes_written,
		bytes_to_write,
		load_size;
	QString file_name;
	QFile *local_file;
	QByteArray out_block;

};

#endif // CLIENT_H
