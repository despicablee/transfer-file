#include "severdialog.h"

SeverDialog::SeverDialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	tcp_sever = new QTcpServer(this);
	total_bytes = received_bytes = file_name_size = 0;

	connect(tcp_sever, SIGNAL(newConnection()), this, SLOT(acceptConnection())) ;

	setFixedSize( this->width(),this->height ());
}

SeverDialog::~SeverDialog()
{

}

void SeverDialog::start()
{
	ui.ButtonRecive->setEnabled(false) ;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	received_bytes = 0;

	while(!tcp_sever->isListening() && !tcp_sever->listen(QHostAddress::Any, 16689))
	{
		QMessageBox::StandardButton ret = QMessageBox::critical(this, tr("回环"), 
			tr("无法开始测试： %1.").arg(tcp_sever->errorString()), 
			QMessageBox::Retry | QMessageBox::Cancel);

		if(ret == QMessageBox::Cancel)
			return ;
	}

	ui.label->setText(tr("正在监听"));
}

void SeverDialog::acceptConnection()
{
	//取出套节字
	tcp_sever_connection = tcp_sever->nextPendingConnection() ;
	//收到消息触发readyRead 信号 
	connect(tcp_sever_connection, SIGNAL(readyRead()), this, SLOT(updateSeverProgress()));
	//出错触发error信号
	connect(tcp_sever_connection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));


	ui.label->setText(tr("接收连接"));
	tcp_sever->close();
}

void SeverDialog::updateSeverProgress()
{
	//in关联套节字，每写出一段数据 tcp_sever_connection的bytesAvailable() 就少一段数据
	QDataStream in(tcp_sever_connection);
	in.setVersion(QDataStream::Qt_4_3);

	// 如果还没有写 总长度和文件名长度
	if(received_bytes <= sizeof(qint64)*2)
	{
		//写 总长度 和 文件名长度
		if( (tcp_sever_connection->bytesAvailable() >= sizeof(qint64)*2 ) && file_name_size == 0)
		{
			in >> total_bytes >> file_name_size;
			received_bytes += sizeof(qint64)*2 ;
		}

		//received_bytes == sizeof(qint64)*2时  写入文件名
		if(tcp_sever_connection->bytesAvailable() >= file_name_size && file_name_size != 0)
		{
			in >> file_name;
			received_bytes += file_name_size;
			local_file = new QFile(file_name);

			if(!local_file->open(QFile::WriteOnly))
			{
				QMessageBox::warning(this, tr("应用程序"),
					tr("无法读取文件 %1:\n%2.")
					.arg(file_name)
					.arg(local_file->errorString()));
				return ;
			}
		}
		else
			return ;
	}
	
	//写入文件数据
	if(received_bytes < total_bytes)
	{
		received_bytes += tcp_sever_connection->bytesAvailable();
		in_block = tcp_sever_connection->readAll() ;
		local_file->write(in_block);
		in_block.resize(0);
	}

	//更新进度条
	ui.progressBar->setMaximum(total_bytes);
	ui.progressBar->setValue(received_bytes);
	ui.label->setText(tr("%1 %").arg(QString::number(received_bytes / total_bytes *100))) ;

	//如果收完数据
	if(received_bytes == total_bytes)
	{
		tcp_sever_connection->close();
		ui.ButtonRecive->setEnabled(true);
		QApplication::restoreOverrideCursor();
	}

}

void SeverDialog::displayError(QAbstractSocket::SocketError soket_error)
{
	if(soket_error == QTcpSocket::RemoteHostClosedError)
		return ;

	QMessageBox::information(this, tr("网络错误"),
		tr("产生如下错误: %1.")
		.arg(tcp_sever_connection->errorString()));

	tcp_sever_connection->close();
	ui.progressBar->reset();
	ui.label->setText(tr("服务端就绪"));
	ui.ButtonRecive->setEnabled(true);
	QApplication::restoreOverrideCursor();
}


