/**
  * dde_basicdockplugin.h
  *
  * 深度DDE Dock插件接口的实现。在这里继承Dock插件的基类，并实现其中的方法。
  * 通过实现相应的方法，我们可以加载插件的本体，并增加诸如上下文菜单、悬停提示等
  * 高级的特性。
  *
  * 每个Dock插件都必须继承PluginsItemInterface类，并实现其中的接口，
  * 否则DDE将无法识别。
  *
  * 需要引入的头文件：dde-dock/pluginsiteminterface.h。
  * 文件中包含了API的介绍，可以参考。
  * 安装dde-dock-dev包后，就可以直接在Qt中使用该文件，无需再进行其他设置。
  */

#ifndef DDE_BASICDOCKPLUGIN_H
#define DDE_BASICDOCKPLUGIN_H

#include "dde-dock/pluginsiteminterface.h"      // DDE Dock的头文件

// 引入插件UI本体的头文件。一般把Dock接口与插件本体分开，各成一个class。
#include "dde_basicdock.h"          // 插件本体的头文件
#include "dde_basicdockpopup.h"     // 插件弹出窗口的头文件

#include <QLabel>
#include <QTimer>                   // 使用计时器对插件UI进行动态更新
#include <qrandom.h>                // 用于生成随机数

class DDE_BasicDockPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "basicDock.json")

public:
    explicit DDE_BasicDockPlugin(QObject *parent = 0);      // 构造函数，用于初始化插件

    const QString pluginName() const override;              // 插件名称，DDE以此为管理插件的依据
    const QString pluginDisplayName() const override;       // 插件的显示名称
    void init(PluginProxyInterface *proxyInter) override;   // 初始化插件的方法

    void pluginStateSwitched() override;                        // 事件：插件状态改变
    bool pluginIsAllowDisable() override { return true; }       // 返回插件是否允许被关闭，一般会允许
    bool pluginIsDisable() override;                            // 返回插件是否被禁用

    int itemSortKey(const QString &itemKey);
    void setSortKey(const QString &itemKey, const int order);

    // 以下三个方法将把相应的UI提供给dde-dock以便显示
    QWidget *itemWidget(const QString &itemKey) override;       // 插件UI的本体
    QWidget *itemTipsWidget(const QString &itemKey) override;   // 插件悬停提示UI的本体
    QWidget *itemPopupApplet(const QString &itemKey) override;  // 插件弹出窗口UI的本体

    const QString itemCommand(const QString &itemKey) override; // 点击插件执行的Shell命令，一般不需要，返回空字符串即可
    const QString itemContextMenu(const QString &itemKey) override;     // 定义插件的上下文菜单（即右键菜单）

    void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;   // 定义点击插件菜单项的事件，类似于Android部件的OnClick

private:
    QPointer<DDE_BasicDock> m_widgetMainUI;             // 指向插件本体的指针
    QPointer<QLabel> m_tipsLabel;                       // 指向悬停提示本体的指针
    QPointer<DDE_BasicDockPopup> m_widgetPopupUI;       // 指向弹出窗口本体的指针
    QSettings m_settings;                               // 设置模块。QSettings是Qt提供的应用程序设置管理模块
    QTimer *m_refreshTimer;                             // 用于刷新插件UI的计时器

    QRandomGenerator *randomGen;                        // 随机数生成器，UI测试时使用

    // 上下文菜单点击后执行的动作。在本例中均为显示一个窗口（或对话框）
    void about();
    void helloWorld();

/* 使用槽函数来实现插件更新 */
private slots:
    void updateBasicDock();
};

#endif // DDE_BASICDOCKPLUGIN_H
