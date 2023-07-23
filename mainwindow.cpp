#include "mainwindow.h"

#include <QLine>
#include <QSerialPortInfo>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMetaEnum>
#include <QPalette>
#include <QApplication>
#include <QStyleFactory>
#include <QTimerEvent>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //App styles
    uiStyleName = new QLabel(tr("UiStyleName"));
    uiStyleNameComboBox = new QComboBox;
    uiStyleNameComboBox->addItems(QStyleFactory::keys());
    connect(uiStyleNameComboBox,&QComboBox::currentTextChanged,this,&MainWindow::UpdateUiStyle);



    //main widget
    resize(800,600);
    setWindowIcon(QIcon(":/images/logo.png"));
    mainWidget = new QWidget;
    leftWidget = new QWidget;
    rightWidget = new QWidget;
    setCentralWidget(mainWidget);
    QHBoxLayout *hboxlayout_main = new QHBoxLayout;
    QVBoxLayout *vboxlayout_setting = new QVBoxLayout;
    QVBoxLayout *vboxlayout_data = new QVBoxLayout;
    hboxlayout_main->addWidget(leftWidget);
    hboxlayout_main->addWidget(rightWidget);
    leftWidget->setLayout(vboxlayout_setting);
    rightWidget->setLayout(vboxlayout_data);
    mainWidget->setLayout(hboxlayout_main);

    leftWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);




    //setting layout
    QGridLayout *gridlayout_setting = new QGridLayout;

    gridlayout_setting->setContentsMargins(20,20,20,20);
    gridlayout_setting->setColumnStretch(0,2);
    gridlayout_setting->setColumnStretch(1,2);
    gridlayout_setting->setColumnStretch(2,1);
    vboxlayout_setting->addLayout(gridlayout_setting);
    //vboxlayout_setting->addStretch();
    serialPortNameLabel = new QLabel(tr("PortName"));
    serialPortBaudRateLabel = new QLabel(tr("BaudRate"));
    serialPortParityLabel = new QLabel(tr("Parity"));
    serialPortDataBitsLabel = new QLabel(tr("DataBits"));
    serialPortStopBitsLabel = new QLabel(tr("StopBits"));
    serialPortFlowControlLabel = new QLabel(tr("FlowControl"));

    serialPortNameComboBox = new QComboBox;
    serialPortBaudRateComboBox = new QComboBox;
    serialPortParityComboBox = new QComboBox;
    serialPortDataBitsComboBox = new QComboBox;
    serialPortStopBitsComboBox = new QComboBox;
    serialPortFlowControlComboBox = new QComboBox;



    gridlayout_setting->addWidget(serialPortNameLabel,0,0);
    gridlayout_setting->addWidget(serialPortNameComboBox,0,1);
    gridlayout_setting->addWidget(serialPortBaudRateLabel,1,0);
    gridlayout_setting->addWidget(serialPortBaudRateComboBox,1,1);
    gridlayout_setting->addWidget(serialPortParityLabel,2,0);
    gridlayout_setting->addWidget(serialPortParityComboBox,2,1);
    gridlayout_setting->addWidget(serialPortDataBitsLabel,3,0);
    gridlayout_setting->addWidget(serialPortDataBitsComboBox,3,1);
    gridlayout_setting->addWidget(serialPortStopBitsLabel,4,0);
    gridlayout_setting->addWidget(serialPortStopBitsComboBox,4,1);
    gridlayout_setting->addWidget(serialPortFlowControlLabel,5,0);
    gridlayout_setting->addWidget(serialPortFlowControlComboBox,5,1);


    gridlayout_setting->setRowMinimumHeight(6,20);



    openSerialPortButton = new QPushButton(tr("open"));
    openSerialPortButton->setDefault(true);
    closeSerialPortButton = new QPushButton(tr("close"));
    hexShowCheckBox = new QCheckBox(tr("Hex show"));
    hexSendCheckBox = new QCheckBox(tr("Hex send"));
    timerSendCheckBox = new QCheckBox(tr("Timer send"));
    newLineCheckBox = new QCheckBox(tr("New line"));
    sendIntervalLabel = new QLabel(tr("Send interval"));
    sendIntervalLineEdit = new QLineEdit("1000");
    sendIntervalUnitsLabel = new QLabel(tr("ms"));
    gridlayout_setting->addWidget(openSerialPortButton,7,0);
    gridlayout_setting->addWidget(closeSerialPortButton,7,1);
    gridlayout_setting->addWidget(hexShowCheckBox,8,0);
    gridlayout_setting->addWidget(newLineCheckBox,8,1);
    gridlayout_setting->addWidget(timerSendCheckBox,9,0);
    gridlayout_setting->addWidget(hexSendCheckBox,9,1);
    gridlayout_setting->addWidget(sendIntervalLabel,10,0);
    gridlayout_setting->addWidget(sendIntervalLineEdit,10,1);
    gridlayout_setting->addWidget(sendIntervalUnitsLabel,10,2);
    gridlayout_setting->addWidget(uiStyleName,11,0);
    gridlayout_setting->addWidget(uiStyleNameComboBox,11,1);




    pictureLabel = new QLabel;
    vboxlayout_setting->addWidget(pictureLabel);
    QPixmap picture(":/images/hospital.png");
    pictureLabel->setPixmap(picture.scaled(QSize(300,300),Qt::KeepAspectRatio,Qt::SmoothTransformation));


    QPalette pe;
    pe.setColor(QPalette::Window,QColor("white"));
    pictureLabel->setAutoFillBackground(true);
    pictureLabel->setPalette(pe);

    QPushButton *button = new QPushButton(tr("Button"));
    vboxlayout_setting->addWidget(button);






    //data layout

    //group receive
    receiveDataGroupBox = new QGroupBox(tr("receive"));
    vboxlayout_data->addWidget(receiveDataGroupBox);
    QVBoxLayout *vboxlayout_receive_group = new QVBoxLayout;
    QHBoxLayout *hboxlayout_receive_bottom = new QHBoxLayout;
    receiveDataGroupBox->setLayout(vboxlayout_receive_group);


    receiveDataEdit = new QPlainTextEdit;

    timeStampCheckBox = new QCheckBox(tr("timestamp"));
    clearReceiveDataButton = new QPushButton(tr("clear"));
    vboxlayout_receive_group->addWidget(receiveDataEdit);
    vboxlayout_receive_group->addLayout(hboxlayout_receive_bottom);
    hboxlayout_receive_bottom->addStretch();
    hboxlayout_receive_bottom->addWidget(timeStampCheckBox);
    hboxlayout_receive_bottom->addWidget(clearReceiveDataButton);

    //group send
    sendDataGroupBox = new QGroupBox(tr("send"));
    vboxlayout_data->addWidget(sendDataGroupBox);
    QVBoxLayout *vboxlayout_send_group = new QVBoxLayout;
    QHBoxLayout *hboxlayout_send_bottom = new QHBoxLayout;
    sendDataGroupBox->setLayout(vboxlayout_send_group);

    sendDataEdit = new QPlainTextEdit;
    sendButton = new QPushButton(tr("send"));
    clearSendEditButton = new QPushButton(tr("clear"));
    vboxlayout_send_group->addWidget(sendDataEdit);
    vboxlayout_send_group->addLayout(hboxlayout_send_bottom);
    hboxlayout_send_bottom->addStretch();
    hboxlayout_send_bottom->addWidget(sendButton);
    hboxlayout_send_bottom->addWidget(clearSendEditButton);





    //specific
    //portName
    QList<QSerialPortInfo> serialPortInfoList = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo &serialPortInfo:serialPortInfoList){
        serialPortNameComboBox->addItem(serialPortInfo.portName());
    }
    //BaudRate
    for(qint32 BaudRate:QSerialPortInfo::standardBaudRates()){
        serialPortBaudRateComboBox->addItem(QString::number(BaudRate));
    }
    serialPortBaudRateComboBox->setCurrentText("115200");
    //parity
    QMetaEnum parityMetaEnum = QMetaEnum::fromType<QSerialPort::Parity>();
    for(int i = 0;i<parityMetaEnum.keyCount();++i){
        serialPortParityComboBox->addItem(QString::number(parityMetaEnum.value(i)));
    }
    //DataBits
    QMetaEnum dataBitsMeteEnum= QMetaEnum::fromType<QSerialPort::DataBits>();
    for (int i = 0; i < dataBitsMeteEnum.keyCount(); ++i) {
        serialPortDataBitsComboBox->addItem(QString::number(dataBitsMeteEnum.value(i)));
    }
    serialPortDataBitsComboBox->setCurrentText("8");
    //StopBits
    QMetaEnum stopBitsMeteEnum= QMetaEnum::fromType<QSerialPort::StopBits>();
    for (int i = 0; i < stopBitsMeteEnum.keyCount(); ++i) {
        serialPortStopBitsComboBox->addItem(QString::number(stopBitsMeteEnum.value(i)));
    }
    //FlowControl
    QMetaEnum FlowControlMeteEnum= QMetaEnum::fromType<QSerialPort::FlowControl>();
    for (int i = 0; i < FlowControlMeteEnum.keyCount(); ++i) {
        serialPortFlowControlComboBox->addItem(QString::number(FlowControlMeteEnum.value(i)));
    }




    isSerialOpened = false;
    timerSendInterval = sendIntervalLineEdit->text().toInt();

    //serialPort = new QSerialPort;
    //connect(serialPort,&QSerialPort::readyRead,this,&MainWindow::RxSerial);



    //connect
    connect(openSerialPortButton,&QPushButton::clicked,this,&MainWindow::OpenSerialPort);
    connect(closeSerialPortButton,&QPushButton::clicked,this,&MainWindow::CloseSerialPort);
    connect(sendButton,&QPushButton::clicked,this,&MainWindow::TxSerial);
    connect(timerSendCheckBox,&QCheckBox::stateChanged,this,&MainWindow::UpdateTimerSend);
    connect(sendIntervalLineEdit,&QLineEdit::textChanged,this,&MainWindow::UpdateTimerSendInterval);
    connect(clearReceiveDataButton,&QPushButton::clicked,this,&MainWindow::ClearReceiveEdit);
    connect(clearSendEditButton,&QPushButton::clicked,this,&MainWindow::ClearSendEdit);




}

