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

#include <QMessageBox>
#include <QDomDocument>
#include <QMenu>
#include "utils.h"
#include "defines.h"
#include "config.h"
#include "logger.h"
#include "mainwidget.h"

using namespace config;

////////////////////
//Class MainWidget//
////////////////////
MainWidget::MainWidget() : m_maxMsgLen(maxDefMsgLen),
    m_numberLen(numderDefLen),
    m_textTooLong(false), m_operator(false),
    m_captchaDisabled(false), m_event(0),
    m_code(0),
    m_upBytes(0), m_downBytes(0),
    m_codeReq(0), m_operatorReq(0), m_captchaReq(0), m_numberLE(0),
    m_lookForSend(false), m_upArrow(":/img/uparrow.png"),
    m_downArrow(":/img/downarrow.png"), m_trayIcon(0),
    m_hideAct(0), m_showAct(0)
{
    LOGGERD<<eDebug<<"MainWidget created"<<NL;
    //random initialization
    srand();

    setupUi(this);

    setWindowIcon(QIcon(":/img/heart2.png"));

    m_numberLE = numberCB->lineEdit();
    Q_CHECK_PTR(m_numberLE);
    //TODO
//    m_numberLE->setInputMask("99999999999999");
    m_numberLE->setMaxLength(numderDefLen);

    CONN(&m_http, readyRead(const QHttpResponseHeader&),
        onHttpReadyRead(const QHttpResponseHeader&));

    CONN(&m_http, requestFinished(int, bool), httpRequestFinished(int, bool));

    CONN(&m_http, dataReadProgress(int, int), onHttpDataReadProgress(int, int));

    CONN(&m_http, dataSendProgress(int, int), onHttpDataSendProgress(int, int));

    CONN(&m_http, done(bool), onHttpDone(bool));

    addUpBytes(0);
    addDownBytes(0);

    authorTL->setText(programmName + " v." + programmVersion + " by " +
        programmAuthor);

    webSiteTL->setText(programmWebSite);

    m_http.setHost(messageSite);
    getRoot();

    load();

    smslen();
    createTrayIcon();
}

MainWidget::~MainWidget()
{
    LOGGERD<<eDebug<<"MainWidget destroyed"<<NL;
    save();
}

void MainWidget::getRoot()
{
    LOGGERD<<eDebug<<"http get / dir"<<NL;
    m_codeReq = m_http.get("/");
}

QHttpRequestHeader MainWidget::createHeader(CQString &method, CQString &path) const
{
    QHttpRequestHeader header(method, path);
    header.addValue("Host", messageSite);
    header.addValue("Connection", "keep-alive");
    header.addValue("User-Agent", "Gecko/20101026 Firefox/3.6.12");
    header.addValue("Referer", http + messageSite);
    header.addValue("Accept", "*/*");
    header.addValue("Accept-Language", "en-us,en;q=0.5");
    header.addValue("Accept-Encoding", "deflate");
    header.addValue("Accept-Charset", "ISO-8859-1,utf-8;q=0.7,*;q=0.7");
    header.addValue("Keep-Alive", "115");

    QString cookie;
    //TODO:: is it cookoe header requered or not?
    cuint c = m_cookies.length();
    if(c)
    {
        for(uint i = 0; i < c; i++)
            cookie += (m_cookies.at(i).toRawForm(QNetworkCookie::NameAndValueOnly) + "; ");

        header.addValue("Cookie", cookie);
    }

    return header;
}

void MainWidget::httpRequestFinished(int id, bool error)
{
    if(error)
    {
        httpError(error);
        return;
    }

    const qint64 b = m_http.bytesAvailable();
    addDownBytes(b);
    //stop the progress bar
    setProgressValue(b, b);

    LOGGERD<<eDebug<<"httpRequestFinished, current id:"<<id<<NL;

    if(id == m_codeReq)
    {
        if(getCode())
            m_codeReq = 0;
    }
    else
    if(id == m_operatorReq)
    {
        processXML();
        m_operatorReq = 0;
    }
    else
    if(id == m_captchaReq)
    {
        processCapture();
        m_captchaReq = 0;
    }
}

void MainWidget::httpError(const bool& error)
{
    if(error)
    {
        statusTL->setText(trUtf8("Ошибка связи с сервером"));
        //set progress to 0
        setProgressValue(0, 1);
        //WARNING:possible Qt bug
        progressBar->update();

        LOGGERD<<eError<<"httpRequestFinished, http error:"<<m_http.errorString()<<NL;
    }
}

