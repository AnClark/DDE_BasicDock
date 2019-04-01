/**
  * dde_basicdockpopup.h
  *
  * 插件弹出窗口UI的本体。双击Dock上的插件本体，就可以显示弹窗。
  * 弹窗可以提供更详尽的信息和更高级的功能，还支持交互。
  */

#ifndef DDE_BASICDOCKPOPUP_H
#define DDE_BASICDOCKPOPUP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTime>                // 时间日期类，用于获取当前时间日期
#include <QSettings>

class DDE_BasicDockPopup : public QWidget
{
    Q_OBJECT

public:
    explicit DDE_BasicDockPopup(QWidget *parent = nullptr);

private:
    QSettings m_settings;       // 设置模块
    QGridLayout *layout;        // 弹出窗口的布局
    QLabel *lblTitle, *lblIcon, *lblText, *lblDateTime;     // 弹出窗口中的标签

    QDate qDate;                                        // 日期类的实例
    QTime qTime;                                        // 时间类的实例

/* 使用槽函数来实现插件更新 */
public slots:
    void updatePopupUI();
};

#endif // DDE_BASICDOCKPOPUP_H