MainWindow::~MainWindow()
{

}

void MainWindow::UpdateUiStyle()
{
    QApplication::setStyle(QStyleFactory::create(uiStyleNameComboBox->currentText()));
}

void MainWindow::OpenSerialPort()
{
    if(isSerialOpened==false){
        //create new serialPort
        serialPort = new QSerialPort;
        connect(serialPort,&QSerialPort::readyRead,this,&MainWindow::RxSerial);

        serialPort->setPortName(serialPortNameComboBox->currentText()); //com
        if(serialPort->open(QIODevice::ReadWrite)){
            serialPort->setBaudRate(serialPortBaudRateComboBox->currentText().toInt()); //BaudRate
            //DataBits
            switch(serialPortDataBitsComboBox->currentText().toInt()){
            case 8:
                serialPort->setDataBits(QSerialPort::Data8);
                break;
            case 7:
                serialPort->setDataBits(QSerialPort::Data7);
                break;
            case 6:
                serialPort->setDataBits(QSerialPort::Data6);
                break;
            case 5:
                serialPort->setDataBits(QSerialPort::Data5);
                break;
            default:
                break;
            }
            //StopBits
            switch(serialPortStopBitsComboBox->currentText().toInt()){
            case 1:
                serialPort->setStopBits(QSerialPort::OneStop);
                break;
            case 3:
                serialPort->setStopBits(QSerialPort::OneAndHalfStop);
                break;
            case 2:
                serialPort->setStopBits(QSerialPort::TwoStop);
                break;
            default:
                break;
            }

            //Parity
            switch(serialPortParityComboBox->currentText().toInt()){
            case 0:
                serialPort->setParity(QSerialPort::NoParity);
                break;
            case 2:
                serialPort->setParity(QSerialPort::EvenParity);
                break;
            case 3:
                serialPort->setParity(QSerialPort::OddParity);
                break;
            case 4:
                serialPort->setParity(QSerialPort::SpaceParity);
                break;
            case 5:
                serialPort->setParity(QSerialPort::MarkParity);
                break;
            default:
                break;

            }

            //FlowControl
            switch(serialPortFlowControlComboBox->currentText().toInt()){
            case 0:
                serialPort->setFlowControl(QSerialPort::NoFlowControl);
                break;
            case 1:
                serialPort->setFlowControl(QSerialPort::HardwareControl);
                break;
            case 2:
                serialPort->setFlowControl(QSerialPort::SoftwareControl);
                break;
            default:
                break;
            }

            isSerialOpened = true;

            QPalette pe;
            pe.setColor(QPalette::ButtonText,QColor("blue"));
            openSerialPortButton->setPalette(pe);

        }
        else{
            QMessageBox::critical(nullptr,tr("information"),tr("serial %1 open failed").arg(serialPort->portName()));
            return;
        }

    }
    else{
        QMessageBox::warning(nullptr,tr("information"),tr("serial %1 is opened").arg(serialPort->portName()));
        return;
    }
}