void MainWidget::processXML()
{
    CQByteArray data(m_http.readAll());
    if(!data.isEmpty())
    {
        QDomDocument doc;
        //conversion to qstring is needed to correct translation
        doc.setContent(QString(data));

        QDomNode e = doc.firstChild();
        //get encoding
        QString enc;
        if(!e.isNull())
        {
            CQString val = e.nodeValue();
            int start = val.indexOf(xmlEncoding);
            if(-1 != start)
            {
                start += xmlEncoding.size();
                int end = val.indexOf(" ", start);
                //check for encoding element is the last element
                if(-1 == end)
                    end = val.size() - 1;

                enc = val.mid(start, end - start);
                enc.remove("\"");
                enc.remove("'");
            }
        }
        //set the default encoding
        if(enc.isEmpty())
            enc = xmlDefEncoding;

        //setting a text codec
        QTextCodec* c = QTextCodec::codecForName(enc.toLatin1());
        //try to use default codec
        if(!c)
            c = QTextCodec::codecForName(xmlDefEncoding.toLatin1());

        QDomElement root = doc.documentElement();

        if(!root.isNull() && xmlRoot == root.tagName() && c)
        {
            m_operator = false;
            //is this operator supports or not
            QDomElement el = root.firstChildElement(xmlOperSupp).toElement();
            if(!el.isNull() && !el.text().toInt())
            {
                operatorTL->setText(trUtf8("Неизвестный оператор"));
                return;
            }

            //operator name and region
            el = root.firstChildElement(xmlOperator).toElement();
            QDomElement el1 = root.firstChildElement(xmlRegion).toElement();
            if(!el.isNull())
            {
                operatorTL->setText(c->toUnicode((el.text() + ", " + el1.text()).toLatin1()));
            }
            else
            {
                operatorTL->setText(trUtf8("Неизвестный оператор"));
                return;
            }

            m_operator = true;

            //number length of current operator
            el = root.firstChildElement(xmlDigits).toElement();
            if(!el.isNull())
            {
                m_numberLen = el.text().toInt();
                m_numberLE->setMaxLength(m_numberLen);
            }

            //max message length of current operator
            el = root.firstChildElement(xmlMaxLen).toElement();
            if(!el.isNull())
                m_maxMsgLen = el.text().toInt();

            //event of current sms
            el = root.firstChildElement(xmlEvent).toElement();
            if(!el.isNull())
                m_event = el.text().toInt();

            //get captcha file name
            el = root.firstChildElement(xmlCaptcha).toElement();
            QString captcha;
            if(!el.isNull())
                captcha = el.text();

            m_captchaDisabled = captcha.isNull();
            if(!m_captchaDisabled)
            {
                LOGGERD<<eDebug<<"processXML(), get captcha:"<<captcha<<NL;
                m_captchaReq = m_http.request(createHeader("GET", captcha));
            }
        }
        else
            operatorTL->setText(trUtf8("Неизвестный оператор"));
    }

}

void MainWidget::processCapture()
{
    const QImage im = QImage::fromData(m_http.readAll());
    captchaTL->setFixedSize(im.size());
    captchaTL->setPixmap(QPixmap::fromImage(im));
    enableCaptchaInputs(true);
    setsubmit();
    LOGGERD<<eDebug<<"processCapture(), captcha size:"<<im.size()<<NL;
}

bool MainWidget::getCode()
{
    CQByteArray data(m_http.readAll());
    if(m_lookForSend)
    {
        int start = data.indexOf(sent1);
        int al = sent1.size();
        if(-1 == start)
        {
            start = data.indexOf(notsent);
            al = notsent.size();
        }
        if(-1 != start)
        {
            start += al;
            cint end = data.indexOf(sent2, start);
            if(-1 != end)
            {
                statusTL->setText(trUtf8(data.mid(start, end - start)));
            }
        }
    }

    int start = data.indexOf(code);
    bool noError = false;
    if(-1 != start && (-1 != (start = data.indexOf(code2, start))))
    {
        start += code2.size();
        cint end = data.indexOf(code3, start);
        if(-1 != end)
        {
            m_code = data.mid(start, end - start).toLong(&noError);
            LOGGERD<<eDebug<<"getCode(), code:"<<m_code<<NL;
        }
    }

    if(!noError)
    {
        LOGGERD<<eDebug<<"getCode(), get code error!"<<NL;
        statusTL->setText(trUtf8("Возможно сообщение не было отослано"));
        getRoot();
    }

    return noError;
}

