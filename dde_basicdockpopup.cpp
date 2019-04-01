#include "dde_basicdockpopup.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

DDE_BasicDockPopup::DDE_BasicDockPopup(QWidget *parent)
    : QWidget(parent),
      m_settings("deepin", "DDEBasicDock")      // 初始化本插件的设置存储
{
    setFixedWidth(300);
    QGridLayout *layout = new QGridLayout;

    QLabel *lblTitle = new QLabel;
    lblTitle->setText("简单的DDE Dock插件");
    lblTitle->setStyleSheet("color: white; font-size: 20px; padding-bottom: 10px; ");      // Qt支持的CSS仅为一个子集。注意字体设置单位不能用em、rem等。
    lblTitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblTitle, 0, 0, 1, 2);    // 五个参数依次为：部件对象、行、列、行扩展、列扩展。后两者用于合并单元格

    QLabel *lblIcon = new QLabel;
    lblIcon->setPixmap(QPixmap(":/icons/popicon.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    lblIcon->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblIcon, 1, 0);

    QLabel *lblText = new QLabel;
    lblText->setText("开发插件就是爽！\nDDE Dock，给你无限拓展可能！");
    lblText->setStyleSheet("color: white; ");
    lblText->setAlignment(Qt::AlignLeft);
    layout->addWidget(lblText, 1, 1);

    setLayout(layout);
}

