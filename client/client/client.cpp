#include "client.h"

Client::Client(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	QTextCodec::setCodecForTr( QTextCodec::codecForName("gb2312"));

	connect(&tcp_socket, SIGNAL(connected()), this, SLOT(startTransfer())) ;
	connect(&tcp_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(updataProgress(qint64))) ;
	connect(&tcp_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError socketError)));

	total_btyes = bytes_written = bytes_to_write = 0;
	load_size = 4 * 1024; //设置每次发送4KB大小
	ui.pushButtonSend->setEnabled(false);
}

Client::~Client()
{

}

void Client::start()
{
	ui.pushButtonSend->setEnabled(false);
	QApplication::setOverrideCursor(Qt::WaitCursor) ;
	bytes_written = 0;
	ui.label->setText(tr("连接中"));
	tcp_socket.connectToHost(QHostAddress::LocalHost, 16689);
}

void Client::startTransfer()
{
	local_file = new QFile(file_name);

	if (!local_file->open(QFile::ReadOnly )) 
	{
		QMessageBox::warning(this, tr("应用程序"),
			tr("无法读取文件 %1:\n%2.")
			.arg(file_name)
			.arg(local_file->errorString()));
		return;
	}

	//将待发送文件的大小暂存于total_btyes中
	total_btyes = local_file->size();
	QDataStream out(&out_block, QIODevice::WriteOnly) ;
	out.setVersion(QDataStream::Qt_4_3) ;

	//这一步目的是获取文件名的大小（不能通过currrent_file.size()函数获取），并将文件名先写入
	QString currrent_file = file_name.right(file_name.size() - file_name.lastIndexOf('/') -1) ;
	out << qint64(0) << qint64(0) << currrent_file;
	total_btyes += out_block.size();

	//重头开始操作写
	out.device()->seek(0);
	//写入总长度和文件名长度 (文件名已经在前面被写进去了）
	out << total_btyes << qint64((out_block.size()-sizeof(qint64)*2)) ;
	ui.progressBar->setMaximum(total_btyes) ;

	//发送协议文件头
	bytes_to_write = total_btyes - tcp_socket.write(out_block);

	ui.label->setText(tr("已连接")) ;

	out_block.resize(0);
}

void Client::updataProgress(qint64 num_bytes)
{
	bytes_written += (int)num_bytes;

	if(bytes_to_write > 0)
	{
		//尽量每次发送4kb（load_size)
		out_block = local_file->read(qMin(bytes_to_write, load_size));
		bytes_to_write -= (int)tcp_socket.write(out_block);
		out_block.resize(0) ;
	}
	else
	{
		local_file->close();
		QApplication::restoreOverrideCursor();
	}

	ui.progressBar->setValue(bytes_written);
	ui.label->setText(tr("已发送 %1MB").arg(bytes_written / (1024 * 1024)));
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
	if (socketError == QTcpSocket::RemoteHostClosedError)
		return;

	QMessageBox::information(this, tr("网络"),
		tr("产生如下错误: %1.")
		.arg(tcp_socket.errorString()));

	tcp_socket.close();
	ui.progressBar->reset();
	ui.label->setText(tr("客户端就绪"));
	ui.pushButtonSend->setEnabled(true);
	QApplication::restoreOverrideCursor();
}

void Client::openFile()
{
	file_name = QFileDialog::getOpenFileName(this);
	if(!file_name.isEmpty())
		ui.pushButtonSend->setEnabled(true);
}