void MainWidget::onHttpReadyRead(const QHttpResponseHeader& rh)
{
    //coockie update
    if(m_cookies.isEmpty())
    {
        QString cookieStr;
        cuint c = rh.values().count();
        for(uint i = 0; i < c; i++)
        {
            if(setCookie == rh.values().at(i).first)
                cookieStr.append(rh.values().at(i).second + '\n');
        }

        m_cookies = QNetworkCookie::parseCookies(cookieStr.toAscii());
    }

    addDownBytes(rh.toString().size());
}

void MainWidget::processNumber()
{
    CQString num = m_numberLE->text();
    if(num.size() >= phoneMinLen)
    {
        if(num.left(phoneMinLen) != m_lastReqNum)
        {
           resetData(false);
           m_lastReqNum = num.left(phoneMinLen);
           requestOperator();
        }
    }
    else
    {
        m_lastReqNum = SNULL;
        resetData(false);
    }

    setsubmit();
}

void MainWidget::onHttpDataReadProgress(int done, int total)
{
    setProgressValue(done, total);
    directionTL->setPixmap(m_downArrow);
}

void MainWidget::onHttpDataSendProgress(int done, int total)
{
    setProgressValue(done, total);
    directionTL->setPixmap(m_upArrow);
}

void MainWidget::setProgressValue(cint& done, cint& total)
{
    progressBar->setRange(0, total);
    progressBar->setValue(done);
}

void MainWidget::requestOperator()
{
    m_operatorReq = m_http.request(createHeader("GET",
        QString("/netxml.php?number=%1&rnd=%2").arg(m_numberLE->text()).arg(smsRand())));
    captchaTL->setText(trUtf8("загрузка..."));
}

void MainWidget::addUpBytes(cuint& n)
{
    m_upBytes += n;
    upTL->setText(bytesToText(m_upBytes));
}

void MainWidget::addDownBytes(cuint& n)
{
    m_downBytes += n;
    downTL->setText(bytesToText(m_downBytes));
}

void MainWidget::onHttpDone(bool b)
{
    httpError(b);
    directionTL->setPixmap(QPixmap());
}

void MainWidget::on_refreshCaptchaPB_clicked()
{
    requestOperator();
    enableCaptchaInputs(false);
}

void MainWidget::on_numberCB_editTextChanged()
{
    processNumber();
}

void MainWidget::on_messageTE_textChanged()
{
    smslen();
    setsubmit();
}

void MainWidget::on_signatureCB_editTextChanged()
{
    smslen();
}

void MainWidget::on_captchaLE_textChanged()
{
    setsubmit();
}

void MainWidget::on_sendPB_clicked()
{
    QHttpRequestHeader post = createHeader("POST", "/");

    CQString s = QString("number=%1&message=").arg(m_numberLE->text()) +
                QUrl::toPercentEncoding(messageTE->toPlainText()) +
                "&sign=" + QUrl::toPercentEncoding(signatureCB->currentText()) +
                 QString("&event=%1&codemod=code%2&code%2=%3").arg(m_event).arg(m_code).
                 arg(captchaLE->text());

    LOGGERD<<eDebug<<"on_sendPB_clicked, code:"<<m_code<<", event:"<<m_event<<NL;

    post.setContentType(formUrl);

    addUpBytes(post.toString().size() + s.size());

    resetData(true);
    m_codeReq = m_http.request(post, s.toLatin1());
    processNumber();
    m_lookForSend = true;
    numberCB->addItem(m_numberLE->text());
    signatureCB->addItem(signatureCB->currentText());
}

void MainWidget::enableCaptchaInputs(bool enable)
{
    refreshCaptchaPB->setEnabled(enable);
    captchaLE->setEnabled(enable);
    captchaLE->setText(SNULL);
}

