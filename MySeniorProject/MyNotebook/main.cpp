/*
  QT创建MainWindow与Widget项目的主要区别是它们的用途和功能范围
  1.MainWindow：是一个包含完整菜单栏、工具栏、状态栏的主窗口应用程序框架，适合于更复杂的应用程序，需要这些额外的用户界面元素来提供丰富的功能和交互
  2.Widget：是一个简单的接口，没有内置的菜单栏、工具栏、状态栏，更适合于简单、专用的应用程序，不需要复杂的用户界面组件
*/
/*
  QT帮助手册：位于 开始菜单->Qt->Assistant
*/

#include "mynotebook.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    //QApplication app(argc, argv)：作用是创建一个QApplication类实例，负责管理应用程序的核心功能
    //1.事件循环：接受和分发各种事件，如鼠标点击、键盘输入等
    //2.全局设置：包括字体、颜色，以及其他用户界面元素
    //3.GUI初始化：没有创建QApplication的情况下，无法使用QT的任何GUI组件
    //4.命令行参数处理：对于需要命令行来进行交互的程序是必要的
    QApplication app(argc, argv);
    MyNotebook window;
    window.show();
    //QApplication::exec()：用来启动程序的事件循环；调用该参数时会处理和分发事件；且一直保持运行直到事件循环结束（通常是因为调用了QApplication::quit()或关闭了应用程序主窗口）
    return app.exec();
}