void MainWindow::CloseSerialPort()
{
    if(isSerialOpened==true){
        serialPort->clear();
        serialPort->close();
        serialPort->deleteLater();
        isSerialOpened = false;

        QPalette pe;
        //pe.setColor(QPalette::ButtonText,QColor("blue"));
        openSerialPortButton->setPalette(pe);//return default
    }
}

void MainWindow::TxSerial()
{
    if(isSerialOpened){
        if(serialPort->isOpen()){
            QString txMsg = sendDataEdit->toPlainText();
            QByteArray txData = txMsg.toLocal8Bit(); //Qt(unicode)->Windows(GBK)

            //hex send
            if(hexSendCheckBox->isChecked()){
                txData = txData.toHex().data();
                qDebug()<<txData;
            }

            //new line
            if(newLineCheckBox->isChecked()){
                txData+="\r\n";
            }

            //send
            serialPort->write(txData);
            qDebug()<<txData;
        }
    }
}

void MainWindow::RxSerial()
{
    rxData = serialPort->readAll();
    if(!rxData.isEmpty()){

        QString currentDate;
        QString rxMsg;
        //hex show
        if(hexShowCheckBox->isChecked()){
            QString str = rxData.toHex().data();
            str = str.toUpper();
            for(int i = 0;i<str.length();i+=2){
                rxMsg+=str.mid(i,2);
                rxMsg+=' ';
            }
        }
        else{
            rxMsg = QString::fromLocal8Bit(rxData); //Windows(GBK)->Qt(unicode)
        }
        //timeStamp
        if(timeStampCheckBox->isChecked()){
            currentDate = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz]");
        }
        //append
        receiveDataEdit->appendPlainText(currentDate + rxMsg);
    }
}

void MainWindow::ClearReceiveEdit()
{
    receiveDataEdit->clear();
}

void MainWindow::ClearSendEdit()
{
    sendDataEdit->clear();
}

void MainWindow::UpdateTimerSend()
{
    if(timerSendCheckBox->isChecked()){
        sendTimerId = startTimer(timerSendInterval);
    }
    else{
        killTimer(sendTimerId);
    }
}

void MainWindow::UpdateTimerSendInterval()
{
    timerSendInterval = sendIntervalLineEdit->text().toInt();
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==sendTimerId){
        TxSerial();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //close serial port
    if(isSerialOpened==true){
        auto standerdButton = QMessageBox::question(this,tr("information"),tr("serial %1 is opened,do you realy want close it?").arg(serialPort->portName()));
        if(standerdButton==QMessageBox::Yes){
            serialPort->clear();
            serialPort->close();
            serialPort->deleteLater();
            isSerialOpened = false;
            QPalette pe;
            openSerialPortButton->setPalette(pe);//return default
            event->accept();
        }
        else{
            event->ignore();
        }
    }
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    return false; //ignore
}

