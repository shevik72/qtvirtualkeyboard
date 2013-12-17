/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#ifndef ABSTRACTINPUTMETHOD_H
#define ABSTRACTINPUTMETHOD_H

#include "declarativeinputengine.h"
#include "declarativeselectionlistmodel.h"

class AbstractInputMethodPrivate
{
public:
    virtual ~AbstractInputMethodPrivate() {}
    DeclarativeInputEngine *inputEngine;
};

class AbstractInputMethod : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractInputMethod)
    Q_PROPERTY(QString className READ className CONSTANT)

protected:
    AbstractInputMethod(AbstractInputMethodPrivate *d_ptr, QObject *parent = 0);
public:
    explicit AbstractInputMethod(QObject *parent = 0);
    ~AbstractInputMethod();

    QString className() const;
    DeclarativeInputContext *inputContext() const;
    DeclarativeInputEngine *inputEngine() const;

    virtual QList<DeclarativeInputEngine::InputMode> inputModes(const QString &locale) = 0;
    virtual bool setInputMode(const QString &locale, DeclarativeInputEngine::InputMode inputMode) = 0;
    virtual bool setTextCase(DeclarativeInputEngine::TextCase textCase) = 0;

    virtual bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) = 0;

    virtual QList<DeclarativeSelectionListModel::Type> selectionLists();
    virtual int selectionListItemCount(DeclarativeSelectionListModel::Type type);
    virtual QVariant selectionListData(DeclarativeSelectionListModel::Type type, int index, int role);
    virtual void selectionListItemSelected(DeclarativeSelectionListModel::Type type, int index);

signals:
    void selectionListChanged(int type);
    void selectionListActiveItemChanged(int type, int index);

public slots:
    virtual void reset();
    virtual void update();

private:
    void setInputEngine(DeclarativeInputEngine *inputEngine);

    friend class DeclarativeInputEngine;

protected:
    QScopedPointer<AbstractInputMethodPrivate> d_ptr;
};

#endif
