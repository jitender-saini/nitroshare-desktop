/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef MDNSSERVICE_H
#define MDNSSERVICE_H

#include <QByteArray>
#include <QHostAddress>
#include <QList>
#include <QMap>
#include <QObject>

#include "dnsmessage.h"
#include "mdnsserver.h"

class MdnsService : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Create an uninitialized service
     */
    explicit MdnsService(MdnsServer *mdnsServer);

    /**
     * @brief Retrieve service type
     */
    QByteArray type() const;

    /**
     * @brief Set service type
     */
    void setType(const QByteArray &type);

    /**
     * @brief Retrieve service name
     */
    QByteArray name() const;

    /**
     * @brief Set service name
     */
    void setName(const QByteArray &name);

    /**
     * @brief Retrieve service addresses
     */
    QList<QHostAddress> addresses() const;

    /**
     * @brief Set service addresses
     */
    void setAddresses(const QList<QHostAddress> &addresses);

    /**
     * @brief Retrieve service port
     */
    quint16 port() const;

    /**
     * @brief Set service port
     */
    void setPort(quint16 port);

    /**
     * @brief Retrieve service attributes
     */
    QMap<QByteArray, QByteArray> attributes() const;

    /**
     * @brief Add service attribute
     */
    void addAttribute(const QByteArray &key, const QByteArray &value);

private Q_SLOTS:

    void onMessageReceived(const DnsMessage &message);

private:

    QHostAddress findInterfaceAddress(const QHostAddress &hostAddress);
    DnsRecord generateAddress(const QHostAddress &address);
    DnsRecord generatePtr();
    DnsRecord generatePtrService();
    DnsRecord generateSrv();
    DnsRecord generateTxt();

    MdnsServer *mMdnsServer;

    QByteArray mType;
    QByteArray mName;
    QList<QHostAddress> mAddresses;
    quint16 mPort;
    QMap<QByteArray, QByteArray> mAttributes;
};

#endif // MDNSSERVICE_H
