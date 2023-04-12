#ifndef XINPUTDIALOG_H
#define XINPUTDIALOG_H

#include "XWidgetGlobal.h"

#include <QInputDialog>

class XTitleBar;

class XWIDGET_EXPORT XInputDialog : public QInputDialog
{
public:
    XInputDialog(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags(),const QString &okText="Ok",const QString &cancelText="Cancel");
    ~XInputDialog();

    void setTitleBar(XTitleBar* titleBar);
    XTitleBar* titleBar() const;
    void removeTitleBar();



    static QString getText(const QString& title,
                           const QString& label,
                           const QString &okText="Ok",
                           const QString &cancelText="Cancel",
                           QWidget* parent=nullptr,
                           QLineEdit::EchoMode echo              = QLineEdit::Normal,
                           const QString& text                   = QString(),
                           bool* ok                              = nullptr,
                           Qt::WindowFlags flags                 = Qt::WindowFlags(),
                           Qt::InputMethodHints inputMethodHints = Qt::ImhNone);

    static QString getMultiLineText(const QString& title,
                                    const QString& label,
                                    const QString &okText="Ok",
                                    const QString &cancelText="Cancel",
                                    QWidget* parent=nullptr,
                                    const QString& text                   = QString(),
                                    bool* ok                              = nullptr,
                                    Qt::WindowFlags flags                 = Qt::WindowFlags(),
                                    Qt::InputMethodHints inputMethodHints = Qt::ImhNone);
    static QString getItem(const QString& title,
                           const QString& label,
                           const QStringList& items,
                           const QString &okText="Ok",
                           const QString &cancelText="Cancel",
                           QWidget* parent=nullptr,
                           int current                           = 0,
                           bool editable                         = true,
                           bool* ok                              = nullptr,
                           Qt::WindowFlags flags                 = Qt::WindowFlags(),
                           Qt::InputMethodHints inputMethodHints = Qt::ImhNone);
    static int getInt(const QString& title,
                      const QString& label,
                      const QString &okText="Ok",
                      const QString &cancelText="Cancel",
                      QWidget* parent=nullptr,
                      int value             = 0,
                      int minValue          = -2147483647,
                      int maxValue          = 2147483647,
                      int step              = 1,
                      bool* ok              = nullptr,
                      Qt::WindowFlags flags = Qt::WindowFlags());
    static double getDouble(const QString& title,
                            const QString& label,
                            const QString &okText="Ok",
                            const QString &cancelText="Cancel",
                            QWidget* parent=nullptr,
                            double value          = 0,
                            double minValue       = -2147483647,
                            double maxValue       = 2147483647,
                            int decimals          = 1,
                            bool* ok              = nullptr,
                            Qt::WindowFlags flags = Qt::WindowFlags(),
                            double step           = 1);

protected:
    void hideEvent(QHideEvent*) override;
    void showEvent(QShowEvent* e) override;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
#else
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
#endif
private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

#endif // XINPUTDIALOG_H
