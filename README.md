# DDE BasicDock

## 简介

深度桌面环境（DDE，Deepin Desktop Environment）Dock插件开发示例。本项目是我学习Qt与DDE Dock插件开发的练习，旨在实现一个最简单的Dock插件。

插件覆盖了深度Dock所提供的主要API，每一个API都有其独特的功能和效果。只要灵活实现它们，一个有趣的插件就能诞生。

## 基本特性

本插件实现了以下特性：

- 插件UI（即显示在Dock上的界面）
- 插件上下文菜单（即右键菜单）
- 插件悬停提示（鼠标悬停在插件UI上显示）
- 插件弹出窗口（点击插件UI显示）
- 自动保存插件所在位置（若不保存则每次都会重置到托盘区左边）

## 开发环境

- **Qt 5.x SDK**。可从这里下载：https://download.qt.io/archive/qt/ ，其中包含有若干个版本，推荐选择最新的版本（我用的是5.10.1）。

  下载时选择Linux对应的版本，这是一个后缀名为`*.run`的可执行文件，可在文件管理器中直接双击运行（若无权限，请先使用`chmod`修改）。

- **Qt Creator**。深度商店和Qt SDK都有提供，但商店的版本要稍微新一些，推荐使用商店的版本。

- **DDE Dock 开发包**。包含了开发Dock插件所需的各种头文件和库。使用以下命令安装：

  ```shell
  sudo apt install dde-dock-dev
  ```

## Credits

由[爱拼安小匠（AnClark）](https://github.com/AnClark)根据[海天鹰（黄颖）](https://github.com/sonichy/)编写的[CMDU插件](https://github.com/sonichy/CMDU_DDE_DOCK)整理出基本代码和文档。在此向海天鹰表示衷心的感谢！
