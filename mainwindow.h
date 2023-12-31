#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QDockWidget>
#include <QGroupBox>
#include <QTextEdit>
#include <QCheckBox>
#include <QLineEdit>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QPlainTextEdit>
#include <QTimer>

class QCheckBox;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    //UI
    //main widget
    QWidget *mainWidget;
    QWidget *leftWidget;
    QWidget *rightWidget;

    //setting widget
    QLabel *serialPortNameLabel;
    QLabel *serialPortBaudRateLabel;
    QLabel *serialPortParityLabel;
    QLabel *serialPortDataBitsLabel;
    QLabel *serialPortStopBitsLabel;
    QLabel *serialPortFlowControlLabel;
    QLabel *uiStyleName;

    QComboBox *serialPortNameComboBox;
    QComboBox *serialPortBaudRateComboBox;
    QComboBox *serialPortParityComboBox;
    QComboBox *serialPortDataBitsComboBox;
    QComboBox *serialPortStopBitsComboBox;
    QComboBox *serialPortFlowControlComboBox;
    QComboBox *uiStyleNameComboBox;

    QPushButton *openSerialPortButton;
    QPushButton *closeSerialPortButton;

    QCheckBox *hexShowCheckBox;
    QCheckBox *hexSendCheckBox;
    QCheckBox *timerSendCheckBox;
    QCheckBox *newLineCheckBox;




    QLabel *sendIntervalLabel;
    QLineEdit *sendIntervalLineEdit;
    QLabel *sendIntervalUnitsLabel;

    QLabel *pictureLabel;



    //data widget
    //receive group
    QGroupBox *receiveDataGroupBox;
    QPlainTextEdit *receiveDataEdit;
    QCheckBox *timeStampCheckBox;
    QPushButton *clearReceiveDataButton;
    //send group
    QGroupBox *sendDataGroupBox;
    QPlainTextEdit *sendDataEdit;
    QPushButton *sendButton;
    QPushButton *clearSendEditButton;


    //not UI
    bool isSerialOpened;
    QSerialPort *serialPort;
    QByteArray rxData;
    int sendTimerId;
    int timerSendInterval;




public:


public slots:
    void UpdateUiStyle();
    void OpenSerialPort();
    void CloseSerialPort();
    void RxSerial();
    void TxSerial();
    void ClearReceiveEdit();
    void ClearSendEdit();
    void UpdateTimerSend();
    void UpdateTimerSendInterval();






    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event);
    virtual void closeEvent(QCloseEvent *event);
    virtual bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result);
};
#endif // MAINWINDOW_H
