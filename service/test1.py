import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QMessageBox, QTextEdit, QListWidget, QDesktopWidget, QTreeWidget, QTreeWidgetItem
from PyQt5.QtGui import QCloseEvent
from PyQt5 import QtCore


class Widget(QWidget):
    myedit: QTextEdit = None
    def __init__(self):
        '''初始化'''
        super().__init__()
        self.initUI()
    def initUI(self):
        '''初始化UI'''
        self.setWindowTitle('hi')
        self.setGeometry(200, 200, 300, 300)
        self.myedit = QTextEdit('', self)
        self.myedit.setGeometry(0,0,200,200)
        return None
    def closeEvent(self, event):
        reply = QMessageBox.question(self, 'mseeage', 'are you sure', QMessageBox.No|QMessageBox.Yes, QMessageBox.No)
        #if reply == QMessageBox.No:
        if reply == QMessageBox.No:
            event.ignore()
        else:
            event.accept()
        

class Test(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('test')
        self.resize(600, 300)
        qr = self.frameGeometry()
        cp = QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())
        list1 = QListWidget(self)
        list1.addItems(['111', '222', '333'])
        list1.doubleClicked[QtCore.QModelIndex].connect(self.doubleClicked1)
        list1.setGeometry(10, 10, 200, 200)


    
    def doubleClicked1(self, index: QtCore.QModelIndex):
        print(index.data())
        return

def main():
    app = QApplication(sys.argv)
    w = Test()
    w.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()