/**
  * dde_basicdock.h
  *
  * 插件UI的本体，主要控制的是在Dock栏上显示的内容。
  */

#ifndef DDE_BASICDOCK_H
#define DDE_BASICDOCK_H

#include <QWidget>
#include <QSettings>

class DDE_BasicDock : public QWidget
{

public:
    explicit DDE_BasicDock(QWidget *parent = 0);           // 构造函数

    bool enabled();                     // 返回插件的可用状态
    void setEnabled(const bool b);      // 设置插件的可用状态

    QString text;                       // 在插件上显示的文字

private:
    // 以下的三个方法继承于QWidget，由Qt自动执行
    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

    // 操作设置
    QSettings m_settings;
};

#endif // DDE_BASICDOCK_H
