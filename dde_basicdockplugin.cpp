#include "dde_basicdockplugin.h"
#include "dde_basicdockpopup.h"

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>

DDE_BasicDockPlugin::DDE_BasicDockPlugin(QObject *parent)
    : QObject(parent),
      // 以下几行属于初始化类的成员，而非继承
      m_tipsLabel(new QLabel),                   // 初始化悬停提示标签
      m_settings("deepin", "DDEBasicDock"),      // 初始化设置模块
      m_refreshTimer(new QTimer(this)),          // 初始化计时器
      randomGen(new QRandomGenerator())          // 初始化随机数生成器
{
    /* 定义悬停提示标签的格式 */
    m_tipsLabel->setObjectName("basicdock");        // 对象名
    m_tipsLabel->setStyleSheet("color:white; padding:0px 3px;");    // 使用CSS设置外观

    /* 创建插件本体的新实例 */
    m_widgetMainUI = new DDE_BasicDock;

    /* 创建插件弹出窗口本体的新实例 */
    m_widgetPopupUI = new DDE_BasicDockPopup;

    /* 配置计时器 */
    m_refreshTimer->setInterval(1000);          // 确定UI的刷新间隔
    m_refreshTimer->start();                    // 使计时器生效

    /* 信号与槽的连接 */
    // 将计时器的计时信号与UI更新函数的槽连接起来，如此就能在计时器工作时自动更新UI了
    connect(m_refreshTimer, &QTimer::timeout, this, &DDE_BasicDockPlugin::updateBasicDock);
    // 插件本体请求更新的信号，与dde-dock的协议（proxy）连接。
    // 但实际上，没有此连接，插件UI也能照常更新。
    //connect(m_widgetMainUI, &DDE_BasicDock::requestUpdateGeometry, [this] { m_proxyInter->itemUpdate(this, pluginName()); });
}

/* 设置插件的名称 */
const QString DDE_BasicDockPlugin::pluginName() const
{
    return "BasicDock";
}

/* 设置插件的显示名称 */
const QString DDE_BasicDockPlugin::pluginDisplayName() const
{
    return tr("Basic Dock");
}

/* 初始化插件 */
void DDE_BasicDockPlugin::init(PluginProxyInterface *proxyInter)
{
    // 以下的代码把插件放入Dock托盘中
    m_proxyInter = proxyInter;
    if (m_widgetMainUI->enabled())
        m_proxyInter->itemAdded(this, pluginName());
}

/* 切换插件的加载状态 */
void DDE_BasicDockPlugin::pluginStateSwitched()
{
    m_widgetMainUI->setEnabled(!m_widgetMainUI->enabled());
    if (m_widgetMainUI->enabled())
        m_proxyInter->itemAdded(this, pluginName());
    else
        m_proxyInter->itemRemoved(this, pluginName());
}

/* 检测插件是否处于禁用状态 */
bool DDE_BasicDockPlugin::pluginIsDisable()
{
    return !m_widgetMainUI->enabled();
}

/* 获取插件排序位置 */
// 函数的返回值就是你期望将插件放置的位置序号。
int DDE_BasicDockPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);      // 我们使用的是保存在设置里的值，因此不需要itemKey提供的键名（？）

    const QString key = QString("pos_%1").arg(displayMode());
    return m_settings.value(key, 0).toInt();
}

/* 记录插件排序位置 */
// 将插件排序位置保存到设置中
void DDE_BasicDockPlugin::setSortKey(const QString &itemKey, const int order)
{
    Q_UNUSED(itemKey);

    const QString key = QString("pos_%1").arg(displayMode());
    m_settings.setValue(key, order);
}

/* 返回插件本体对象 */
QWidget *DDE_BasicDockPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return m_widgetMainUI;
}

/* 返回悬停提示本体对象 */
QWidget *DDE_BasicDockPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return m_tipsLabel;
}

/* 返回弹出窗口本体对象 */
QWidget *DDE_BasicDockPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return m_widgetPopupUI;
}

/* 指定插件点击运行的Shell命令，一般为空 */
const QString DDE_BasicDockPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return "";
}

/* 为插件添加上下文菜单 */
// ①菜单项：上下文菜单使用QList组织。QList中的每个菜单项都是一个QMap键值对
// 常用的键有：itemId→菜单项名称，itemText→菜单项显示名，isActive→是否可用。
// ②导出菜单：菜单项最终要导出，先由一个QMap进行封装。
// 封装QMap的键有：items→菜单项QList，checkableMenu→设置是否为复选菜单，
//               singleCheck→设置是否为单选菜单。
// 最终导出的结果是QJsonDocument。
const QString DDE_BasicDockPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    // 定义用于存储菜单项的QList
    QList<QVariant> items;
    items.reserve(1);

    // 第一个菜单项
    QMap<QString, QVariant> mnuAbout;
    mnuAbout["itemId"] = "about";
    mnuAbout["itemText"] = tr("关于");
    mnuAbout["isActive"] = true;
    items.push_back(mnuAbout);

    // 第二个菜单项
    QMap<QString, QVariant> mnuHelloWorld;
    mnuHelloWorld["itemId"] = "helloworld";
    mnuHelloWorld["itemText"] = "Hello World!";
    mnuHelloWorld["isActive"] = true;
    items.push_back(mnuHelloWorld);

    // 第三个菜单项
    QMap<QString, QVariant> mnuAboutQt;
    mnuAboutQt["itemId"] = "aboutqt";
    mnuAboutQt["itemText"] = "关于 Qt";
    mnuAboutQt["isActive"] = true;
    items.push_back(mnuAboutQt);

    // 将菜单项封装起来
    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    // 导出结果。结果为JSON格式。
    return QJsonDocument::fromVariant(menu).toJson();
}

/* 菜单项点击事件 */
void DDE_BasicDockPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey);
    Q_UNUSED(checked);

    // 根据menuId传入的值，确定是哪一个菜单项被点击
    // 注意：不能用switch，因为switch只支持整数。
    if(menuId == "about") {
        about();
    }
    else if(menuId == "helloworld") {
        helloWorld();
    }
    else if(menuId == "aboutqt") {
        qApp->aboutQt();
    }
}


/** 以下部分为你自己的代码 **/

/* 显示一个“关于”对话框 */
void DDE_BasicDockPlugin::about()
{
    QMessageBox aboutMB(QMessageBox::NoIcon, "Basic Dock Plugin",
                        "这是一个简单的深度DDE Dock插件开发示例！\n作者：AnClark Liu");
    aboutMB.setIconPixmap(QPixmap(":/icons/icon.png"));
    aboutMB.exec();
}

/* 显示一个 Hello World 对话框 */
void DDE_BasicDockPlugin::helloWorld()
{
    QMessageBox helloWorldMB(QMessageBox::Information, "Hello World!", "你好，Deepin DDE Dock！");
    helloWorldMB.exec();
}

/* 刷新插件UI */
// 本插件将示范：
// ①在插件本体上显示随机数
// ②在插件悬停提示中显示另外一个随机数
void DDE_BasicDockPlugin::updateBasicDock()
{
    m_widgetMainUI->text = QString::number(randomGen->generate());
    m_widgetMainUI->update();
    m_tipsLabel->setText("随机数使用高端的QRandomGenerator生成！\n当前随机数：" + QString::number(randomGen->generate()));
}
