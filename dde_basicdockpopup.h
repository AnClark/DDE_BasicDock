/**
  * dde_basicdockpopup.h
  *
  * 插件弹出窗口UI的本体。双击Dock上的插件本体，就可以显示弹窗。
  * 弹窗可以提供更详尽的信息和更高级的功能，还支持交互。
  */

#ifndef DDE_BASICDOCKPOPUP_H
#define DDE_BASICDOCKPOPUP_H

#include <QWidget>
#include <QSettings>

class DDE_BasicDockPopup : public QWidget
{
    Q_OBJECT
public:
    explicit DDE_BasicDockPopup(QWidget *parent = nullptr);

signals:

public slots:
    //void updateSystemInfo();

private:
    // 操作设置
    QSettings m_settings;
};

#endif // DDE_BASICDOCKPOPUP_H
