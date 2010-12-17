/***************************************************************************
 *   Copyright (C) 2010 by Igor Sobinov   *
 *   sluge@mail.ru *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

//////////////////////////////////////////////////////////////////////////
//    Author :       Igor Sobinov
//    File:          $Source:  $
//    Revision:      $Revision: $
//    Last modified: $Date:  $
//    Description:   
//////////////////////////////////////////////////////////////////////////

#ifndef _MAINWIDGET_H_
#define _MAINWIDGET_H_

#include <QWidget>
#include <QHttp>
#include <QNetworkCookie>
#include <QSystemTrayIcon>
#include "ui_mainwidget.h"
#include "types.h"

class MainWidget : public QWidget, private Ui_MainWidget
{
    Q_OBJECT

public:

    MainWidget();

    virtual ~MainWidget();

protected:

    virtual void closeEvent(QCloseEvent *event);

private slots:

    void on_numberCB_editTextChanged();

    void on_messageTE_textChanged();

    void on_signatureCB_editTextChanged();

    void on_captchaLE_textChanged();
    //send clicked
    void on_sendPB_clicked();

    void on_refreshCaptchaPB_clicked();
    //all requests are finished
    void onHttpDone();

    void httpRequestFinished(int id, bool error);
    //it is something to read
    void onHttpReadyRead(const QHttpResponseHeader&);

    void onHttpDataReadProgress(int done, int total);

    void onHttpDataSendProgress(int done, int total);
    //slot for manage messages from tray icon, if it is exist
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:

    void smslen();

    void setsubmit();

    QHttpRequestHeader createHeader(CQString &method, CQString &path) const;

    void processXML();

    void processCapture();

    void resetData(bool inputs);

    void enableCaptchaInputs(bool enable);

    bool getCode();

    void requestCaptcha();

    void processNumber();

    void requestOperator();

    void setProgressValue(cint& done, cint& total);

    void addUpBytes(cuint& n);

    void addDownBytes(cuint& n);

    void save();

    void load();

    void getRoot();

    void createTrayIcon();
    //maximum sms length for current operator
    uint m_maxMsgLen;
    //number's lenght of current operator
    uint m_numberLen;
    //is message text is too long or not
    bool m_textTooLong;
    //is operator determeted or not
    bool m_operator;
    //it is not needed to input captcha for some operators
    bool m_captchaDisabled;
    //http protocol implementation
    QHttp m_http;

    typedef QList<QNetworkCookie> CookieList;

    CookieList m_cookies;
    //last number that was requested operator info for
    QString m_lastReqNum;
    //number o current message event
    uint m_event,
    //code storage
         m_code,
         //how many bytes downloaded
         m_upBytes,
         //how many bytes uploaded
         m_downBytes;
    //number of http code request
    int m_codeReq,
    //number of http operator request
        m_operatorReq,

        m_captchaReq;
    //line edit of number input
    QLineEdit* m_numberLE;
    //looking for "send success" message in input stream
    bool m_lookForSend;
    //up arrow(red) pixmap
    const QPixmap m_upArrow,
    //down arrow(gren) pixmap
                  m_downArrow;
    //tray lives here
    QSystemTrayIcon* m_trayIcon;
    //Action that hide main widget
    QAction* m_hideAct;
    //Action that shows main widget
    QAction* m_showAct;
};


#endif //_MAINWIDGET_H_
