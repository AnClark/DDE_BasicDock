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
    /* Q_OBJECT宏，标示本类是一个Qt对象。
     * 只有加入这个宏，才能在本模块使用信号，否则编译器会报错。
     * 使用这个宏，还要求工程PRO文件加入`CONFIG += plugin`这个配置，否则dde-dock将无法加载插件。
     *
     * 实际上，不加入Q_OBJECT且不在本模块使用信号的话，插件也可以被加载，即使不改PRO中的设置。
     */
    Q_OBJECT

public:
    explicit DDE_BasicDock(QWidget *parent = 0);           // 构造函数

    bool enabled();                     // 返回插件的可用状态
    void setEnabled(const bool b);      // 设置插件的可用状态

    QString text;                       // 在插件上显示的文字

/* requestUpdateGeometry方法
 * 海天鹰在设计插件时使用的信号，可能用于通知dde-dock更新插件界面
 * 但事实上，不使用本信号，插件UI也能照常更新。
 * 且他的源码里并没有实现本方法，而只是将该信号与m_ProxyInter->itemUpdate绑定。
 *
 * 注：不使用信号，开头的Q_OBJECT和PRO文件里的`CONFIG += plugin`也就不用添加。
 */
//signals:
//    void requestUpdateGeometry() const;

private:
    // 以下的三个方法继承于QWidget，由Qt自动执行
    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

    // 操作设置
    QSettings m_settings;
};

#endif // DDE_BASICDOCK_H