void MainWidget::resetData(bool inputs)
{
    if(inputs)
    {
        messageTE->setPlainText(SNULL);
        m_numberLE->setMaxLength(numderDefLen);
        m_numberLE->setSelection(0, m_numberLE->text().size());
        statusTL->setText(SNULL);
        operatorTL->setText(SNULL);
        m_cookies.clear();
        m_code = 0;
        m_lastReqNum = SNULL;
    }

    enableCaptchaInputs(false);

    captchaTL->setPixmap(QPixmap());
    m_event = 0;

    m_maxMsgLen = maxDefMsgLen;
    m_numberLen = numderDefLen;
    m_operator = m_textTooLong = false;
    operatorTL->setText(SNULL);
    captchaLE->setText(SNULL);
}

void MainWidget::smslen()
{
    QString txt = messageTE->toPlainText() + signatureCB->currentText();

    uint size = txt.size() + (signatureCB->currentText() > 0 ? 2 : 0);

    if (size > intermedSmsLen)
    {
        cuint c = txt.length();
        for (uint i = 0; i < c; ++i)
        {
            const QChar ch = txt.at(i);
            //TODO: check that Qt can recognize russial capital and non-capital letters
            if(-1 != extra1.indexOf(ch, 0, Qt::CaseSensitive))
                size += 1;
            else
            if(-1 != extra2.indexOf(ch, 0, Qt::CaseSensitive))
                size += 2;
        }
    }

    counterTL->setText(QString::number(size));

    QColor c;
    m_textTooLong = false;
    if(size <= intermedSmsLen)
       c = QColor("#fff");
    else 
    if(size <= m_maxMsgLen)
        c = QColor("#ffc");
    else
    {
        m_textTooLong = true;
        c = QColor("#fcc");
    }

    counterTL->setPalette(QPalette(QPalette::Window, c));
    setsubmit();
}

void MainWidget::setsubmit()
{
    sendPB->setEnabled(!m_textTooLong && messageTE->toPlainText().size() &&
        numberCB->currentText().size() ==  m_numberLen &&
        (m_captchaDisabled || !captchaLE->text().isEmpty()));
}

void MainWidget::save()
{
    QSettings conf(programmAuthorEn, programmName);
    QStringList l;
    conf.setValue(confNumbers, l = clearList(combo2StringList(numberCB)));
    conf.setValue(confLastNumber, l.indexOf(m_numberLE->text()));
    conf.setValue(confSignatures,  l = clearList(combo2StringList(signatureCB)));
    conf.setValue(confLastSign, l.indexOf(signatureCB->currentText()));
}

void MainWidget::load()
{
    QSettings conf(programmAuthorEn, programmName);

    fillCombo(numberCB, clearList(conf.value(confNumbers).toStringList()));
    fillCombo(signatureCB, clearList(conf.value(confSignatures).toStringList()));
    bool res = false;
    int c = conf.value(confLastNumber).toInt(&res);
    if(res)
        numberCB->setCurrentIndex(c);

    c = conf.value(confLastSign).toInt(&res);
    if(res)
        signatureCB->setCurrentIndex(c);
}

void MainWidget::createTrayIcon()
{
    if(!QSystemTrayIcon::isSystemTrayAvailable())
        return;

    QMenu* tiMenu = new QMenu(this);

    m_hideAct = tiMenu->addAction(trUtf8("Свернуть"), this, SLOT(hide()));
    Q_CHECK_PTR(m_hideAct);
    m_showAct = tiMenu->addAction(trUtf8("Восстановить"), this, SLOT(showNormal()));
    Q_CHECK_PTR(m_hideAct);
    tiMenu->addSeparator();
    tiMenu->addAction(trUtf8("Выход"), qApp, SLOT(quit()));

    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setContextMenu(tiMenu);

    CONN(m_trayIcon, activated(QSystemTrayIcon::ActivationReason),
            iconActivated(QSystemTrayIcon::ActivationReason));

    m_trayIcon->setIcon(QIcon(":/img/heart2.png"));
    m_trayIcon->setToolTip(programmName);
    m_trayIcon->show();
}

void MainWidget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::MiddleClick:
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
        if(isVisible())
            hide();
        else
            showNormal();
        break;
        case QSystemTrayIcon::Context:
            if(m_hideAct && m_showAct)
            {
                m_hideAct->setEnabled(isVisible());
                m_showAct->setEnabled(!isVisible());
            }
        break;
        default:;
    }
}

void MainWidget::closeEvent(QCloseEvent* e)
{
    if(m_trayIcon && m_trayIcon->isVisible())
    {
        hide();
        e->ignore();
    }
    else
        QWidget::closeEvent(e);
}
